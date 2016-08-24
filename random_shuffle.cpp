#include <utility>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

void randomShuffle(int* arr, int size)
{
  srand (time(NULL));

  for (int i = 0; i < size; ++i)
  {
    int r = rand() % i;
    std::swap(arr[i], arr[r]);
  }
}
