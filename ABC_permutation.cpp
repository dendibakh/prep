#include <gtest/gtest.h>
#include <utility>
#include <iostream>
#include <string>
#include <algorithm>

namespace rotations
{
void permuteString(std::string str, int fixed)
{
  if (fixed < 0)
  {
    std::cout << str << std::endl;
    return;
  }
 
  permuteString(str, fixed - 1);
  int rotations = (str.size() - 1) - fixed;
  for (int i = 0; i < rotations; ++i)
  {
    std::rotate(str.begin() + fixed, str.end() - 1, str.end());
    permuteString(str, fixed - 1);
  }
}

void permuteString(const std::string& str)
{
  permuteString(str, str.size() - 2);
}
}

namespace backtracking
{
  /* Function to print permutations of string
   This function takes three parameters:
   1. String
   2. Starting index of the string
   3. Ending index of the string. */
void permuteString(std::string& str, int l, int r)
{
   if (l == r)
   {
     std::cout << str << std::endl;
   }
   else
   {
       for (int i = l; i <= r; i++)
       {
          std::swap(str[l], str[i]);
          permuteString(str, l+1, r);
          std::swap(str[l], str[i]); //backtrack
       }
   }
}

void permuteString(const std::string& str)
{
  permuteString(const_cast<std::string&>(str), 0, str.size() - 1);
}
}

TEST(ABC_permutation, 1)
{
  using namespace rotations;
  permuteString("abc");
}

TEST(ABC_permutation, 2)
{
  using namespace rotations;
  permuteString("abcd");
}

TEST(ABC_permutation, 3)
{
  using namespace rotations;
  permuteString("abcde");
}

TEST(ABC_permutation, 4)
{
  using namespace backtracking;
  permuteString("abc");
}

TEST(ABC_permutation, 5)
{
  using namespace backtracking;
  permuteString("abcd");
}

TEST(ABC_permutation, 6)
{
  using namespace backtracking;
  permuteString("abcde");
}

/*
TEST(ABC_permutation, 7)
{
  using namespace backtracking;
  permuteString("abcdefghj");
}

TEST(ABC_permutation, 8)
{
  using namespace rotations;
  permuteString("abcdefghj");
}
*/
