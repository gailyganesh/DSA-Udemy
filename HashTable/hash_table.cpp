#include "hash_table.h"
#include <algorithm>
#include <string>

using namespace std;

HashTable::HashTable() {
  for (int i = 0; i < HashTable::SIZE; i++) {
    mDataMap[i] = nullptr;
  }
}

HashTable::~HashTable() {
  for (int i = 0; i < HashTable::SIZE; i++) {
    auto head = mDataMap[i];
    auto temp = head;
    while (head) {
      head = head->next;
      delete temp;
      temp = head;
    }
  }
}

void HashTable::printTable() {
  for (int i = 0; i < HashTable::SIZE; i++) {
    std::cout << i << ": [";
    auto temp = mDataMap[i];
    while (temp) {
      std::cout << "{" << temp->key << ", " << temp->value << "}";
      temp = temp->next;
    }
    std::cout << "]" << std::endl;
  }
}

int HashTable::hash(std::string key) {
  int hash = 0;
  for (int i = 0; i < key.size(); i++) {
    int ascii_value = int(key[i]);
    hash = (hash + ascii_value * 23) % HashTable::SIZE;
  }
  return hash;
}

void HashTable::set(std::string key, int value) {
  int index = hash(key);
  auto newNode = new HashTableLLNode(key, value);
  newNode->next = mDataMap[index];
  mDataMap[index] = newNode;
}

int HashTable::get(std::string key) {
  int index = hash(key);
  auto temp = mDataMap[index];
  while (temp) {
    if (temp->key == key)
      return temp->value;
    temp = temp->next;
  }
  return INT_MIN;
}

std::vector<std::string> HashTable::keys() {
  std::vector<std::string> allkeys;
  for (int i = 0; i < HashTable::SIZE; i++) {
    auto temp = mDataMap[i];
    while (temp) {
      allkeys.push_back(temp->key);
      temp = temp->next;
    }
  }
  return allkeys;
}

bool HashTable::itemInCommon(std::vector<int> vec1, std::vector<int> vec2) {
  std::unordered_map<int, bool> myMap;
  for (auto i : vec1) {
    myMap.insert({i, true});
  }
  for (auto i : vec2) {
    if (myMap[i])
      return true;
  }
}

int main() {
  {
    cout << "\n----- Test: Set Single Value -----\n";
    HashTable ht;
    ht.set("key1", 42);
    int value = ht.get("key1");
    cout << "Inserting and getting a single value - EXPECTED: 42\n";
    cout << (value == 42 ? "PASS\n" : "FAIL\n");
  }

  {
    cout << "\n----- Test: Set Multiple Values -----\n";
    HashTable ht;
    ht.set("key1", 42);
    ht.set("key2", 24);
    int value1 = ht.get("key1");
    int value2 = ht.get("key2");
    cout << "Inserting and getting multiple values - EXPECTED: 42, 24\n";
    cout << ((value1 == 42 && value2 == 24) ? "PASS\n" : "FAIL\n");
  }

  {
    cout << "\n----- Test: Set Collision Values -----\n";
    HashTable ht;
    ht.set("key1", 42);
    ht.set("collision", 23);
    int value1 = ht.get("key1");
    int value2 = ht.get("collision");
    cout << "Inserting and getting collision values - EXPECTED: 42, 23\n";
    cout << ((value1 == 42 && value2 == 23) ? "PASS\n" : "FAIL\n");
  }

  {
    cout << "\n----- Test: Set Large Number of Values -----\n";
    HashTable ht;
    bool pass = true;
    for (int i = 0; i < 100; i++) {
      ht.set("key" + to_string(i), i);
      if (ht.get("key" + to_string(i)) != i) {
        pass = false;
        break;
      }
    }
    cout << "Inserting and getting a large number of values - EXPECTED: 0 to "
            "99\n";
    cout << (pass ? "PASS\n" : "FAIL\n");
  }

  {
    cout << "\n----- Test: Get From Empty Table -----\n";
    HashTable ht;
    int value = ht.get("non_existent_key");
    cout << "Getting value for a non-existent key - EXPECTED: 0\n";
    cout << (value == INT_MIN ? "PASS\n" : "FAIL\n");
  }

  {
    cout << "\n----- Test: Get Single Value -----\n";
    HashTable ht;
    ht.set("key1", 42);
    int value = ht.get("key1");
    cout << "Getting value for key1 - EXPECTED: 42\n";
    cout << (value == 42 ? "PASS\n" : "FAIL\n");
  }

  {
    cout << "\n----- Test: Get Multiple Values -----\n";
    HashTable ht;
    ht.set("key1", 42);
    ht.set("key2", 24);
    int value1 = ht.get("key1");
    int value2 = ht.get("key2");
    cout << "Getting values for key1 and key2 - EXPECTED: 42, 24\n";
    cout << ((value1 == 42 && value2 == 24) ? "PASS\n" : "FAIL\n");
  }

  {
    cout << "\n----- Test: Get Collision Values -----\n";
    HashTable ht;
    ht.set("key1", 42);
    ht.set("collision", 23);
    int value1 = ht.get("key1");
    int value2 = ht.get("collision");
    cout << "Getting values for keys with collision - EXPECTED: 42, 23\n";
    cout << ((value1 == 42 && value2 == 23) ? "PASS\n" : "FAIL\n");
  }

  {
    cout << "\n----- Test: Get Large Number of Values -----\n";
    HashTable ht;
    for (int i = 0; i < 100; i++) {
      ht.set("key" + to_string(i), i);
    }
    bool pass = true;
    for (int i = 0; i < 100; i++) {
      if (ht.get("key" + to_string(i)) != i) {
        pass = false;
        break;
      }
    }
    cout << "Getting a large number of values - EXPECTED: 0 to 99\n";
    cout << (pass ? "PASS\n" : "FAIL\n");
  }

  {
    cout << "\n----- Test: Keys From Empty Table -----\n";
    HashTable ht;
    vector<string> expectedKeys;
    vector<string> actualKeys = ht.keys();
    cout << "Retrieving keys from an empty table - EXPECTED: 0 keys\n";
    cout << (actualKeys == expectedKeys ? "PASS\n" : "FAIL\n");
  }

  {
    cout << "\n----- Test: Keys Single Value -----\n";
    HashTable ht;
    ht.set("key1", 42);
    vector<string> expectedKeys{"key1"};
    vector<string> actualKeys = ht.keys();
    cout << "Retrieving a single key - EXPECTED: key1\n";
    cout << (actualKeys == expectedKeys ? "PASS\n" : "FAIL\n");
  }

  {
    cout << "\n----- Test: Keys Multiple Values -----\n";
    HashTable ht;
    ht.set("key1", 42);
    ht.set("key2", 24);
    vector<string> expectedKeys{"key1", "key2"};
    vector<string> actualKeys = ht.keys();
    std::sort(actualKeys.begin(), actualKeys.end());
    cout << "Retrieving multiple keys - EXPECTED: key1, key2\n";
    cout << (actualKeys == expectedKeys ? "PASS\n" : "FAIL\n");
  }

  {
    cout << "\n----- Test: Keys Collision Values -----\n";
    HashTable ht;
    ht.set("key1", 42);
    ht.set("collision", 23);
    vector<string> expectedKeys{"collision", "key1"};
    vector<string> actualKeys = ht.keys();
    std::sort(actualKeys.begin(), actualKeys.end());
    cout << "Retrieving keys with collision - EXPECTED: key1, collision\n";
    cout << (actualKeys == expectedKeys ? "PASS\n" : "FAIL\n");
  }

  {
    cout << "\n----- Test: Keys Large Number of Values -----\n";
    HashTable ht;
    vector<string> expectedKeys;
    for (int i = 0; i < 100; i++) {
      string key = "key" + std::to_string(i);
      ht.set(key, i);
      expectedKeys.push_back(key);
    }
    vector<string> actualKeys = ht.keys();
    sort(actualKeys.begin(), actualKeys.end());
    sort(expectedKeys.begin(), expectedKeys.end());
    cout << "Retrieving a large number of keys - EXPECTED: key0 to key99\n";
    cout << (actualKeys == expectedKeys ? "PASS\n" : "FAIL\n");
  }
}