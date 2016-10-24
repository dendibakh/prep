#include <gtest/gtest.h>
#include <unordered_map>
#include <string>
#include <chrono>
#include <thread>
#include <mutex>
#include <atomic>
#include <map>

class Cache
{
  struct data
  {
    unsigned int count; 
    // This algorithm with using counts can be improved with storing the last request time.
    // If the counts for some id are the same we will look at the last access time.
    std::string value;
  };

  using cacheCont = std::unordered_map<unsigned int, data>;

  struct cacheCleaner
  {
    void decrementCounts();
  public:
    cacheCleaner(Cache& cache);
    void operator()();
  private:
    Cache& cache;
  };
public:
  Cache(unsigned int elemsLimit, std::chrono::milliseconds period);
  ~Cache();
  std::string get(unsigned int id) const;
protected:  
  mutable cacheCont cache;
private:
  const unsigned int elemsLimit;
  const std::chrono::milliseconds period;
  cacheCleaner cleaner;
  std::thread cleanThread;
  mutable std::mutex m;
  std::atomic<bool> running {true};
  friend struct cacheCleaner;
};

Cache::cacheCleaner::cacheCleaner(Cache& cache) : cache(cache)
{
}

//#include <iostream>

void Cache::cacheCleaner::operator()()
{
  while (cache.running)
  {
    std::this_thread::sleep_for(cache.period);
    std::lock_guard<std::mutex> lock(cache.m);
    decrementCounts();
    if (cache.cache.size() > cache.elemsLimit)
    {
      unsigned int exceeding = cache.cache.size() - cache.elemsLimit;
      std::multimap<unsigned int, unsigned int> coldElems;
      for (auto it = cache.cache.begin(); it != cache.cache.end(); ++it)
      {
        coldElems.insert(std::make_pair(it->second.count, it->first));
        //std::cout << it->second.count << ' ' << it->first << '\n';
      }
      auto it = coldElems.begin();
      for (unsigned int i = 0; i < exceeding; ++i)
      {
        if (it != coldElems.end())
        {
          cache.cache.erase(it->second);
          //std::cout << it->second << '\n';
          ++it;
        }
      }
    }
  }
}

void Cache::cacheCleaner::decrementCounts()
{
  for (auto it = cache.cache.begin(); it != cache.cache.end(); ++it)
  {
    if (it->second.count > 0)
      --it->second.count;
    //if (0 == it->second.count)
    //  cache.cache.erase(it);
  }
}

Cache::Cache(unsigned int elemsLimit, std::chrono::milliseconds period) : elemsLimit(elemsLimit), period(period), cleaner(*this), cleanThread(cleaner)
{
}

Cache::~Cache()
{
  running = false;
  cleanThread.join();
}

namespace
{
  std::string getFromDatabase(unsigned int id)
  {
    std::stringstream stream;
    stream << id;
    return stream.str();
  }
}

std::string Cache::get(unsigned int id) const 
{
  std::lock_guard<std::mutex> lock(m);
  auto it = cache.find(id);
  if (it == cache.end())
  {
    auto retStr = getFromDatabase(id);
    cache.insert(std::pair<unsigned int, data>(id, {1, retStr}));
    return retStr;
  }
  else
  {
    ++it->second.count;
    return it->second.value;
  }
}

using namespace std::literals::chrono_literals;

namespace
{
  class FakeCache : public Cache
  {
    public:
      template <typename ...T>
      FakeCache(T&& ...args) : Cache(std::forward<T>(args)...) {}
      using Cache::cache;
  };
}

TEST(databaseCache, 1)
{
  FakeCache c(10, 2000ms);
  EXPECT_EQ(0, c.cache.size());
}

TEST(databaseCache, 2)
{
  FakeCache c(10, 2000ms);
  c.get(1);
  EXPECT_EQ(1, c.cache.size());
  EXPECT_TRUE(c.cache.find(1) != c.cache.end());
}

TEST(databaseCache, 3)
{
  FakeCache c(10, 2000ms);
  c.get(1);
  c.get(2);
  EXPECT_EQ(2, c.cache.size());
  EXPECT_TRUE(c.cache.find(1) != c.cache.end());
  EXPECT_TRUE(c.cache.find(2) != c.cache.end());
  EXPECT_FALSE(c.cache.find(0) != c.cache.end());
  EXPECT_FALSE(c.cache.find(3) != c.cache.end());
}

TEST(databaseCache, if_limit_exceeded_we_wont_resize_in_that_moment_but_after_period)
{
  FakeCache c(2, 200ms);
  c.get(1);
  c.get(2);
  c.get(1);
  c.get(3);
  EXPECT_EQ(3, c.cache.size());
  EXPECT_TRUE(c.cache.find(1) != c.cache.end());
  EXPECT_TRUE(c.cache.find(2) != c.cache.end());
  EXPECT_FALSE(c.cache.find(0) != c.cache.end());
  EXPECT_TRUE(c.cache.find(3) != c.cache.end());

  std::this_thread::sleep_for(250ms);

  // our cleaning loop will erase one element from the cache.

  EXPECT_EQ(2, c.cache.size());
  EXPECT_TRUE(c.cache.find(1) != c.cache.end());
  EXPECT_TRUE(c.cache.find(2) != c.cache.end() || c.cache.find(3) != c.cache.end());
  EXPECT_FALSE(c.cache.find(0) != c.cache.end());
}

TEST(databaseCache, exceeding_limit_two_times)
{
  FakeCache c(2, 200ms);
  c.get(1);
  c.get(2);
  c.get(1);
  c.get(3);
  EXPECT_EQ(3, c.cache.size());
  EXPECT_TRUE(c.cache.find(1) != c.cache.end());
  EXPECT_TRUE(c.cache.find(2) != c.cache.end());
  EXPECT_FALSE(c.cache.find(0) != c.cache.end());
  EXPECT_TRUE(c.cache.find(3) != c.cache.end());

  std::this_thread::sleep_for(250ms);

  // our cleaning loop will erase one element from the cache.

  EXPECT_EQ(2, c.cache.size());
  EXPECT_TRUE(c.cache.find(1) != c.cache.end());
  EXPECT_TRUE(c.cache.find(2) != c.cache.end() || c.cache.find(3) != c.cache.end());
  EXPECT_FALSE(c.cache.find(0) != c.cache.end());

  c.get(4);
  c.get(4);
  c.get(5);
  c.get(5);

  EXPECT_EQ(4, c.cache.size());
  EXPECT_TRUE(c.cache.find(1) != c.cache.end());
  EXPECT_EQ(1, c.cache.find(1)->second.count);
  EXPECT_TRUE(c.cache.find(4) != c.cache.end());
  EXPECT_EQ(2, c.cache.find(4)->second.count);
  EXPECT_TRUE(c.cache.find(5) != c.cache.end());
  EXPECT_EQ(2, c.cache.find(5)->second.count);

  std::this_thread::sleep_for(250ms);

  EXPECT_EQ(2, c.cache.size());
  EXPECT_FALSE(c.cache.find(1) != c.cache.end());
  EXPECT_TRUE(c.cache.find(4) != c.cache.end());
  EXPECT_TRUE(c.cache.find(5) != c.cache.end());
}
