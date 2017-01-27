#include <gtest/gtest.h>
#include <utility>
#include <iostream>
#include <vector>
#include <algorithm>

// Practical improvements:
// 1. Use insertion sort for small subarrays. Cut off at some point.
// 2. Do not merge arrays if they are already sorted.
// 3. Eliminate copying by returning aux array.

namespace mergesort
{
void merge(int* arr, int* aux, int lo, int mid, int high)
{
  for (int k = lo; k <= high; ++k)
    aux[k] = arr[k];

  int i = lo;      // the index of first partition
  int j = mid + 1; // the index of second partition

  for (int k = lo; k <= high; ++k)
  {
    if (i > mid) // no more element of the first partition
    {
      arr[k] = aux[j];
      ++j;
    }
    else if (j > high) // no more elements of the second partition
    {
      arr[k] = aux[i];
      ++i;
    }
    else if (aux[j] < aux[i]) // actually sorting
    {
      arr[k] = aux[j];
      ++j;
    }
    else // if (aux[i] <= aux[j]) notice that this provides stability!
    {
      arr[k] = aux[i];
      ++i;
    }
  }
}

void mergesort(int* arr, int* aux, int lo, int high)
{
  if (lo >= high)
    return;

  int mid = lo + (high - lo) / 2;
  mergesort(arr, aux, lo, mid);
  mergesort(arr, aux, mid + 1, high);

  // 2. Do not merge arrays if they are already sorted.
  if (arr[mid] <= arr[mid + 1])
    return;

  merge(arr, aux, lo, mid, high);
}

void mergesort(int* arr, int size)
{
  int* aux = new int[size];
  mergesort(arr, aux, 0, size - 1);
  delete [] aux;
}

void testCase(const std::vector<int>& arr)
{
  std::vector<int> actual(arr);
  std::vector<int> expected(arr);
  mergesort(actual.data(), actual.size());
  std::sort(expected.begin(), expected.end());
  EXPECT_TRUE(actual == expected);
}

TEST(mergesort, 1)
{
  testCase({5, 3, 7, 1, 6, 9, 8});
  testCase({5, 3, 7, 1, 6, 10, 12, 7, 3, 2, 6, 4, 16, 9, 8});
  testCase({1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2});
  testCase({15, 78, 8, 7, 99, 45, 26, 67, 19, 31, 44, 65, 82, 73 });
}

}
