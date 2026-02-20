# 05 · Stacks
> **26 units · ~80 min · Patterns: LIFO Matching, Monotonic Stack**

A stack is Last-In-First-Out (LIFO). Use it when you need to match pairs (brackets), track the "most recent" item, or process things in reverse. Two main patterns: **matching/validation** and **monotonic stacks** (next greater element). Both appear frequently at MAANG.

---

## Unit Map

| Unit | Title | Time |
|------|-------|------|
| [5.1](#51-intro) | Intro — When to use stacks | 2 min |
| [5.2](#52-problem--valid-parentheses) | Problem — Valid Parentheses | 3 min |
| [5.3](#53-valid-parentheses--hint) | Valid Parentheses — Hint | 3 min |
| [5.4](#54-valid-parentheses--solution) | Valid Parentheses — Solution | 4 min |
| [5.5](#55-valid-parentheses--pseudocode) | Valid Parentheses — Pseudocode | 3 min |
| [5.6](#56-valid-parentheses--implementation) | Valid Parentheses — Implementation | 10 min |
| [5.7](#57-valid-parentheses--why-this-problem) | Valid Parentheses — Why This Problem? | 2 min |
| [5.8](#58-problem--min-stack) | Problem — Min Stack | 3 min |
| [5.9](#59-min-stack--hint) | Min Stack — Hint | 3 min |
| [5.10](#510-min-stack--solution) | Min Stack — Solution | 4 min |
| [5.11](#511-min-stack--pseudocode) | Min Stack — Pseudocode | 3 min |
| [5.12](#512-min-stack--implementation) | Min Stack — Implementation | 10 min |
| [5.13](#513-min-stack--why-this-problem) | Min Stack — Why This Problem? | 2 min |
| [5.14](#514-problem--next-greater-element-i) | Problem — Next Greater Element I | 2 min |
| [5.15](#515-next-greater-element-i--hint) | Next Greater Element I — Hint | 3 min |
| [5.16](#516-next-greater-element-i--solution) | Next Greater Element I — Solution | 3 min |
| [5.17](#517-next-greater-element-i--pseudocode) | Next Greater Element I — Pseudocode | 3 min |
| [5.18](#518-next-greater-element-i--implementation) | Next Greater Element I — Implementation | 8 min |
| [5.19](#519-next-greater-element-i--why-this-problem) | Next Greater Element I — Why This Problem? | 2 min |
| [5.20](#520-problem--daily-temperatures) | Problem — Daily Temperatures | 3 min |
| [5.21](#521-daily-temperatures--hint) | Daily Temperatures — Hint | 3 min |
| [5.22](#522-daily-temperatures--solution) | Daily Temperatures — Solution | 4 min |
| [5.23](#523-daily-temperatures--pseudocode) | Daily Temperatures — Pseudocode | 3 min |
| [5.24](#524-daily-temperatures--implementation) | Daily Temperatures — Implementation | 10 min |
| [5.25](#525-daily-temperatures--why-this-problem) | Daily Temperatures — Why This Problem? | 2 min |
| [5.26](#526-section-recap) | Section Recap | 2 min |

---

## 5.1 Intro
**When to use stacks · 2 min**

A stack is Last-In-First-Out (LIFO). The last element you push is the first one you pop. Use a stack when you need to:
- Match pairs (parentheses, HTML tags)
- Track the "most recent" unsettled item
- Process things in reverse order

Two patterns appear in MAANG interviews:
1. **Matching/validation** — push opens, pop on close
2. **Monotonic stacks** — maintain a stack in increasing or decreasing order to answer "next greater/smaller" queries in O(n)

---

## 5.2 Problem — Valid Parentheses
**The classic stack problem · [LeetCode #20](https://leetcode.com/problems/valid-parentheses/) · 🟢 Easy · 3 min**

Given a string `s` containing only `'('`, `')'`, `'{'`, `'}'`, `'['`, `']'`, determine if the input string is **valid**.

A string is valid if:
- Every open bracket is closed by the same type of bracket
- Open brackets are closed in the correct order
- Every close bracket has a corresponding open bracket

```
Input: s = "()"      → true
Input: s = "()[]{}"  → true
Input: s = "(]"      → false
Input: s = "([)]"    → false
Input: s = "{[]}"    → true
```

---

## 5.3 Valid Parentheses — Hint
**The main idea · 3 min**

Use a stack for opening brackets. When you encounter a closing bracket, check if the top of the stack is the matching opener. If yes → pop. If no → invalid. At the end, the stack must be empty.

Build a close→open map: `{')':'(', '}':'{', ']':'['}` to look up the expected opener in O(1).

---

## 5.4 Valid Parentheses — Solution
**The algorithm · 4 min**

For each character `c` in `s`:
- If `c` is a **close bracket**: check if `stack` is non-empty AND `stack.top() == closeToOpen[c]`. If both → pop. Otherwise → return `false`.
- If `c` is an **open bracket**: push to stack.

After the loop, return `stack.empty()` — any unpaired openers make it invalid.

**Key insight:** The stack order tracks the "most recently opened unmatched bracket," which must match the next close bracket.

---

## 5.5 Valid Parentheses — Pseudocode
**The code · 3 min**

```
closeToOpen = { ')':'(', '}':'{', ']':'[' }
stack = []

for c in s:
    if c in closeToOpen:        // closing bracket
        if stack and stack.top == closeToOpen[c]:
            stack.pop()
        else:
            return false
    else:
        stack.push(c)           // opening bracket

return stack.empty()
```

---

## 5.6 Valid Parentheses — Implementation
**Code it yourself · 10 min**

### ✅ C++ & C# Solutions
See [`valid_parentheses.cpp`](valid_parentheses.cpp) | [`valid_parentheses.cs`](valid_parentheses.cs)

**C++ Implementation**
```cpp
class Solution {
public:
    bool isValid(string s) {
        stack<char> st;
        unordered_map<char, char> closeToOpen = {
            {')', '('}, {'}', '{'}, {']', '['}
        };
        for (char c : s) {
            if (closeToOpen.count(c)) {
                // closing bracket: stack must have matching opener
                if (st.empty() || st.top() != closeToOpen[c])
                    return false;
                st.pop();
            } else {
                st.push(c);   // opening bracket
            }
        }
        return st.empty();
    }
};
```

**C# Implementation**
```csharp
using System.Collections.Generic;

public class Solution {
    public bool IsValid(string s) {
        var stack = new Stack<char>();
        var map = new Dictionary<char, char> {
            {')', '('},
            {'}', '{'},
            {']', '['}
        };
        
        foreach (char c in s) {
            if (map.ContainsKey(c)) {
                if (stack.Count == 0 || stack.Peek() != map[c]) {
                    return false;
                }
                stack.Pop();
            } else {
                stack.Push(c);
            }
        }
        
        return stack.Count == 0;
    }
}
```

**Compile & run (C++):**
```bash
g++ -std=c++17 valid_parentheses.cpp && ./a.out
```

| | Complexity |
|-|------------|
| **Time** | O(n) — single pass |
| **Space** | O(n) — stack holds up to n/2 openers |

**Edge cases:**
- Odd-length string → always `false` (but algorithm handles it naturally)
- `"]"` with empty stack → `false` (caught by `st.empty()` check)
- `"([)]"` → `false` (inner close doesn't match inner open)

**Common mistakes:**
- Forgetting `st.empty()` check before `st.top()` → null dereference
- Wrong mapping direction (open→close instead of close→open)

---

## 5.7 Valid Parentheses — Why This Problem?
**Interview context · 2 min**

- Classic "first stack problem" — asked at Google, Amazon, Meta constantly
- Shows you know when to reach for a stack
- **Follow-up:** *"What about HTML/XML tag validation?"* → Same approach, store tag name strings instead of chars
- **Follow-up:** *"What if there's whitespace or other characters?"* → Skip non-bracket characters

---

## 5.8 Problem — Min Stack
**Stack with O(1) minimum · [LeetCode #155](https://leetcode.com/problems/min-stack/) · 🟡 Medium · 3 min**

Design a stack that supports `push`, `pop`, `top`, and **`getMin()`** — all in **O(1) time**.

```
MinStack ms;
ms.push(-2); ms.push(0); ms.push(-3);
ms.getMin() → -3
ms.pop();
ms.top()    → 0
ms.getMin() → -2
```

---

## 5.9 Min Stack — Hint
**The main idea · 3 min**

Store pairs `(value, current_min_so_far)` instead of just values. When you push a new element, the new min is `min(val, stack.top().second)`. When you pop, the min is automatically restored because each frame carries its own snapshot of the minimum.

---

## 5.10 Min Stack — Solution
**The algorithm · 4 min**

**Key insight:** Each stack frame stores `(value, minimum_of_everything_below_and_including_this_frame)`. So `getMin()` is always just `stack.top().second` — O(1).

On `push(val)`:
- `currentMin = stack.empty() ? val : min(val, stack.top().second)`
- Push `{val, currentMin}`

On `pop()`: just pop the top pair.  
`top()`: return `stack.top().first`  
`getMin()`: return `stack.top().second`

---

## 5.11 Min Stack — Pseudocode
**The code · 3 min**

```
stack of (value, min_so_far) pairs

push(val):
    current_min = stack.empty() ? val : min(val, stack.top().second)
    stack.push( {val, current_min} )

pop():    stack.pop()
top():    return stack.top().first
getMin(): return stack.top().second
```

---

## 5.12 Min Stack — Implementation
**Code it yourself · 10 min**

### ✅ C++ & C# Solutions
See [`min_stack.cpp`](min_stack.cpp) | [`min_stack.cs`](min_stack.cs)

**C++ Implementation**
```cpp
class MinStack {
    stack<pair<int,int>> st;   // {value, min_so_far}
public:
    MinStack() {} // Constructor
    void push(int val) {
        int currentMin = st.empty() ? val : min(val, st.top().second);
        st.push({val, currentMin});
    }
    
    void pop() {
        st.pop();
    }
    
    int top() {
        return st.top().first;
    }
    
    int getMin() {
        return st.top().second;
    }
};
```

**C# Implementation**
```csharp
using System;
using System.Collections.Generic;

public class MinStack {
    private Stack<int> stack;
    private Stack<int> minStack;

    public MinStack() {
        stack = new Stack<int>();
        minStack = new Stack<int>();
    }
    
    public void Push(int val) {
        stack.Push(val);
        if (minStack.Count == 0 || val <= minStack.Peek()) {
            minStack.Push(val);
        }
    }
    
    public void Pop() {
        if (stack.Count == 0) return;
        int popped = stack.Pop();
        if (minStack.Count > 0 && popped == minStack.Peek()) {
            minStack.Pop();
        }
    }
    
    public int Top() { return stack.Peek(); }
    public int GetMin() { return minStack.Peek(); }
}
```

| | Complexity |
|-|------------|
| **Time** | O(1) for all operations |
| **Space** | O(n) — stores two integers per element |

**Edge cases:**
- Empty stack before calling `top()`/`pop()`/`getMin()` — problem guarantees valid calls
- Duplicate minimums — handled correctly (each frame tracks its own min)

**Common mistakes:**
- Using a separate min-stack that gets out of sync with the main stack
- Forgetting to handle the empty stack on `push`

---

## 5.13 Min Stack — Why This Problem?
**Interview context · 2 min**

- Tests "augmented data structure" thinking — wrap existing structure with extra metadata
- **Follow-up:** *"Can you do it with two separate stacks?"* → Yes: `minStack` only pushes when new val ≤ current min; pop only when top equals current min
- **Variant:** Max stack (symmetrical)

---

## 5.14 Problem — Next Greater Element I
**Introduction to monotonic stack · [LeetCode #496](https://leetcode.com/problems/next-greater-element-i/) · 🟢 Easy · 2 min**

`nums1` is a subset of `nums2`. For each element in `nums1`, find its **next greater element** in `nums2`. Return `-1` if none exists.

```
nums1 = [4,1,2], nums2 = [1,3,4,2]
Output: [-1, 3, -1]
  4 → no element greater than 4 to its right in nums2 → -1
  1 → next greater after 1 in nums2 is 3           → 3
  2 → no element greater than 2 to its right         → -1
```

---

## 5.15 Next Greater Element I — Hint
**The main idea · 3 min**

Use a **monotonic decreasing stack** on `nums2`. Process each element; while the stack's top is smaller than the current element, the current element is the "next greater" for whatever's on top. Record this in a hash map. Then answer `nums1` queries from the map.

---

## 5.16 Next Greater Element I — Solution
**The algorithm · 3 min**

Precompute `nextGreater[val]` for every val in `nums2`:

1. Traverse `nums2` left to right
2. Maintain a monotonic **decreasing** stack (values, not indices)
3. For each `num`: while `stack.top() < num` → `nextGreater[stack.top()] = num`; pop
4. Push `num` onto stack
5. Remaining items in stack have no next greater → they keep `-1` (default)

Then for each element in `nums1`: look up `nextGreater[element]`.

---

## 5.17 Next Greater Element I — Pseudocode
**The code · 3 min**

```
nextGreater = { n: -1 for n in nums1 }   // default -1
stack = []

for num in nums2:
    while stack and num > stack.top():
        nextGreater[stack.top()] = num
        stack.pop()
    if num in nextGreater:       // only track nums1 elements
        stack.push(num)

return [nextGreater[n] for n in nums1]
```

---

## 5.18 Next Greater Element I — Implementation
**Code it yourself · 8 min**

### ✅ C++ & C# Solutions
See [`next_greater_element.cpp`](next_greater_element.cpp) | [`next_greater_element.cs`](next_greater_element.cs)

**C++ Implementation**
```cpp
class Solution {
public:
    vector<int> nextGreaterElement(vector<int>& nums1, vector<int>& nums2) {
        unordered_map<int, int> nextGreater;
        stack<int> st;  // monotonic decreasing

        for (int num : nums2) {
            while (!st.empty() && st.top() < num) {
                nextGreater[st.top()] = num;
                st.pop();
            }
            st.push(num);
        }
        // anything remaining in stack has no next greater → stays -1

        vector<int> result;
        for (int n : nums1)
            result.push_back(nextGreater.count(n) ? nextGreater[n] : -1);
        
        return result;
    }
};
```

**C# Implementation**
```csharp
using System.Collections.Generic;

public class Solution {
    public int[] NextGreaterElement(int[] nums1, int[] nums2) {
        var nextGreater = new Dictionary<int, int>();
        var stack = new Stack<int>();
        
        foreach (int num in nums2) {
            while (stack.Count > 0 && stack.Peek() < num) {
                nextGreater[stack.Pop()] = num;
            }
            stack.Push(num);
        }
        
        int[] result = new int[nums1.Length];
        for (int i = 0; i < nums1.Length; i++) {
            result[i] = nextGreater.ContainsKey(nums1[i]) ? nextGreater[nums1[i]] : -1;
        }
        
        return result;
    }
}
```

| | Complexity |
|-|------------|
| **Time** | O(n + m) — n = nums2 length, m = nums1 length |
| **Space** | O(n) — map + stack |

**Edge cases:**
- Decreasing `nums2` → all answers are `-1`
- All elements in `nums1` are the largest in `nums2` → all `-1`

**Common mistakes:**
- Pushing all of `nums2` to the stack instead of only relevant elements
- Using a monotonic *increasing* stack instead of decreasing

---

## 5.19 Next Greater Element I — Why This Problem?
**Interview context · 2 min**

- Introduces the monotonic stack pattern — once you see it here, Daily Temperatures and Largest Rectangle in Histogram become straightforward
- **Variant:** Next Greater Element II (circular array, LeetCode #503) — traverse array twice
- **More advanced:** Trapping Rain Water (LeetCode #42) uses the same "find the boundary" intuition

---

## 5.20 Problem — Daily Temperatures
**Monotonic stack pattern · [LeetCode #739](https://leetcode.com/problems/daily-temperatures/) · 🟡 Medium · 3 min**

Given `temperatures`, return an array where `answer[i]` is the number of days until a warmer temperature. Return `0` if no warmer day exists.

```
Input:  [73, 74, 75, 71, 69, 72, 76, 73]
Output: [1,  1,  4,  2,  1,  1,  0,  0]
```

---

## 5.21 Daily Temperatures — Hint
**The main idea · 3 min**

Use a monotonic **decreasing** stack of **indices** (not values). When you find a day warmer than the day on the top of the stack, you've found the "next warmer day" for that stack entry. The answer = current index − stored index.

---

## 5.22 Daily Temperatures — Solution
**The algorithm · 4 min**

Traverse the array. For each day `i`:
- While `stack` is not empty AND `temperatures[i] > temperatures[stack.top()]`:
  - Pop `prevDay` from stack
  - `result[prevDay] = i - prevDay`
- Push `i` onto the stack

At the end, all remaining indices in the stack have `result[i] = 0` (no warmer day found).

**Why does this work?** The stack maintains indices of days whose "next warmer day" hasn't been found yet, in decreasing order of temperature. The first day warmer than the top resolves it.

---

## 5.23 Daily Temperatures — Pseudocode
**The code · 3 min**

```
result = [0] * n
stack = []          // indices with unresolved "next warmer"

for i from 0 to n-1:
    while stack and temperatures[i] > temperatures[stack.top()]:
        prevDay = stack.pop()
        result[prevDay] = i - prevDay
    stack.push(i)

return result
```

---

## 5.24 Daily Temperatures — Implementation
**Code it yourself · 10 min**

### ✅ C++ & C# Solutions
See [`daily_temperatures.cpp`](daily_temperatures.cpp) | [`daily_temperatures.cs`](daily_temperatures.cs)

**C++ Implementation**
```cpp
class Solution {
public:
    vector<int> dailyTemperatures(vector<int>& temperatures) {
        int n = temperatures.size();
        vector<int> result(n, 0);
        stack<int> st;   // stores indices, monotonically decreasing temperatures

        for (int i = 0; i < n; i++) {
            while (!st.empty() && temperatures[i] > temperatures[st.top()]) {
                int prevDay = st.top(); st.pop();
                result[prevDay] = i - prevDay;
            }
            st.push(i);
        }
}
};
```

**C# Implementation**
```csharp
using System.Collections.Generic;

public class Solution {
    public int[] DailyTemperatures(int[] temperatures) {
        int n = temperatures.Length;
        int[] result = new int[n];
        var stack = new Stack<int>(); // stores indices
        
        for (int i = 0; i < n; i++) {
            while (stack.Count > 0 && temperatures[i] > temperatures[stack.Peek()]) {
                int prevDay = stack.Pop();
                result[prevDay] = i - prevDay;
            }
            stack.Push(i);
        }
        
        return result;
    }
}
```

| | Complexity |
|-|------------|
| **Time** | O(n) — each index pushed and popped at most once |
| **Space** | O(n) — stack in worst case (all decreasing) |

**Edge cases:**
- Constant temperatures → all `0`s
- Strictly increasing → each day's answer is `1`
- Last element → always `0`

**Common mistakes:**
- Storing values instead of **indices** → can't compute the distance
- Forgetting that equal temperatures do NOT count as "warmer"

---

## 5.25 Daily Temperatures — Why This Problem?
**Interview context · 2 min**

- One of the best intro problems for monotonic stacks
- **Amortized O(n):** Each element is pushed once and popped at most once = 2n total ops
- **Follow-up:** *"Solve without extra space?"* → Strictly speaking you can't without O(n) if you need the output array
- **Generalization:** "Days until price exceeds X" — immediate application in stock problems

---

## 5.26 Section Recap
**What you learned · 2 min**

| Problem | Pattern | Data Stored | Time | Space |
|---------|---------|-------------|------|-------|
| Valid Parentheses | LIFO Matching | Characters | O(n) | O(n) |
| Min Stack | Augmented Stack | (val, min) pairs | O(1) all ops | O(n) |
| Next Greater Element I | Monotonic Decreasing Stack | Values | O(n+m) | O(n) |
| Daily Temperatures | Monotonic Decreasing Stack | **Indices** | O(n) | O(n) |

**Core takeaways:**
- 🔑 Stack for matching: push openers, check/pop on closers
- 🔑 Augmented stack: carry extra metadata in each frame
- 🔑 Monotonic stack: O(n) answer to "next greater/smaller" for all elements
- 🔑 Store **indices** (not values) when you need to compute distances

**Next section →** [06 · Trees & BST](../06_Trees_and_BST/README.md)
