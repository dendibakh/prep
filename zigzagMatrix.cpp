#include <vector>
#include <gtest/gtest.h>
#include <iostream>

using Matrix = std::vector<std::vector<int>>;

std::vector<int> zigzagTraversal(const Matrix& matrix)
{
  std::vector<int> traversal;

  if (matrix.empty())
    return traversal;

  size_t n = matrix[0].size();
  size_t m = matrix.size();

  for (size_t sum = 0; sum < m + n - 1; ++sum)
  {
    if (sum % 2 == 0)
    {
      for (int i = m - 1; i >= 0; --i)
        for (int j = n - 1; j >= 0; --j)
          if (i + j == sum)
            traversal.push_back(matrix[i][j]);
    }
    else
    {
      for (int i = 0; i < m; ++i)
        for (int j = 0; j < n; ++j)
          if (i + j == sum)
            traversal.push_back(matrix[i][j]);
    }
  }
  return traversal;
}

TEST(zigzag, square)
{
  std::vector<int> expected = {0, 1, 4, 8, 5, 2, 3, 6, 9, 12, 13, 10, 7, 11, 14, 15};
  auto actual = zigzagTraversal({ {0,  1,  2,  3},
                                  {4,  5,  6,  7},
                                  {8,  9,  10, 11},
                                  {12, 13, 14, 15}
                                });
  //for (auto& i : actual)
  //  std::cout << i << ' ';
  EXPECT_TRUE(expected == actual);
}

TEST(zigzag, rectangle)
{
  std::vector<int> expected = {0, 1, 4, 8, 5, 2, 3, 6, 9, 10, 7, 11};
  auto actual = zigzagTraversal({ {0,  1,  2,  3},
                                  {4,  5,  6,  7},
                                  {8,  9,  10, 11}
                                });
  //for (auto& i : actual)
  //  std::cout << i << ' ';
  EXPECT_TRUE(expected == actual);
}

TEST(zigzag, rectangle2)
{
  std::vector<int> expected = {0, 1, 3, 6, 4, 2, 5, 7, 9, 10, 8, 11};
  auto actual = zigzagTraversal({ {0,  1,  2},
                                  {3,  4,  5},
                                  {6,  7,  8},
                                  {9, 10, 11}
                                });
  //for (auto& i : actual)
  //  std::cout << i << ' ';
  EXPECT_TRUE(expected == actual);
}
