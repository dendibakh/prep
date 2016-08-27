#include <vector>
#include <string>
#include <gtest/gtest.h>
#include <list>
#include <iostream>

// hashtable of <int, string>
// hash is modulo M

const int M = 50;

int hashModuloM(int key)
{
  return (key & 0x7FFFFFFF) % M;
}

namespace separateChaining 
{
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
}

namespace linearProbing
{
  class hashTable
  {
  public:
    static const int emptySlotKey{-1};
    static const int deletedSlotKey{-2};

    hashTable() : hashTab(M , std::make_pair(-1, ""))
    {
    }
    ~hashTable() {}
    hashTable(const hashTable& rhs) = delete;
    hashTable& operator=(const hashTable& rhs) = delete;


    void insert(int key, const std::string& value)
    {
      int index = hashModuloM(key);
      int saveIndex = index;
      while (true)
      {
        auto& elem = hashTab[index];
        if (elem.first == emptySlotKey || elem.first == key || elem.first == deletedSlotKey)
        {
          elem.first = key;
          elem.second = value;
          break;
        }
        if (index < M - 1)
        {
          index++;
          if (index == saveIndex)
            throw std::runtime_error("not enough space");
        }
        else
        {
          index = 0;
        }
      }
      return;
    }

    std::string find(int key)
    {
      int index = findIndex(key);
      if (index == emptySlotKey)
        return "";
      return hashTab[index].second;
    }

    bool remove(int key)
    {
      int index = findIndex(key);
      if (index == emptySlotKey)
        return false;
      hashTab[index].first = deletedSlotKey;
      return true;
    }

  private:
    int findIndex(int key)
    {
      int index = hashModuloM(key);
      int saveIndex = index;
      while (true)
      {
        //std::cout << "search: " << index << " \n";
        auto& elem = hashTab[index];
        if (elem.first == emptySlotKey)
          return emptySlotKey;
        else if (elem.first == key && elem.first != deletedSlotKey)
          return index;

        if (index < M - 1)
        {
          index++;
          if (index == saveIndex)
            return emptySlotKey;
        }
        else
        {
          index = 0;
        }
      }
      return emptySlotKey;
    }

  private:
    std::vector < std::pair <int, std::string> > hashTab;
  };
}

//using namespace separateChaining;
using namespace linearProbing;

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

TEST(hashTable, 8)
{
  hashTable ht;
  ht.insert(5, "a");
  ht.insert(55, "b");
  ht.insert(6, "c");
  ht.insert(105, "d");
  
  EXPECT_TRUE(ht.remove(55));
  EXPECT_TRUE("" == ht.find(55));

  EXPECT_TRUE("a" == ht.find(5));
  EXPECT_TRUE("c" == ht.find(6));
  EXPECT_TRUE("d" == ht.find(105));
}

TEST(hashTable, 9)
{
  hashTable ht;
  ht.insert(5, "a");
  ht.insert(55, "b");
  ht.insert(6, "c");
  ht.insert(105, "d");
  
  EXPECT_TRUE(ht.remove(55));
  EXPECT_TRUE("" == ht.find(55));

  EXPECT_TRUE("a" == ht.find(5));
  EXPECT_TRUE("c" == ht.find(6));
  EXPECT_TRUE("d" == ht.find(105));

  ht.insert(155, "e");
  
  EXPECT_TRUE("a" == ht.find(5));
  EXPECT_TRUE("e" == ht.find(155));
  EXPECT_TRUE("c" == ht.find(6));
  EXPECT_TRUE("d" == ht.find(105));
}

