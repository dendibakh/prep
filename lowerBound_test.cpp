#include <vector>
#include <gtest/gtest.h>
#include <iostream>
#include <stack>

int solution(std::vector<int>& A, int X) {
    int N = A.size();
    if (N == 0) {
        return -1;
    }
    int l = 0;
    int r = N - 1;
    while (l < r) {
        int m = (l + r) / 2;
        if (A[m] > X) {
            r = m - 1;
        } else if (A[m] == X){
            r = m;
        }
        else{
        	l = m + 1;
        }
    }
    if (A[l] == X) {
        return l;
    }
    return -1;
}

TEST(lowerBound, 1)
{
  //std::vector<int> arr = {0, 0, 0, 0, 1, 1, 2, 3, 4, 4, 5, 6, 7, 8, 8, 8, 9, 9, 9, 9, 10, 10};
  std::vector<int> arr = {1, 2, 5, 9, 9, 10, 11};
	EXPECT_EQ(2, solution(arr, 5));
}

TEST(lowerBound, 2)
{
  //std::vector<int> arr = {0, 0, 0, 0, 1, 1, 2, 3, 4, 4, 5, 6, 7, 8, 8, 8, 9, 9, 9, 9, 10, 10};
  std::vector<int> arr = {1, 2, 5, 9, 9};
	EXPECT_EQ(2, solution(arr, 5));
  }

TEST(lowerBound, 3)
{
  //std::vector<int> arr = {0, 0, 0, 0, 1, 1, 2, 3, 4, 4, 5, 6, 7, 8, 8, 8, 9, 9, 9, 9, 10, 10};
  std::vector<int> arr = {1, 2, 5, 9, 9, 10};
	EXPECT_EQ(2, solution(arr, 5));
  }

TEST(lowerBound, 4)
{
  std::vector<int> arr = {0, 0, 0, 0, 1, 1, 2, 3, 4, 4, 5, 6, 7, 8, 8, 8, 9, 9, 9, 9, 10, 10};
	EXPECT_EQ(0, solution(arr, 0));
	EXPECT_EQ(4, solution(arr, 1));
	EXPECT_EQ(6, solution(arr, 2));
	EXPECT_EQ(7, solution(arr, 3));
	EXPECT_EQ(10, solution(arr, 5));
	EXPECT_EQ(13, solution(arr, 8));
	EXPECT_EQ(20, solution(arr, 10));
  }
