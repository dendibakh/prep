#include <algorithm>
#include <vector>
#include <gtest/gtest.h>
#include <iostream>

using namespace ::testing;

template <typename T>
class VectorTrackingAccesses : public std::vector<T>
{
public:
  //template <typename... Args>
  VectorTrackingAccesses(std::initializer_list<T> init) : std::vector<T>(init) {}
  decltype(auto) operator[](size_t index) const
  {
    accesses.push_back(index);
    return std::vector<int>::operator[](index);
  }
  std::string printAccesses()
  {
    std::string indecies;
    for (auto i : accesses)
      indecies += std::to_string(i) + ' ';
    return "Total accesses: " + std::to_string(accesses.size()) + ". Trace: " + indecies;
  }
  ~VectorTrackingAccesses()
  {
    std::cout << printAccesses() << '\n';
  }
private:
  mutable std::vector<size_t> accesses;
};

bool fast_lower_bound(const VectorTrackingAccesses<int>& arr, int val)
{
  if (arr.empty())
    return false;

  size_t next = val;
  size_t left = 0;
  size_t right = arr.size() - 1;

  size_t saveNext = next;

  while (left < right)
  {
    saveNext = next;
    auto cur = arr[next];

    if (cur == val)
      return true;

    auto diff = float(cur) / val;

    if (diff == 0)
    {
      left = next + 1;
      next *= 2;
    }
    else if (diff < 1 && diff > 0.5)
    {
      left = next + 1;
      next = std::round(float(next) / diff);
      next += next - saveNext;
    }
    else if (diff < 1)
    {
      left = next + 1;
      next = std::round(float(next) / diff);
    }
    else if (diff > 1 && diff < 1.5)
    {
      right = next - 1;
      next = std::round(left + (next - left) / diff);
      next -= saveNext - next;
    }
    else if (diff > 1)
    {
      right = next - 1;
      next = std::round(left + (next - left) / diff);
    }

    if (next == saveNext)
      throw std::runtime_error("stuck on the same place.");

    if (next > right)
      next = right;
      //throw std::runtime_error("getting out of bounds.");
  }
  return false;
}

auto lowerBound(const VectorTrackingAccesses<int>& arr, int value)
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
    if (arr[it - arr.begin()] < value)
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

bool lower_bound(const VectorTrackingAccesses<int>& arr, int val)
{
  auto iter = lowerBound(arr, val);
  return *iter == val;
}

TEST(binSearchImprove, index_find)
{
  VectorTrackingAccesses<int> arr1( {{ 0, 1, 2, 3, 4 ,5, 6, 7, 8, 9, 10 }});
  VectorTrackingAccesses<int> arr2( {{ 0, 1, 2, 3, 4 ,5, 6, 7, 8, 9, 10 }});
  EXPECT_TRUE(lower_bound(arr1, 4) == fast_lower_bound(arr2, 4));
}

TEST(binSearchImprove, dense_find)
{
  auto init = { 0, 0, 1, 1, 1 ,9, 9, 9, 10, 10, 10 };

  std::cout << "Input:" << '\n';
  for (auto i : init)
    std::cout << i << ", ";
  std::cout << '\n';
  VectorTrackingAccesses<int> arr1 = init;
  VectorTrackingAccesses<int> arr2 = init;
  EXPECT_TRUE(lower_bound(arr1, 4) == fast_lower_bound(arr2, 4));
}

TEST(binSearchImprove, dense_find2)
{
  auto init = { 0, 0, 1, 1, 1 ,9, 9, 9, 10, 10, 10 };

  std::cout << "Input:" << '\n';
  for (auto i : init)
    std::cout << i << ", ";
  std::cout << '\n';
  VectorTrackingAccesses<int> arr1 = init;
  VectorTrackingAccesses<int> arr2 = init;
  EXPECT_TRUE(lower_bound(arr1, 9) == fast_lower_bound(arr2, 9));
}

TEST(binSearchImprove, dense_find3)
{
  auto init = { 9, 9, 9, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10 };

  std::cout << "Input:" << '\n';
  for (auto i : init)
    std::cout << i << ", ";
  std::cout << '\n';
  VectorTrackingAccesses<int> arr1 = init;
  VectorTrackingAccesses<int> arr2 = init;
  EXPECT_TRUE(lower_bound(arr1, 9) == fast_lower_bound(arr2, 9));
}

