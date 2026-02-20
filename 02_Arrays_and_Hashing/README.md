# 📦 Section 02: Arrays & Hashing

> **Units**: 32 | **Pattern**: HashMap for O(1) lookup, Prefix Sum for range queries | **Difficulty**: Easy–Medium

Arrays appear in *every* MAANG interview. Hash maps transform O(n²) brute-force solutions into elegant O(n) approaches. Master this section first — these patterns appear as sub-components of nearly every other topic.

**Core Insight**: When you need to check "have I seen this before?" or "what's the count of X?" — reach for a hash map.

**Problems Covered:**
1. [Two Sum](#problem-1-two-sum)
2. [Contains Duplicate](#problem-2-contains-duplicate)
3. [Group Anagrams](#problem-3-group-anagrams)
4. [Running Sum of 1D Array](#problem-4-running-sum-of-1d-array)
5. [Product of Array Except Self](#problem-5-product-of-array-except-self)

---

## Problem 1: Two Sum

> **LeetCode**: [#1 - Two Sum](https://leetcode.com/problems/two-sum/) | **Difficulty**: 🟢 Easy | **Pattern**: HashMap (Complement Lookup)

### 📝 Problem Statement

Given an array of integers `nums` and an integer `target`, return **indices** of the two numbers such that they add up to `target`. Assume exactly one solution exists. You may not use the same element twice.

**Example:**
```
Input:  nums = [2, 7, 11, 15], target = 9
Output: [0, 1]
Explanation: nums[0] + nums[1] = 2 + 7 = 9
```

```
Input:  nums = [3, 2, 4], target = 6
Output: [1, 2]
```

### 💡 Intuition & Approach

The brute-force checks every pair → O(n²). The key insight: for each number `x`, we need `target - x` (the *complement*). Instead of scanning the whole array each time, store what we've seen in a hash map: `{value → index}`. On each iteration, check if the complement already exists.

**One pass:** As we go left to right, we simultaneously look up and insert. If the complement is in our map, we're done. Otherwise we store the current number.

### 🔍 Hint
> For each element, the answer you're looking for is `target - current`. Store seen elements in a map and look up the complement.

### 🗂️ Pseudocode
```
map = {}  // value → index
for i from 0 to n-1:
    complement = target - nums[i]
    if complement in map:
        return [map[complement], i]
    map[nums[i]] = i
```

### ✅ C++ Solution
See [`two_sum.cpp`](two_sum.cpp)

```cpp
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int, int> seen; // value → index
        for (int i = 0; i < (int)nums.size(); i++) {
            int complement = target - nums[i];
            if (seen.count(complement)) {
                return {seen[complement], i};
            }
            seen[nums[i]] = i;
        }
        return {}; // guaranteed solution exists
    }
};
```

### 📊 Complexity Analysis

| | Complexity | Explanation |
|-|------------|-------------|
| **Time** | O(n) | Single pass through the array |
| **Space** | O(n) | Hash map stores up to n elements |

### ⚠️ Edge Cases
- Array with exactly 2 elements (e.g., `[1, 3]`, target = 4)
- Negative numbers (e.g., `[-1, -2]`, target = -3)
- Duplicate values (e.g., `[3, 3]`, target = 6 → `[0, 1]`)
- Zero values (e.g., `[0, 4]`, target = 4)

### 🚫 Common Mistakes
- **Using nested loops**: Correct but O(n²) — always mention you can optimize
- **Sorting the array**: Destroys original indices, making them unrecoverable
- **Using the same element twice**: Map lookup prevents this since we check before inserting

### 🎯 Interview Tips
- **Communicate**: "I'll use a hash map for O(1) complement lookups"
- **Mention brute-force first**: "Naively we'd check all pairs in O(n²), but we can do O(n) with a hash map"
- **Follow-up**: "What if we need all pairs? What if the array is sorted?" (leads to Two Pointers)
- This is one of the most common first questions at Google and Amazon

---

## Problem 2: Contains Duplicate

> **LeetCode**: [#217 - Contains Duplicate](https://leetcode.com/problems/contains-duplicate/) | **Difficulty**: 🟢 Easy | **Pattern**: HashSet (Seen Tracking)

### 📝 Problem Statement

Given an integer array `nums`, return `true` if any value appears **at least twice**, and `false` if every element is distinct.

**Example:**
```
Input:  nums = [1, 2, 3, 1]
Output: true
```
```
Input:  nums = [1, 2, 3, 4]
Output: false
```

### 💡 Intuition & Approach

We need to detect repetitions. A **hash set** tracks elements we've already seen in O(1). For each element: if it's already in the set → duplicate found → return true. Otherwise, insert it and continue.

**Alternative** (not recommended): Sort the array and check adjacent elements. This is O(n log n) and modifies the input.

### 🔍 Hint
> Use a set. If inserting an element fails (it's already there), you found a duplicate.

### 🗂️ Pseudocode
```
seen = empty set
for each num in nums:
    if num in seen:
        return true
    seen.insert(num)
return false
```

### ✅ C++ Solution
See [`contains_duplicate.cpp`](contains_duplicate.cpp)

```cpp
class Solution {
public:
    bool containsDuplicate(vector<int>& nums) {
        unordered_set<int> seen;
        for (int num : nums) {
            if (seen.count(num)) return true;
            seen.insert(num);
        }
        return false;
    }
};
```

### 📊 Complexity Analysis

| | Complexity | Explanation |
|-|------------|-------------|
| **Time** | O(n) | Single pass |
| **Space** | O(n) | Set stores up to n elements |

### ⚠️ Edge Cases
- Single element array → always `false`
- All elements identical → returns `true` immediately at index 1
- Two identical elements at start

### 🚫 Common Mistakes
- Sorting (unnecessary O(n log n) when O(n) exists)
- Comparing all pairs O(n²)

### 🎯 Interview Tips
- One-liner alternative: `return nums.size() != unordered_set<int>(nums.begin(), nums.end()).size();`
- Follow-up: "What if duplicates must be within k positions?" → Use sliding window with a set

---

## Problem 3: Group Anagrams

> **LeetCode**: [#49 - Group Anagrams](https://leetcode.com/problems/group-anagrams/) | **Difficulty**: 🟡 Medium | **Pattern**: HashMap with Sorted Key

### 📝 Problem Statement

Given an array of strings `strs`, group the **anagrams** together. Return the answer in any order.

*Anagram*: strings with the same characters in possibly different orders (e.g., "eat" and "tea").

**Example:**
```
Input:  strs = ["eat","tea","tan","ate","nat","bat"]
Output: [["bat"],["nat","tan"],["ate","eat","tea"]]
```

### 💡 Intuition & Approach

Anagrams share the same characters → if we sort each string, all anagrams produce the **same key**. Use a hash map where the key is the sorted string and the value is the list of all strings that sort to that key.

**Alternative key idea**: A 26-integer character frequency array also works as a key, avoiding the O(k log k) sort cost per string.

### 🔍 Hint
> Sort each string alphabetically — all anagrams will sort to the same string. Use that sorted string as a hash map key.

### 🗂️ Pseudocode
```
map = {}  // sorted_string → [strings]
for each s in strs:
    key = sort(s)
    map[key].append(s)
return values of map
```

### ✅ C++ Solution
See [`group_anagrams.cpp`](group_anagrams.cpp)

```cpp
class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        unordered_map<string, vector<string>> groups;
        for (const string& s : strs) {
            string key = s;
            sort(key.begin(), key.end()); // sort to create canonical key
            groups[key].push_back(s);
        }
        vector<vector<string>> result;
        for (auto& [key, group] : groups) {
            result.push_back(group);
        }
        return result;
    }
};
```

### 📊 Complexity Analysis

| | Complexity | Explanation |
|-|------------|-------------|
| **Time** | O(n × k log k) | n = #strings, k = max string length |
| **Space** | O(n × k) | Storing all strings in the map |

### ⚠️ Edge Cases
- Single-character strings
- Empty strings (they're all anagrams of each other)
- All strings are the same
- Single string in input

### 🚫 Common Mistakes
- Checking all pairs for anagram property → O(n² × k log k), too slow
- Using string value as key instead of sorted string

### 🎯 Interview Tips
- Mention the character-count key as an O(n × k) alternative: `[0,0,0,...,0]` (26 ints)
- Follow-up: "What if strings contain Unicode?" → character frequency map with full range

---

## Problem 4: Running Sum of 1D Array

> **LeetCode**: [#1480 - Running Sum of 1D Array](https://leetcode.com/problems/running-sum-of-1d-array/) | **Difficulty**: 🟢 Easy | **Pattern**: Prefix Sum

### 📝 Problem Statement

Given an array `nums`, return the **running sum** where `runningSum[i] = sum(nums[0] + ... + nums[i])`.

**Example:**
```
Input:  nums = [1, 2, 3, 4]
Output: [1, 3, 6, 10]
```

### 💡 Intuition & Approach

The prefix sum pattern: each element becomes the sum of all elements up to that index. Simply accumulate: `nums[i] += nums[i-1]`. This modifies in-place (O(1) extra space).

Prefix sums are the foundation for range sum queries: `sum(i, j) = prefix[j] - prefix[i-1]`.

### 🔍 Hint
> Each element is just the previous element plus the current original value. Modify the array in-place.

### 🗂️ Pseudocode
```
for i from 1 to n-1:
    nums[i] += nums[i-1]
return nums
```

### ✅ C++ Solution
See [`running_sum.cpp`](running_sum.cpp)

```cpp
class Solution {
public:
    vector<int> runningSum(vector<int>& nums) {
        for (int i = 1; i < (int)nums.size(); i++) {
            nums[i] += nums[i - 1]; // accumulate prefix sum
        }
        return nums;
    }
};
```

### 📊 Complexity Analysis

| | Complexity | Explanation |
|-|------------|-------------|
| **Time** | O(n) | Single pass |
| **Space** | O(1) | In-place modification |

### ⚠️ Edge Cases
- Single element → return as-is
- All zeros → all zeros
- Integer overflow for very large arrays

### 🚫 Common Mistakes
- Allocating a new array when in-place works

### 🎯 Interview Tips
- This is the building block for **Range Sum Query** problems
- Follow-up: "How would you answer range sum queries efficiently?" → 2D prefix sums

---

## Problem 5: Product of Array Except Self

> **LeetCode**: [#238 - Product of Array Except Self](https://leetcode.com/problems/product-of-array-except-self/) | **Difficulty**: 🟡 Medium | **Pattern**: Prefix & Suffix Products

### 📝 Problem Statement

Given an integer array `nums`, return an array `answer` such that `answer[i]` equals the **product of all elements** except `nums[i]`. Solve in **O(n)** time **without division**.

**Example:**
```
Input:  nums = [1, 2, 3, 4]
Output: [24, 12, 8, 6]
Explanation: answer[2] = 1*2*4 = 8
```

### 💡 Intuition & Approach

For each index `i`, the product is: `(product of all elements left of i)` × `(product of all elements right of i)`.

**Two-pass approach:**
1. **Left pass**: Fill `result[i]` with the product of all elements to the left
2. **Right pass**: Multiply `result[i]` by the product of all elements to the right (tracked in a running variable)

This avoids division entirely and handles zeros correctly.

### 🔍 Hint
> Build a prefix product array (products to the left of each index), then multiply by a suffix product running variable from the right.

### 🗂️ Pseudocode
```
result = [1] * n

// Left pass: result[i] = product of nums[0..i-1]
prefix = 1
for i from 0 to n-1:
    result[i] = prefix
    prefix *= nums[i]

// Right pass: multiply result[i] by product of nums[i+1..n-1]
suffix = 1
for i from n-1 to 0:
    result[i] *= suffix
    suffix *= nums[i]

return result
```

### ✅ C++ Solution
See [`product_except_self.cpp`](product_except_self.cpp)

```cpp
class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        int n = nums.size();
        vector<int> result(n, 1);

        // Left pass: result[i] = product of all elements to the left
        int prefix = 1;
        for (int i = 0; i < n; i++) {
            result[i] = prefix;
            prefix *= nums[i];
        }

        // Right pass: multiply by product of all elements to the right
        int suffix = 1;
        for (int i = n - 1; i >= 0; i--) {
            result[i] *= suffix;
            suffix *= nums[i];
        }

        return result;
    }
};
```

### 📊 Complexity Analysis

| | Complexity | Explanation |
|-|------------|-------------|
| **Time** | O(n) | Two passes through the array |
| **Space** | O(1) | Output array doesn't count; only O(1) extra |

### ⚠️ Edge Cases
- Array with zeros: output will have zeros (handled correctly — no division)
- Array with two zeros: entire output is zeros
- Negative numbers: handled naturally by multiplication
- Single zero element: all positions except that one become 0

### 🚫 Common Mistakes
- **Using division**: Fails when any element is 0 (division by zero)
- **Using two separate extra arrays**: Correct but uses O(n) extra space; the two-variable trick avoids this

### 🎯 Interview Tips
- Always state: "I won't use division" proactively
- If allowed O(n) space: "I can use two prefix/suffix arrays first, but I can optimize to O(1) space"
- **Common follow-up**: "What if there are zeros?" (handled correctly) or "What if the input has exactly one zero?" (only that position's product is nonzero)

---

## 🔄 Section Recap

| Problem | Pattern | Time | Space |
|---------|---------|------|-------|
| Two Sum | HashMap Complement | O(n) | O(n) |
| Contains Duplicate | HashSet | O(n) | O(n) |
| Group Anagrams | HashMap with Sorted Key | O(nk log k) | O(nk) |
| Running Sum | Prefix Sum (in-place) | O(n) | O(1) |
| Product Except Self | Prefix + Suffix Products | O(n) | O(1) |

**Key takeaways:**
- 🔑 Hash maps give O(1) lookup — use them to avoid nested loops
- 🔑 Prefix sums enable range queries in O(1) after O(n) preprocessing
- 🔑 Always ask "do I need division?" — prefix×suffix avoids it

**Next up**: [Two Pointers & Sliding Window →](../03_Two_Pointers_and_Sliding_Window/README.md)
