# 11 · Backtracking
> **32 units · ~100 min · Patterns: Subsets, Permutations, Combinations, Grid Search**

Backtracking is a systematic way to iterate through all possible configurations of a search space. Think of it as brute-force DFS where you stop early ("prune") the moment you realize a piece of the search tree will not yield a valid result.

---

## Unit Map

| Unit | Title | Time |
|------|-------|------|
| [11.1](#111-intro) | Intro — What backtracking solves | 3 min |
| [11.2](#112-problem--subsets) | Problem — Subsets | 2 min |
| [11.3](#113-subsets--hint) | Subsets — Hint | 3 min |
| [11.4](#114-subsets--solution) | Subsets — Solution | 4 min |
| [11.5](#115-subsets--pseudocode) | Subsets — Pseudocode | 3 min |
| [11.6](#116-subsets--implementation) | Subsets — Implementation | 8 min |
| [11.7](#117-subsets--why-this-problem) | Subsets — Why This Problem? | 2 min |
| [11.8](#118-problem--permutations) | Problem — Permutations | 3 min |
| [11.9](#119-permutations--hint) | Permutations — Hint | 3 min |
| [11.10](#1110-permutations--solution) | Permutations — Solution | 4 min |
| [11.11](#1111-permutations--pseudocode) | Permutations — Pseudocode | 3 min |
| [11.12](#1112-permutations--implementation) | Permutations — Implementation | 8 min |
| [11.13](#1113-permutations--why-this-problem) | Permutations — Why This Problem? | 2 min |
| [11.14](#1114-problem--combination-sum) | Problem — Combination Sum | 3 min |
| [11.15](#1115-combination-sum--hint) | Combination Sum — Hint | 3 min |
| [11.16](#1116-combination-sum--solution) | Combination Sum — Solution | 4 min |
| [11.17](#1117-combination-sum--pseudocode) | Combination Sum — Pseudocode | 3 min |
| [11.18](#1118-combination-sum--implementation) | Combination Sum — Implementation | 10 min |
| [11.19](#1119-combination-sum--why-this-problem) | Combination Sum — Why This Problem? | 2 min |
| [11.20](#1120-problem--generate-parentheses) | Problem — Generate Parentheses | 3 min |
| [11.21](#1121-generate-parentheses--hint) | Generate Parentheses — Hint | 3 min |
| [11.22](#1122-generate-parentheses--solution) | Generate Parentheses — Solution | 4 min |
| [11.23](#1123-generate-parentheses--pseudocode) | Generate Parentheses — Pseudocode | 3 min |
| [11.24](#1124-generate-parentheses--implementation) | Generate Parentheses — Implementation | 10 min |
| [11.25](#1125-generate-parentheses--why-this-problem) | Generate Parentheses — Why This Problem? | 2 min |
| [11.26](#1126-problem--word-search) | Problem — Word Search | 3 min |
| [11.27](#1127-word-search--hint) | Word Search — Hint | 3 min |
| [11.28](#1128-word-search--solution) | Word Search — Solution | 4 min |
| [11.29](#1129-word-search--pseudocode) | Word Search — Pseudocode | 3 min |
| [11.30](#1130-word-search--implementation) | Word Search — Implementation | 10 min |
| [11.31](#1131-word-search--why-this-problem) | Word Search — Why This Problem? | 2 min |
| [11.32](#1132-section-recap) | Section Recap | 3 min |

---

## 11.1 Intro
**What backtracking solves · 3 min**

### Why use Backtracking?
Some problems ask you to find *all* possible solutions, configurations, or paths that satisfy specific constraints (e.g., generate all subsets, passwords, permutations, crosswords). DP asks for "how many" or "maximum." Backtracking asks "give me all of them."

### When to use Backtracking?
- **Combinatorial Searches:** Generating subsets, permutations, combinations.
- **Path Puzzles:** Word Search, N-Queens, Sudoku Solver.
- **Constraints:** If it requires searching exhaustively but stopping paths when they become invalid ("pruning").

### How Backtracking works
It's DFS on an imaginary decision tree. 
**The Template:**
```cpp
void backtrack(State state, std::vector<Result>& results) {
    if (state.isValidResult()) {
        results.push_back(state.copy());
        return;
    }
    for (Choice c : state.getAvailableChoices()) {
        state.makeChoice(c);     // DO
        backtrack(state, results); // RECURSE
        state.undoChoice(c);     // UNDO (Backtrack)
    }
}
```

---

## 11.2 Problem — Subsets
**Generate all subsets · [LeetCode #78](https://leetcode.com/problems/subsets/) · 🟡 Medium · 2 min**

Given an integer array `nums` of unique elements, return all possible subsets (the power set). The solution set must not contain duplicate subsets.

```
nums = [1,2,3]
Output: [[],[1],[2],[1,2],[3],[1,3],[2,3],[1,2,3]]
```

---

## 11.3 Subsets — Hint
**The main idea · 3 min**

At every element `nums[i]`, you have exactly two choices: include it in your subset or don't include it. Use recursion ( DFS ) to systematically branch these two choices for all elements.

---

## 11.4 Subsets — Solution
**The algorithm · 4 min**

For an array of `n` elements, there are `2^n` possible subsets.
Start a DFS at index 0 with an empty `path`:
1. Add `path` to the global `results`.
2. For `i` from `start` to `nums.length`:
   - Include `nums[i]` (push to `path`)
   - Recurse starting from `i + 1`
   - Exclude `nums[i]` (**pop** from `path`)

By doing this, the loop handles the "don't include" branch implicitly when it advances to `i + 1` without maintaining the previous element.

---

## 11.5 Subsets — Pseudocode
**The code · 3 min**

```
function backtrack(start, path):
    results.append(path[:])  // append a copy!
    for i from start to len(nums):
        path.append(nums[i])
        backtrack(i + 1, path)
        path.pop()

results = []
backtrack(0, [])
return results
```

---

## 11.6 Subsets — Implementation
**Code it yourself · 8 min**

See full solution: [`subsets.cpp`](subsets.cpp)

```cpp
class Solution {
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<vector<int>> res;
        vector<int> path;
        backtrack(0, nums, path, res);
        return res;
    }
private:
    void backtrack(int start, vector<int>& nums, vector<int>& path, vector<vector<int>>& res) {
        res.push_back(path); // Add current subset
        for (int i = start; i < nums.size(); i++) {
            path.push_back(nums[i]);       // DO
            backtrack(i + 1, nums, path, res); // RECURSE
            path.pop_back();               // UNDO
        }
    }
};
```

**Compile & run:**
```bash
g++ -std=c++17 subsets.cpp && ./a.out
```

| | Complexity |
|-|------------|
| **Time** | O(2^n × n) — 2^n subsets, copying each takes n |
| **Space** | O(n) call stack |

**Edge cases:** Empty array → returns `[[]]`.

**Common mistakes:** Forgetting to pass `path` by reference, or trying to `push_back(path)` manually when you meant to push a copy. (C++ `push_back` on a vector copies the vector automatically).

---

## 11.7 Subsets — Why This Problem?
**Interview context · 2 min**

- The purest, simplest backtracking template.
- **Variant:** Subsets II (LeetCode #90) — contains duplicates, so you sort first and add a conditional `if (i > start && nums[i] == nums[i-1]) continue;` to skip branches.

---

## 11.8 Problem — Permutations
**All possible orderings · [LeetCode #46](https://leetcode.com/problems/permutations/) · 🟡 Medium · 3 min**

Given an array `nums` of distinct integers, return all the possible permutations. You can return the answer in any order.

```
nums = [1,2,3]
Output: [[1,2,3],[1,3,2],[2,1,3],[2,3,1],[3,1,2],[3,2,1]]
```

---

## 11.9 Permutations — Hint
**The main idea · 3 min**

Unlike Subsets, order matters. `[1,2]` is not `[2,1]`. Instead of starting the loop from `start`, you must start the loop from `0` every time. To prevent reusing the same element in the same permutation, you either maintain a `used` array/hashset or dynamically swap elements in place.

---

## 11.10 Permutations — Solution
**The algorithm · 4 min**

**Approach 1: `used` array**
Maintain a boolean array `used[i]`. In the DFS loop from `0` to `n-1`:
- If `used[i]` is true, skip.
- Else: `path.push_back`, set `used[i] = true`, recurse, then `path.pop_back`, set `used[i] = false`.

**Approach 2: In-place swapping**
Recursion signature `backtrack(start)`. For `i` from `start` to `n-1`:
- Swap `nums[start]` and `nums[i]`.
- Recurse `backtrack(start + 1)`.
- Swap back `nums[start]` and `nums[i]`.

Both are valid; swapping uses less space, the `used` array maintains original ordering (lexicographical).

---

## 11.11 Permutations — Pseudocode
**The code · 3 min**

```
function backtrack(path, used):
    if length of path == length of nums:
        res.append(path copy)
        return
        
    for i from 0 to len(nums):
        if not used[i]:
            used[i] = true
            path.append(nums[i])
            backtrack(path, used)
            path.pop()
            used[i] = false
```

---

## 11.12 Permutations — Implementation
**Code it yourself · 8 min**

See full solution: [`permutations.cpp`](permutations.cpp)

```cpp
class Solution {
public:
    vector<vector<int>> permute(vector<int>& nums) {
        vector<vector<int>> res;
        vector<int> path;
        vector<bool> used(nums.size(), false);
        backtrack(nums, path, used, res);
        return res;
    }
private:
    void backtrack(vector<int>& nums, vector<int>& path, vector<bool>& used, vector<vector<int>>& res) {
        if (path.size() == nums.size()) {
            res.push_back(path);
            return;
        }
        for (int i = 0; i < nums.size(); i++) {
            if (used[i]) continue;
            used[i] = true;
            path.push_back(nums[i]);
            
            backtrack(nums, path, used, res);
            
            path.pop_back();
            used[i] = false;
        }
    }
};
```

| | Complexity |
|-|------------|
| **Time** | O(n! × n) — n! permutations |
| **Space** | O(n) for used array + call stack |

**Edge cases:** 1 element array → returns single permutation.

**Common mistakes:** Forgetting to unset `used[i] = false` during the backtrack (undo) step.

---

## 11.13 Permutations — Why This Problem?
**Interview context · 2 min**

- Standard combinatorial explosion problem.
- **Variant:** Permutations II (LC #47) — array contains duplicates. Solution: sort, and skip if `i > 0 && nums[i] == nums[i-1] && !used[i-1]`.

---

## 11.14 Problem — Combination Sum
**Combinations with infinite reuse · [LeetCode #39](https://leetcode.com/problems/combination-sum/) · 🟡 Medium · 3 min**

Given an array of distinct integers `candidates` and a integer `target`, return a list of all unique combinations where the chosen numbers sum to `target`.
You may reuse the same number an unlimited number of times. Combinations are unique.

```
candidates = [2,3,6,7], target = 7
Output: [[2,2,3],[7]]
```

---

## 11.15 Combination Sum — Hint
**The main idea · 3 min**

This is like Subsets, but you can choose the same number multiple times. Instead of moving `start = i + 1` in the recursion, you move `start = i`. To stop infinite loops, only recurse when `currentSum <= target`.

---

## 11.16 Combination Sum — Solution
**The algorithm · 4 min**

State required: `target_remaining`, `start_index`, `path`.

Base cases: 
- If `target == 0`: found a valid combination, push to results. Return.
- If `target < 0`: overshoot, return.

Loop from `start_index` to `cand.size()`:
- Do: push `cand[i]` to `path`.
- Recursion: `target - cand[i]`. (Keep `start_index = i`, allowing endless reuse of current element).
- Undo: pop `cand[i]`.

---

## 11.17 Combination Sum — Pseudocode
**The code · 3 min**

```
function dfs(start, target, path):
    if target == 0:
        res.append(path copy)
        return
    if target < 0:
        return
        
    for i from start to len(candidates):
        path.append(candidates[i])
        dfs(i, target - candidates[i], path) // Notice `i` not `i+1`
        path.pop()
```

---

## 11.18 Combination Sum — Implementation
**Code it yourself · 10 min**

See full solution: [`combination_sum.cpp`](combination_sum.cpp)

```cpp
class Solution {
public:
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        vector<vector<int>> res;
        vector<int> path;
        dfs(0, target, candidates, path, res);
        return res;
    }
private:
    void dfs(int start, int target, vector<int>& cands, vector<int>& path, vector<vector<int>>& res) {
        if (target == 0) {
            res.push_back(path);
            return;
        }
        if (target < 0) return; // overshoot

        for (int i = start; i < cands.size(); i++) {
            path.push_back(cands[i]);
            dfs(i, target - cands[i], cands, path, res);
            path.pop_back();
        }
    }
};
```

| | Complexity |
|-|------------|
| **Time** | O(2^T) where T is target / min(cands). Combinatorial bounds are heavy |
| **Space** | O(T / min_cand) call stack depth max |

**Edge cases:** Candidates larger than target.

**Common mistakes:** Advancing `start` to `i+1`, breaking the "unlimited reuse" rule. Starting loop from 0 instead of `start`, leading to duplicate permutations of combinations (e.g. `[2,3]` and `[3,2]`).

---

## 11.19 Combination Sum — Why This Problem?
**Interview context · 2 min**

- Standard "Knapsack-like" backtracking.
- **Variant:** Combination Sum II (LC #40) — Candidates cannot be reused and input contains duplicates. You must sort, use `i+1`, and skip duplicates.

---

## 11.20 Problem — Generate Parentheses
**Constrained path search · [LeetCode #22](https://leetcode.com/problems/generate-parentheses/) · 🟡 Medium · 3 min**

Given `n` pairs of parentheses, write a function to generate all combinations of well-formed parentheses.

```
n = 3
Output: ["((()))","(()())","(())()","()(())","()()()"]
```

---

## 11.21 Generate Parentheses — Hint
**The main idea · 3 min**

At any point building the string, you can either add `(` or `)`. 
Rules for adding:
1. You can add `(` if `open_count < n`.
2. You can add `)` if `closed_count < open_count`.
Base case: length of string is `2 * n`.

---

## 11.22 Generate Parentheses — Solution
**The algorithm · 4 min**

Rather than generating all strings of length 2n and filtering the valid ones (O(2^(2n))), we dynamically prune invalid paths using constraints.

Maintain `open_count` and `closed_count`.
- DFS State: `string current`
- If `current.length() == n * 2` -> append to results.
- If `open_count < n`: Recurse with `open_count + 1`.
- If `closed_count < open_count`: Recurse with `closed_count + 1`.

Because C++ strings are passed by value if not referenced, the "undo" step happens automatically via the stack dropping the local string.

---

## 11.23 Generate Parentheses — Pseudocode
**The code · 3 min**

```
function backtrack(openN, closedN, current_str):
    if openN == n and closedN == n:
        res.append(current_str)
        return
        
    if openN < n:
        backtrack(openN + 1, closedN, current_str + "(")
    if closedN < openN:
        backtrack(openN, closedN + 1, current_str + ")")
```

---

## 11.24 Generate Parentheses — Implementation
**Code it yourself · 10 min**

See full solution: [`generate_parentheses.cpp`](generate_parentheses.cpp)

```cpp
class Solution {
public:
    vector<string> generateParenthesis(int n) {
        vector<string> res;
        backtrack(0, 0, n, "", res);
        return res;
    }
private:
    void backtrack(int openN, int closedN, int n, string current, vector<string>& res) {
        if (current.size() == n * 2) {
            res.push_back(current);
            return;
        }
        if (openN < n) {
            backtrack(openN + 1, closedN, n, current + "(", res);
        }
        if (closedN < openN) {
            backtrack(openN, closedN + 1, n, current + ")", res);
        }
    }
};
```

| | Complexity |
|-|------------|
| **Time** | O(4^n / sqrt(n)) Catalan number bounds |
| **Space** | O(n) stack depth |

**Edge cases:** `n = 1` -> `["()"]`

**Common mistakes:** Using `closed_count < n` instead of `closed_count < open_count`, which leads to structurally incorrect prefixes.

---

## 11.25 Generate Parentheses — Why This Problem?
**Interview context · 2 min**

- Excellent pruning demonstration. It is standard string construction backtracking.
- Passing `string current` natively copies it, making it look cleaner than `string& current` + `push_back`/`pop_back` (though latter is slightly faster).

---

## 11.26 Problem — Word Search
**Grid traversal backtracking · [LeetCode #79](https://leetcode.com/problems/word-search/) · 🟡 Medium · 3 min**

Given an `m x n` grid of characters `board` and a string `word`, return `true` if `word` exists in the grid.
The word can be constructed from letters of sequentially adjacent cells (horizontal or vertical). The same letter cell may not be used more than once.

```
Input: board = [
  ["A","B","C","E"],
  ["S","F","C","S"],
  ["A","D","E","E"]
], word = "ABCCED"
Output: true
```

---

## 11.27 Word Search — Hint
**The main idea · 3 min**

Iterate through every cell. If a cell matches the first letter of `word`, launch a DFS Backtracking search. 
During search, mark cells as visited. If a branch fails, **unmark** the cell and backtrack to try another path.

---

## 11.28 Word Search — Solution
**The algorithm · 4 min**

Iterate `r` and `c` on the board.
`dfs(r, c, index_in_word)`:
- If `index == word.length()` return true (Success!)
- If `r, c` out of bounds, or `board[r][c] != word[index]`, or cell is visited, return false.
- Do: Mark cell globally (e.g., set `board[r][c] = '#'`).
- Recurse: Check 4 directions `dfs(r+1,c)` or `dfs(r-1,c)`... 
  If any return true, immediately return true.
- Undo: Reset `board[r][c] = word[index]`.

---

## 11.29 Word Search — Pseudocode
**The code · 3 min**

```
function dfs(r, c, index):
    if index == len(word): return true
    if r, c out of bounds or visited or board[r][c] != word[index]: 
        return false
        
    temp = board[r][c]
    board[r][c] = '#' // mark visited in-place
    
    res = dfs(r+1, c, i+1) or dfs(r-1, c, i+1) ...
    
    board[r][c] = temp // backtrack
    return res

for r to rows:
    for c to cols:
        if board[r][c] == word[0] and dfs(r, c, 0):
            return true
```

---

## 11.30 Word Search — Implementation
**Code it yourself · 10 min**

See full solution: [`word_search.cpp`](word_search.cpp)

```cpp
class Solution {
public:
    bool exist(vector<vector<char>>& board, string word) {
        int rows = board.size();
        int cols = board[0].size();
        
        for (int r = 0; r < rows; r++) {
            for (int c = 0; c < cols; c++) {
                if (board[r][c] == word[0] && dfs(r, c, 0, board, word)) {
                    return true;
                }
            }
        }
        return false;
    }
private:
    bool dfs(int r, int c, int i, vector<vector<char>>& board, string& word) {
        if (i == word.size()) return true;
        
        if (r < 0 || r >= board.size() || c < 0 || c >= board[0].size() || 
            board[r][c] != word[i]) {
            return false;
        }
        
        char temp = board[r][c];
        board[r][c] = '#'; // Mark as visited in-place
        
        bool res = dfs(r+1, c, i+1, board, word) ||
                   dfs(r-1, c, i+1, board, word) ||
                   dfs(r, c+1, i+1, board, word) ||
                   dfs(r, c-1, i+1, board, word);
                   
        board[r][c] = temp; // Undo
        return res;
    }
};
```

| | Complexity |
|-|------------|
| **Time** | O(N * 3^L) where N is cells on board, L length of word |
| **Space** | O(L) max recursion depth |

**Edge cases:** Single character matrix, single character word. 

**Common mistakes:** Not undoing the `#` visit flag. This permanently breaks the board for future coordinate DFS checks!

---

## 11.31 Word Search — Why This Problem?
**Interview context · 2 min**

- Standard 2D grid backtracking (unlike simple flooding, paths matter).
- **Variant:** Word Search II (LeetCode #212) — Searching for multiple words simultaneously. Requires building a Trie prefix tree to prune paths aggressively.

---

## 11.32 Section Recap

| Problem | Constraints & Structure |
|---------|-------------------------|
| Subsets | Pick/Not Pick, start index advances |
| Permutations | Order matters, use boolean `visited` mask |
| Combination Sum | Reusable items, start index doesn't strictly advance |
| Gen Parentheses | String building logic masks constraints |
| Word Search | Grid mapping, in-place visited arrays (`#`) |

**Core takeaways:**
- 🔑 Always ensure the "Undo" code effectively happens exactly symmetrically to the "Do" code. Pass by value vs reference matters.
- 🔑 The DFS Tree visualization holds the key. Draw the decision branches.
- 🔑 Start loops from `0` when order matters (permutations). Start loops from `start` when just picking combos/subsets.

---
*End of roadmap. You've completed 11 sections.*
