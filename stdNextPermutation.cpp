#include <gtest/gtest.h>
#include <vector>
#include <algorithm>
#include <iostream>

using Iter = std::vector<int>::iterator;

bool nextPermutation(Iter first, Iter last)
{
  if (first == last)
    return false;
  Iter i = last;
  if (first == --i)
    return false;

  while (true)
  {
    Iter i1 = i;
    if (*(--i) < *i1)
    {
      Iter i2 = last;
      while (*i >= *(--i2))
        ;
      std::swap(*i, *i2);
      std::reverse(i1, last);
      return true;
    }
    if (first == i)
    {
      std::reverse(first, last);
      return false;
    }
  }
}

TEST(next_permutation, 112)
{
  std::vector<int> src = {1, 1, 2};
  EXPECT_TRUE(nextPermutation(src.begin(), src.end()));
  //EXPECT_TRUE(std::next_permutation(src.begin(), src.end()));
  std::vector<int> expected = {1, 2, 1};

  //for (auto v : src)
  //  std::cout << v << ' ';
  EXPECT_TRUE(src == expected);
}

TEST(next_permutation, 121)
{
  std::vector<int> src = {1, 2, 1};
  EXPECT_TRUE(nextPermutation(src.begin(), src.end()));
  std::vector<int> expected = {2, 1, 1};
  EXPECT_TRUE(src == expected);
}

TEST(next_permutation, 211)
{
  std::vector<int> src = {2, 1, 1};
  EXPECT_FALSE(nextPermutation(src.begin(), src.end()));
  std::vector<int> expected = {1, 1, 2};
  EXPECT_TRUE(src == expected);
}

TEST(next_permutation, 123)
{
  std::vector<int> src = {1, 2, 3};
  {
    EXPECT_TRUE(nextPermutation(src.begin(), src.end()));
    std::vector<int> expected = {1, 3, 2};
    EXPECT_TRUE(src == expected);
  }
  {
    EXPECT_TRUE(nextPermutation(src.begin(), src.end()));
    std::vector<int> expected = {2, 1, 3};
    EXPECT_TRUE(src == expected);
  }
  {
    EXPECT_TRUE(nextPermutation(src.begin(), src.end()));
    std::vector<int> expected = {2, 3, 1};
    EXPECT_TRUE(src == expected);
  }
  {
    EXPECT_TRUE(nextPermutation(src.begin(), src.end()));
    std::vector<int> expected = {3, 1, 2};
    EXPECT_TRUE(src == expected);
  }
  {
    EXPECT_TRUE(nextPermutation(src.begin(), src.end()));
    std::vector<int> expected = {3, 2, 1};
    EXPECT_TRUE(src == expected);
  }
  {
    EXPECT_FALSE(nextPermutation(src.begin(), src.end()));
    std::vector<int> expected = {1, 2, 3};
    EXPECT_TRUE(src == expected);
  }
}

