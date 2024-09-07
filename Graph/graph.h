#pragma once

#include <iostream>
#include <unordered_map> //C++ implementation of the Graph
#include <unordered_set>

class Graph {
private:
  std::unordered_map<std::string, std::unordered_set<std::string>> mAdjList;

public:
  Graph();
  ~Graph();
  void printGraph();
  bool addVertex(std::string vertex);
  bool addEdge(std::string vertex1, std::string vertex2);
  bool removeEdge(std::string vertex1, std::string vertex2);
  bool removeVertex(std::string vertex);
};