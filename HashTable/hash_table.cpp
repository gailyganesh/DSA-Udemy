#include "hash_table.h"
#include <algorithm>
#include <string>
#include <unordered_set>

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

/************************ leetcode problems ***************************************/
bool itemInCommon(std::vector<int> vec1, std::vector<int> vec2) {
  std::unordered_map<int, bool> myMap;
  for (auto i : vec1) {
    myMap.insert({i, true});
  }
  for (auto i : vec2) {
    if (myMap[i])
      return true;
  }
  return false;
}

vector<int> findDuplicates(const vector<int>& nums) {
  std::unordered_map<int,bool>mymap;
  std::unordered_map<int,bool>mymap2;

  std::vector<int> output;
  for (auto i:nums) {
    if(!mymap[i]) mymap[i]=true;
    else if(!mymap2[i]) mymap2[i]=true;
  }
  for(auto pair:mymap2)
  {
    output.push_back(pair.first);
  }
  return output;
}

char firstNonRepeatingChar(const string& input_string) {
  std::unordered_map<char,int> charcount;
  for(auto ch:input_string)
  {
    charcount[ch] += 1;
  }
  for(auto ch:input_string)
  {
    if(charcount[ch]==1) return ch;
  }
  return '\0';
}

vector<vector<string>> groupAnagrams(const vector<string>& strings) {
  std::unordered_map<std::string, std::vector<std::string>> anagramsMap;
  for(auto str:strings)
  {
    std::string temp=str;
    std::sort(str.begin(),str.end());
    anagramsMap[str].push_back(temp);
  }
  vector<vector<string>>output;
  for(auto pair:anagramsMap)
  {
    output.push_back(pair.second);
  }
  return output;
}

vector<int> twoSum(const vector<int>& nums, int target) {
    unordered_map<int, int> numToIndex;
    
    for (int i = 0; i < nums.size(); ++i) {
        int complement = target - nums[i];
        
        // Check if the complement exists in the map
        if (numToIndex.find(complement) != numToIndex.end()) {
            // Return indices of the two numbers
            return {numToIndex[complement], i};
        }
        
        // Store the current number's index
        numToIndex[nums[i]] = i;
    }
    
    // Return an empty vector if no solution is found
    return {};
}

vector<int> subarraySum(const vector<int>& nums, int target) {
	//   +=====================================================+
	//   |                 WRITE YOUR CODE HERE                |
	//   | Description:                                        |
	//   | - This function finds a subarray in 'nums' that     |
	//   |   sums up to the given 'target'.                    |
	//   | - It uses an unordered_map for quick look-up.       |
	//   | - It returns the indices of the start and end       |
	//   |   elements of the subarray.                         |
	//   |                                                     |
	//   | Return type: vector<int>                            |
	//   |                                                     |
	//   | Tips:                                               |
	//   | - 'sumIndex' stores cumulative sums and their       |
	//   |   indices.                                          |
	//   | - 'currentSum' keeps track of the sum up to index i.|
	//   | - Use 'find' method for quick look-up in map.       |
	//   | - Check output from Test.cpp in "User logs".        |
	//   +=====================================================+
	
  unordered_map<int, int> sumIndex;
    sumIndex[0] = -1;
    int currentSum = 0;
 
    for (int i = 0; i < nums.size(); i++) {
        currentSum += nums[i];
        if (sumIndex.find(currentSum - target) != sumIndex.end()) {
            return {sumIndex[currentSum - target] + 1, i};
        }
        sumIndex[currentSum] = i;
    }
 
    return {};

}

vector<int> removeDuplicates(const vector<int>& myList) {
    //   +=====================================================+
    //   |                 WRITE YOUR CODE HERE                |
    //   | Description:                                        |
    //   | - This function removes duplicate integers from a   |
    //   |   given vector 'myList'.                            |
    //   | - It uses an unordered_set for quick look-up and    |
    //   |   elimination of duplicates.                        |
    //   | - Returns a vector of unique integers.              |
    //   |                                                     |
    //   | Return type: vector<int>                            |
    //   |                                                     |
    //   | Tips:                                               |
    //   | - 'uniqueSet' stores unique numbers from 'myList'.  |
    //   | - Use 'begin()' and 'end()' to copy elements back   |
    //   |   to a vector.                                      |
    //   | - Check output from Test.cpp in "User logs".        |
    //   +=====================================================+
  unordered_set<int> uniqueSet(myList.begin(), myList.end());
  return vector<int>(uniqueSet.begin(), uniqueSet.end());

}

bool hasUniqueChars(const string& str) {
    //   +=====================================================+
    //   |                 WRITE YOUR CODE HERE                |
    //   | Description:                                        |
    //   | - This function checks if a string 'str' has unique |
    //   |   characters.                                       |
    //   | - It uses an unordered_set for quick look-up.       |
    //   | - It returns a boolean value.                       |
    //   |                                                     |
    //   | Return type: bool                                   |
    //   |                                                     |
    //   | Tips:                                               |
    //   | - 'charSet' stores characters we've seen.           |
    //   | - Loop through 'str' to populate 'charSet'.         |
    //   | - Use 'find' method for quick look-up in set.       |
    //   | - If a duplicate is found, return false.            |
    //   | - Check output from Test.cpp in "User logs".        |
    //   +=====================================================+
    std::unordered_set<char> myset;
  for(auto num:str)
  {
    if(myset.find(num)==myset.end())
      myset.insert(num);
    else return false;
  }
  return true;
}

vector<vector<int>> findPairs(const vector<int>& arr1, const vector<int>& arr2, int target) {
    //   +=========================================================+
    //   |                 WRITE YOUR CODE HERE                    |
    //   | Description:                                            |
    //   | - This function finds all pairs of integers from        |
    //   |   'arr1' and 'arr2' that sum up to 'target'.            |
    //   | - It uses an unordered_set for quick look-up.           |
    //   | - It returns a 2D vector containing the pairs.          |
    //   |                                                         |
    //   | Return type: vector<vector<int>>                        |
    //   |                                                         |
    //   | Tips:                                                   |
    //   | - 'mySet' stores numbers from 'arr1'.                   |
    //   | - 'pairs' will store the pairs that meet the target.    |
    //   | - Loop through 'arr1' to populate 'mySet'.              |
    //   | - Loop through 'arr2' to find pairs.                    |
    //   | - Use 'find' method for quick look-up in set.           |
    //   | - Check output from Test.cpp in "User logs".            |
    //   +=========================================================+

    std::unordered_set<int>set1(arr1.begin(), arr1.end());
    vector<vector<int>> output;
    for(auto value:arr2)
    {
        if(set1.find(target-value)!=set1.end())
        {
          output.push_back({target-value,value});
        }
    }
    return output;
}

int longestConsecutiveSequence(const vector<int>& nums) {
    //   +=====================================================+
    //   |                 WRITE YOUR CODE HERE                |
    //   | Description:                                        |
    //   | - This function finds the longest consecutive       |
    //   |   sequence of integers in a given array.            |
    //   | - It uses an unordered_set for quick look-up.       |
    //   | - Loop through each unique number in the set.       |
    //   | - For each number, check its sequence length.       |
    //   | - Update 'longestStreak' if a longer sequence is    |
    //   |   found.                                            |
    //   |                                                     |
    //   | Return type: int                                    |
    //   |                                                     |
    //   | Tips:                                               |
    //   | - 'numSet' stores unique numbers from 'nums'.       |
    //   | - 'longestStreak' keeps track of the longest        |
    //   |   sequence found so far.                            |
    //   | - Use 'find' method for quick look-up in set.       |
    //   | - Check output from Test.cpp in "User logs".        |
    //   +=====================================================+
    std::unordered_set<int> myset(nums.begin(), nums.end());
    int longest=0;
    for(auto num:myset)
    {
      int temp=num;
      int localLongest=0;
      while(myset.find(temp++)!=myset.end())
      {
        localLongest+=1;
      }
      if(localLongest>longest)longest=localLongest;
    }
    return longest;
}

/***************************** Helper functions ***********************************************/
auto printVector = [](const vector<int>& v) {
        cout << "(";
        for(int i = 0; i < v.size(); i++) {
            cout << v[i];
            if (i < v.size() - 1) cout << ", ";
        }
        cout << ")";
    };

void printGroups(const vector<vector<string>>& groups) {
    cout << "{ ";
    for (const auto& group : groups) {
        cout << "( ";
        for (const string& str : group) {
            cout << str << " ";
        }
        cout << ") ";
    }
    cout << "}\n";
}

// Helper to print a vector
string vecToString(const vector<int>& vec) {
    string str = "[";
    for (size_t i = 0; i < vec.size(); ++i) {
        str += to_string(vec[i]);
        if (i < vec.size() - 1) {
            str += ", ";
        }
    }
    str += "]";
    return str;
}

void displayResult(bool output, bool expected) {
    cout << "EXPECTED: " << (expected ? "True" : "False") << '\n';
    cout << "RETURNED: " << (output ? "True" : "False") << '\n';
    cout << (output == expected ? "PASS\n" : "FAIL\n");
}

// Helper function to display test result
void displayResult(vector<vector<int>> output, size_t expected,
                   vector<int> arr1, vector<int> arr2, int target) {
    cout << "arr1: ";
    for (int num : arr1) cout << num << " ";
    cout << '\n';
    cout << "arr2: ";
    for (int num : arr2) cout << num << " ";
    cout << '\n';
    cout << "Target: " << target << '\n';
    cout << "EXPECTED: Pairs found = " << expected << '\n';
    cout << "RETURNED: Pairs found = " << output.size() << '\n';
    cout << (output.size() == expected ? "PASS\n" : "FAIL\n");
}

// Helper function to display test result
void displayResult(vector<int> nums, int expected) {
    cout << "\nInput vector: ";
    for (int num : nums) cout << num << " ";
    cout << "\nEXPECTED: Longest consecutive sequence = " << expected;
    int output = longestConsecutiveSequence(nums);
    cout << "\nRETURNED: Longest consecutive sequence = " << output;
    cout << (output == expected ? "\nPASS\n" : "\nFAIL\n");
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

  {
        cout << "\n----- Test: Has Items In Common -----\n";
        vector<int> vect1 = {1, 2, 3, 4, 5};
        vector<int> vect2 = {5, 6, 7, 8, 9};
        cout << "EXPECTED: True\n";
        cout << "RETURNED: " << (itemInCommon(vect1, vect2) ? "True\n" : "False\n");
        cout << (itemInCommon(vect1, vect2) ? "PASS\n" : "FAIL\n");
    }

    {
        cout << "\n----- Test: No Items In Common -----\n";
        vector<int> vect1 = {1, 2, 3, 4, 5};
        vector<int> vect2 = {6, 7, 8, 9, 10};
        cout << "EXPECTED: False\n";
        cout << "RETURNED: " << (itemInCommon(vect1, vect2) ? "True\n" : "False\n");
        cout << (!itemInCommon(vect1, vect2) ? "PASS\n" : "FAIL\n");
    }

    {
        cout << "\n----- Test: Both Vectors Empty -----\n";
        vector<int> vect1 = {};
        vector<int> vect2 = {};
        cout << "EXPECTED: False\n";
        cout << "RETURNED: " << (itemInCommon(vect1, vect2) ? "True\n" : "False\n");
        cout << (!itemInCommon(vect1, vect2) ? "PASS\n" : "FAIL\n");
    }

    {
        cout << "\n----- Test: One Vector Empty -----\n";
        vector<int> vect1 = {1, 2, 3, 4, 5};
        vector<int> vect2 = {};
        cout << "EXPECTED: False\n";
        cout << "RETURNED: " << (itemInCommon(vect1, vect2) ? "True\n" : "False\n");
        cout << (!itemInCommon(vect1, vect2) ? "PASS\n" : "FAIL\n");
    }

  {
        cout << "\n----- Test: No Duplicates -----\n";
        vector<int> nums = {1, 2, 3, 4, 5};
        vector<int> expected = {};
        vector<int> result = findDuplicates(nums);
        cout << "EXPECTED: No Duplicates\n";
        cout << "RETURNED: ";
        printVector(result);
        cout << "\n";
        cout << (result == expected ? "PASS\n" : "FAIL\n");
    }

    {
        cout << "\n----- Test: Some Duplicates -----\n";
        vector<int> nums = {1, 2, 3, 2, 1, 4, 5, 6, 5};
        vector<int> expected = {1, 2, 5};
        vector<int> result = findDuplicates(nums);
        sort(result.begin(), result.end());
        cout << "EXPECTED: Has Duplicates: ";
        printVector(expected);
        cout << "\n";
        cout << "RETURNED: ";
        printVector(result);
        cout << "\n";
        cout << (result == expected ? "PASS\n" : "FAIL\n");
    }

    {
        cout << "\n----- Test: All Duplicates -----\n";
        vector<int> nums = {1, 1, 2, 2, 3, 3};
        vector<int> expected = {1, 2, 3};
        vector<int> result = findDuplicates(nums);
        sort(result.begin(), result.end());
        cout << "EXPECTED: Has Duplicates: (1, 2, 3)\n";
        cout << "RETURNED: ";
        printVector(result);
        cout << "\n";
        cout << (result == expected ? "PASS\n" : "FAIL\n");
    }

    {
        cout << "\n----- Test: Empty Vector -----\n";
        vector<int> nums = {};
        vector<int> expected = {};
        vector<int> result = findDuplicates(nums);
        cout << "EXPECTED: No Duplicates\n";
        cout << "RETURNED: ";
        printVector(result);
        cout << "\n";
        cout << (result == expected ? "PASS\n" : "FAIL\n");
    }

    {
        cout << "\n----- Test: Empty String -----\n";
        string input;
        char result = firstNonRepeatingChar(input);
        cout << "EXPECTED: No non-repeating characters\n";
        cout << "RETURNED: " << (result == '\0' ? "No non-repeating characters" : "Character found") << "\n";
        cout << (result == '\0' ? "PASS\n" : "FAIL\n");
    }

    {
        cout << "\n----- Test: Single Character -----\n";
        string input = "a";
        char result = firstNonRepeatingChar(input);
        cout << "EXPECTED: 'a'\n";
        cout << "RETURNED: '" << result << "'\n";
        cout << (result == 'a' ? "PASS\n" : "FAIL\n");
    }

    {
        cout << "\n----- Test: All Characters Repeat -----\n";
        string input = "aabbcc";
        char result = firstNonRepeatingChar(input);
        cout << "EXPECTED: No non-repeating characters\n";
        cout << "RETURNED: " << (result == '\0' ? "No non-repeating characters" : "Character found") << "\n";
        cout << (result == '\0' ? "PASS\n" : "FAIL\n");
    }

    {
        cout << "\n----- Test: Some Characters Repeat -----\n";
        string input = "aabccde";
        char result = firstNonRepeatingChar(input);
        cout << "EXPECTED: 'b'\n";
        cout << "RETURNED: '" << result << "'\n";
        cout << (result == 'b' ? "PASS\n" : "FAIL\n");
    }

    {
        cout << "\n----- Test: No Characters Repeat -----\n";
        string input = "abcde";
        char result = firstNonRepeatingChar(input);
        cout << "EXPECTED: 'a'\n";
        cout << "RETURNED: '" << result << "'\n";
        cout << (result == 'a' ? "PASS\n" : "FAIL\n");
    }

    {
        cout << "\n----- Test: Empty Input -----\n";
        vector<string> input;
        vector<vector<string>> result = groupAnagrams(input);
        cout << "EXPECTED: No anagrams\n";
        cout << "RETURNED: ";
        printGroups(result);
        cout << (result.empty() ? "PASS\n" : "FAIL\n");
    }

    {
        cout << "\n----- Test: Single Anagram Group -----\n";
        vector<string> input{"listen", "silent", "enlist"};
        vector<vector<string>> result = groupAnagrams(input);
        sort(result[0].begin(), result[0].end());
        sort(input.begin(), input.end());
        cout << "EXPECTED: ";
        printGroups({input});
        cout << "RETURNED: ";
        printGroups(result);
        cout << (result.size() == 1 && result[0] == input ? "PASS\n" : "FAIL\n");
    }

    {
        cout << "\n----- Test: Multiple Anagram Groups -----\n";
        vector<string> input{"listen", "silent", "dog", "god", "evil", "vile"};
        vector<vector<string>> result = groupAnagrams(input);
        for (auto& group : result) {
            sort(group.begin(), group.end());
        }
        sort(result.begin(), result.end());
        vector<vector<string>> expected{
            {"dog", "god"},
            {"evil", "vile"},
            {"listen", "silent"}
        };
        sort(expected.begin(), expected.end());
        cout << "EXPECTED: ";
        printGroups(expected);
        cout << "RETURNED: ";
        printGroups(result);
        cout << (result == expected ? "PASS\n" : "FAIL\n");
    }

    {
        cout << "\n----- Test: No Anagrams -----\n";
        vector<string> input{"cat", "bat", "rat"};
        vector<vector<string>> result = groupAnagrams(input);
        vector<vector<string>> expected;
        for (const string& str : input) {
            expected.push_back({str});
        }
        sort(result.begin(), result.end());
        sort(expected.begin(), expected.end());
        cout << "EXPECTED: ";
        printGroups(expected);
        cout << "RETURNED: ";
        printGroups(result);
        cout << (result == expected ? "PASS\n" : "FAIL\n");
    }

    {
        cout << "\n----- Test: Empty Input -----\n";
        vector<int> nums;
        int target = 10;
        vector<int> result = twoSum(nums, target);
        cout << "EXPECTED: No two sum solution\n";
        cout << "RETURNED: " << (result.empty() ? "No solution" : "Has solution") << "\n";
        cout << (result.empty() ? "PASS\n" : "FAIL\n");
    }

    {
        cout << "\n----- Test: Single Element -----\n";
        vector<int> nums{42};
        int target = 42;
        vector<int> result = twoSum(nums, target);
        cout << "EXPECTED: No two sum solution\n";
        cout << "RETURNED: " << (result.empty() ? "No solution" : "Has solution") << "\n";
        cout << (result.empty() ? "PASS\n" : "FAIL\n");
    }

    {
        cout << "\n----- Test: Two Elements -----\n";
        vector<int> nums{3, 4};
        int target = 7;
        vector<int> result = twoSum(nums, target);
        vector<int> expected{0, 1};
        cout << "EXPECTED: Indices (0, 1)\n";
        cout << "RETURNED: Indices (" << (result.empty() ? "" : to_string(result[0])) << ", " 
             << (result.empty() ? "" : to_string(result[1])) << ")\n";
        cout << (result == expected ? "PASS\n" : "FAIL\n");
    }

    {
        cout << "\n----- Test: Multiple Elements -----\n";
        vector<int> nums{1, 3, 4, 2, 5};
        int target = 6;
        vector<int> result = twoSum(nums, target);
        vector<int> expected{2, 3};
        cout << "EXPECTED: Indices (2, 3)\n";
        cout << "RETURNED: Indices (" << (result.empty() ? "" : to_string(result[0])) << ", " 
             << (result.empty() ? "" : to_string(result[1])) << ")\n";
        cout << (result == expected ? "PASS\n" : "FAIL\n");
    }

    {
        cout << "\n----- Test: No Match -----\n";
        vector<int> nums{10, 20, 30, 40};
        int target = 100;
        vector<int> result = twoSum(nums, target);
        cout << "EXPECTED: No two sum solution\n";
        cout << "RETURNED: " << (result.empty() ? "No solution" : "Has solution") << "\n";
        cout << (result.empty() ? "PASS\n" : "FAIL\n");
    }

    {
        cout << "\n----- Test: With Duplicates -----\n";
        vector<int> nums{3, 3, 4, 4};
        int target = 6;
        vector<int> result = twoSum(nums, target);
        vector<int> expected{0, 1};
        cout << "EXPECTED: Indices (0, 1)\n";
        cout << "RETURNED: Indices (" << (result.empty() ? "" : to_string(result[0])) << ", " 
             << (result.empty() ? "" : to_string(result[1])) << ")\n";
        cout << (result == expected ? "PASS\n" : "FAIL\n");
    }

    {
        cout << "\n----- Test: Empty Input -----\n";
        vector<int> nums;
        int target = 10;
        vector<int> result = subarraySum(nums, target);
        cout << "EXPECTED: No solution\n";
        cout << "RETURNED: " << (result.empty() ? "No solution" : "Has solution") << "\n";
        cout << (result.empty() ? "PASS\n" : "FAIL\n");
    }

    {
        cout << "\n----- Test: No Subarray Sum -----\n";
        vector<int> nums{1, 2, 3, 4, 5};
        int target = 100;
        vector<int> result = subarraySum(nums, target);
        cout << "EXPECTED: No solution\n";
        cout << "RETURNED: " << (result.empty() ? "No solution" : "Has solution") << "\n";
        cout << (result.empty() ? "PASS\n" : "FAIL\n");
    }

    {
        cout << "\n----- Test: Entire Array -----\n";
        vector<int> nums{3, 2, 5};
        int target = 10;
        vector<int> result = subarraySum(nums, target);
        vector<int> expected{0, 2};
        cout << "EXPECTED: Indices (0, 2)\n";
        cout << "RETURNED: Indices (" << (result.empty() ? "" : to_string(result[0])) << ", " 
             << (result.empty() ? "" : to_string(result[1])) << ")\n";
        cout << (result == expected ? "PASS\n" : "FAIL\n");
    }

    {
        cout << "\n----- Test: Partial Array -----\n";
        vector<int> nums{1, 2, 3, 4, 5};
        int target = 9;
        vector<int> result = subarraySum(nums, target);
        vector<int> expected{1, 3};
        cout << "EXPECTED: Indices (1, 3)\n";
        cout << "RETURNED: Indices (" << (result.empty() ? "" : to_string(result[0])) << ", " 
             << (result.empty() ? "" : to_string(result[1])) << ")\n";
        cout << (result == expected ? "PASS\n" : "FAIL\n");
    }

    {
        cout << "\n----- Test: Single Element -----\n";
        vector<int> nums{10};
        int target = 10;
        vector<int> result = subarraySum(nums, target);
        vector<int> expected{0, 0};
        cout << "EXPECTED: Indices (0, 0)\n";
        cout << "RETURNED: Indices (" << (result.empty() ? "" : to_string(result[0])) << ", " 
             << (result.empty() ? "" : to_string(result[1])) << ")\n";
        cout << (result == expected ? "PASS\n" : "FAIL\n");
    }

    {
        cout << "\n----- Test: With Negative Numbers -----\n";
        vector<int> nums{1, -2, 3, 4, -5, 6};
        int target = 6;
        vector<int> result = subarraySum(nums, target);
        vector<int> expected{0, 3};
        cout << "EXPECTED: Indices (0, 3)\n";
        cout << "RETURNED: Indices (" << (result.empty() ? "" : to_string(result[0])) << ", " 
             << (result.empty() ? "" : to_string(result[1])) << ")\n";
        cout << (result == expected ? "PASS\n" : "FAIL\n");
    }

    {
        cout << "SETS DO NOT MAINTAIN ORDER SO THE ORDER MAY BE DIFFERENT IN 'BEFORE' & 'AFTER' \n";
        cout << "\n----- Test: Empty Vector -----\n";
        vector<int> input = {};
        cout << "BEFORE: " << vecToString(input) << '\n';
        vector<int> output = removeDuplicates(input);
        cout << "AFTER: " << vecToString(output) << '\n';
        cout << "EXPECTED: Size 0\n";
        cout << "RETURNED: Size " << output.size() << '\n';
        cout << (output.size() == 0 ? "PASS\n" : "FAIL\n");
    }
    {
        cout << "\n----- Test: No Duplicates -----\n";
        vector<int> input = {1, 2, 3, 4};
        cout << "BEFORE: " << vecToString(input) << '\n';
        vector<int> output = removeDuplicates(input);
        cout << "AFTER: " << vecToString(output) << '\n';
        cout << "EXPECTED: Size 4\n";
        cout << "RETURNED: Size " << output.size() << '\n';
        cout << (output.size() == 4 ? "PASS\n" : "FAIL\n");
    }
    {
        cout << "\n----- Test: Duplicates -----\n";
        vector<int> input = {1, 2, 2, 3, 3, 3, 4, 4, 4, 4};
        cout << "BEFORE: " << vecToString(input) << '\n';
        vector<int> output = removeDuplicates(input);
        cout << "AFTER: " << vecToString(output) << '\n';
        cout << "EXPECTED: Size 4\n";
        cout << "RETURNED: Size " << output.size() << '\n';
        cout << (output.size() == 4 ? "PASS\n" : "FAIL\n");
    }
    {
        cout << "\n----- Test: All Same Elements -----\n";
        vector<int> input = {1, 1, 1, 1, 1};
        cout << "BEFORE: " << vecToString(input) << '\n';
        vector<int> output = removeDuplicates(input);
        cout << "AFTER: " << vecToString(output) << '\n';
        cout << "EXPECTED: Size 1\n";
        cout << "RETURNED: Size " << output.size() << '\n';
        cout << (output.size() == 1 ? "PASS\n" : "FAIL\n");
    }
    {
        cout << "\n----- Test: Negative Numbers -----\n";
        vector<int> input = {-1, -2, -2, -3, -3};
        cout << "BEFORE: " << vecToString(input) << '\n';
        vector<int> output = removeDuplicates(input);
        cout << "AFTER: " << vecToString(output) << '\n';
        cout << "EXPECTED: Size 3\n";
        cout << "RETURNED: Size " << output.size() << '\n';
        cout << (output.size() == 3 ? "PASS\n" : "FAIL\n");
    }
    {
        cout << "\n----- Test: Mixed Numbers -----\n";
        vector<int> input = {1, -1, 2, -2, 3, 3};
        cout << "BEFORE: " << vecToString(input) << '\n';
        vector<int> output = removeDuplicates(input);
        cout << "AFTER: " << vecToString(output) << '\n';
        cout << "EXPECTED: Size 5\n";
        cout << "RETURNED: Size " << output.size() << '\n';
        cout << (output.size() == 5 ? "PASS\n" : "FAIL\n");
    }
    {
        cout << "\n----- Test: Large Numbers -----\n";
        vector<int> input = {1000000000, 1000000000, 2000000000};
        cout << "BEFORE: " << vecToString(input) << '\n';
        vector<int> output = removeDuplicates(input);
        cout << "AFTER: " << vecToString(output) << '\n';
        cout << "EXPECTED: Size 2\n";
        cout << "RETURNED: Size " << output.size() << '\n';
        cout << (output.size() == 2 ? "PASS\n" : "FAIL\n");
    }

    {
        cout << "\n----- Test: Empty String -----\n";
        string input = "";
        bool output = hasUniqueChars(input);
        displayResult(output, true);
    }
    {
        cout << "\n----- Test: Unique Chars -----\n";
        string input = "abc";
        bool output = hasUniqueChars(input);
        displayResult(output, true);
    }
    {
        cout << "\n----- Test: Duplicate Chars -----\n";
        string input = "aabc";
        bool output = hasUniqueChars(input);
        displayResult(output, false);
    }
    {
        cout << "\n----- Test: Case Sensitivity -----\n";
        string input = "AbC";
        bool output = hasUniqueChars(input);
        displayResult(output, true);
    }
    {
        cout << "\n----- Test: Numbers & Special Chars -----\n";
        string input = "a1@";
        bool output = hasUniqueChars(input);
        displayResult(output, true);
    }
    {
        cout << "\n----- Test: All Same Chars -----\n";
        string input = "aaaa";
        bool output = hasUniqueChars(input);
        displayResult(output, false);
    }
    {
        cout << "\n----- Test: Whitespace -----\n";
        string input = "a a";
        bool output = hasUniqueChars(input);
        displayResult(output, false);
    }
    {
        cout << "\n----- Test: Mixed Case Duplicates -----\n";
        string input = "Aa";
        bool output = hasUniqueChars(input);
        displayResult(output, true);
    }
    {
        cout << "\n----- Test: Long String -----\n";
        string input(256, 'a');
        bool output = hasUniqueChars(input);
        displayResult(output, false);
    }
    {
        cout << "\n----- Test: Full ASCII -----\n";
        string input;
        for (int i = 0; i < 128; ++i) {
            input += static_cast<char>(i);
        }
        bool output = hasUniqueChars(input);
        displayResult(output, true);
    }

    {
        cout << "\n----- Test: Empty Vectors -----\n";
        vector<int> arr1 = {};
        vector<int> arr2 = {};
        int target = 10;
        vector<vector<int>> output = findPairs(arr1, arr2, target);
        displayResult(output, 0, arr1, arr2, target);
    }
    {
        cout << "\n----- Test: Empty arr1 -----\n";
        vector<int> arr1 = {};
        vector<int> arr2 = {1, 2, 3};
        int target = 10;
        vector<vector<int>> output = findPairs(arr1, arr2, target);
        displayResult(output, 0, arr1, arr2, target);
    }
    {
        cout << "\n----- Test: Empty arr2 -----\n";
        vector<int> arr1 = {1, 2, 3};
        vector<int> arr2 = {};
        int target = 10;
        vector<vector<int>> output = findPairs(arr1, arr2, target);
        displayResult(output, 0, arr1, arr2, target);
    }
    {
        cout << "\n----- Test: No Pairs Found -----\n";
        vector<int> arr1 = {1, 2, 3};
        vector<int> arr2 = {7, 8, 9};
        int target = 6;
        vector<vector<int>> output = findPairs(arr1, arr2, target);
        displayResult(output, 0, arr1, arr2, target);
    }
    {
        cout << "\n----- Test: One Pair Found -----\n";
        vector<int> arr1 = {1, 2, 3};
        vector<int> arr2 = {9, 10, 11};
        int target = 10;
        vector<vector<int>> output = findPairs(arr1, arr2, target);
        displayResult(output, 1, arr1, arr2, target);
    }
    {
        cout << "\n----- Test: Multiple Pairs Found -----\n";
        vector<int> arr1 = {3, 4, 5};
        vector<int> arr2 = {4, 5, 6, 7};
        int target = 10;
        vector<vector<int>> output = findPairs(arr1, arr2, target);
        displayResult(output, 3, arr1, arr2, target);
    }
    {
        cout << "\n----- Test: Duplicate Elements In arr1 -----\n";
        vector<int> arr1 = {1, 2, 2, 3};
        vector<int> arr2 = {7, 8, 9};
        int target = 10;
        vector<vector<int>> output = findPairs(arr1, arr2, target);
        displayResult(output, 3, arr1, arr2, target);
    }
    {
        cout << "\n----- Test: Duplicate Elements In arr2 -----\n";
        vector<int> arr1 = {1, 2, 3};
        vector<int> arr2 = {7, 7, 8, 9};
        int target = 10;
        vector<vector<int>> output = findPairs(arr1, arr2, target);
        displayResult(output, 4, arr1, arr2, target);
    }
    {
        cout << "\n----- Test: Zero As Target -----\n";
        vector<int> arr1 = {-1, 0, 1};
        vector<int> arr2 = {1, 0, -1};
        int target = 0;
        vector<vector<int>> output = findPairs(arr1, arr2, target);
        displayResult(output, 3, arr1, arr2, target);
    }

    {
        cout << "\n----- Test: Empty Vector -----\n";
        vector<int> nums = {};
        displayResult(nums, 0);
    }
    {
        cout << "\n----- Test: Single Element -----\n";
        vector<int> nums = {1};
        displayResult(nums, 1);
    }
    {
        cout << "\n----- Test: All Duplicates -----\n";
        vector<int> nums = {1, 1, 1, 1};
        displayResult(nums, 1);
    }
    {
        cout << "\n----- Test: No Sequence -----\n";
        vector<int> nums = {1, 3, 5, 7};
        displayResult(nums, 1);
    }
    {
        cout << "\n----- Test: Single Sequence -----\n";
        vector<int> nums = {1, 2, 3, 4};
        displayResult(nums, 4);
    }
    {
        cout << "\n----- Test: Multiple Sequences -----\n";
        vector<int> nums = {1, 2, 3, 10, 11, 12};
        displayResult(nums, 3);
    }
    {
        cout << "\n----- Test: Unordered Sequence -----\n";
        vector<int> nums = {4, 2, 3, 1};
        displayResult(nums, 4);
    }
    {
        cout << "\n----- Test: Negative Numbers -----\n";
        vector<int> nums = {0, -1, -2};
        displayResult(nums, 3);
    }
    {
        cout << "\n----- Test: Mixed Numbers -----\n";
        vector<int> nums = {1, 2, 0, -1};
        displayResult(nums, 4);
    }
    return 0;
}