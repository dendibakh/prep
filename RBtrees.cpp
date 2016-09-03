#include <gtest/gtest.h>
#include <vector>
#include <iostream>
#include <stack>
#include <string>
#include <sstream>

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

  bool isRed(Node* node);
  bool insert(Node*& node, int key);
  Node* RotateLeft(Node* node);
  Node* RotateRight(Node* node);
  Node** findNode(int key);
  void flipColors(Node* node);

public:
  RBtree();
  ~RBtree();
  RBtree(const RBtree &rhs) = delete;
  RBtree operator=(const RBtree &rhs) = delete;

  bool insert(int key);
  bool find(int key);
  bool isEmpty();
  int height();

  std::string toString();

private:
  Node *root;
};

RBtree::RBtree() : root(nullptr) {}

RBtree::~RBtree()
{
  // ToDo: implement deletion of memory
}

bool RBtree::insert(int key) 
{
  return insert(root, key);
}

bool RBtree::insert(Node*& node, int key)
{
  if (!node)
  {
    node = new Node{ key, Color::RED, nullptr, nullptr };
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
  // Root is supposed to be always black
  if ((node != root) && isRed(node))
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
      levels.back() += ( node->col == Color::RED ) ? 'R' : 'B';
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

TEST(RBtree, ToString) {
  RBtree T;

  EXPECT_TRUE(T.insert(50));
  EXPECT_STREQ("R50 \n", T.toString().c_str());

  EXPECT_TRUE(T.insert(25));
  EXPECT_STREQ("R50 \nR25 \n", T.toString().c_str());

  EXPECT_TRUE(T.insert(15));
  EXPECT_STREQ("R25 \nB15 B50 \n", T.toString().c_str());

  EXPECT_TRUE(T.insert(35));
  EXPECT_STREQ("R25 \nB15 B50 \nR35 \n", T.toString().c_str());

  EXPECT_TRUE(T.insert(20));
  EXPECT_STREQ("R25 \nB20 B50 \nR15 R35 \n", T.toString().c_str());

  EXPECT_TRUE(T.insert(30));
  EXPECT_STREQ("R35 \nR25 B50 \nB20 B30 \nR15 \n", T.toString().c_str());

  EXPECT_TRUE(T.insert(90));
  EXPECT_STREQ("R35 \nR25 B90 \nB20 B30 R50 \nR15 \n", T.toString().c_str());

  EXPECT_TRUE(T.insert(32));
  EXPECT_STREQ("R35 \nR25 B90 \nB20 B32 R50 \nR15 R30 \n", T.toString().c_str());

  EXPECT_TRUE(T.insert(33));
  EXPECT_STREQ("R32 \nB25 B35 \nB20 B30 B33 B90 \nR15 R50 \n", T.toString().c_str());
}

