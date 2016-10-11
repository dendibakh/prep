#include <string>
#include <gtest/gtest.h>
#include <iostream>
#include <stack>

bool validBracketsInTheString(const std::string& str)
{
  std::stack<char> st;

  for (auto s : str)
  {
    if (s == '(')
      st.push(s);
    else
      if (s == ')' && st.top() == '(')
        st.pop();
  }

  return st.empty();
}

TEST(validBracketsInTheString, 1)
{
  EXPECT_TRUE(validBracketsInTheString("()"));
  EXPECT_TRUE(validBracketsInTheString("asd(sd)d(sad)dsf"));
  EXPECT_TRUE(validBracketsInTheString("asd(sd)d(s((a))d)dsf"));
  EXPECT_FALSE(validBracketsInTheString("asd(sd)d(s((a())d)dsf"));
}
