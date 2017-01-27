#include <gtest/gtest.h>
#include <vector>

bool find(const std::vector<int>& vect, int val)
{
  size_t size = vect.size();
  for (size_t i = 0; i < size; ++i)
  {
    if (val == vect[i])
      return true;
  }
  return false;
}

bool sentinel_find(std::vector<int>& vect, int val)
{
  vect.push_back(val);
  size_t i = 0;
  for (;;++i)
  {
    if (val == vect[i])
    {
      if (i == vect.size() - 1)
      {
        vect.pop_back();
        return false;
      }
      else
      {
        vect.pop_back();
        return true;
      }
    }
  }

  vect.pop_back();
  return false;
}

TEST(sentinels, find)
{
  std::vector<int> v = {1, 2, 3, 4, 5};
  EXPECT_TRUE(find(v, 1));
  EXPECT_TRUE(find(v, 2));
  EXPECT_TRUE(find(v, 3));
  EXPECT_TRUE(find(v, 4));
  EXPECT_TRUE(find(v, 5));
  EXPECT_FALSE(find(v, 0));
  EXPECT_FALSE(find(v, 6));
}

TEST(sentinels, sentinel_find)
{
  std::vector<int> v = {1, 2, 3, 4, 5};
  EXPECT_TRUE(sentinel_find(v, 1));
  EXPECT_TRUE(sentinel_find(v, 2));
  EXPECT_TRUE(sentinel_find(v, 3));
  EXPECT_TRUE(sentinel_find(v, 4));
  EXPECT_TRUE(sentinel_find(v, 5));
  EXPECT_FALSE(sentinel_find(v, 0));
  EXPECT_FALSE(sentinel_find(v, 6));
}

bool find_benchmark(int* arr, size_t size, int val)
{
  for (size_t i = 0; i < size; ++i)
  {
    if (val == arr[i])
      return true;
  }
  return false;
}

/*
Effective loop:
        mov     rax, QWORD PTR [rbp-8]
        cmp     rax, QWORD PTR [rbp-32]
        jnb     .L2
        mov     rax, QWORD PTR [rbp-8]
        lea     rdx, [0+rax*4]
        mov     rax, QWORD PTR [rbp-24]
        add     rax, rdx
        mov     eax, DWORD PTR [rax]
        cmp     eax, DWORD PTR [rbp-36]
        jne     .L3
*/

/*
TEST(sentinels, find_benchmark)
{
  int v[1000];
  for (int i = 0; i < 999; ++i)
  {
    if (i == 5)
      v[i] = 0;
    else
      v[i] = i;
  }
  for (size_t i = 0; i < 1000000; ++i)
    EXPECT_FALSE(find_benchmark(v, 999, 5));
}
*/

bool sentinel_find_benchmark(int* vect, size_t size, int val)
{
  vect[size] = val;
  size_t i = 0;
  for (;;++i)
  {
    if (val == vect[i])
    {
      if (i == size)
        return false;
      else
        return true;
    }
  }
  return false;
}

/*
Effective loop:
        mov     rax, QWORD PTR [rbp-8]
        lea     rdx, [0+rax*4]
        mov     rax, QWORD PTR [rbp-24]
        add     rax, rdx
        mov     eax, DWORD PTR [rax]
        cmp     eax, DWORD PTR [rbp-36]
        jne     .L2
*/
/*
TEST(sentinels, sentinel_find_benchmark)
{
  int v[1000];
  for (int i = 0; i < 999; ++i)
  {
    if (i == 5)
      v[i] = 0;
    else
      v[i] = i;
  }
  for (size_t i = 0; i < 1000000; ++i)
    EXPECT_FALSE(sentinel_find_benchmark(v, 999, 5));
}
*/

/*
Measurements:

-O0
find				find_sentinels	
								
4134	4134			2541	2541				
2781	2781			2557	2557				
3397	3397			3428	3428				
3136	3136			3589	3589				
3086	3086			2544	2544				
2921	2921			2810	2810				
2905	2905			3404	3404				
3880	3880			2815	2815				
4168	4168			2711	2711				
2767	2767			2959	2959

total	avg			total	avg			diff	
33175	3317.5			29358	2935.8			0.884943482	1.130015669
									
-O3									
find				find_sentinels	
								
1893	1893			1640	1640				
1831	1831			1404	1404				
2784	2784			2508	2508				
2406	2406			1728	1728				
2071	2071			1916	1916				
2498	2498			1741	1741				
1560	1560			1325	1325				
1236	1236			1055	1055				
1238	1238			979	979				
2175	2175			1036	1036				

total	avg			total	avg			diff
19692	1969.2			15332	1533.2			0.77859029	1.284372554

*/
