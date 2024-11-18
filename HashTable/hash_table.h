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
  vector<int> findDuplicates(const vector<int>& nums);
  char firstNonRepeatingChar(const string& input_string);
  vector<vector<string>> groupAnagrams(const vector<string>& strings);
  vector<int> twoSum(const vector<int>& nums, int target);
  vector<int> subarraySum(const vector<int>& nums, int target);
  vector<int> removeDuplicates(const vector<int>& myList);
  bool hasUniqueChars(const string& str);
  vector<vector<int>> findPairs(const vector<int>& arr1, const vector<int>& arr2, int target);
  int longestConsecutiveSequence(const vector<int>& nums);
};