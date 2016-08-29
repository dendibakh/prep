#include <gtest/gtest.h>
#include <vector>
#include <iostream>
#include <stack>
#include <sstream>

// find
// insert
// delete
// red-black bst
// iterations:
// - inorder
// - preorder
// - postorder
//
// iterators (optionaly)

class Btree {
  struct Node {
    int val;
    Node *left;
    Node *right;
  };

  Node** findNode(int key);
  bool nodeHasBothChildren(Node* node);
  bool removeSimpleNode(Node** node);

public:
  Btree();
  Btree(const Btree &rhs) = delete;
  Btree operator=(const Btree &rhs) = delete;

  bool insert(int key);
  bool find(int key);
  bool isEmpty();
  int height();
  bool remove(int key);

  std::string inOrderTraversal();
  std::string preOrderTraversal();
  std::string postOrderTraversal();

private:
  Node *root;
};

Btree::Btree() : root(nullptr) {}

bool Btree::insert(int key) 
{
  Node** current = &root;
  while (*current)
  {
    if ((*current)->val == key)
      return false;
    else if ((*current)->val < key)
      current = &((*current)->right);
    else
      current = &((*current)->left);
  }
  *current = new Node{ key, nullptr, nullptr };
  return true;
}

bool Btree::find(int key)
{
  return findNode(key) != nullptr;
}

Btree::Node** Btree::findNode(int key) 
{
  Node** current = &root;
  while (*current)
  {
    if ((*current)->val == key)
      return current;
    else if ((*current)->val < key)
      current = &((*current)->right);
    else
      current = &((*current)->left);
  }
  return nullptr;
}

bool Btree::isEmpty()
{
  return root == nullptr;
}

int Btree::height()
{
  if (isEmpty())
    return 0;
  std::vector<Node*> nodes;
  nodes.push_back(root);
  int height = 0;
  
  while(!nodes.empty())
  {
    ++height;
    std::vector<Node*> nextLevel;
    for (auto node : nodes)
    {
      if (node->left)
        nextLevel.push_back(node->left);
      if (node->right)
        nextLevel.push_back(node->right);
    }
    nodes = std::move(nextLevel);
  }

  return height;
}

bool Btree::remove(int key)
{
  Node** node = findNode(key);
  if (!node || !(*node))
    return false;

  if (!nodeHasBothChildren(*node))
    return removeSimpleNode(node);

  // both children
  // 1. find leftmost node in the right subtree
  Node** temp = &(*node)->right;
  while(*temp)
  {
    if ((*temp)->left)
      temp = &(*temp)->left;
    else
      break;
  }
  (*node)->val = (*temp)->val;
  removeSimpleNode(temp);
}

bool Btree::removeSimpleNode(Node** node)
{
  if (!node)
    return false;

  // leaf node
  if (!(*node)->left && !(*node)->right)
  {
    delete *node;
    *node = nullptr;
    return true;
  }

  // one children - left
  if ((*node)->left && !(*node)->right)
  {
    Node* temp = (*node)->left;
    delete *node;
    *node = temp;
    return true;
  }

  // one children - right
  if (!(*node)->left && (*node)->right)
  {
    Node* temp = (*node)->right;
    delete *node;
    *node = temp;
    return true;
  }

  return false;
}

bool Btree::nodeHasBothChildren(Node* node)
{
  if (!node)
    throw std::runtime_error("WTF? node is invalid.");
  return node->right && node->left;
}

std::string itoa(int value)
{
  std::stringstream stream;
  stream << value;
  return stream.str();
}

std::string Btree::inOrderTraversal()
{
  std::string result = "";
  std::stack<Node*> inOrder;
  Node* current = root;

  do
  {
    while (current)
    {
      inOrder.push(current);
      current = current->left;
    }

    if (!inOrder.empty())
    {
      Node* top = inOrder.top();
      inOrder.pop();
      result += itoa(top->val) + ' ';
      current = top->right;
    }
  }
  while(!inOrder.empty() || current);

  return result;
}

std::string Btree::preOrderTraversal()
{
  std::string result = "";
  std::stack<Node*> inOrder;
  Node* current = root;

  do
  {
    while (current)
    {
      result += itoa(current->val) + ' ';
      inOrder.push(current);
      current = current->left;
    }

    if (!inOrder.empty())
    {
      Node* top = inOrder.top();
      inOrder.pop();
      current = top->right;
    }
  }
  while(!inOrder.empty() || current);

  return result;
}

std::string Btree::postOrderTraversal()
{
  std::string result = "";
  std::stack<Node*> inOrder;
  Node* current = root;

  std::stack<int> values;

  do
  {
    while (current)
    {
      values.push(current->val);
      inOrder.push(current);
      current = current->right;
    }

    if (!inOrder.empty())
    {
      Node* top = inOrder.top();
      inOrder.pop();
      current = top->left;
    }
  }
  while(!inOrder.empty() || current);

  while(!values.empty())
  {
    result += itoa(values.top()) + ' ';
    values.pop();
  }

  return result;
}

TEST(Btree, IsEmpty) 
{
  Btree T;

  EXPECT_TRUE(T.isEmpty());
}

TEST(Btree, Sample) 
{
  Btree T;
  EXPECT_TRUE(T.insert(1));

  EXPECT_FALSE(T.isEmpty());
}

TEST(Btree, SampleFind) 
{
  Btree T;
  EXPECT_TRUE(T.insert(1));

  EXPECT_TRUE(T.find(1));
  EXPECT_FALSE(T.find(0));
  EXPECT_FALSE(T.find(2));
  EXPECT_FALSE(T.find(3));
}

TEST(Btree, FaultyInsert) 
{
  Btree T;
  EXPECT_TRUE(T.insert(1));
  EXPECT_FALSE(T.insert(1));

  EXPECT_TRUE(T.find(1));
  EXPECT_FALSE(T.find(0));
  EXPECT_FALSE(T.find(2));
  EXPECT_FALSE(T.find(3));
}

TEST(Btree, Height_int) {
  Btree T;
  EXPECT_TRUE(T.insert(5));
  EXPECT_TRUE(T.insert(6));
  EXPECT_TRUE(T.insert(3));
  EXPECT_TRUE(T.insert(4));
  EXPECT_TRUE(T.insert(2));
  EXPECT_TRUE(T.insert(1));

  EXPECT_EQ(4, T.height());
}

TEST(Btree, Insert_Find) {
  Btree T;
  EXPECT_TRUE(T.insert(1));
  EXPECT_TRUE(T.insert(2));
  EXPECT_TRUE(T.insert(3));

  EXPECT_TRUE(T.find(1));
  EXPECT_TRUE(T.find(2));
  EXPECT_TRUE(T.find(3));
}

TEST(Btree, Remove_FromEnd) {
  Btree T;
  EXPECT_TRUE(T.insert(1));
  EXPECT_TRUE(T.insert(2));
  EXPECT_TRUE(T.insert(3));

  EXPECT_TRUE(T.remove(3));

  EXPECT_TRUE(T.find(1));
  EXPECT_TRUE(T.find(2));
  EXPECT_FALSE(T.find(3));
}


TEST(Btree, Remove_FromRoot) {
  Btree T;
  EXPECT_TRUE(T.insert(1));
  EXPECT_TRUE(T.insert(2));
  EXPECT_TRUE(T.insert(3));

  EXPECT_TRUE(T.remove(1));

  EXPECT_FALSE(T.find(1));
  EXPECT_TRUE(T.find(2));
  EXPECT_TRUE(T.find(3));
}

TEST(Btree, Remove_FromMiddle_int) {
  Btree T;
  EXPECT_TRUE(T.insert(3));
  EXPECT_TRUE(T.insert(2));
  EXPECT_TRUE(T.insert(1));
  EXPECT_TRUE(T.insert(5));
  EXPECT_TRUE(T.insert(4));
  EXPECT_TRUE(T.insert(6));

  EXPECT_TRUE(T.remove(5));
  EXPECT_TRUE(T.remove(3));
  EXPECT_TRUE(T.remove(2));

  EXPECT_TRUE(T.find(1));
  EXPECT_FALSE(T.find(2));
  EXPECT_FALSE(T.find(3));
  EXPECT_TRUE(T.find(4));
  EXPECT_FALSE(T.find(5));
  EXPECT_TRUE(T.find(6));
}

TEST(Btree, Traversals) {
  Btree T;
  EXPECT_TRUE(T.insert(7));
  EXPECT_TRUE(T.insert(3));
  EXPECT_TRUE(T.insert(11));
  EXPECT_TRUE(T.insert(1));
  EXPECT_TRUE(T.insert(5));
  EXPECT_TRUE(T.insert(9));
  EXPECT_TRUE(T.insert(13));

  EXPECT_STREQ("1 3 5 7 9 11 13 ", T.inOrderTraversal().c_str());
  EXPECT_STREQ("7 3 1 5 11 9 13 ", T.preOrderTraversal().c_str());
  EXPECT_STREQ("1 5 3 9 13 11 7 ", T.postOrderTraversal().c_str());
}
