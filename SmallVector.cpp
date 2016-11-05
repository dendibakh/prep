#include <gtest/gtest.h>
#include <array>

// This is a simplified version of a vector with a small-size buffer optimization.

template <unsigned N>
class SmallVector
{
  public:
    SmallVector();
    ~SmallVector();

    SmallVector(const SmallVector& rhs) = delete;
    SmallVector& operator=(const SmallVector& rhs) = delete;

    void push_back(int value);
    int& operator[](size_t index);
    int& at(size_t index);

  protected:
    std::array<int, N> smallBuffer;
    unsigned size;
    unsigned capacity;
    int* heapVector;
};

template <unsigned N>
SmallVector<N>::SmallVector() : size(0), capacity(N), heapVector(smallBuffer.data())
{
  for (auto& e : smallBuffer)
    e = int();
}

template <unsigned N>
SmallVector<N>::~SmallVector()
{
  if (heapVector != smallBuffer.data())
    delete [] heapVector;
}

template <unsigned N>
void SmallVector<N>::push_back(int value)
{
  if (size == capacity)
  {
    int* newStorage = new int[capacity * 2];
    capacity *= 2;
    memcpy(newStorage, heapVector, size * sizeof(int));
    if (heapVector != smallBuffer.data())
      delete [] heapVector;
    heapVector = newStorage;
  }
  heapVector[size++] = value;
}

template <unsigned N>
int& SmallVector<N>::operator[](size_t index)
{
  return heapVector[index];
}

template <unsigned N>
int& SmallVector<N>::at(size_t index)
{
  if (index >= size)
    throw std::runtime_error("bad index");
  return heapVector[index];
}

template <unsigned N>
class SmallVectorFake : public SmallVector<N>
{
  public:
    using SmallVector<N>::smallBuffer;
    using SmallVector<N>::size;
    using SmallVector<N>::capacity;
    using SmallVector<N>::heapVector;
};

TEST(SmallVector, sample)
{
  SmallVector<4> vec;
  vec.push_back(0);
  EXPECT_EQ(0, vec[0]);
}

TEST(SmallVector, exceeding_small_buffer)
{
  SmallVectorFake<2> vec;
  vec.push_back(0);
  vec.push_back(1);
  vec.push_back(5);

  EXPECT_EQ(0, vec[0]);
  EXPECT_EQ(1, vec[1]);
  EXPECT_EQ(5, vec[2]);
  EXPECT_EQ(3, vec.size);
  EXPECT_EQ(4, vec.capacity);
  // we switched to heap allocated buffer
  EXPECT_TRUE(vec.smallBuffer.data() != vec.heapVector);
  // smallBuffer is still alive
  EXPECT_EQ(0, vec.smallBuffer[0]);
  EXPECT_EQ(1, vec.smallBuffer[1]);
}

TEST(SmallVector, not_exceeding_the_stack_buffer)
{
  SmallVectorFake<4> vec;
  vec.push_back(0);
  vec.push_back(1);
  vec.push_back(5);

  EXPECT_EQ(0, vec[0]);
  EXPECT_EQ(1, vec[1]);
  EXPECT_EQ(5, vec[2]);
  EXPECT_EQ(3, vec.size);
  EXPECT_EQ(4, vec.capacity);
  // we didn't switch to heap allocated buffer
  EXPECT_TRUE(vec.smallBuffer.data() == vec.heapVector);
}

TEST(SmallVector, exceeding_small_buffer_two_times)
{
  SmallVectorFake<2> vec;
  vec.push_back(0);
  vec.push_back(1);
  vec.push_back(5);
  vec.push_back(6);
  vec.push_back(7);

  EXPECT_EQ(0, vec[0]);
  EXPECT_EQ(1, vec[1]);
  EXPECT_EQ(5, vec[2]);
  EXPECT_EQ(6, vec[3]);
  EXPECT_EQ(7, vec[4]);

  EXPECT_EQ(5, vec.size);
  EXPECT_EQ(8, vec.capacity);

  // we switched to heap allocated buffer
  EXPECT_TRUE(vec.smallBuffer.data() != vec.heapVector);

  // smallBuffer is still alive
  EXPECT_EQ(0, vec.smallBuffer[0]);
  EXPECT_EQ(1, vec.smallBuffer[1]);
}

TEST(SmallVector, at_throws_exceptions)
{
  SmallVectorFake<2> vec;
  vec.push_back(0);

  EXPECT_NO_THROW(vec.at(0));
  EXPECT_THROW(vec.at(1), std::exception);
  EXPECT_THROW(vec.at(2), std::exception);
 
  vec.push_back(1);

  EXPECT_NO_THROW(vec.at(0));
  EXPECT_NO_THROW(vec.at(1));
  EXPECT_THROW(vec.at(2), std::exception);

  vec.push_back(5);

  EXPECT_NO_THROW(vec.at(0));
  EXPECT_NO_THROW(vec.at(1));
  EXPECT_NO_THROW(vec.at(2));
  EXPECT_THROW(vec.at(3), std::exception);
}

