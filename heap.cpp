#include <iostream>
#include <vector>
#include <gtest/gtest.h>

class Heap
{
public:
  Heap();
  void insert(int value);
  int deleteMin();

protected:
  bool hasParentNode(size_t index);
  size_t parentNode(size_t index);
  size_t leftChild(size_t index);
  size_t rightChild(size_t index);
  void BubbleUp(size_t index);
  void BubbleDown(size_t index);

  std::vector<int> heap;
};

Heap::Heap()
{
}

bool Heap::hasParentNode(size_t index)
{
  return index != 0;
}

size_t Heap::parentNode(size_t index)
{
  return (index - 1) / 2;
}

size_t Heap::leftChild(size_t index)
{
  return index * 2 + 1;
}

size_t Heap::rightChild(size_t index)
{
  return index * 2 + 2;
}

void Heap::BubbleUp(size_t index)
{
  if (!hasParentNode(index))
    return;

  size_t parent = parentNode(index);

  if (heap[parent] > heap[index])
  {
    std::swap(heap[parent], heap[index]);
    BubbleUp(parent);
  }
}

void Heap::BubbleDown(size_t index)
{
  size_t left = leftChild(index);
  size_t right = rightChild(index);

  // no children
  if (left >= heap.size())
    return; 

  // only left children
  if (right >= heap.size())
  {
    if (heap[index] > heap[left])
    {
      std::swap(heap[index], heap[left]);
      BubbleDown(left);
    }
    return;
  }    

  // both childrens
  if (heap[index] < heap[left] && heap[index] < heap[right])
    return;

  if (heap[right] < heap[left])
  {
    std::swap(heap[index], heap[right]);
    BubbleDown(right);
  }
  else
  {
    std::swap(heap[index], heap[left]);
    BubbleDown(left);
  }
}

void Heap::insert(int value)
{
  heap.push_back(value);
  BubbleUp(heap.size() - 1);
}

int Heap::deleteMin()
{
  int retVal = heap[0];
  std::swap(heap[0], heap.back());
  heap.pop_back();
  BubbleDown(0);
  return retVal;
}

using namespace testing;

class FakeHeap : public Heap
{
public:
    FakeHeap() : Heap() {}
    template <class U>
    FakeHeap(U& source) : Heap() 
    { 
      for (auto& elem: source)
        insert(elem);
    }
    using Heap::heap;
    using Heap::hasParentNode;
    using Heap::parentNode;
    using Heap::leftChild;
    using Heap::rightChild;
    using Heap::BubbleUp;
    using Heap::BubbleDown;
};

template <class T>
void checkTwoVectorsAreEqual(const T& lhs, const T& rhs)
{
     EXPECT_EQ(lhs.size(), rhs.size());
     EXPECT_TRUE(std::equal(lhs.begin(), lhs.end(), rhs.begin()));
}

TEST(HeapUnitTest, 1)
{
     FakeHeap heap;
     (void)heap;
}

TEST(HeapUnitTest, 2)
{
     FakeHeap heap;
     heap.insert(1);
     checkTwoVectorsAreEqual({1}, heap.heap);
}

TEST(HeapUnitTest, 3)
{
     FakeHeap heap;
     heap.insert(0);
     checkTwoVectorsAreEqual({0}, heap.heap);
}

TEST(HeapUnitTest, 4)
{
     FakeHeap heap;
     heap.insert(std::numeric_limits<int>::max());
     checkTwoVectorsAreEqual({std::numeric_limits<int>::max()}, heap.heap);
}

TEST(HeapUnitTest, 5)
{
     FakeHeap heap;
     heap.insert(0);
     heap.insert(1);
     checkTwoVectorsAreEqual({0, 1}, heap.heap);
}

TEST(HeapUnitTest, 6)
{
     FakeHeap heap;
     heap.insert(0);
     heap.insert(1);
     heap.insert(2);
     checkTwoVectorsAreEqual({0, 1, 2}, heap.heap);
}

TEST(HeapUnitTest, 7)
{
     FakeHeap heap;
     heap.insert(2);
     heap.insert(1);
     checkTwoVectorsAreEqual({1, 2}, heap.heap);
}

TEST(HeapUnitTest, 8)
{
    FakeHeap heap;
    EXPECT_EQ(1, heap.leftChild(0));
    EXPECT_EQ(2, heap.rightChild(0));

    EXPECT_EQ(3, heap.leftChild(1));
    EXPECT_EQ(4, heap.rightChild(1));

    EXPECT_EQ(5, heap.leftChild(2));
    EXPECT_EQ(6, heap.rightChild(2));
}

TEST(HeapUnitTest, 9)
{
    FakeHeap heap;
    EXPECT_EQ(2, heap.parentNode(6));
    EXPECT_EQ(2, heap.parentNode(5));
    EXPECT_EQ(1, heap.parentNode(4));
    EXPECT_EQ(1, heap.parentNode(3));
    EXPECT_EQ(0, heap.parentNode(2));
    EXPECT_EQ(0, heap.parentNode(1));
    EXPECT_EQ(0, heap.parentNode(heap.parentNode(6)));
}

TEST(HeapUnitTest, 11)
{
    size_t counter = 0;

    size_t parent = 6;
    FakeHeap heap;
    while (heap.hasParentNode(parent))
    {
        parent = heap.parentNode(parent);
        ++counter;
    }

    ASSERT_EQ(2, counter);
}

TEST(HeapUnitTest, 12)
{
    FakeHeap heap;
    heap.insert(2);
    heap.insert(1);
    heap.insert(0);
    checkTwoVectorsAreEqual({0, 2, 1}, heap.heap);
}

TEST(HeapUnitTest, 13)
{
    // Skiena example
    FakeHeap heap;
    heap.insert(1804);
    heap.insert(1776);
    heap.insert(1492);
    heap.insert(2001);
    heap.insert(1963);
    heap.insert(1918);
    heap.insert(1783);
    heap.insert(1945);
    heap.insert(1865);
    heap.insert(1941);
    checkTwoVectorsAreEqual({1492, 1804, 1776, 1865, 1941, 1918, 1783, 2001, 1945, 1963}, heap.heap);
}

TEST(HeapUnitTest, 14)
{
    // Skiena example with duplicates
    FakeHeap heap;
    heap.insert(1804);
    heap.insert(1776);
    heap.insert(1492);
    heap.insert(2001);
    heap.insert(1963);
    heap.insert(1918);
    heap.insert(1783);
    heap.insert(1945);
    heap.insert(1865);
    heap.insert(1941);
    heap.insert(1941);
    heap.insert(1941);
    heap.insert(1941);
    checkTwoVectorsAreEqual({1492, 1804, 1776, 1865, 1941, 1918, 1783, 2001, 1945, 1963, 1941, 1941, 1941}, heap.heap);
}

TEST(HeapUnitTest, 15)
{
    // Skiena example
    FakeHeap heap;
    heap.insert(1804);
    heap.insert(1776);
    heap.insert(1492);
    heap.insert(2001);
    heap.insert(1963);
    heap.insert(1918);
    heap.insert(1783);
    heap.insert(1945);
    heap.insert(1865);
    heap.insert(1941);
    checkTwoVectorsAreEqual({1492, 1804, 1776, 1865, 1941, 1918, 1783, 2001, 1945, 1963}, heap.heap);
    ASSERT_EQ(1492, heap.deleteMin());
}

TEST(HeapUnitTest, 16)
{
     FakeHeap heap;
     heap.insert(2);
     heap.insert(1);
     checkTwoVectorsAreEqual({1, 2}, heap.heap);
     ASSERT_EQ(1, heap.deleteMin());
     checkTwoVectorsAreEqual({2}, heap.heap);
     ASSERT_EQ(2, heap.deleteMin());
     checkTwoVectorsAreEqual({}, heap.heap);
}

TEST(HeapUnitTest, 17)
{
     FakeHeap heap;
     heap.insert(2);
     heap.insert(1);
     heap.insert(0);
     checkTwoVectorsAreEqual({0, 2, 1}, heap.heap);
     ASSERT_EQ(0, heap.deleteMin());
     checkTwoVectorsAreEqual({1, 2}, heap.heap);
     ASSERT_EQ(1, heap.deleteMin());
     checkTwoVectorsAreEqual({2}, heap.heap);
     ASSERT_EQ(2, heap.deleteMin());
     checkTwoVectorsAreEqual({}, heap.heap);
}

TEST(HeapUnitTest, 18)
{
    // Skiena example
    FakeHeap heap;
    heap.insert(1804);
    heap.insert(1776);
    heap.insert(1492);
    heap.insert(2001);
    heap.insert(1963);
    heap.insert(1918);
    heap.insert(1783);
    heap.insert(1945);
    heap.insert(1865);
    heap.insert(1941);
    checkTwoVectorsAreEqual({1492, 1804, 1776, 1865, 1941, 1918, 1783, 2001, 1945, 1963}, heap.heap);
    ASSERT_EQ(1492, heap.deleteMin());
    ASSERT_EQ(1776, heap.deleteMin());
    ASSERT_EQ(1783, heap.deleteMin());
    ASSERT_EQ(1804, heap.deleteMin());
    ASSERT_EQ(1865, heap.deleteMin());
    ASSERT_EQ(1918, heap.deleteMin());
    ASSERT_EQ(1941, heap.deleteMin());
    ASSERT_EQ(1945, heap.deleteMin());
    ASSERT_EQ(1963, heap.deleteMin());
    ASSERT_EQ(2001, heap.deleteMin());
}

TEST(HeapUnitTest, 19)
{
    std::vector<int> source = { 1804, 1776, 1492, 2001, 1963, 1918, 1783 };
    FakeHeap heap(source);
    
    //checkTwoVectorsAreEqual({1492, 1776, 1783, 2001, 1963, 1918, 1804}, heap.heap);
    ASSERT_EQ(1492, heap.deleteMin());
    ASSERT_EQ(1776, heap.deleteMin());
    ASSERT_EQ(1783, heap.deleteMin());
    ASSERT_EQ(1804, heap.deleteMin());
    ASSERT_EQ(1918, heap.deleteMin());
    ASSERT_EQ(1963, heap.deleteMin());
    ASSERT_EQ(2001, heap.deleteMin());
}

