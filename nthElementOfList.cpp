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

int nthElementOfListFromTheBack(Node* head, size_t n)
{
  if (!head)
    return 0;

  Node* cur = head;
  for (size_t i = 0; i < n; ++i)
  {
    if (cur)
      cur = cur->next;
    else
      break;
  }

  Node* temp = head;
  while(cur)
  {
    cur = cur->next;
    temp = temp->next;
  }

  return temp->val;
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

TEST(nthElementOfList, util)
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

TEST(nthElementOfList, n_in_range)
{
  Node* list = nullptr;
  addToList(list, 5);
  addToList(list, 2);
  addToList(list, 7);
  addToList(list, 5);

  EXPECT_EQ(5, nthElementOfListFromTheBack(list, 1));
  EXPECT_EQ(7, nthElementOfListFromTheBack(list, 2));
  EXPECT_EQ(2, nthElementOfListFromTheBack(list, 3));
  EXPECT_EQ(5, nthElementOfListFromTheBack(list, 4));
  EXPECT_EQ(5, nthElementOfListFromTheBack(list, 5));
}
