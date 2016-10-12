#include <vector>
#include <gtest/gtest.h>
#include <iostream>
#include <stack>

auto lowerBound(const std::vector<int>& arr, int value)
{
  int count = static_cast<int>(arr.size());
  int step = 0;
  auto retIter = arr.begin();
  auto it = retIter;

  while (count > 0)
  {
    it = retIter;
    step = count / 2;
    it = it + step;
    if (*it < value)
    {
      retIter = ++it;
      count -= step + 1;
    }
    else
    {
      count = step;
    }
  }  
  return retIter;
}

TEST(lowerBound, 1)
{
  std::vector<int> arr = {0, 0, 0, 0, 1, 1, 2, 3, 4, 4, 5, 6, 7, 8, 8, 8, 9, 9, 9, 9, 10, 10};
  { 
    auto iter = lowerBound(arr, 1); 
    EXPECT_EQ(0, *(iter-2));
    EXPECT_EQ(0, *(iter-1));
    EXPECT_EQ(1, *iter);
    EXPECT_EQ(1, *(iter+1));
    EXPECT_EQ(2, *(iter+2));
  }
  { 
    auto iter = lowerBound(arr, 2); 
    EXPECT_EQ(1, *(iter-2));
    EXPECT_EQ(1, *(iter-1));
    EXPECT_EQ(2, *iter);
    EXPECT_EQ(3, *(iter+1));
    EXPECT_EQ(4, *(iter+2));
  }
  { 
    auto iter = lowerBound(arr, 8); 
    EXPECT_EQ(6, *(iter-2));
    EXPECT_EQ(7, *(iter-1));
    EXPECT_EQ(8, *iter);
    EXPECT_EQ(8, *(iter+1));
    EXPECT_EQ(8, *(iter+2));
  }
  { 
    auto iter = std::lower_bound(arr.begin(), arr.end(), 8); 
    EXPECT_EQ(6, *(iter-2));
    EXPECT_EQ(7, *(iter-1));
    EXPECT_EQ(8, *iter);
    EXPECT_EQ(8, *(iter+1));
    EXPECT_EQ(8, *(iter+2));
  }
  { 
    auto iter = lowerBound(arr, 0); 
    EXPECT_EQ(0, *iter);
    EXPECT_EQ(0, *(iter+1));
    EXPECT_EQ(0, *(iter+2));
    EXPECT_EQ(0, *(iter+3));
    EXPECT_EQ(1, *(iter+4));
  }
  { 
    auto iter = std::lower_bound(arr.begin(), arr.end(), 0); 
    EXPECT_EQ(0, *iter);
    EXPECT_EQ(0, *(iter+1));
    EXPECT_EQ(0, *(iter+2));
    EXPECT_EQ(0, *(iter+3));
    EXPECT_EQ(1, *(iter+4));
  }
}
