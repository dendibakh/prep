#include "gtest/gtest.h"
#include "unordered_map"

TEST(HashTest, 1)
{
    std::unordered_map<size_t, int> m;

    EXPECT_EQ(11, m.bucket_count());
/*    
    EXPECT_EQ(768614336404564650, m.max_bucket_count());
    EXPECT_EQ(0xAAAAAAAAAAAAAAA, m.max_bucket_count());
    EXPECT_EQ(0, m.bucket_size(0));
    EXPECT_EQ(0, m.bucket_size(1));
    //EXPECT_EQ(0, m.bucket_size(2)); segfault
    EXPECT_EQ(0, m.bucket(0));
    EXPECT_EQ(0, m.bucket(1));
    EXPECT_EQ(0, m.bucket(2));
    

    m[1] = 1;
    EXPECT_EQ(2, m.bucket_count());
    EXPECT_EQ(0xAAAAAAAAAAAAAAA, m.max_bucket_count());
    EXPECT_EQ(0, m.bucket_size(0));
	EXPECT_EQ(1, m.bucket_size(1));
	EXPECT_EQ(0, m.bucket(0));
	EXPECT_EQ(1, m.bucket(1));
	EXPECT_EQ(0, m.bucket(2));
	m[0xFFFFFFFF] = 7;
        EXPECT_EQ(5, m.bucket_count());
	EXPECT_TRUE(m.bucket(0xFFFFFFFF) != m.bucket(1));
	EXPECT_EQ(1, m.bucket(1));
	EXPECT_EQ(0, m.bucket(0xFFFFFFFF));

	m[0] = 8;
	EXPECT_EQ(5, m.bucket_count());
	EXPECT_TRUE(m.bucket(0xFFFFFFFF) != m.bucket(1));
	EXPECT_TRUE(m.bucket(0xFFFFFFFF) == m.bucket(0));
	EXPECT_EQ(0, m.bucket(0xFFFFFFFF));
	EXPECT_EQ(0, m.bucket(0));
        */
}

TEST(HashTest, 2)
{
  std::unordered_map<size_t, int> x;
  EXPECT_EQ(11, x.bucket_count());
}

TEST(HashTest, 3)
{
  std::unordered_map<size_t, int> m;
  m[1] = 1;
  EXPECT_EQ(11, m.bucket_count());
}

TEST(HashTest, 4)
{
  std::unordered_map<size_t, int> m;
  m[1] = 1;
  m[0xFFFFFFFF] = 1;
  EXPECT_EQ(11, m.bucket_count());
}

TEST(HashTest, 5)
{
  std::unordered_map<size_t, int> m;
  m[1] = 1;
  m[0xFFFFFFFF] = 2;
  m[0x40000000] = 3;
  m[0x80000000] = 4;
  m[0xC0000000] = 5;
  m[0x12345678] = 6;
  m[0xABCDEF12] = 7;
  m[0x3456789A] = 8;
  m[0x56789ABC] = 9;
  m[0x23456789] = 10;
  EXPECT_EQ(1.0, m.max_load_factor());
  EXPECT_EQ(11, m.bucket_count());
}

TEST(HashTest, 6)
{
  std::unordered_map<size_t, int> m;
  m[1] = 1;
  m[0xFFFFFFFF] = 2;
  m[0x40000000] = 3;
  m[0x80000000] = 4;
  m[0xC0000000] = 5;
  m[0x12345678] = 6;
  m[0xABCDEF12] = 7;
  m[0x3456789A] = 8;
  m[0x56789ABC] = 9;
  m[0x23456789] = 10;
  EXPECT_EQ(1.0, m.max_load_factor());
  m[0x456789AB] = 11;
  EXPECT_EQ(1.0, m.max_load_factor());
  EXPECT_EQ(23, m.bucket_count());
  m[0x6789ABCD] = 12;
  m[0x789ABCDE] = 13;
  EXPECT_EQ(23, m.bucket_count());
}

TEST(HashTest, 10)
{
	std::unordered_map<size_t, int> m;
	for (size_t i = 0; i < 0x0000FFFF; ++i)
	{
		if (i != m.hash_function()(i))
			FAIL() << i;
	}

	for (size_t i = 0; i < 0x0000FFFF; ++i)
	{
		m[i] = i;
	}
	EXPECT_EQ(126271, m.bucket_count());

	EXPECT_EQ(1.0, m.max_load_factor());

        EXPECT_FLOAT_EQ(0.519003, m.load_factor());
}
