# 10 · Dynamic Programming
> **44 units · ~140 min · Patterns: 1D DP, Grid DP, 2D String DP**

Dynamic Programming (DP) solves problems by breaking them into overlapping subproblems. It's essentially smart recursion — calculating each subproblem once and storing the result. It appears in ~25% of MAANG interviews. 

---

## Unit Map

| Unit | Title | Time |
|------|-------|------|
| [10.1](#101-intro) | Intro — Why dynamic programming matters | 3 min |
| [10.2](#102-problem--climbing-stairs) | Problem — Climbing Stairs | 2 min |
| [10.3](#103-climbing-stairs--hint) | Climbing Stairs — Hint | 3 min |
| [10.4](#104-climbing-stairs--solution) | Climbing Stairs — Solution | 4 min |
| [10.5](#105-climbing-stairs--pseudocode) | Climbing Stairs — Pseudocode | 3 min |
| [10.6](#106-climbing-stairs--implementation) | Climbing Stairs — Implementation | 8 min |
| [10.7](#107-climbing-stairs--why-this-problem) | Climbing Stairs — Why This Problem? | 2 min |
| [10.8](#108-problem--house-robber) | Problem — House Robber | 3 min |
| [10.9](#109-house-robber--hint) | House Robber — Hint | 3 min |
| [10.10](#1010-house-robber--solution) | House Robber — Solution | 4 min |
| [10.11](#1011-house-robber--pseudocode) | House Robber — Pseudocode | 3 min |
| [10.12](#1012-house-robber--implementation) | House Robber — Implementation | 8 min |
| [10.13](#1013-house-robber--why-this-problem) | House Robber — Why This Problem? | 2 min |
| [10.14](#1014-problem--coin-change) | Problem — Coin Change | 3 min |
| [10.15](#1015-coin-change--hint) | Coin Change — Hint | 3 min |
| [10.16](#1016-coin-change--solution) | Coin Change — Solution | 4 min |
| [10.17](#1017-coin-change--pseudocode) | Coin Change — Pseudocode | 3 min |
| [10.18](#1018-coin-change--implementation) | Coin Change — Implementation | 10 min |
| [10.19](#1019-coin-change--why-this-problem) | Coin Change — Why This Problem? | 2 min |
| [10.20](#1020-problem--longest-increasing-subsequence) | Problem — Longest Increasing Subsequence | 3 min |
| [10.21](#1021-lis--hint) | LIS — Hint | 3 min |
| [10.22](#1022-lis--solution) | LIS — Solution | 4 min |
| [10.23](#1023-lis--pseudocode) | LIS — Pseudocode | 3 min |
| [10.24](#1024-lis--implementation) | LIS — Implementation | 10 min |
| [10.25](#1025-lis--why-this-problem) | LIS — Why This Problem? | 2 min |
| [10.26](#1026-problem--unique-paths) | Problem — Unique Paths | 3 min |
| [10.27](#1027-unique-paths--hint) | Unique Paths — Hint | 3 min |
| [10.28](#1028-unique-paths--solution) | Unique Paths — Solution | 4 min |
| [10.29](#1029-unique-paths--pseudocode) | Unique Paths — Pseudocode | 3 min |
| [10.30](#1030-unique-paths--implementation) | Unique Paths — Implementation | 8 min |
| [10.31](#1031-unique-paths--why-this-problem) | Unique Paths — Why This Problem? | 2 min |
| [10.32](#1032-problem--longest-common-subsequence) | Problem — Longest Common Subsequence | 3 min |
| [10.33](#1033-lcs--hint) | LCS — Hint | 3 min |
| [10.34](#1034-lcs--solution) | LCS — Solution | 4 min |
| [10.35](#1035-lcs--pseudocode) | LCS — Pseudocode | 3 min |
| [10.36](#1036-lcs--implementation) | LCS — Implementation | 10 min |
| [10.37](#1037-lcs--why-this-problem) | LCS — Why This Problem? | 2 min |
| [10.38](#1038-problem--word-break) | Problem — Word Break | 3 min |
| [10.39](#1039-word-break--hint) | Word Break — Hint | 3 min |
| [10.40](#1040-word-break--solution) | Word Break — Solution | 4 min |
| [10.41](#1041-word-break--pseudocode) | Word Break — Pseudocode | 3 min |
| [10.42](#1042-word-break--implementation) | Word Break — Implementation | 10 min |
| [10.43](#1043-word-break--why-this-problem) | Word Break — Why This Problem? | 2 min |
| [10.44](#1044-section-recap) | Section Recap | 3 min |

---

## 10.1 Intro
**Why dynamic programming matters · 3 min**

### Why use DP?
A naive recursive solution might branch exponentially (e.g., O(2^n)). By recognizing that the recursion evaluates the *same inputs* repeatedly (overlapping subproblems), DP caches the results. What was O(2^n) becomes O(n) or O(n²).

### When to use DP?
Look for two properties:
1. **Optimal Substructure:** The optimal solution can be constructed from optimal solutions to its subproblems (e.g., shortest path).
2. **Overlapping Subproblems:** The problem breaks down into redundant subproblems (e.g., Fibonacci).

**Signal words:** "Find the maximum/minimum," "Find the number of ways," "Is it possible to..."

### How to solve DP problems
Always identify these three elements:
1. **State:** What variables define a subproblem? (e.g., `dp[i]` = max profit at index `i`)
2. **Transition:** How does a state depend on previous states? (e.g., `dp[i] = max(dp[i-1], dp[i-2] + nums[i])`)
3. **Base cases:** Where does the transition start? (e.g., `dp[0] = 0, dp[1] = nums[0]`)

**Memoization (Top-down)** vs **Tabulation (Bottom-up)**:
- Top-down: Recursive function + hash map/array. Explores only needed states. Easiest to write from a naive recursion.
- Bottom-up: Iterative loop filling an array. Prevents stack overflow, often uses less space (e.g., saving only the last two states).

---

## 10.2 Problem — Climbing Stairs
**1D DP · [LeetCode #70](https://leetcode.com/problems/climbing-stairs/) · 🟢 Easy · 2 min**

You are climbing a staircase. It takes `n` steps to reach the top. Each time you can either climb 1 or 2 steps. In how many distinct ways can you climb to the top?

```
n = 2 → 2 (1+1, 2)
n = 3 → 3 (1+1+1, 1+2, 2+1)
```

---

## 10.3 Climbing Stairs — Hint
**The main idea · 3 min**

To reach step `i`, you either came from step `i-1` (took a 1-step) or from step `i-2` (took a 2-step). Therefore, the total ways to reach step `i` is the sum of ways to reach `i-1` and `i-2`. 
Does that relation `dp[i] = dp[i-1] + dp[i-2]` look familiar? Expected O(n) time, O(1) space.

---

## 10.4 Climbing Stairs — Solution
**The algorithm · 4 min**

This is the Fibonacci sequence. The state definition is `dp[i] = distinct ways to reach step i`.

- Transition: `dp[i] = dp[i-1] + dp[i-2]`
- Base cases: `dp[1] = 1`, `dp[2] = 2`

**Optimization:** Since we only ever need the last two states (`i-1` and `i-2`), we don't need a full array. We can just use two variables (`prev1` and `prev2`) to compute the next step, reducing space from O(n) to O(1).

---

## 10.5 Climbing Stairs — Pseudocode
**The code · 3 min**

```
if n <= 2: return n

a = 1   // approaches to step 1
b = 2   // approaches to step 2

for i from 3 to n:
    next = a + b
    a = b
    b = next

return b
```

---

## 10.6 Climbing Stairs — Implementation
**Code it yourself · 8 min**

See full solution: [`climbing_stairs.cpp`](climbing_stairs.cpp)

```cpp
class Solution {
public:
    int climbStairs(int n) {
        if (n <= 2) return n;
        
        int prev2 = 1; // ways to reach step 1
        int prev1 = 2; // ways to reach step 2
        
        for (int i = 3; i <= n; i++) {
            int current = prev1 + prev2;
            prev2 = prev1;
            prev1 = current;
        }
        
        return prev1;
    }
};
```

**Compile & run:**
```bash
g++ -std=c++17 climbing_stairs.cpp && ./a.out
```

| | Complexity |
|-|------------|
| **Time** | O(n) |
| **Space** | O(1) |

**Edge cases:** `n = 1` or `n = 2` handled before the loop.

**Common mistakes:** Using a naive recursive function `climbStairs(n-1) + climbStairs(n-2)` → O(2^n) time limit exceeded.

---

## 10.7 Climbing Stairs — Why This Problem?
**Interview context · 2 min**

- This is the quintessential "Hello World" of DP. It proves you understand state transitions.
- **Variant:** Min Cost Climbing Stairs (LeetCode #746) — attaches a cost to each step `i`, min-cost to top.
- **Variant:** Climb using 1, 2, or 3 steps → `dp[i] = dp[i-1] + dp[i-2] + dp[i-3]`.

---

## 10.8 Problem — House Robber
**1D DP with constraints · [LeetCode #198](https://leetcode.com/problems/house-robber/) · 🟡 Medium · 3 min**

You are planning to rob houses along a street. Each house has a certain amount of money hidden. The only constraint: **adjacent houses have security systems connected** and it will automatically contact the police if two adjacent houses were broken into on the same night. Return the maximum amount of money you can rob.

```
nums = [1,2,3,1] → 4 (rob house 1 and house 3: 1 + 3 = 4)
nums = [2,7,9,3,1] → 12 (rob house 1, 3, 5: 2 + 9 + 1 = 12)
```

---

## 10.9 House Robber — Hint
**The main idea · 3 min**

At any house `i`, you have a choice: you can **rob** it (and take `nums[i]` plus the max money from `i-2`), or you can **skip** it (and take the max money from `i-1`). Your state is the max money possible up to house `i`.

---

## 10.10 House Robber — Solution
**The algorithm · 4 min**

State `dp[i]` = max money you can have deciding whether to rob or skip up to index `i`.

**Transition:**
`dp[i] = max(dp[i-1], dp[i-2] + nums[i])`
Where:
- `dp[i-1]` represents the SKIP decision
- `dp[i-2] + nums[i]` represents the ROB decision

Like Climbing Stairs, we only need the two previous states. Let's call them `prev1` (max up to `i-1`) and `prev2` (max up to `i-2`).

---

## 10.11 House Robber — Pseudocode
**The code · 3 min**

```
if empty nums: return 0
prev2 = 0
prev1 = 0

for num in nums:
    current = max(prev1, prev2 + num)
    prev2 = prev1
    prev1 = current

return prev1
```

---

## 10.12 House Robber — Implementation
**Code it yourself · 8 min**

See full solution: [`house_robber.cpp`](house_robber.cpp)

```cpp
class Solution {
public:
    int rob(vector<int>& nums) {
        if (nums.empty()) return 0;
        
        int prev2 = 0; // max rob up to house i-2
        int prev1 = 0; // max rob up to house i-1
        
        for (int num : nums) {
            int current = max(prev1, prev2 + num);
            prev2 = prev1;
            prev1 = current;
        }
        
        return prev1;
    }
};
```

| | Complexity |
|-|------------|
| **Time** | O(n) |
| **Space** | O(1) |

**Edge cases:** Empty array (return 0), 1 house (return `nums[0]`), zero values.

**Common mistakes:** Trying a greedy approach (e.g., alternating houses [0, 2, 4...] vs [1, 3, 5...]) — this fails for cases like `[2, 1, 1, 2]` where the optimal is index 0 and 3 (total 4).

---

## 10.13 House Robber — Why This Problem?
**Interview context · 2 min**

- Standard intro to the "take it or leave it" decision tree pattern.
- **Follow-up:** House Robber II (LeetCode #213) — the street is circular (first and last are adjacent). Solution: Run House Robber twice (once skipping the first, once skipping the last) and take the max.
- **Variant:** Delete and Earn (LeetCode #740).

---

## 10.14 Problem — Coin Change
**Unbounded Knapsack · [LeetCode #322](https://leetcode.com/problems/coin-change/) · 🟡 Medium · 3 min**

Given integer array `coins` and an integer `amount`, return the **fewest number of coins** to make up that amount. If impossible, return `-1`. You have infinite supply of each coin.

```
coins = [1,2,5], amount = 11 → 3 (5+5+1)
coins = [2], amount = 3 → -1
```

---

## 10.15 Coin Change — Hint
**The main idea · 3 min**

`dp[a]` is the minimum coins to make amount `a`. For every amount from 1 to `target`, iterate through the coins. If you take `coin`, the number of coins needed is `1 + dp[a - coin]`. Take the minimum across all coins. Initialize the array with `amount + 1` (acting as infinity).

---

## 10.16 Coin Change — Solution
**The algorithm · 4 min**

State: `dp[a] = min coins to make amount a`.
Base case: `dp[0] = 0` (0 coins to make 0 amount).
Default value: `amount + 1` (a value strictly greater than any possible valid answer).

**Transition:**
For `a` from 1 to `amount`:
  For `c` in `coins`:
    if `a - c >= 0`:
      `dp[a] = min(dp[a], 1 + dp[a - c])`

After processing array, if `dp[amount] == amount + 1`, return `-1`. Otherwise return `dp[amount]`.

**Why not Greedy?** Greedy (picking the largest coin first) fails for inputs like `coins=[1, 3, 4, 5], amount=7`. Greedy gives `5 + 1 + 1` (3 coins). Optimal is `3 + 4` (2 coins). DP guarantees the absolute minimum.

---

## 10.17 Coin Change — Pseudocode
**The code · 3 min**

```
dp = array of size (amount + 1) initialized to (amount + 1)
dp[0] = 0

for a from 1 to amount:
    for c in coins:
        if a - c >= 0:
            dp[a] = min(dp[a], 1 + dp[a - c])

return dp[amount] if (dp[amount] != amount + 1) else -1
```

---

## 10.18 Coin Change — Implementation
**Code it yourself · 10 min**

See full solution: [`coin_change.cpp`](coin_change.cpp)

```cpp
class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        // max possible answer is amount (using 1 coins). So amount+1 acts as INF.
        int MAX = amount + 1;
        vector<int> dp(amount + 1, MAX);
        dp[0] = 0;
        
        for (int a = 1; a <= amount; a++) {
            for (int c : coins) {
                if (a - c >= 0) {
                    dp[a] = min(dp[a], 1 + dp[a - c]);
                }
            }
        }
        
        return dp[amount] == MAX ? -1 : dp[amount];
    }
};
```

| | Complexity |
|-|------------|
| **Time** | O(amount × len(coins)) |
| **Space** | O(amount) for DP array |

**Edge cases:** `amount = 0` → 0. Impossible amounts → `-1`.

**Common mistakes:**
- Initializing with `INT_MAX` → causes integer overflow when doing `1 + dp[a-c]`
- Starting the outer loop over coins instead of amounts → actually works equally well here, but looping amounts first is more intuitive for states.

---

## 10.19 Coin Change — Why This Problem?
**Interview context · 2 min**

- The quintessential "Unbounded Knapsack" problem (elements can be used infinitely).
- Shows you know memory limits and why Greedy fails.
- **Variant:** Coin Change II (LeetCode #518) — find the *number of combinations* that make the amount, instead of the minimum coins.

---

## 10.20 Problem — Longest Increasing Subsequence
**O(n²) sequence DP · [LeetCode #300](https://leetcode.com/problems/longest-increasing-subsequence/) · 🟡 Medium · 3 min**

Given integer array `nums`, return length of the longest strictly increasing subsequence.

```
nums = [10,9,2,5,3,7,101,18] → 4 (LIS is [2,3,7,101])
```

---

## 10.21 LIS — Hint
**The main idea · 3 min**

`dp[i]` = length of LIS ending exactly at index `i`.
Initialize all `dp[i] = 1`.
For each `i`, look at all `j < i`. If `nums[i] > nums[j]`, you can append `nums[i]` to the LIS ending at `j`. So `dp[i] = max(dp[i], dp[j] + 1)`.

---

## 10.22 LIS — Solution
**The algorithm · 4 min**

State: `dp[i]` = length of LIS ending at `i`.
Base: `dp[i] = 1` for all `i`.
Transition: For each `j` from 0 to `i-1`:
  If `nums[i] > nums[j]`: `dp[i] = max(dp[i], dp[j] + 1)`

Global LIS length is `max(dp)`.

*(Note: There is an O(n log n) solution using Binary Search, but the O(n²) DP solution is required knowledge first.)*

---

## 10.23 LIS — Pseudocode
**The code · 3 min**

```
dp = array of size n, initialized to 1

for i from 0 to n-1:
    for j from 0 to i-1:
        if nums[i] > nums[j]:
            dp[i] = max(dp[i], dp[j] + 1)

return max(dp)
```

---

## 10.24 LIS — Implementation
**Code it yourself · 10 min**

See full solution: [`longest_increasing_subsequence.cpp`](longest_increasing_subsequence.cpp)

```cpp
class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        int n = nums.size();
        if (n == 0) return 0;
        
        vector<int> dp(n, 1);
        int max_len = 1;
        
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < i; j++) {
                if (nums[i] > nums[j]) {
                    dp[i] = max(dp[i], dp[j] + 1);
                }
            }
            max_len = max(max_len, dp[i]);
        }
        
        return max_len;
    }
};
```

| | Complexity |
|-|------------|
| **Time** | O(n²) |
| **Space** | O(n) |

**Edge cases:** Strictly decreasing array → returns 1. Array with all same values → returns 1.

**Common mistakes:**
- Returning `dp[n-1]` instead of the global maximum across all `dp` entries. The LIS doesn't have to end at the last element.

---

## 10.25 LIS — Why This Problem?
**Interview context · 2 min**

- Standard pattern for subsequence problems.
- If asked for O(n log n) follow-up: Construct a "patience sorting" array `tails` and use binary search (`std::lower_bound`) to insert or replace.

---

## 10.26 Problem — Unique Paths
**Grid DP · [LeetCode #62](https://leetcode.com/problems/unique-paths/) · 🟡 Medium · 3 min**

Robot is at `(0, 0)` of an `m x n` grid. You can only move down or right. Return number of unique paths to reach `(m-1, n-1)`.

```
m = 3, n = 7 → 28
m = 3, n = 2 → 3
```

---

## 10.27 Unique Paths — Hint
**The main idea · 3 min**

You can only reach cell `[r][c]` from `[r-1][c]` (above) or `[r][c-1]` (left). So `paths[r][c] = paths[r-1][c] + paths[r][c-1]`.
Top row and left column are all 1s (only one straight path).

---

## 10.28 Unique Paths — Solution
**The algorithm · 4 min**

State: `dp[r][c]` = unique paths to cell.
Base cases: `dp[0][i] = 1`, `dp[i][0] = 1`.
Transition: `dp[r][c] = dp[r-1][c] + dp[r][c-1]`.

**Space Optimization:** We only ever need the row *above* us (`r-1`). We can just maintain an array of size `n` representing the previous row, and update it in place. `row[c] = row[c] + row[c-1]`.

---

## 10.29 Unique Paths — Pseudocode
**The code · 3 min**

```
row = array of size n, initialized to 1

for r from 1 to m-1:
    for c from 1 to n-1:
        row[c] = row[c] + row[c-1]  // (prev row val) + (left val)

return row[n-1]
```

---

## 10.30 Unique Paths — Implementation
**Code it yourself · 8 min**

See full solution: [`unique_paths.cpp`](unique_paths.cpp)

```cpp
class Solution {
public:
    int uniquePaths(int m, int n) {
        vector<int> row(n, 1);
        
        // Skip first row as it stays 1s
        for (int r = 1; r < m; r++) {
            for (int c = 1; c < n; c++) {
                row[c] = row[c] + row[c - 1]; // current_col = above_same_col + left_col
            }
        }
        
        return row[n - 1];
    }
};
```

| | Complexity |
|-|------------|
| **Time** | O(m × n) |
| **Space** | O(n) |

**Edge cases:** `m=1` or `n=1` → loops skipped, returns 1.

**Common mistakes:** Using a full `m x n` DP table isn't wrong, but wastes space. Optimizing to O(n) is expected in interviews.

---

## 10.31 Unique Paths — Why This Problem?
**Interview context · 2 min**

- The foundation of 2D grid DP problems.
- Note: This is also computable with Combinatorics: `(m+n-2) choose (m-1)`.
- **Variant:** Unique Paths II (LeetCode #63) — includes obstacles in the grid.

---

## 10.32 Problem — Longest Common Subsequence
**2D string DP · [LeetCode #1143](https://leetcode.com/problems/longest-common-subsequence/) · 🟡 Medium · 3 min**

Given two strings `text1` and `text2`, return the length of their longest common subsequence.

```
text1 = "abcde", text2 = "ace" → 3 ("ace")
text1 = "abc", text2 = "def" → 0
```

---

## 10.33 LCS — Hint
**The main idea · 3 min**

Use a 2D grid. Compare characters `text1[i]` and `text2[j]`. If they match, the LCS increases by 1 over the LCS of the remainder: `1 + dp[i-1][j-1]`. If they don't, take the max of advancing on string 1 vs string 2: `max(dp[i-1][j], dp[i][j-1])`.

---

## 10.34 LCS — Solution
**The algorithm · 4 min**

State: `dp[i][j]` = LCS of prefix `text1[0..i-1]` and `text2[0..j-1]`.
It's easiest to add an extra row and column of zeros to handle base cases (empty strings).

`dp[i][j]` evaluates:
- If `text1[i-1] == text2[j-1]`: `dp[i][j] = 1 + dp[i-1][j-1]` (match: diagonal + 1)
- If `text1[i-1] != text2[j-1]`: `dp[i][j] = max(dp[i-1][j], dp[i][j-1])` (mismatch: max of above or left)

---

## 10.35 LCS — Pseudocode
**The code · 3 min**

```
dp = 2D array of zeros, size (len1 + 1) x (len2 + 1)

for i from 1 to len1:
    for j from 1 to len2:
        if text1[i-1] == text2[j-1]:
            dp[i][j] = 1 + dp[i-1][j-1]
        else:
            dp[i][j] = max(dp[i-1][j], dp[i][j-1])

return dp[len1][len2]
```

---

## 10.36 LCS — Implementation
**Code it yourself · 10 min**

See full solution: [`longest_common_subsequence.cpp`](longest_common_subsequence.cpp)

```cpp
class Solution {
public:
    int longestCommonSubsequence(string text1, string text2) {
        int m = text1.size();
        int n = text2.size();
        vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
        
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                if (text1[i - 1] == text2[j - 1]) {
                    dp[i][j] = 1 + dp[i - 1][j - 1];
                } else {
                    dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
                }
            }
        }
        return dp[m][n];
    }
};
```

| | Complexity |
|-|------------|
| **Time** | O(m × n) |
| **Space** | O(m × n) |

**Edge cases:** No common characters → returns 0.

**Common mistakes:** Indexing strings out of bounds. The `+1` padding resolves this: row/col `0` means empty strings, so `text[i-1]` aligns perfectly.

---

## 10.37 LCS — Why This Problem?
**Interview context · 2 min**

- The classic 2D String matching algorithm.
- Variations test modifications to the matching logic (e.g., Edit Distance).
- **Variant:** Edit Distance (LeetCode #72)

---

## 10.38 Problem — Word Break
**Segmentation DP · [LeetCode #139](https://leetcode.com/problems/word-break/) · 🟡 Medium · 3 min**

String `s` and a dictionary of strings `wordDict`. Return `true` if `s` can be segmented into a space-separated sequence of dictionary words.

```
s = "leetcode", wordDict = ["leet","code"] → true
s = "catsandog", wordDict = ["cats","dog","sand","and","cat"] → false
```

---

## 10.39 Word Break — Hint
**The main idea · 3 min**

`dp[i]` = `true` if substring `s[0...i-1]` can be segmented. 
For every `dp[i]`, iterate over possible previous split points `j`. If `dp[j]` is true AND `s[j...i-1]` is in `wordDict`, then `dp[i]` is true.

---

## 10.40 Word Break — Solution
**The algorithm · 4 min**

State: `dp[i] = true` if `s[0..i-1]` is valid.
Base case: `dp[0] = true` (empty string is always valid).

For `i` from 1 to `s.length()`:
  For `w` in `wordDict`:
    If `w.length() <= i`:
      If `dp[i - w.length()]` is true AND `s.substr(i - w.length(), w.length()) == w`:
        `dp[i] = true`
        `break` (no need to check other words if one works)

*Note: Instead of checking all prefixes `j`, we loop through the dictionary sizes, which is generally faster if `wordDict` is small.*

---

## 10.41 Word Break — Pseudocode
**The code · 3 min**

```
dp = array of length (len(s) + 1), false
dp[0] = true

for i from 1 to len(s):
    for w in wordDict:
        if i >= w.length():
            if dp[i - w.length()] == true and s.substring(i - w.length(), w.length()) == w:
                dp[i] = true
                break

return dp[len(s)]
```

---

## 10.42 Word Break — Implementation
**Code it yourself · 10 min**

See full solution: [`word_break.cpp`](word_break.cpp)

```cpp
class Solution {
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        int n = s.size();
        vector<bool> dp(n + 1, false);
        dp[0] = true; // empty string is valid
        
        for (int i = 1; i <= n; i++) {
            for (const string& w : wordDict) {
                int len = w.size();
                // Check if string is long enough, previous split works, and substring matches
                if (i >= len && dp[i - len] && s.substr(i - len, len) == w) {
                    dp[i] = true;
                    break;
                }
            }
        }
        
        return dp[n];
    }
};
```

| | Complexity |
|-|------------|
| **Time** | O(n × M × L) where n=string len, M=dict size, L=max word len |
| **Space** | O(n) for DP array |

**Edge cases:** `wordDict` strings larger than `s` → cleanly skipped by `i >= len`. Unbreakable strings.

**Common mistakes:** Doing substring matches from every `j` without using the dictionary lengths. `std::string::substr` takes (index, length), not indices `[start, end]`.

---

## 10.43 Word Break — Why This Problem?
**Interview context · 2 min**

- Standard string segmentation pattern.
- The state checks previous valid states before verifying string chunks.
- **Variant:** Word Break II (LC #140) — return all valid segment sequences (requires backtracking/DFS with memoization).

---

## 10.44 Section Recap

| Problem | Type | State & Transition | Space Opt |
|---------|------|--------------------|-----------|
| Climbing Stairs | 1D | `dp[i] = dp[i-1] + dp[i-2]` | O(1) two vars |
| House Robber | 1D | `dp[i] = max(dp[i-1], dp[i-2] + val)` | O(1) two vars |
| Coin Change | Unbounded | `dp[a] = min(dp[a], 1 + dp[a-coin])` | N/A |
| LIS | 1D Seq | `dp[i] = max(dp[i], 1 + dp[j])` if `n[i]>n[j]`| N/A |
| Unique Paths | 2D Grid | `dp[r][c] = dp[r-1][c] + dp[r][c-1]` | O(n) row |
| LCS | 2D Str | `dp[i][j] = match ? 1+diag : max(up, left)` | O(n) 2 rows |
| Word Break | 1D Seg | `dp[i] = dp[i-len] && substr_match` | N/A |

**Core takeaways:**
- 🔑 Draw out a state diagram and a DP table for small examples.
- 🔑 Start with a brute force recursive formula in your head, then memoize, then tabulate to bottom-up.
- 🔑 1D states often optimize space down to O(1) (holding 2 variables). 2D grids often optimize space to O(N) (holding 1-2 rows).

**Next section →** [11 · Backtracking](../11_Backtracking/README.md)
