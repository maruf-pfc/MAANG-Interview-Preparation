# 08 · Binary Search
> **20 units · ~62 min · Pattern: Halve the Search Space**

Binary search finds a target in a sorted array in O(log n) time. But it's not just for "find this value." Whenever you can **divide the search space in half** based on some condition, binary search applies. Master the template, then apply it to rotated arrays, answer-space problems, and more.

---

## Unit Map

| Unit | Title | Time |
|------|-------|------|
| [8.1](#81-intro) | Intro — When to use binary search | 2 min |
| [8.2](#82-problem--binary-search) | Problem — Binary Search | 3 min |
| [8.3](#83-binary-search--hint) | Binary Search — Hint | 3 min |
| [8.4](#84-binary-search--solution) | Binary Search — Solution | 4 min |
| [8.5](#85-binary-search--pseudocode) | Binary Search — Pseudocode | 3 min |
| [8.6](#86-binary-search--implementation) | Binary Search — Implementation | 10 min |
| [8.7](#87-binary-search--why-this-problem) | Binary Search — Why This Problem? | 2 min |
| [8.8](#88-problem--search-in-rotated-sorted-array) | Problem — Search in Rotated Sorted Array | 3 min |
| [8.9](#89-search-rotated--hint) | Search Rotated — Hint | 3 min |
| [8.10](#810-search-rotated--solution) | Search Rotated — Solution | 4 min |
| [8.11](#811-search-rotated--pseudocode) | Search Rotated — Pseudocode | 3 min |
| [8.12](#812-search-rotated--implementation) | Search Rotated — Implementation | 10 min |
| [8.13](#813-search-rotated--why-this-problem) | Search Rotated — Why This Problem? | 2 min |
| [8.14](#814-problem--find-minimum-in-rotated-array) | Problem — Find Minimum in Rotated Array | 3 min |
| [8.15](#815-find-minimum--hint) | Find Minimum — Hint | 3 min |
| [8.16](#816-find-minimum--solution) | Find Minimum — Solution | 4 min |
| [8.17](#817-find-minimum--pseudocode) | Find Minimum — Pseudocode | 3 min |
| [8.18](#818-find-minimum--implementation) | Find Minimum — Implementation | 10 min |
| [8.19](#819-find-minimum--why-this-problem) | Find Minimum — Why This Problem? | 2 min |
| [8.20](#820-section-recap) | Section Recap | 2 min |

---

## 8.1 Intro
**When to use binary search · 2 min**

Binary search finds a target in sorted data in **O(log n)** — cutting the search space in half each iteration. The real power: it applies beyond simple lookup.

**Use binary search when:**
- Input is sorted (or partially sorted)
- You can determine "the answer lies in the left half or right half" from mid
- You're searching in an "answer space" (e.g., "minimum possible answer" problems)

**The universal template:**
```cpp
int left = 0, right = n - 1;
while (left <= right) {
    int mid = left + (right - left) / 2;  // prevents overflow
    if (condition(mid)) right = mid - 1;  // or left = mid + 1
    else                left = mid + 1;
}
```

**Why `left + (right - left) / 2` instead of `(left + right) / 2`?**  
When `left` and `right` are both near `INT_MAX`, their sum overflows. The safe formula prevents this.

---

## 8.2 Problem — Binary Search
**The classic algorithm · [LeetCode #704](https://leetcode.com/problems/binary-search/) · 🟢 Easy · 3 min**

Given a **sorted** array of distinct integers `nums` and a `target`, return the index of `target`. Return `-1` if not found.

```
Input:  nums = [-1, 0, 3, 5, 9, 12], target = 9
Output: 4

Input:  nums = [-1, 0, 3, 5, 9, 12], target = 2
Output: -1
```

---

## 8.3 Binary Search — Hint
**The main idea · 3 min**

Use `left` and `right` pointers. Compute `mid`. If `nums[mid] == target` → found. If `nums[mid] < target` → move left up (`left = mid + 1`). If `nums[mid] > target` → move right down (`right = mid - 1`). Continue until `left > right`.

---

## 8.4 Binary Search — Solution
**The algorithm · 4 min**

The key invariant: target is always in `[left, right]` if it exists.

- `nums[mid] < target` → target must be in `[mid+1, right]` → `left = mid + 1`
- `nums[mid] > target` → target must be in `[left, mid-1]` → `right = mid - 1`
- `nums[mid] == target` → found

Loop exits when `left > right` → target not in array → return `-1`.

**Why `left <= right` (not `<`)?** When the range has exactly one element (`left == right`), we still need to check it.

---

## 8.5 Binary Search — Pseudocode
**The code · 3 min**

```
left = 0, right = n - 1

while left <= right:
    mid = left + (right - left) / 2      // safe mid
    if nums[mid] == target:
        return mid
    elif nums[mid] < target:
        left = mid + 1
    else:
        right = mid - 1

return -1
```

---

## 8.6 Binary Search — Implementation
**Code it yourself · 10 min**

### ✅ C++ & C# Solutions
See [`binary_search.cpp`](binary_search.cpp) | [`binary_search.cs`](binary_search.cs)

**C++ Implementation**
```cpp
class Solution {
public:
    int search(vector<int>& nums, int target) {
        int left = 0, right = (int)nums.size() - 1;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (nums[mid] == target) return mid;
            else if (nums[mid] < target) left = mid + 1;
            else right = mid - 1;
        }
}
};
```

**C# Implementation**
```csharp
public class Solution {
    public int Search(int[] nums, int target) {
        int left = 0;
        int right = nums.Length - 1;
        
        while (left <= right) {
            int mid = left + (right - left) / 2;
            
            if (nums[mid] == target) {
                return mid;
            } else if (nums[mid] < target) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        
        return -1;
    }
}
```

**Compile & run (C++):**
```bash
g++ -std=c++17 binary_search.cpp && ./a.out
```

| | Complexity |
|-|------------|
| **Time** | O(log n) — halves range each iteration |
| **Space** | O(1) — no extra memory |

**Edge cases:**
- Target smaller than all elements → `left` keeps advancing past `right`
- Target larger than all elements → `right` keeps retreating past `left`
- Single element array → one comparison, return 0 or -1

**Common mistakes:**
- Using `left < right` → misses the last element check
- Integer overflow with `(left + right) / 2` when values are large

---

## 8.7 Binary Search — Why This Problem?
**Interview context · 2 min**

- The template is used everywhere: not just basic lookup but rotated arrays, first/last position, minimum in rotated array, etc.
- **Follow-up:** *"What if there are duplicates?"* → Returns *an* index, not necessarily the first/last
- **Variation:** `lower_bound` / `upper_bound` in C++ STL — find first element ≥ target

---

## 8.8 Problem — Search in Rotated Sorted Array
**Binary search with a twist · [LeetCode #33](https://leetcode.com/problems/search-in-rotated-sorted-array/) · 🟡 Medium · 3 min**

A sorted array was **rotated** at some pivot. Find `target` and return its index, or `-1`.

```
Input:  nums = [4,5,6,7,0,1,2], target = 0
Output: 4

Input:  nums = [4,5,6,7,0,1,2], target = 3
Output: -1
```

No duplicates in the input.

---

## 8.9 Search Rotated — Hint
**The main idea · 3 min**

Even in a rotated array, **one of the two halves is always sorted**. Determine which half is sorted by comparing `nums[left]` with `nums[mid]`. Then check if `target` is in the sorted half. If yes → search there. If no → search the other half.

---

## 8.10 Search Rotated — Solution
**The algorithm · 4 min**

At each step, compare `nums[left]` with `nums[mid]`:

**Left half `[left, mid]` is sorted** if `nums[left] <= nums[mid]`:
- If `nums[left] <= target < nums[mid]` → `right = mid - 1` (target in left half)
- Else → `left = mid + 1` (target in right half)

**Right half `[mid, right]` is sorted** otherwise:
- If `nums[mid] < target <= nums[right]` → `left = mid + 1` (target in right half)
- Else → `right = mid - 1` (target in left half)

---

## 8.11 Search Rotated — Pseudocode
**The code · 3 min**

```
left = 0, right = n - 1

while left <= right:
    mid = left + (right - left) / 2
    if nums[mid] == target: return mid

    // Determine which half is sorted
    if nums[left] <= nums[mid]:             // left half sorted
        if nums[left] <= target < nums[mid]:
            right = mid - 1                 // target in sorted left half
        else:
            left = mid + 1
    else:                                   // right half sorted
        if nums[mid] < target <= nums[right]:
            left = mid + 1                  // target in sorted right half
        else:
            right = mid - 1

return -1
```

---

## 8.12 Search Rotated — Implementation
**Code it yourself · 10 min**

### ✅ C++ & C# Solutions
See [`search_rotated_array.cpp`](search_rotated_array.cpp) | [`search_2d_matrix.cs`](search_2d_matrix.cs) (Using Search 2D Matrix instead as per C# additions)

**C++ Implementation (Search Rotated Array)**
```cpp
class Solution {
public:
    int search(vector<int>& nums, int target) {
        int left = 0, right = (int)nums.size() - 1;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (nums[mid] == target) return mid;

            if (nums[left] <= nums[mid]) {          // left half sorted
                if (nums[left] <= target && target < nums[mid])
                    right = mid - 1;
                else
                    left = mid + 1;
            } else {                                // right half sorted
                if (nums[mid] < target && target <= nums[right])
                    left = mid + 1;
                else
                    right = mid - 1;
            }
        }
    }
};
```

**C# Implementation (Search 2D Matrix)**
```csharp
public class Solution {
    public bool SearchMatrix(int[][] matrix, int target) {
        if (matrix == null || matrix.Length == 0 || matrix[0].Length == 0) return false;
        
        int rows = matrix.Length, cols = matrix[0].Length;
        int top = 0, bottom = rows - 1;
        while (top <= bottom) {
            int row = top + (bottom - top) / 2;
            if (target > matrix[row][cols - 1]) top = row + 1;
            else if (target < matrix[row][0]) bottom = row - 1;
            else break;
        }
        
        if (top > bottom) return false;
        
        int targetRow = top + (bottom - top) / 2;
        int left = 0, right = cols - 1;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (target == matrix[targetRow][mid]) return true;
            else if (target > matrix[targetRow][mid]) left = mid + 1;
            else right = mid - 1;
        }
        
        return false;
    }
}
```

| | Complexity |
|-|------------|
| **Time** | O(log n) |
| **Space** | O(1) |

**Edge cases:**
- No rotation (already sorted) → standard binary search behavior (still works)
- Target at the rotation pivot → found when `mid` lands on it
- Single element array → one comparison

**Common mistakes:**
- Off-by-one in the range check: `nums[left] <= target < nums[mid]` (strict on right, inclusive on left)
- Using `nums[left] < nums[mid]` (not `<=`) — misses the case where left == mid

---

## 8.13 Search Rotated — Why This Problem?
**Interview context · 2 min**

- Tests systematic reasoning about modified binary search — the key is "which half is guaranteed sorted"
- **Follow-up:** *"What if there are duplicates?"* → LeetCode #81; worst case becomes O(n) because you can't determine the sorted half
- **Pro tip:** Draw the rotated array on paper and trace through one case to convince yourself, then code

---

## 8.14 Problem — Find Minimum in Rotated Array
**Finding the pivot point · [LeetCode #153](https://leetcode.com/problems/find-minimum-in-rotated-sorted-array/) · 🟡 Medium · 3 min**

A sorted array was rotated. Find the **minimum** element. All values are unique.

```
Input:  [3, 4, 5, 1, 2]    → 1
Input:  [4, 5, 6, 7, 0, 1, 2] → 0
Input:  [11, 13, 15, 17]   → 11   (no rotation)
```

---

## 8.15 Find Minimum — Hint
**The main idea · 3 min**

Compare `nums[mid]` with `nums[right]`. If `nums[mid] > nums[right]`, the minimum must be in the **right half** (the rotation happened there). Otherwise, the minimum is in the **left half** (including `mid`).

---

## 8.16 Find Minimum — Solution
**The algorithm · 4 min**

Key insight: In a rotated sorted array, compare `mid` against `right` (not left):

- `nums[mid] > nums[right]` → rotation point (minimum) is to the RIGHT of mid → `left = mid + 1`
- `nums[mid] <= nums[right]` → minimum is at mid or to the left → `right = mid` (don't exclude mid)

Use `left < right` (not `<=`) to stop when the range is single element — that element is the minimum.

---

## 8.17 Find Minimum — Pseudocode
**The code · 3 min**

```
left = 0, right = n - 1

while left < right:               // stop when 1 element remains
    mid = left + (right - left) / 2
    if nums[mid] > nums[right]:
        left = mid + 1            // minimum in right half
    else:
        right = mid               // minimum is mid or in left half (keep mid)

return nums[left]
```

---

## 8.18 Find Minimum — Implementation
**Code it yourself · 10 min**

### ✅ C++ & C# Solutions
See [`find_min_rotated_array.cpp`](find_min_rotated_array.cpp) | [`find_minimum_in_rotated_sorted_array.cs`](find_minimum_in_rotated_sorted_array.cs)

**C++ Implementation**
```cpp
class Solution {
public:
    int findMin(vector<int>& nums) {
        int left = 0, right = (int)nums.size() - 1;
        while (left < right) {
            int mid = left + (right - left) / 2;
            if (nums[mid] > nums[right])
                left = mid + 1;  // minimum is in right half
            else
                right = mid;     // minimum is at mid or left of mid
        }
    }
};
```

**C# Implementation**
```csharp
using System;

public class Solution {
    public int FindMin(int[] nums) {
        int left = 0;
        int right = nums.Length - 1;
        int res = nums[0];
        
        while (left <= right) {
            if (nums[left] < nums[right]) {
                res = Math.Min(res, nums[left]);
                break;
            }
            
            int mid = left + (right - left) / 2;
            res = Math.Min(res, nums[mid]);
            
            if (nums[mid] >= nums[left]) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        
        return res;
    }
}
```

| | Complexity |
|-|------------|
| **Time** | O(log n) |
| **Space** | O(1) |

**Edge cases:**
- No rotation (sorted array) → `nums[mid] <= nums[right]` always, `right` moves left to 0, returns `nums[0]` ✓
- Two elements, rotated ([2,1]) → `nums[0]=2 > nums[1]=1` → `left=1 = right` → returns 1 ✓
- Single element → `left == right` from start, returns `nums[0]`

**Common mistakes:**
- Using `left <= right` → infinite loop (when `nums[mid] <= nums[right]`, we set `right = mid`, and if `left == mid`, we'd loop forever)
- Comparing with `nums[left]` instead of `nums[right]` — the right comparison is the anchor

---

## 8.19 Find Minimum — Why This Problem?
**Interview context · 2 min**

- This `mid-vs-right` insight is important for binary search on answer spaces
- Once you find the pivot index, you can binary search either half directly
- **Follow-up:** *"What if there are duplicates?"* → Need O(n) worst case (can't determine which half in some cases)

---

## 8.20 Section Recap
**What you learned · 2 min**

| Problem | Key Condition | Template |
|---------|--------------|---------|
| Binary Search | `nums[mid] vs target` | `while left <= right` |
| Search Rotated | Which half is sorted? | `while left <= right` |
| Find Minimum Rotated | `nums[mid] vs nums[right]` | `while left < right` |

**Core takeaways:**
- 🔑 Safe mid: always use `left + (right - left) / 2`
- 🔑 `while left <= right` when you want to check the exact target; `while left < right` when converging to a boundary
- 🔑 Rotated array: always one half is sorted — use that as your oracle
- 🔑 `mid vs right` for find-minimum; `left vs mid` for search-in-rotated

**Next section →** [09 · Heaps & Priority Queues](../09_Heaps_and_Priority_Queues/README.md)
