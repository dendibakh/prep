#include <algorithm>
#include <vector>
#include <gtest/gtest.h>

using namespace ::testing;

bool fast_lower_bound(const std::vector<int>& arr, int val)
{
  if (arr.empty())
    return false;

  size_t next = 0;
  size_t left = 0;
  while (true)
  {
    auto cur = arr[next];

    if (cur == val)
      return true;

    auto diff = float(cur) / val;

    if (diff == 0)
    {
      next = val;
    }
    else if (diff < 1)
    {
      next = left + next / diff;
      if (next >= arr.size())
        next = arr.size() - 1;
    }
    else
    {
      left = next;
      next = next / diff;
      if (next >= arr.size())
        next = arr.size() - 1;
      
    }
  }

  return arr[val] == val;
}

bool lower_bound(const std::vector<int>& arr, int val)
{
  return std::lower_bound(arr.begin(), arr.end(), val) != arr.end();
}

TEST(binSearchImprove, index_find)
{
  std::vector<int> arr = { 0, 1, 2, 3, 4 ,5, 6, 7, 8, 9, 10 };
  EXPECT_TRUE(lower_bound(arr, 4) == fast_lower_bound(arr, 4));
}

TEST(binSearchImprove, dense_find)
{
  std::vector<int> arr = { 0, 0, 1, 1, 1 ,9, 9, 9, 10, 10, 10 };
  EXPECT_TRUE(lower_bound(arr, 4) == fast_lower_bound(arr, 4));
}


