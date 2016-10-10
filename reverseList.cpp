#include <vector>
#include <gtest/gtest.h>
#include <iostream>
#include <stack>

struct Node
{
  Node* next;
  int val;
};

void addToList(Node*& head, int val)
{
  if (!head)
  {
    head = new Node {nullptr, val};
  }
  else
  {
    Node* cur = head;
    while(cur->next)
    {
      cur = cur->next;
    }
    cur->next = new Node {nullptr, val};
  }
}

void reverseList(Node*& head)
{
  if (!head)
    return;

  Node* cur = head;
  Node* prev = nullptr;
  while (cur)
  {
    Node* next = cur->next;
    cur->next = prev;
    prev = cur;
    cur = next;
  }
  head = prev;
}

void reverseListStack(Node*& head)
{
  if (!head || !head->next)
    return;

  std::stack<Node*> order;

  Node* cur = head;
  while(cur)
  {
    order.push(cur);
    cur = cur->next;
  }

  head = order.top();
  order.pop();

  cur = head;
  Node* next = nullptr;

  while(!order.empty())
  {
    next = order.top();
    order.pop();
    cur->next = next;
    cur = next;
  }

  cur->next = nullptr;
}

void reverseListRecursive(Node*& head, Node* cur)
{
  if (cur->next)
  {
    reverseListRecursive(head, cur->next);
    cur->next->next = cur;
  }
  else
  {
    head = cur;
  }
}

void reverseListRecursive(Node*& head)
{
  if (head)
  {
    Node* temp = head;
    reverseListRecursive(head, head);
    temp->next = nullptr;
  }
}

void printList(Node* head)
{
  while (head)
  {
    std::cout << head->val << ' ';
    head = head->next;
  }
  std::cout << '\n';
}

bool twoListsAreEqual(Node* head1, Node* head2)
{
  while (head1 && head2)
  {
    if (head1->val != head2->val)
      return false;
    head1 = head1->next;
    head2 = head2->next;
  }
  if (head1 || head2)
    return false;
  return true;
}

TEST(reverseList, util)
{
  Node* list1 = nullptr;
  addToList(list1, 5);
  addToList(list1, 2);
  addToList(list1, 7);
  addToList(list1, 5);
  printList(list1);

  Node* list2 = nullptr;
  addToList(list2, 5);
  addToList(list2, 2);
  addToList(list2, 7);

  EXPECT_FALSE(twoListsAreEqual(list1, list2));
  
  addToList(list2, 5);
  EXPECT_TRUE(twoListsAreEqual(list1, list2));

  addToList(list2, 5);
  EXPECT_FALSE(twoListsAreEqual(list1, list2));
}

TEST(reverseList, empty)
{
  Node* list = nullptr;

  Node* expected = nullptr;

  reverseList(list);

  EXPECT_TRUE(twoListsAreEqual(list, expected));
}

TEST(reverseList, oneElem)
{
  Node* list = nullptr;
  addToList(list, 5);

  Node* expected = nullptr;
  addToList(expected, 5);

  reverseList(list);

  EXPECT_TRUE(twoListsAreEqual(list, expected));
}

TEST(reverseList, manyElems)
{
  Node* list = nullptr;
  addToList(list, 5);
  addToList(list, 2);
  addToList(list, 7);
  addToList(list, 5);

  Node* expected = nullptr;
  addToList(expected, 5);
  addToList(expected, 7);
  addToList(expected, 2);
  addToList(expected, 5);

  reverseList(list);

  EXPECT_TRUE(twoListsAreEqual(list, expected));
}

TEST(reverseListRecursive, empty)
{
  Node* list = nullptr;

  Node* expected = nullptr;

  reverseListRecursive(list);

  EXPECT_TRUE(twoListsAreEqual(list, expected));
}

TEST(reverseListRecursive, oneElem)
{
  Node* list = nullptr;
  addToList(list, 5);

  Node* expected = nullptr;
  addToList(expected, 5);

  reverseListRecursive(list);

  EXPECT_TRUE(twoListsAreEqual(list, expected));
}

TEST(reverseListRecursive, manyElems)
{
  Node* list = nullptr;
  addToList(list, 5);
  addToList(list, 2);
  addToList(list, 7);
  addToList(list, 5);

  Node* expected = nullptr;
  addToList(expected, 5);
  addToList(expected, 7);
  addToList(expected, 2);
  addToList(expected, 5);

  reverseListRecursive(list);

  EXPECT_TRUE(twoListsAreEqual(list, expected));
}

TEST(reverseListStack, empty)
{
  Node* list = nullptr;

  Node* expected = nullptr;

  reverseListStack(list);

  EXPECT_TRUE(twoListsAreEqual(list, expected));
}

TEST(reverseListStack, oneElem)
{
  Node* list = nullptr;
  addToList(list, 5);

  Node* expected = nullptr;
  addToList(expected, 5);

  reverseListStack(list);

  EXPECT_TRUE(twoListsAreEqual(list, expected));
}

TEST(reverseListStack, manyElems)
{
  Node* list = nullptr;
  addToList(list, 5);
  addToList(list, 2);
  addToList(list, 7);
  addToList(list, 5);

  Node* expected = nullptr;
  addToList(expected, 5);
  addToList(expected, 7);
  addToList(expected, 2);
  addToList(expected, 5);

  reverseListStack(list);

  EXPECT_TRUE(twoListsAreEqual(list, expected));
}
