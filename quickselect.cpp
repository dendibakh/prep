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

int quickselect(int* arr, int lo, int high, int k)
{
  if (lo >= high)
    return arr[k];

  int pivot = medianOfThree(arr, lo, high);

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

  /*
  std::cout << "pivot = " << pivot << '\n'; 
  std::cout << "i = " << i << '\n';
  std::cout << "j = " << j << '\n';

  for (int y = lo; y <= high; ++y)
    std::cout << arr[y] << ' ';
  std::cout << '\n';
  */

  //if (k == j)
  //  return arr[k];
  if (k <= j)
    return quickselect(arr, lo, j, k);
  else
    return quickselect(arr, i, high, k);
}

int quickselect(int* arr, int size, int k)
{
  if (k < 0 || k >= size)
    return 0;
  return quickselect(arr, 0, size - 1, k);
}

void testCase(const std::vector<int>& arr, int k)
{
  std::vector<int> actual(arr);
  std::vector<int> expected(arr);
  int result = quickselect(actual.data(), actual.size(), k);
  std::nth_element(expected.begin(), expected.begin() + k, expected.end());
  EXPECT_EQ(*(expected.begin() + k), result);
}

void testAllK(const std::vector<int>& arr)
{
  auto size = arr.size();
  for (int i = 0; i < size; ++i)
    testCase(arr, i);
}

TEST(quickselect, 1)
{
  testCase({5, 3, 7, 1, 6, 9, 8}, 1);  
  testAllK({5, 3, 7, 1, 6, 9, 8});
  testAllK({5, 3, 7, 1, 6, 10, 12, 7, 3, 2, 6, 4, 16, 9, 8});
  testCase({5, 3, 7, 1, 6, 10, 12, 7, 3, 2, 6, 4, 16, 9, 8}, 4);
  testAllK({1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2});
}
