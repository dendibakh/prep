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
  int weight;
};

class Graph
{
public:
  Graph(int vertexNumber);
  void addEdge(int from, int to, int weight);
  std::vector<std::vector<Edge>> edges;
};

Graph::Graph(int vertexNumber) : edges(vertexNumber)
{
  
}

class SP
{
  void relaxEdge(Edge& e);
public:
  SP(Graph& g, int source);

  Graph& g;
  std::map<int, int> weight;
  std::map<int, int> vertex;
};

SP::SP(Graph& g, int source) : g(g)
{
  weight.insert(std::make_pair(0, source));
  vertex.insert(std::make_pair(source, 0));

  for (int i = 1; i < 6; ++i)
  {
    weight.insert(std::make_pair(999, i));
    vertex.insert(std::make_pair(i, 999));
  }

  while (!weight.empty())
  {
    int nextClosest = weight.begin()->second;
    std::cout << nextClosest << '\n'; 
    weight.erase(weight.begin());
    //vertex.erase(nextClosest);
    for (auto& w : g.edges[nextClosest])
      relaxEdge(w);
  }
}

void SP::relaxEdge(Edge& e)
{
  std::cout << "edge " << e.from << ' ' << e.to << ' ' << e.weight << '\n'; 
  int newFoundWeight = vertex[e.from] + e.weight;
  if (vertex[e.to] > newFoundWeight)
  {
    // relax
    std::cout << "new weight " << e.to << ' ' << newFoundWeight << '\n'; 
    weight.erase(vertex[e.to]);
    vertex[e.to] = newFoundWeight;
    weight.insert(std::make_pair(newFoundWeight, e.to));
  }
}

void Graph::addEdge(int from, int to, int weight)
{
  if (from < static_cast<int>(edges.size()) && to < static_cast<int>(edges.size()))
  {
    edges[from].push_back(Edge{from, to, weight});
    //edges[to].push_back(from);
  }
  else
  {
    throw std::runtime_error("wrong edge!");
  }
}

TEST(Graph, ConstructionTest) 
{
  Graph g(6);

  g.addEdge(0, 1, 1);
  g.addEdge(0, 2, 3);
  g.addEdge(1, 3, 5);
  g.addEdge(2, 3, 4);
  g.addEdge(3, 4, 2);
  g.addEdge(2, 4, 2);
  g.addEdge(4, 5, 7);
  g.addEdge(1, 5, 20);
  g.addEdge(4, 1, 1);
 
  SP sp(g, 0);
  EXPECT_EQ(0, sp.vertex[0]);
  EXPECT_EQ(1, sp.vertex[1]);
  EXPECT_EQ(3, sp.vertex[2]);
  EXPECT_EQ(6, sp.vertex[3]);
  EXPECT_EQ(5, sp.vertex[4]);
  EXPECT_EQ(12, sp.vertex[5]);
}

