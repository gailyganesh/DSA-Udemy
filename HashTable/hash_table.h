#pragma once

#include "hash_table_LL_node.h"
#include <iostream>
#include <unordered_map> //C++ implementation of the HashTable
#include <vector>

class HashTable {
private:
  static const int SIZE = 7;
  HashTableLLNode *mDataMap[HashTable::SIZE];

public:
  HashTable();
  ~HashTable();
  void printTable();
  int hash(std::string key);
  void set(std::string key, int value);
  int get(std::string key);
  std::vector<std::string> keys();

  // interview question: find if both vector have same element
  bool itemInCommon(std::vector<int> vec1, std::vector<int> vec2);
};