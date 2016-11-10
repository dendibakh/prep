#include <gtest/gtest.h>

namespace Iterative
{
int factorial(int n)
{
  int result = 1;
  while (n > 0)
    result *= n--;
  return result;
}
}

namespace Recursive
{
int factorial(int n)
{
  if (n <= 0)
    return 1;
  return n * factorial(n-1);
}
}

namespace TailRecursive
{
int fact(int n, int acc)
{
  if (n > 1)
    return fact(n-1, acc*n);
  return acc;
}

int factorial(int n)
{
  return fact(n, 1);
}
}

TEST(Factorial, iterative)
{
  using namespace Iterative;
  EXPECT_EQ(1, factorial(0));
  EXPECT_EQ(1, factorial(1));
  EXPECT_EQ(2, factorial(2));
  EXPECT_EQ(6, factorial(3));
}

TEST(Factorial, rescursive)
{
  using namespace Recursive;
  EXPECT_EQ(1, factorial(0));
  EXPECT_EQ(1, factorial(1));
  EXPECT_EQ(2, factorial(2));
  EXPECT_EQ(6, factorial(3));
}

TEST(Factorial, tail_rescursive)
{
  using namespace TailRecursive;
  EXPECT_EQ(1, factorial(0));
  EXPECT_EQ(1, factorial(1));
  EXPECT_EQ(2, factorial(2));
  EXPECT_EQ(6, factorial(3));
}

