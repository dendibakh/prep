#include <gtest/gtest.h>
#include <vector>

using Iter = std::vector<int>::iterator;

void rotate(Iter first, Iter nextFirst, Iter last)
{
  Iter next = nextFirst;

  while (first != next)
  {
    std::swap(*first, *next);
    ++first;
    ++next;
    if (next == last)
      next = nextFirst;
    else if (first == nextFirst)
      nextFirst = next;
  }
}

TEST(rotate, 45123)
{
  std::vector<int> src = {1, 2, 3, 4,  5};
  rotate(src.begin(), src.begin() + 3, src.end());

  std::vector<int> expected = {4, 5, 1, 2, 3};

  EXPECT_TRUE(src == expected);
}

TEST(rotate, 34512)
{
  std::vector<int> src = {1, 2, 3, 4,  5};
  rotate(src.begin(), src.begin() + 2, src.end());

  std::vector<int> expected = {3, 4, 5, 1, 2};

  EXPECT_TRUE(src == expected);
}

TEST(rotate, 23451)
{
  std::vector<int> src = {1, 2, 3, 4,  5};
  rotate(src.begin(), src.begin() + 1, src.end());

  std::vector<int> expected = {2, 3, 4, 5, 1};

  EXPECT_TRUE(src == expected);
}

TEST(rotate, 51234)
{
  std::vector<int> src = {1, 2, 3, 4,  5};
  rotate(src.begin(), src.begin() + 4, src.end());

  std::vector<int> expected = {5, 1, 2, 3, 4};

  EXPECT_TRUE(src == expected);
}

TEST(rotate, 12345)
{
  std::vector<int> src = {1, 2, 3, 4, 5};
  rotate(src.begin(), src.begin(), src.end());

  std::vector<int> expected = {1, 2, 3, 4, 5};

  EXPECT_TRUE(src == expected);
}
