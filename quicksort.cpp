#include <gtest/gtest.h>
#include <utility>
#include <iostream>
#include <vector>
#include <algorithm>

int medianOfThree(int* arr, int left, int right)
{
    int mid = left + (right - left)/2;
    if (arr[right] < arr[left])
        std::swap(arr[left], arr[right]);
    if (arr[mid] < arr[left])
        std::swap(arr[mid], arr[left]);
    if (arr[right] < arr[mid])
        std::swap(arr[right], arr[mid]);
    return arr[mid];
}

void quicksort(int* arr, int lo, int high)
{
  if (lo >= high)
    return;

  int pivot = medianOfThree(arr, lo, high);
  // int pivot = arr[lo + (high - lo) / 2]; using simply element in the middle
  // int pivot = arr[(high + lo) / 2]; this could cause an integer overflow

  int i = lo;
  int j = high;
  while (i <= j)
  {
    while (arr[i] < pivot)
      ++i;

    while (arr[j] > pivot)
      --j;

    if (i <= j)
    {
      std::swap(arr[i], arr[j]);
      i++;
      --j;
    }
  }
  //std::cout << "i = " << i << '\n';
  //std::cout << "j = " << j << '\n';
 
  //for (int k = lo; k <= high; ++k)
  //  std::cout << arr[k] << ' ';
  //std::cout << '\n';

  quicksort(arr, lo, j);
  quicksort(arr, i, high);
}

void quicksort(int* arr, int size)
{
  quicksort(arr, 0, size - 1);
}

void testCase(const std::vector<int>& arr)
{
  std::vector<int> actual(arr);
  std::vector<int> expected(arr);
  quicksort(actual.data(), actual.size());
  std::sort(expected.begin(), expected.end());
  EXPECT_TRUE(actual == expected);
}

TEST(medianOfThree, 1)
{
  {
    int arr[] = {5, 3, 7, 1, 6, 9, 8};
    EXPECT_EQ(5, medianOfThree(arr, 0, 6));
  }
  {
    int arr[] = {5, 3, 7, 1, 6, 9, 8};
    EXPECT_EQ(3, medianOfThree(arr, 0, 1));
  }
  {
    int arr[] = {5, 3, 7, 1, 6, 9, 8};
    EXPECT_EQ(6, medianOfThree(arr, 2, 4));
  }
}

TEST(quicksort, 1)
{
  testCase({5, 3, 7, 1, 6, 9, 8});
  testCase({5, 3, 7, 1, 6, 10, 12, 7, 3, 2, 6, 4, 16, 9, 8});
  testCase({1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2});
}

