#include <gtest/gtest.h>
#include <vector>
#include <iostream>

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

