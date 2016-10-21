#include <array>
#include <vector>
#include <limits>
#include <gtest/gtest.h>

struct data
{
  unsigned int position;
  unsigned int count;
};

unsigned char firstUnique(const std::vector<unsigned char>& stream)
{
  std::array<data, std::numeric_limits<unsigned char>::max()> collection({0, 0});
  for (auto it = stream.begin(); it != stream.end(); ++it)
  {
    ++collection[*it].count;
    collection[*it].position = std::distance(stream.begin(), it);
  }

  unsigned char firstUnique = 0;
  unsigned int firstUniquePos = std::numeric_limits<int>::max();
  for (auto it = collection.begin(); it != collection.end(); ++it)
  {
    if (it->count == 1)
    {
      if (it->position < firstUniquePos)
      {
        firstUniquePos = it->position;
        firstUnique = std::distance(collection.begin(), it);
      }
    }
  }

  return firstUnique;
}

TEST(firstUnique, 1)
{
  std::vector<unsigned char> stream = {2, 5, 7, 10, 2, 10, 6, 4, 5};
  EXPECT_EQ(7, firstUnique(stream));
}

TEST(firstUnique, 2)
{
  std::vector<unsigned char> stream = {2, 5, 7, 10, 2, 10, 7, 7, 5};
  EXPECT_EQ(0, firstUnique(stream));
}

TEST(firstUnique, 3)
{
  std::vector<unsigned char> stream = {2};
  EXPECT_EQ(2, firstUnique(stream));
}

TEST(firstUnique, 4)
{
  std::vector<unsigned char> stream = {};
  EXPECT_EQ(0, firstUnique(stream));
}
