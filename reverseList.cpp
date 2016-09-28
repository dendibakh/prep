#include <vector>
#include <gtest/gtest.h>
#include <iostream>

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

void reverseList(Node* head)
{
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
  }
  if (head1 || head2)
    return false;
  return true;
}

TEST(reverseList, util)
{
  Node* list1;
  addToList(list1, 5);
  //addToList(list1, 2);
  //addToList(list1, 7);
  //addToList(list1, 5);
  //printList(list1);
}

TEST(reverseList, empty)
{
  Node* list;
  //rever
}

TEST(reverseList, oneElem)
{
}

TEST(reverseList, manyElems)
{
}

