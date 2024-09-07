#include "graph.h"

using namespace std;

Graph::Graph() {
}

Graph::~Graph() {
}

void Graph::printGraph() {
  for (auto [vertex, edges] : mAdjList)
  {
    std::cout << vertex << ": [ ";
    for(auto edge:edges)
    {
      std::cout << edge << " ";
    }
    std::cout << "]" << std::endl;
  }
}

bool Graph::addVertex(std::string vertex)
{
  if(mAdjList.count(vertex)==0)
  {
    mAdjList[vertex];
    return true;
  }
  return false;
}

bool Graph::addEdge(std::string vertex1, std::string vertex2)
{
  if(mAdjList.count(vertex1)!=0 && mAdjList.count(vertex2)!=0)
  {
    mAdjList.at(vertex1).insert(vertex2);
    mAdjList.at(vertex2).insert(vertex1);
    return true;
  }
  return false;
}

bool Graph::removeEdge(std::string vertex1, std::string vertex2)
{
  if(mAdjList.count(vertex1)!=0 && mAdjList.count(vertex2)!=0)
  {
    mAdjList.at(vertex1).erase(vertex2);
    mAdjList.at(vertex2).erase(vertex1);
    return true;
  }
  return false;
}

bool Graph::removeVertex(std::string vertex)
{
  if(mAdjList.count(vertex)==0)
  {
    return false;
  }

  for (auto vertices:mAdjList.at(vertex))
  {
    mAdjList.at(vertices).erase(vertex);
  }
  mAdjList.erase(vertex);
  return true;
}

int main() {
  Graph myGraph;
  myGraph.addVertex("A");
  myGraph.addVertex("B");
  myGraph.addVertex("C");
  myGraph.printGraph();
  {
        cout << "\n----- Test: Add New Vertex -----\n";
        Graph g;
        cout << "Before:\n";
        g.printGraph();
        cout << "Adding vertex 'A'.\n";
        bool result = g.addVertex("A");
        cout << "After:\n";
        g.printGraph();
        cout << "EXPECTED: true\n";
        cout << "RETURNED: " << (result ? "true" : "false") << "\n";
        cout << (result == true ? "PASS\n" : "FAIL\n");
    }

    {
        cout << "\n----- Test: Add Duplicate Vertex -----\n";
        Graph g;
        g.addVertex("A");
        cout << "Before:\n";
        g.printGraph();
        cout << "Adding duplicate vertex 'A'.\n";
        bool result = g.addVertex("A");
        cout << "After:\n";
        g.printGraph();
        cout << "EXPECTED: false\n";
        cout << "RETURNED: " << (result ? "true" : "false") << "\n";
        cout << (result == false ? "PASS\n" : "FAIL\n");
    }

    {
        cout << "\n----- Test: Add Multiple Vertices -----\n";
        Graph g;
        cout << "Before:\n";
        g.printGraph();
        cout << "Adding vertices 'A', 'B', duplicate 'A', and duplicate 'B'.\n";
        bool result1 = g.addVertex("A");
        bool result2 = g.addVertex("B");
        bool result3 = g.addVertex("A");
        bool result4 = g.addVertex("B");
        cout << "After:\n";
        g.printGraph();
        cout << "Adding 'A': EXPECTED: true, RETURNED: " << (result1 ? "true" : "false") << "\n";
        cout << "Adding 'B': EXPECTED: true, RETURNED: " << (result2 ? "true" : "false") << "\n";
        cout << "Adding duplicate 'A': EXPECTED: false, RETURNED: " << (result3 ? "true" : "false") << "\n";
        cout << "Adding duplicate 'B': EXPECTED: false, RETURNED: " << (result4 ? "true" : "false") << "\n";
        cout << (result1 && result2 && !result3 && !result4 ? "PASS\n" : "FAIL\n");
    }

    {
        cout << "\n----- Test: Add Empty String Vertex -----\n";
        Graph g;
        cout << "Before:\n";
        g.printGraph();
        cout << "Adding empty string vertex.\n";
        bool result = g.addVertex("");
        cout << "After:\n";
        g.printGraph();
        cout << "EXPECTED: true\n";
        cout << "RETURNED: " << (result ? "true" : "false") << "\n";
        cout << (result == true ? "PASS\n" : "FAIL\n");
    }

{
        cout << "\n----- Test: Add Edge To Empty Graph -----\n";
        Graph g;
        cout << "Before:\n";
        g.printGraph();
        cout << "Adding edge between 'A' and 'B'.\n";
        bool result = g.addEdge("A", "B");
        cout << "After:\n";
        g.printGraph();
        cout << "EXPECTED: false\n";
        cout << "RETURNED: " << (result ? "true" : "false") << "\n";
        cout << (result == false ? "PASS\n" : "FAIL\n");
    }

    {
        cout << "\n---- Test: Add Edge Between Nonexistent Vertices (C & D) ----\n";
        Graph g;
        g.addVertex("A");
        g.addVertex("B");
        cout << "Before:\n";
        g.printGraph();
        cout << "Adding edge between 'C' and 'D'.\n";
        bool result = g.addEdge("C", "D");
        cout << "After:\n";
        g.printGraph();
        cout << "EXPECTED: false\n";
        cout << "RETURNED: " << (result ? "true" : "false") << "\n";
        cout << (result == false ? "PASS\n" : "FAIL\n");
    }

    {
        cout << "\n----- Test: Add Edge Between One Nonexistent Vertex (B) -----\n";
        Graph g;
        g.addVertex("A");
        cout << "Before:\n";
        g.printGraph();
        cout << "Adding edge between 'A' and 'B'.\n";
        bool result = g.addEdge("A", "B");
        cout << "After:\n";
        g.printGraph();
        cout << "EXPECTED: false\n";
        cout << "RETURNED: " << (result ? "true" : "false") << "\n";
        cout << (result == false ? "PASS\n" : "FAIL\n");
    }

    {
        cout << "\n----- Test: Add Edge Between Existing Vertices (A & B) -----\n";
        Graph g;
        g.addVertex("A");
        g.addVertex("B");
        cout << "Before:\n";
        g.printGraph();
        cout << "Adding edge between 'A' and 'B'.\n";
        bool result = g.addEdge("A", "B");
        cout << "After:\n";
        g.printGraph();
        cout << "EXPECTED: true\n";
        cout << "RETURNED: " << (result ? "true" : "false") << "\n";
        cout << (result == true ? "PASS\n" : "FAIL\n");
    }

    {
        cout << "\n----- Test: Add Duplicate Edge (A & B) -----\n";
        Graph g;
        g.addVertex("A");
        g.addVertex("B");
        g.addEdge("A", "B");
        cout << "Before:\n";
        g.printGraph();
        cout << "Adding edge again between 'A' and 'B'.\n";
        bool result = g.addEdge("A", "B");
        cout << "After:\n";
        g.printGraph();
        cout << "EXPECTED: true\n";  // Adjusted based on your tests. If duplicates are not allowed, this should be "false"
        cout << "RETURNED: " << (result ? "true" : "false") << "\n";
        cout << (result == true ? "PASS\n" : "FAIL\n");
    }

  {
        cout << "\n----- Test: Remove Edge From Empty Graph -----\n";
        Graph g;
        cout << "Before:\n";
        g.printGraph();
        cout << "Removing edge between 'A' and 'B'.\n";
        bool result = g.removeEdge("A", "B");
        cout << "After:\n";
        g.printGraph();
        cout << "EXPECTED: false\n";
        cout << "RETURNED: " << (result ? "true" : "false") << "\n";
        cout << (result == false ? "PASS\n" : "FAIL\n");
    }

    {
        cout << "\n----- Test: Remove Edge Between Nonexistent Vertices -----\n";
        Graph g;
        g.addVertex("A");
        g.addVertex("B");
        cout << "Before:\n";
        g.printGraph();
        cout << "Removing edge between 'C' and 'D'.\n";
        bool result = g.removeEdge("C", "D");
        cout << "After:\n";
        g.printGraph();
        cout << "EXPECTED: false\n";
        cout << "RETURNED: " << (result ? "true" : "false") << "\n";
        cout << (result == false ? "PASS\n" : "FAIL\n");
    }

    {
        cout << "\n----- Test: Remove NonExistent Edge Between Existing Vertices -----\n";
        Graph g;
        g.addVertex("A");
        g.addVertex("B");
        cout << "Before:\n";
        g.printGraph();
        cout << "Removing edge between 'A' and 'B'.\n";
        bool result = g.removeEdge("A", "B");
        cout << "After:\n";
        g.printGraph();
        cout << "EXPECTED: true\n";
        cout << "RETURNED: " << (result ? "true" : "false") << "\n";
        cout << (result == true ? "PASS\n" : "FAIL\n");
    }

    {
        cout << "\n----- Test: Remove Existing Edge -----\n";
        Graph g;
        g.addVertex("A");
        g.addVertex("B");
        g.addEdge("A", "B");
        cout << "Before first removal:\n";
        g.printGraph();
        cout << "Removing edge between 'A' and 'B'.\n";
        bool result1 = g.removeEdge("A", "B");
        cout << "After first removal:\n";
        g.printGraph();
        cout << "Removing edge again between 'A' and 'B'.\n";
        bool result2 = g.removeEdge("A", "B");
        cout << "After second removal:\n";
        g.printGraph();
        cout << "First removal: EXPECTED: true, RETURNED: " << (result1 ? "true" : "false") << "\n";
        cout << "Second removal: EXPECTED: true, RETURNED: " << (result2 ? "true" : "false") << "\n";
        cout << ((result1 && result2) == true ? "PASS\n" : "FAIL\n");
    }

    {
        cout << "\n----- Test: Remove Edge After Vertex Removal -----\n";
        Graph g;
        g.addVertex("A");
        g.addVertex("B");
        g.addEdge("A", "B");
        g.removeEdge("A", "B");
        cout << "Before second removal:\n";
        g.printGraph();
        cout << "Removing edge again between 'A' and 'B'.\n";
        bool result = g.removeEdge("A", "B");
        cout << "After second removal:\n";
        g.printGraph();
        cout << "EXPECTED: true\n";
        cout << "RETURNED: " << (result ? "true" : "false") << "\n";
        cout << (result == true ? "PASS\n" : "FAIL\n");
    }

  {
        cout << "\n----- Test: Remove NonExistent Vertex -----\n";
        Graph g;
        g.addVertex("A");
        g.addVertex("B");
        cout << "Before:\n";
        g.printGraph();
        cout << "Removing vertex 'C'.\n";
        bool result = g.removeVertex("C");
        cout << "After:\n";
        g.printGraph();
        cout << "EXPECTED: false\n";
        cout << "RETURNED: " << (result ? "true" : "false") << "\n";
        cout << (result == false ? "PASS\n" : "FAIL\n");
    }

    {
        cout << "\n----- Test: Remove Vertex With No Edges -----\n";
        Graph g;
        g.addVertex("A");
        cout << "Before:\n";
        g.printGraph();
        cout << "Removing vertex 'A'.\n";
        bool result = g.removeVertex("A");
        cout << "After:\n";
        g.printGraph();
        cout << "EXPECTED: true\n";
        cout << "RETURNED: " << (result ? "true" : "false") << "\n";
        cout << (result == true ? "PASS\n" : "FAIL\n");
    }

    {
        cout << "\n----- Test: Remove Vertex With Multiple Edges -----\n";
        Graph g;
        g.addVertex("A");
        g.addVertex("B");
        g.addVertex("C");
        g.addEdge("A", "B");
        g.addEdge("A", "C");
        cout << "Before:\n";
        g.printGraph();
        cout << "Removing vertex 'A'.\n";
        bool result1 = g.removeVertex("A");
        bool result2 = g.removeVertex("A");  // Trying again
        cout << "After:\n";
        g.printGraph();
        cout << "EXPECTED 1st Removal: true\n";
        cout << "RETURNED 1st Removal: " << (result1 ? "true" : "false") << "\n";
        cout << "EXPECTED 2nd Removal: false\n";
        cout << "RETURNED 2nd Removal: " << (result2 ? "true" : "false") << "\n";
        cout << (result1 && !result2 ? "PASS\n" : "FAIL\n");
    }

    {
        cout << "\n----- Test: Remove Vertex And Check Edges -----\n";
        Graph g;
        g.addVertex("A");
        g.addVertex("B");
        g.addVertex("C");
        g.addEdge("A", "B");
        g.addEdge("A", "C");
        cout << "Before:\n";
        g.printGraph();
        cout << "Removing vertex 'A'.\n";
        g.removeVertex("A");
        bool result1 = g.removeEdge("A", "B");
        bool result2 = g.removeEdge("A", "C");
        cout << "After:\n";
        g.printGraph();
        cout << "EXPECTED Edges Removal: false, false\n";
        cout << "RETURNED Edges Removal: " << (result1 ? "true" : "false") << ", " << (result2 ? "true" : "false") << "\n";
        cout << (!result1 && !result2 ? "PASS\n" : "FAIL\n");
    }

    {
        cout << "\n----- Test: Remove Vertex And Update Graph -----\n";
        Graph g;
        g.addVertex("A");
        g.addVertex("B");
        g.addEdge("A", "B");
        cout << "Before:\n";
        g.printGraph();
        cout << "Removing vertex 'A' and re-adding it, then re-adding edge A-B.\n";
        g.removeVertex("A");
        g.addVertex("A");
        bool result = g.addEdge("A", "B");
        cout << "After:\n";
        g.printGraph();
        cout << "EXPECTED Edge Addition: true\n";
        cout << "RETURNED Edge Addition: " << (result ? "true" : "false") << "\n";
        cout << (result ? "PASS\n" : "FAIL\n");
    }
  return 0;
}