#include <vector>
#include <gtest/gtest.h>
#include <iostream>
#include <limits>

std::pair<int, int> largestSubArray(const std::vector<int> arr)
{
  std::pair<int, int> larSubArr = {0, 0};
  int max = std::numeric_limits<int>::min();
  int total = 0;
  int front = 0;
  int back = 0;
  int N = arr.size();
  for (; back < N; ++back)
  {
    total += arr[front];
    while (front < N && max < total + :warr[front]) 
    {
      if (max < total)
      {
        max = total;
        larSubArr = {back, front};
      }
      ++front;
    }
  }
  return larSubArr;
}

TEST(largestSubArray, empty)
{
  std::vector<int> arr = {};
  EXPECT_TRUE(largestSubArray(arr) == {0, 0};
}

TEST(largestSubArray, simple)
{
  std::vector<int> arr = {0, 1, 2};
  EXPECT_TRUE(largestSubArray(arr) == {0, 2};
}

TEST(largestSubArray, with_negative_numbers)
{
  std::vector<int> arr = {0, 1, -2, 2, -3};
  EXPECT_TRUE(largestSubArray(arr) == {3, 3};
}
