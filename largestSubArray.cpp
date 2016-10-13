#include <vector>
#include <gtest/gtest.h>
#include <iostream>
#include <limits>

std::pair<size_t, size_t> largestSubArray(const std::vector<int> arr)
{
  size_t len = arr.size();
  int maxSumSoFar = std::numeric_limits<int>::min();
  int curSum = 0;
  int s = 0;
  size_t left = 0;
  size_t right = 0;
  for(size_t i = 0; i < len; ++i ) 
  {
    curSum += arr[i];
    if ( curSum > maxSumSoFar ) 
    {
      maxSumSoFar = curSum;
      left = s;
      right = i;
    }
    if ( curSum < 0 ) 
    {
      curSum = 0;
      s = i + 1;
    }
  }
  return {left, right};
}

TEST(largestSubArray, empty)
{
  std::vector<int> arr = {};
  auto actual = largestSubArray(arr);
  EXPECT_TRUE(actual == std::make_pair(0lu, 0lu));
}

TEST(largestSubArray, simple)
{
  std::vector<int> arr = {0, 1, 2};
  EXPECT_TRUE(largestSubArray(arr) == std::make_pair(0lu, 2lu));
}

TEST(largestSubArray, with_negative_numbers)
{
  std::vector<int> arr = {0, 1, -2, 2, -3};
  EXPECT_TRUE(largestSubArray(arr) == std::make_pair(3lu, 3lu));
}
