#include <type_traits>

template <int N>
struct Factorial
{
  static const int value = N * Factorial<N-1>::value;
};

template <>
struct Factorial<0>
{
  static const int value = 1;
};

static_assert(Factorial<5>::value == 120, "wrong");
static_assert(Factorial<1>::value == 1, "wrong");
static_assert(Factorial<3>::value == 6, "wrong");
static_assert(Factorial<6>::value == 720, "wrong");

constexpr int factorial(int N)
{
  return (N == 0 ) ? 1 : N * factorial(N-1);
}

static_assert(factorial(5) == 120, "wrong");
static_assert(factorial(1) == 1, "wrong");
static_assert(factorial(3) == 6, "wrong");
static_assert(factorial(6) == 720, "wrong");

