#include <vector>
#include <gtest/gtest.h>
#include <iostream>
#include <algorithm>

auto upperBound(const std::vector<int>& arr, int value)
{
  auto it = arr.begin();

  int leftElems = static_cast<int>(arr.size());
  int step = 0;
  while (leftElems > 0)
  {
    step = leftElems / 2;
    if (*(it + step) > value)
    {
      leftElems = step;
    }
    else
    {
      leftElems -= step + 1;
      it = it + step + 1;
    }
  }

  return it;
}

TEST(upperBound, 1)
{
  std::vector<int> arr = {0, 0, 0, 0, 1, 1, 2, 3, 4, 4, 5, 6, 7, 8, 8, 8, 9, 9, 9, 9, 10, 10};
  { 
    auto iter = upperBound(arr, 1); 
    EXPECT_EQ(1, *(iter-2));
    EXPECT_EQ(1, *(iter-1));
    EXPECT_EQ(2, *iter);
    EXPECT_EQ(3, *(iter+1));
    EXPECT_EQ(4, *(iter+2));
  }
  { 
    auto iter = upperBound(arr, 2); 
    EXPECT_EQ(1, *(iter-2));
    EXPECT_EQ(2, *(iter-1));
    EXPECT_EQ(3, *iter);
    EXPECT_EQ(4, *(iter+1));
    EXPECT_EQ(4, *(iter+2));
  }
  { 
    auto iter = upperBound(arr, 8); 
    EXPECT_EQ(8, *(iter-2));
    EXPECT_EQ(8, *(iter-1));
    EXPECT_EQ(9, *iter);
    EXPECT_EQ(9, *(iter+1));
    EXPECT_EQ(9, *(iter+2));
  }
  { 
    auto iter = std::upper_bound(arr.begin(), arr.end(), 8); 
    EXPECT_EQ(8, *(iter-2));
    EXPECT_EQ(8, *(iter-1));
    EXPECT_EQ(9, *iter);
    EXPECT_EQ(9, *(iter+1));
    EXPECT_EQ(9, *(iter+2));
  }
  { 
    auto iter = upperBound(arr, 0); 
    EXPECT_EQ(1, *iter);
    EXPECT_EQ(1, *(iter+1));
    EXPECT_EQ(2, *(iter+2));
    EXPECT_EQ(3, *(iter+3));
    EXPECT_EQ(4, *(iter+4));
  }
  { 
    auto iter = std::upper_bound(arr.begin(), arr.end(), 0); 
    EXPECT_EQ(1, *iter);
    EXPECT_EQ(1, *(iter+1));
    EXPECT_EQ(2, *(iter+2));
    EXPECT_EQ(3, *(iter+3));
    EXPECT_EQ(4, *(iter+4));
  }
}
