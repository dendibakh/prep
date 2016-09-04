#include <gtest/gtest.h>
#include <vector>
#include <map>
#include <iostream>
#include <string>
#include <stack>
#include <queue>

struct Edge
{
  int from;
  int to;
};

class Graph
{
  void DFS(std::vector<int>& result, std::vector<bool>& marked, int v);
public:
  Graph(int vertexNumber);
  void addEdge(int from, int to);
  std::vector<int> DFS(int startVertex);
  std::vector<int> IDFS(int startVertex);
  std::vector<int> IBFS(int startVertex);
private:
  std::vector<std::vector<int>> edges;
};

Graph::Graph(int vertexNumber) : edges(vertexNumber)
{
  
}

void Graph::addEdge(int from, int to)
{
  if (from < edges.size() && to < edges.size())
  {
    edges[from].push_back(to);
    edges[to].push_back(from);
  }
  else
  {
    throw std::runtime_error("wrong edge!");
  }
}

std::vector<int> Graph::IDFS(int startVertex)
{
  std::vector<int> retDFS;

  if (startVertex > edges.size() - 1)
    return retDFS;

  std::vector<bool> marked(edges.size(), false);

  std::stack<int> dfs;
  dfs.push(startVertex);

  while (!dfs.empty())
  {
    int current = dfs.top();
    dfs.pop();

    if (!marked[current])
    {
      marked[current] = true;
      retDFS.push_back(current);
 
      for (auto iter = edges[current].rbegin(); iter != edges[current].rend(); ++iter)
      {   
        if (!marked[*iter])
          dfs.push(*iter);
      }
    }
  }
  
  return retDFS;
}

void Graph::DFS(std::vector<int>& result, std::vector<bool>& marked, int v)
{
  marked[v] = true;
  result.push_back(v);
  for (auto w : edges[v])
  {
    if (!marked[w])
    {
      DFS(result, marked, w);
    }
  }
}

std::vector<int> Graph::DFS(int startVertex)
{
  std::vector<int> retDFS;

  if (startVertex > edges.size() - 1)
    return retDFS;

  std::vector<bool> marked(edges.size(), false);

  DFS(retDFS, marked, startVertex);

  return retDFS;
}

std::vector<int> Graph::IBFS(int startVertex)
{
  std::vector<int> retBFS;

  if (startVertex > edges.size() - 1)
    return retBFS;

  std::vector<bool> marked(edges.size(), false);

  marked[startVertex] = true;
  std::queue<int> bfs;
  bfs.push(startVertex);

  while (!bfs.empty())
  {
    int current = bfs.front();
    bfs.pop();
    retBFS.push_back(current);

    for (auto& vert : edges[current])
    {
      if (!marked[vert])
      {
        marked[vert] = true;
        bfs.push(vert);
      }
    }
  }
  
  return retBFS;
}

TEST(Graph, ConstructionTest) 
{
  Graph g(6);

  g.addEdge(0, 1);
  g.addEdge(0, 2);
  g.addEdge(1, 3);
  g.addEdge(2, 3);
  g.addEdge(3, 4);
  g.addEdge(3, 5);
  g.addEdge(4, 5);
  g.addEdge(1, 5);

  std::vector<int> expectedDFS = {0, 1, 3, 2, 4, 5};
  EXPECT_TRUE(expectedDFS == g.DFS(0));
  
  std::vector<int> expectedBFS = {0, 1, 2, 3, 5, 4};
  EXPECT_TRUE(expectedBFS == g.IBFS(0));
   
  for (int i = 0; i < 6; ++i)
    EXPECT_TRUE(g.DFS(i) == g.IDFS(i));

  //for (auto elem : g.IDFS(0))
  //  std::cout << elem << ' ';
}

