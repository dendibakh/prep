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

int getLeftPartitionBorder(int* arr, int left, int right, int pivot)
{
  int leftBorder = right;
  while((arr[leftBorder] == pivot) && (leftBorder > left))
    leftBorder--;
      
  return leftBorder;
}

int getRightPartitionBorder(int* arr, int left, int right, int pivot)
{
  int rightBorder = left;
  while((arr[rightBorder] == pivot) && (rightBorder < right))
    rightBorder++;

  return rightBorder;
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

  // This is an optimization for repeated elements.
  // We divide array in three regions: low, equal and high.
  // And recurse only with low and high.
  // This optimization works against O(N^2) in case lots of duplicate elements
  j = getLeftPartitionBorder(arr, lo, j, pivot);
  quicksort(arr, lo, j);
  i = getRightPartitionBorder(arr, i, high, pivot);
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

TEST(leftPartitionBorder, 1)
{
  {
    int arr[] = {1, 1, 1, 1, 1, 5, 5, 5, 5, 6, 7};
    EXPECT_EQ(3, getLeftPartitionBorder(arr, 0, 3, 5));
    EXPECT_EQ(4, getLeftPartitionBorder(arr, 0, 5, 5));
    EXPECT_EQ(4, getLeftPartitionBorder(arr, 0, 7, 5));
    EXPECT_EQ(4, getLeftPartitionBorder(arr, 0, 8, 5));
    EXPECT_EQ(9, getLeftPartitionBorder(arr, 0, 9, 5));
  }
}

TEST(rightPartitionBorder, 1)
{
  {
    int arr[] = {1, 1, 1, 1, 1, 5, 5, 5, 5, 6, 7};
    EXPECT_EQ(0, getRightPartitionBorder(arr, 0, 10, 5));
    EXPECT_EQ(9, getRightPartitionBorder(arr, 5, 10, 5));
    EXPECT_EQ(9, getRightPartitionBorder(arr, 7, 10, 5));
    EXPECT_EQ(9, getRightPartitionBorder(arr, 8, 10, 5));
    EXPECT_EQ(9, getRightPartitionBorder(arr, 9, 10, 5));
  }
}

TEST(quicksort, 1)
{
  testCase({5, 3, 7, 1, 6, 9, 8});
  testCase({5, 3, 7, 1, 6, 10, 12, 7, 3, 2, 6, 4, 16, 9, 8});
  testCase({1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2});
}

