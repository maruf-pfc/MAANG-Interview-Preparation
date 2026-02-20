# 👆 Section 03: Two Pointers & Sliding Window

> **Units**: 26 | **Pattern**: Two coordinated indices to eliminate nested loops | **Difficulty**: Easy–Medium

The two-pointer technique transforms O(n²) "check all pairs" solutions into elegant O(n) single-pass algorithms. When you see a problem that *seems* to require nested loops, **think two pointers**.

**Two main forms:**
- **Opposite-end pointers**: start at both ends, move inward (sorted arrays, pairs)
- **Sliding window**: both start at left, right expands window, left shrinks it (substrings, subarrays)

**Problems Covered:**
1. [Two Sum II](#problem-1-two-sum-ii)
2. [3Sum](#problem-2-3sum)
3. [Longest Substring Without Repeating Characters](#problem-3-longest-substring-without-repeating-characters)
4. [Container With Most Water](#problem-4-container-with-most-water)

---

## Problem 1: Two Sum II

> **LeetCode**: [#167 - Two Sum II](https://leetcode.com/problems/two-sum-ii-input-array-is-sorted/) | **Difficulty**: 🟡 Medium | **Pattern**: Two Pointers (Opposite Ends)

### 📝 Problem Statement

Given a **sorted** (non-decreasing) integer array `numbers`, find two numbers that add to `target`. Return their **1-indexed** positions.

**Example:**
```
Input:  numbers = [2, 7, 11, 15], target = 9
Output: [1, 2]   (1-indexed)
```
```
Input:  numbers = [2, 3, 4], target = 6
Output: [1, 3]
```

### 💡 Intuition & Approach

Since the array is **sorted**, we can exploit its order. Place a `left` pointer at the start and a `right` pointer at the end:
- If `sum > target`: the sum is too big → move `right` left (decrease the larger value)
- If `sum < target`: the sum is too small → move `left` right (increase the smaller value)
- If `sum == target`: found it!

The sorted property guarantees this greedy movement is correct — we never miss a valid pair.

### 🔍 Hint
> Use left and right pointers from opposite ends. Move the pointer on the side that will bring the sum closer to the target.

### 🗂️ Pseudocode
```
left = 0, right = n - 1
while left < right:
    sum = numbers[left] + numbers[right]
    if sum > target:  right--
    elif sum < target: left++
    else: return [left+1, right+1]  // 1-indexed
```

### ✅ C++ & C# Solutions
See [`two_sum_ii.cpp`](two_sum_ii.cpp) | [`two_sum_ii.cs`](two_sum_ii.cs)

**C++ Implementation**
```cpp
class Solution {
public:
    vector<int> twoSum(vector<int>& numbers, int target) {
        int left = 0, right = (int)numbers.size() - 1;
        while (left < right) {
            int sum = numbers[left] + numbers[right];
            if (sum > target)       right--;
            else if (sum < target)  left++;
            else return {left + 1, right + 1}; // 1-indexed
        }
}
};
```

**C# Implementation**
```csharp
public class Solution {
    public int[] TwoSum(int[] numbers, int target) {
        int left = 0;
        int right = numbers.Length - 1;
        
        while (left < right) {
            int currentSum = numbers[left] + numbers[right];
            
            if (currentSum > target) {
                right--;
            } else if (currentSum < target) {
                left++;
            } else {
                return new int[] { left + 1, right + 1 };
            }
        }
        
        return new int[0];
    }
}
```

### 📊 Complexity Analysis

| | Complexity | Explanation |
|-|------------|-------------|
| **Time** | O(n) | Each pointer moves at most n times total |
| **Space** | O(1) | No extra data structures |

### ⚠️ Edge Cases
- Target = 0 with two zeros (e.g., `[0, 0]`)
- Duplicate values adjacent (e.g., `[3, 3]`, target = 6)
- Very large/small target values

### 🚫 Common Mistakes
- **0-based indexing**: The problem asks for 1-based indices
- **Using a hash map**: Works but O(n) space unnecessarily when array is sorted
- **Moving both pointers at once**: Only move one per iteration

### 🎯 Interview Tips
- Emphasize that *sorted* is what makes two pointers work here
- Distinguish from Two Sum (#1): "Here the array is sorted, so we don't need a hash map"
- Follow-up: "What if there's no solution?" → Return `[-1, -1]`

---

## Problem 2: 3Sum

> **LeetCode**: [#15 - 3Sum](https://leetcode.com/problems/3sum/) | **Difficulty**: 🟡 Medium | **Pattern**: Sort + Two Pointers

### 📝 Problem Statement

Given an integer array `nums`, return all **unique triplets** `[nums[i], nums[j], nums[k]]` such that they sum to 0 and `i ≠ j ≠ k`.

**Example:**
```
Input:  nums = [-1, 0, 1, 2, -1, -4]
Output: [[-1, -1, 2], [-1, 0, 1]]
```

### 💡 Intuition & Approach

Fix one element `nums[i]`, then find two elements in the **rest** of the array that sum to `-nums[i]`. That's exactly Two Sum on a sorted array.

**Algorithm:**
1. **Sort** the array (enables two pointers and easy duplicate skipping)
2. For each index `i` (skipping duplicates):
   - Use two pointers `left = i+1`, `right = n-1`
   - Find pairs that sum to `-nums[i]`
   - Skip duplicates whenever a pair is found

Early termination: if `nums[i] > 0`, no three positives can sum to 0.

### 🔍 Hint
> Sort the array. Fix the first element with a loop, then use two pointers on the remainder to find pairs that sum to the negative of the fixed element.

### 🗂️ Pseudocode
```
sort(nums)
result = []
for i from 0 to n-3:
    if i > 0 and nums[i] == nums[i-1]: continue  // skip duplicates
    if nums[i] > 0: break                          // early termination
    left, right = i+1, n-1
    while left < right:
        sum = nums[i] + nums[left] + nums[right]
        if sum > 0:  right--
        if sum < 0:  left++
        else:
            result.append([nums[i], nums[left], nums[right]])
            left++; right--
            // skip duplicates
            while left < right and nums[left] == nums[left-1]:  left++
            while left < right and nums[right] == nums[right+1]: right--
return result
```

### ✅ C++ & C# Solutions
See [`three_sum.cpp`](three_sum.cpp) | [`three_sum.cs`](three_sum.cs)

**C++ Implementation**
```cpp
class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        vector<vector<int>> result;

        for (int i = 0; i < (int)nums.size() - 2; i++) {
            if (nums[i] > 0) break;               // no triple of positives sums to 0
            if (i > 0 && nums[i] == nums[i-1]) continue; // skip outer duplicates

            int left = i + 1, right = (int)nums.size() - 1;
            while (left < right) {
                int sum = nums[i] + nums[left] + nums[right];
                if (sum > 0) {
                    right--;
                } else if (sum < 0) {
                    left++;
                } else {
                    result.push_back({nums[i], nums[left], nums[right]});
                    left++;  right--;
                    // skip duplicates from both ends
                    while (left < right && nums[left] == nums[left-1])   left++;
                    while (left < right && nums[right] == nums[right+1]) right--;
                }
            }
        }
}
};
```

**C# Implementation**
```csharp
using System;
using System.Collections.Generic;

public class Solution {
    public IList<IList<int>> ThreeSum(int[] nums) {
        var result = new List<IList<int>>();
        Array.Sort(nums);
        
        for (int i = 0; i < nums.Length; i++) {
            if (i > 0 && nums[i] == nums[i - 1]) continue;
            if (nums[i] > 0) break;
            
            int left = i + 1;
            int right = nums.Length - 1;
            
            while (left < right) {
                int sum = nums[i] + nums[left] + nums[right];
                
                if (sum > 0) {
                    right--;
                } else if (sum < 0) {
                    left++;
                } else {
                    result.Add(new List<int> { nums[i], nums[left], nums[right] });
                    left++;
                    right--;
                    while (left < right && nums[left] == nums[left - 1]) left++;
                    while (left < right && nums[right] == nums[right + 1]) right--;
                }
            }
        }
        
        return result;
    }
}
```

### 📊 Complexity Analysis

| | Complexity | Explanation |
|-|------------|-------------|
| **Time** | O(n²) | O(n log n) sort + O(n²) for outer loop × two pointers |
| **Space** | O(1) | No extra space (output not counted) |

### ⚠️ Edge Cases
- All zeros (`[0,0,0]`) → `[[0,0,0]]`
- No valid triplets → `[]`
- All same negative values
- Two elements only → impossible, return `[]`

### 🚫 Common Mistakes
- **Forgetting to skip duplicates**: Produces duplicate triplets
- **Using a set for deduplication**: Works but adds O(n) space unnecessarily
- **Not sorting first**: Two pointers require sorted input

### 🎯 Interview Tips
- State complexity upfront: "O(n²) is optimal for this problem — no known O(n log n) solution"
- Walk through duplicate skipping carefully — it's the trickiest part
- Follow-up: "4Sum?" → Add another outer loop → O(n³)

---

## Problem 3: Longest Substring Without Repeating Characters

> **LeetCode**: [#3 - Longest Substring Without Repeating Characters](https://leetcode.com/problems/longest-substring-without-repeating-characters/) | **Difficulty**: 🟡 Medium | **Pattern**: Sliding Window

### 📝 Problem Statement

Given a string `s`, find the length of the **longest substring** without repeating characters.

**Example:**
```
Input:  s = "abcabcbb"
Output: 3   (substring "abc")
```
```
Input:  s = "bbbbb"
Output: 1   (substring "b")
```
```
Input:  s = "pwwkew"
Output: 3   (substring "wke")
```

### 💡 Intuition & Approach

Maintain a **sliding window** `[left, right]` that contains no duplicates. Expand `right` to include new characters. When a duplicate is found, shrink from `left` until the duplicate is gone. Track the maximum window size seen.

Use a hash set to check membership and a single pass for O(n).

### 🔍 Hint
> Use a set to track characters in the current window. Expand right; when you hit a duplicate, shrink from the left until it's gone.

### 🗂️ Pseudocode
```
charSet = empty set
left = 0, maxLen = 0
for right from 0 to n-1:
    while s[right] in charSet:
        charSet.remove(s[left])
        left++
    charSet.add(s[right])
    maxLen = max(maxLen, right - left + 1)
return maxLen
```

### ✅ C++ & C# Solutions
See [`longest_substring_no_repeat.cpp`](longest_substring_no_repeat.cpp) | [`longest_substring_no_repeat.cs`](longest_substring_no_repeat.cs)

**C++ Implementation**
```cpp
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        unordered_set<char> window;
        int left = 0, maxLen = 0;

        for (int right = 0; right < (int)s.size(); right++) {
            // shrink from left until the duplicate is gone
            while (window.count(s[right])) {
                window.erase(s[left]);
                left++;
            }
            window.insert(s[right]);
            maxLen = max(maxLen, right - left + 1);
        }
}
};
```

**C# Implementation**
```csharp
using System;
using System.Collections.Generic;

public class Solution {
    public int LengthOfLongestSubstring(string s) {
        var charSet = new HashSet<char>();
        int left = 0;
        int maxLength = 0;
        
        for (int right = 0; right < s.Length; right++) {
            while (charSet.Contains(s[right])) {
                charSet.Remove(s[left]);
                left++;
            }
            charSet.Add(s[right]);
            maxLength = Math.Max(maxLength, right - left + 1);
        }
        
        return maxLength;
    }
}
```

### 📊 Complexity Analysis

| | Complexity | Explanation |
|-|------------|-------------|
| **Time** | O(n) | Each character inserted/removed at most once |
| **Space** | O(min(n, 26)) | Set bounded by alphabet size |

### ⚠️ Edge Cases
- Empty string → 0
- All same character (e.g., "aaaa") → 1
- All unique characters → n
- String with spaces (space is a valid character)

### 🚫 Common Mistakes
- Nested loops (O(n²)) when O(n) is achievable
- Forgetting to update `left` pointer position
- Using string methods for substring checks (expensive)

### 🎯 Interview Tips
- One of the most common sliding window problems
- Optimize: use `unordered_map<char, int>` to store last index — lets you jump `left` directly instead of step-by-step shrinking
- Follow-up: "What if characters have weights? Return max weight substring without repeating."

---

## Problem 4: Container With Most Water

> **LeetCode**: [#11 - Container With Most Water](https://leetcode.com/problems/container-with-most-water/) | **Difficulty**: 🟡 Medium | **Pattern**: Two Pointers (Greedy)

### 📝 Problem Statement

Given `n` non-negative integers `height[i]`, where each represents a vertical line at position `i`, find two lines that together with the x-axis forms a container with the **most water**.

**Example:**
```
Input:  height = [1, 8, 6, 2, 5, 4, 8, 3, 7]
Output: 49
Explanation: Lines at index 1 (height=8) and index 8 (height=7) → area = min(8,7) * (8-1) = 7*7 = 49
```

### 💡 Intuition & Approach

Area = `min(height[left], height[right]) × (right - left)`

Use two pointers from opposite ends. At each step, move the **shorter** side inward. Why? Moving the taller side can only decrease width without increasing the min-height bottleneck, so it can only decrease area. Moving the shorter side gives a chance to find a taller height.

### 🔍 Hint
> The area is limited by the shorter line. Always move the pointer pointing to the shorter line inward — that's the only way to potentially find more water.

### 🗂️ Pseudocode
```
left = 0, right = n - 1, maxArea = 0
while left < right:
    area = min(height[left], height[right]) * (right - left)
    maxArea = max(maxArea, area)
    if height[left] < height[right]:
        left++
    else:
        right--
return maxArea
```

### ✅ C++ & C# Solutions
See [`container_with_most_water.cpp`](container_with_most_water.cpp) | [`container_with_most_water.cs`](container_with_most_water.cs)

**C++ Implementation**
```cpp
class Solution {
public:
    int maxArea(vector<int>& height) {
        int left = 0, right = (int)height.size() - 1;
        int maxArea = 0;

        while (left < right) {
            int area = min(height[left], height[right]) * (right - left);
            maxArea = max(maxArea, area);

            // move the shorter line — it's the limiting factor
            if (height[left] < height[right]) {
                left++;
            } else {
                right--;
            }
        }
}
};
```

**C# Implementation**
```csharp
using System;

public class Solution {
    public int MaxArea(int[] height) {
        int maxArea = 0;
        int left = 0;
        int right = height.Length - 1;
        
        while (left < right) {
            int currentArea = Math.Min(height[left], height[right]) * (right - left);
            maxArea = Math.Max(maxArea, currentArea);
            
            if (height[left] < height[right]) {
                left++;
            } else {
                right--;
            }
        }
        
        return maxArea;
    }
}
```

### 📊 Complexity Analysis

| | Complexity | Explanation |
|-|------------|-------------|
| **Time** | O(n) | Single pass, each pointer moves ≤ n times |
| **Space** | O(1) | No extra storage |

### ⚠️ Edge Cases
- Two lines only → single valid container
- All equal heights → widest container wins
- Strictly decreasing or increasing heights
- All height = 0 → area = 0

### 🚫 Common Mistakes
- Moving the taller pointer: provably suboptimal — the shorter is the bottleneck
- Checking all pairs: O(n²) brute force
- Using the full height (not the min) for area calculation

### 🎯 Interview Tips
- The key proof: "If we have `height[left] < height[right]`, can moving right inward ever give a better answer? No — new width is smaller, min height is still ≤ height[left]. So we must move left."
- Follow-up: "Trapping Rain Water" (LeetCode #42) — harder variant counting total trapped water

---

## 🔄 Section Recap

| Problem | Pattern | Time | Space |
|---------|---------|------|-------|
| Two Sum II | Two Pointers | O(n) | O(1) |
| 3Sum | Sort + Two Pointers | O(n²) | O(1) |
| Longest Substring No Repeat | Sliding Window | O(n) | O(n) |
| Container With Most Water | Greedy Two Pointers | O(n) | O(1) |

**Key takeaways:**
- 🔑 **Sorted array + pairs** → Two Pointers from opposite ends
- 🔑 **Subarray/substring with constraint** → Sliding Window
- 🔑 **Bottleneck reasoning** → Always move the limiting pointer

**Next up**: [Linked Lists →](../04_Linked_Lists/README.md)
