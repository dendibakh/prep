#include <array>
#include <vector>
#include <limits>
#include <memory>
#include <gtest/gtest.h>
#include <random>

#include "fixed_arena_controller.hpp"
#include "fixed_block_memory_manager.hpp"

class MemMgrTester
{
    size_t contents_[1000];
public:
    MemMgrTester(size_t c)
	{
    	for (auto i = 0; i < 1000; ++i)
    	{
    		contents_[i] = c;
    	}
	}

    static void* operator new(size_t s) {
        return mgr_.allocate(s);
    }
    static void  operator delete(void* p) {
        mgr_.deallocate(p);
    }
    static fixed_block_memory_manager<fixed_arena_controller> mgr_;
};

char arena[10001 * (sizeof(MemMgrTester) + sizeof(void*))];
fixed_block_memory_manager<fixed_arena_controller> MemMgrTester::mgr_(arena);

/*TEST(FixedSizeAllocator, correction_test)
{
	auto p1 = std::make_unique<MemMgrTester>(0x12);
	auto p2 = std::make_unique<MemMgrTester>(0x34);
	{
		auto p3 = std::make_unique<MemMgrTester>(0x56);
	}
	auto p4 = std::make_unique<MemMgrTester>(0x78);
	auto p5 = std::make_unique<MemMgrTester>(0xAB);
	p2.reset();
	auto p6 = std::make_unique<MemMgrTester>(0xCD);
	auto p7 = std::make_unique<MemMgrTester>(0xEF);
}*/

TEST(FixedSizeAllocator, benchmark_1_fixed)
{
	  std::uniform_int_distribution<std::mt19937::result_type> dist(0, 99); // distribution in range [0, 99]
	  std::mt19937 rng;
	  rng.seed(std::random_device()());
	  std::array<std::unique_ptr<MemMgrTester>, 100> ptrs;
	  for (auto i = 0; i < 1000000; ++i)
	  {
		  auto pos = dist(rng);
		  ptrs[pos] = std::make_unique<MemMgrTester>(0xFFFFFFFF);
	  }
	  // 3037 ms
	  // benefit around 0.8%
	  // this is realistic gain.
}

TEST(FixedSizeAllocator, benchmark_2_fixed)
{
	  std::array<std::unique_ptr<MemMgrTester>, 10000> ptrs;
	  for (auto i = 0; i < 10000; ++i)
	  {
		  ptrs[i] = std::make_unique<MemMgrTester>(0xFFFFFFFF);
	  }
	  // 40 ms
	  // benefit around 55%
	  // this is not a realistic gain.
}

class MemMgrTesterStd
{
    size_t contents_[1000];
public:
    MemMgrTesterStd(size_t c)
	{
    	for (auto i = 0; i < 1000; ++i)
    	{
    		contents_[i] = c;
    	}
	}
};

TEST(FixedSizeAllocator, benchmark_1_std)
{
	  std::uniform_int_distribution<std::mt19937::result_type> dist(0, 99); // distribution in range [0, 99]
	  std::mt19937 rng;
	  rng.seed(std::random_device()());
	  std::array<std::unique_ptr<MemMgrTesterStd>, 100> ptrs;
	  for (auto i = 0; i < 1000000; ++i)
	  {
		  auto pos = dist(rng);
		  ptrs[pos] = std::make_unique<MemMgrTesterStd>(0xFFFFFFFF);
	  }
	  // 11 brk calls
	  // 3060 ms
}

TEST(FixedSizeAllocator, benchmark_2_std)
{
	  std::array<std::unique_ptr<MemMgrTesterStd>, 10000> ptrs;
	  for (auto i = 0; i < 10000; ++i)
	  {
		  ptrs[i] = std::make_unique<MemMgrTesterStd>(0xFFFFFFFF);
	  }
	  // ~10500 brk calls
	  // 89 ms
}

