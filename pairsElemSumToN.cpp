#include <gtest/gtest.h>
#include <utility>
#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>

using Pair = std::pair<size_t, size_t>;

std::vector<Pair> pairsElemSumToN(const std::vector<int>& arr, int N)
{
  std::vector<Pair> retPairs;

  size_t size = arr.size();
  std::unordered_map<int, std::vector<size_t>> numbers;
  for (size_t i = 0; i < size; ++i)
  {
    auto iter = numbers.find(arr[i]);
    if (iter == numbers.end())
      numbers.insert({arr[i], {i}});
    else
      iter->second.push_back(i);
  }
  
  for (size_t i = 0; i < size; ++i)
  {
    int comp = N - arr[i];
    auto iter = numbers.find(comp);
    if (iter != numbers.end())
    {
      for (auto e : iter->second)
        if (i < e) // for discard duplicate pairs
          retPairs.push_back({i, e});
    }
  }

  return retPairs;
}

TEST(pairsElemsSumUpToN, 1)
{
  auto actual = pairsElemSumToN({1, 3, -2, 4, 5, -7, 0}, 3);
  std::vector<Pair> expected = {{1, 6}, {2, 4}};
  EXPECT_EQ(actual.size(), expected.size());
  EXPECT_TRUE(actual == expected);
}

TEST(pairsElemsSumUpToN, 2)
{
  auto actual = pairsElemSumToN({1, 3, -2, 4, 5, -7, 0, 5}, 3);
  std::vector<Pair> expected = {{1, 6}, {2, 4}, {2, 7}};
  EXPECT_EQ(actual.size(), expected.size());
  EXPECT_TRUE(actual == expected);
}

TEST(pairsElemsSumUpToN, 3)
{
  auto actual = pairsElemSumToN({1, 3, -2, 4, 5, -7, 0, 5, 10}, 3);
  std::vector<Pair> expected = {{1, 6}, {2, 4}, {2, 7}, {5, 8}};
  EXPECT_EQ(actual.size(), expected.size());
  EXPECT_TRUE(actual == expected);
}

TEST(pairsElemsSumUpToN, 4)
{
  auto actual = pairsElemSumToN({1, 3, -2, 4, 5, -7, 0, 5, 10, -1, 0, -1}, -2);
  std::vector<Pair> expected = {{2, 6}, {2, 10}, {4, 5}, {5, 7}, {9, 11}};
  EXPECT_EQ(actual.size(), expected.size());
  EXPECT_TRUE(actual == expected);
}

TEST(pairsElemsSumUpToN, 5)
{
  auto actual = pairsElemSumToN({1, 3, -2, 4, 5, -7, 0, 5, 10, -1, 0, -1, -1}, -2);
  std::vector<Pair> expected = {{2, 6}, {2, 10}, {4, 5}, {5, 7}, {9, 11}, {9, 12}, {11, 12}};
  EXPECT_EQ(actual.size(), expected.size());
  EXPECT_TRUE(actual == expected);
}

