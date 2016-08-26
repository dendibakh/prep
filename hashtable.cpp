#include <vector>
#include <string>
#include <gtest/gtest.h>
#include <list>

// hashtable of <int, string>
// hash is modulo M

const int M = 50;

int hashModuloM(int key)
{
  return (key & 0x7FFFFFFF) % M;
}

class hashTable
{
public:
  hashTable()
  {
    hashTab.resize(M);
  }
  ~hashTable() {}
  hashTable(const hashTable& rhs) = delete;
  hashTable& operator=(const hashTable& rhs) = delete;

  void insert(int key, const std::string& value)
  {
    int index = hashModuloM(key);
    for (auto& elem : hashTab[index])
      if (elem.first == key)
      {
        elem.second = value;
        return;
      }
    hashTab[index].push_back(std::make_pair(key, value));
  }

  std::string find(int key)
  {
    int index = hashModuloM(key);
    for (auto& elem : hashTab[index])
      if (elem.first == key)
        return elem.second;
    return "";
  }

  bool remove(int key)
  {
    int index = hashModuloM(key);
    auto& list = hashTab[index];
    for (auto iter = list.begin(); iter != list.end(); ++iter)
    {
      if (iter->first == key)
      {
        list.erase(iter);
        return true;
      }
    }
    return false;
  }

private:
  std::vector < std::list < std::pair <int, std::string> > > hashTab;
};

TEST(hashTable, 1)
{
  hashTable ht;
  ht.insert(1, "abc");
  EXPECT_TRUE("abc" == ht.find(1));
}

TEST(hashTable, 2)
{
  hashTable ht;
  ht.insert(1, "abc");
  ht.insert(1, "def");
  EXPECT_TRUE("def" == ht.find(1));
}

TEST(hashTable, 3)
{
  hashTable ht;
  ht.insert(1, "abc");
  ht.insert(2, "dfe");
  EXPECT_TRUE("abc" == ht.find(1));
  EXPECT_TRUE("dfe" == ht.find(2));
}

TEST(hashTable, 4)
{
  hashTable ht;
  ht.insert(1, "abc");
  ht.insert(2, "dfe");
  EXPECT_TRUE("" == ht.find(3));
  EXPECT_TRUE("" == ht.find(0));
  EXPECT_TRUE("" == ht.find(M));
  EXPECT_TRUE("" == ht.find(M + 1));
}

TEST(hashTable, 5)
{
  hashTable ht;
  ht.insert(0, "abc");
  EXPECT_TRUE("abc" == ht.find(0));
  EXPECT_TRUE("" == ht.find(M));
}

TEST(hashTable, 6)
{
  hashTable ht;
  ht.insert(0, "abc");
  EXPECT_TRUE("abc" == ht.find(0));
  EXPECT_TRUE(ht.remove(0));
  EXPECT_TRUE("" == ht.find(0));
}

TEST(hashTable, 7)
{
  hashTable ht;
  ht.insert(0, "abc");
  ht.insert(2, "dfe");
  ht.insert(4, "gh");
  
  EXPECT_TRUE(ht.remove(0));
  EXPECT_TRUE("" == ht.find(0));

  EXPECT_FALSE(ht.remove(0));
  EXPECT_FALSE(ht.remove(1));
  EXPECT_FALSE(ht.remove(3));

  EXPECT_TRUE(ht.remove(4));

  EXPECT_TRUE("" == ht.find(4));
  EXPECT_TRUE("dfe" == ht.find(2));
}

