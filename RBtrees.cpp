#include <gtest/gtest.h>
#include <vector>
#include <iostream>
#include <stack>
#include <string>
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

enum class Color
{
RED = 0,
BLACK
};

class RBtree {
  struct Node {
    int val;
    Color col;
    Node *left;
    Node *right;
  };

  bool nodeHasBothChildren(Node* node);
  bool isRed(Node* node);
  bool insert(Node*& node, int key);

public:
  RBtree();
  RBtree(const RBtree &rhs) = delete;
  RBtree operator=(const RBtree &rhs) = delete;

  bool insert(int key);
  bool find(int key);
  bool isEmpty();
  int height();

  std::string toString();
  
  std::string inOrderTraversal();
  std::string preOrderTraversal();
  std::string postOrderTraversal();

protected:
  Node* RotateLeft(Node* node);
  Node* RotateRight(Node* node);
  Node** findNode(int key);
  void flipColors(Node* node);
 
private:
  Node *root;
};

RBtree::RBtree() : root(nullptr) {}

bool RBtree::insert(int key) 
{
  return insert(root, key);
}

bool RBtree::insert(Node*& node, int key)
{
  if (!node)
  {
    node = new Node{ key, Color::BLACK, nullptr, nullptr };
    return true;
  }

  bool result = false;
  if (key > node->val) 
    result = insert(node->right, key);
  else if (key < node->val) 
    result = insert(node->left, key);
  else
    return false;

  if (isRed(node->right) && !isRed(node->left))
    node = RotateLeft(node);
  if (isRed(node->left) && isRed(node->left->left))
    node = RotateRight(node);
  if (isRed(node->left) && isRed(node->right))
    flipColors(node);

  return result;
}

bool RBtree::isRed(Node* node)
{
  if (!node)
    return false;
  return node->col == Color::RED;
}

RBtree::Node* RBtree::RotateLeft(Node* node)
{
  if (!isRed(node->right))
    throw std::runtime_error("For left rotation right node should be red!");

  Node* x = node->right;
  node->right = x->left;
  x->left = node;
  x->col = node->col;
  node->col = Color::RED;
  return x;
}

RBtree::Node* RBtree::RotateRight(Node* node)
{
  if (!isRed(node->left))
    throw std::runtime_error("For right rotation left node should be red!");

  Node* x = node->left;
  node->left = x->right;
  x->right = node;
  x->col = node->col;
  node->col = Color::RED;
  return x;
}

void RBtree::flipColors(Node* node)
{
  if (isRed(node))
    return;
  if (!isRed(node->right))
    return;
  if (!isRed(node->left))
    return;

  node->col = Color::RED;
  node->right->col = Color::BLACK;
  node->left->col = Color::BLACK;
}

bool RBtree::find(int key)
{
  return findNode(key) != nullptr;
}

RBtree::Node** RBtree::findNode(int key) 
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

bool RBtree::isEmpty()
{
  return root == nullptr;
}

int RBtree::height()
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

bool RBtree::nodeHasBothChildren(Node* node)
{
  if (!node)
    throw std::runtime_error("WTF? node is invalid.");
  return node->right && node->left;
}

namespace
{
std::string itoa(int value)
{
  std::stringstream stream;
  stream << value;
  return stream.str();
}
}

std::string RBtree::toString()
{
  if (isEmpty())
    return "";

  std::vector<Node*> nodes;
  nodes.push_back(root);
  std::vector<std::string> levels;
  
  while(!nodes.empty())
  {
    levels.push_back("");
    std::vector<Node*> nextLevel;
    for (auto node : nodes)
    {
      levels.back() += itoa(node->val);
      levels.back() += ' ';
      if (node->left)
        nextLevel.push_back(node->left);
      if (node->right)
        nextLevel.push_back(node->right);
    }
    nodes = std::move(nextLevel);
  }

  std::string result = "";
  for (auto& level : levels)
  {
    result += level + "\n";
  }
  return result;
}

std::string RBtree::inOrderTraversal()
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

std::string RBtree::preOrderTraversal()
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

std::string RBtree::postOrderTraversal()
{
  std::string result = "";
  std::stack<Node*> postOrder;
  Node* current = root;
  Node* lastVisited = nullptr;

  while(!postOrder.empty() || current)
  {
    if (current)
    {
      postOrder.push(current);
      current = current->left;
    }
    else
    {
      Node* top = postOrder.top();
      if (top->right && lastVisited != top->right)
      {
        current = top->right;
      }
      else
      {
        result += itoa(top->val) + ' ';
        lastVisited = postOrder.top();
        postOrder.pop();
      }
    }
  } 
  return result;
}

TEST(RBtree, IsEmpty) 
{
  RBtree T;

  EXPECT_TRUE(T.isEmpty());
}

TEST(RBtree, Sample) 
{
  RBtree T;
  EXPECT_TRUE(T.insert(1));

  EXPECT_FALSE(T.isEmpty());
}

TEST(RBtree, SampleFind) 
{
  RBtree T;
  EXPECT_TRUE(T.insert(1));

  EXPECT_TRUE(T.find(1));
  EXPECT_FALSE(T.find(0));
  EXPECT_FALSE(T.find(2));
  EXPECT_FALSE(T.find(3));
}

TEST(RBtree, FaultyInsert) 
{
  RBtree T;
  EXPECT_TRUE(T.insert(1));
  EXPECT_FALSE(T.insert(1));

  EXPECT_TRUE(T.find(1));
  EXPECT_FALSE(T.find(0));
  EXPECT_FALSE(T.find(2));
  EXPECT_FALSE(T.find(3));
}

TEST(RBtree, Height_int) {
  RBtree T;
  EXPECT_TRUE(T.insert(5));
  EXPECT_TRUE(T.insert(6));
  EXPECT_TRUE(T.insert(3));
  EXPECT_TRUE(T.insert(4));
  EXPECT_TRUE(T.insert(2));
  EXPECT_TRUE(T.insert(1));

  EXPECT_EQ(4, T.height());
}

TEST(RBtree, Insert_Find) {
  RBtree T;
  EXPECT_TRUE(T.insert(1));
  EXPECT_TRUE(T.insert(2));
  EXPECT_TRUE(T.insert(3));

  EXPECT_TRUE(T.find(1));
  EXPECT_TRUE(T.find(2));
  EXPECT_TRUE(T.find(3));
}

TEST(RBtree, Traversals) {
  RBtree T;
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

class RBtreeFake : public RBtree
{
  public:
    using RBtree::RotateRight;
    using RBtree::RotateLeft;
    using RBtree::flipColors;
    using RBtree::findNode;
};

TEST(RBtree, Rotations) 
{
  RBtreeFake T;
  EXPECT_TRUE(T.insert(7));
  EXPECT_TRUE(T.insert(3));
  EXPECT_TRUE(T.insert(11));
  EXPECT_TRUE(T.insert(1));
  EXPECT_TRUE(T.insert(5));
  EXPECT_TRUE(T.insert(9));
  EXPECT_TRUE(T.insert(13));
}

TEST(RBtree, flippingColors) 
{
  RBtreeFake T;
  EXPECT_TRUE(T.insert(7));
  EXPECT_TRUE(T.insert(3));
  EXPECT_TRUE(T.insert(11));
  EXPECT_TRUE(T.insert(1));
  EXPECT_TRUE(T.insert(5));
  EXPECT_TRUE(T.insert(9));
  EXPECT_TRUE(T.insert(13));
}

