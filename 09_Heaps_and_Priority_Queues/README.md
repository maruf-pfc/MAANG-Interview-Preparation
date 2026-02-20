# 09 · Heaps & Priority Queues
> **26 units · ~82 min · Patterns: Fixed-size Min-Heap, Two Heaps, K-Way Merge**

A heap gives you O(1) access to the min/max and O(log n) insert/delete. Use heaps when you need to repeatedly access the extreme element from a dynamic set.

---

## Unit Map

| Unit | Title | Time |
|------|-------|------|
| [9.1](#91-intro) | Intro — When to use heaps | 2 min |
| [9.2](#92-problem--kth-largest-element) | Problem — Kth Largest Element | 3 min |
| [9.3](#93-kth-largest--hint) | Kth Largest — Hint | 3 min |
| [9.4](#94-kth-largest--solution) | Kth Largest — Solution | 4 min |
| [9.5](#95-kth-largest--pseudocode) | Kth Largest — Pseudocode | 3 min |
| [9.6](#96-kth-largest--implementation) | Kth Largest — Implementation | 10 min |
| [9.7](#97-kth-largest--why-this-problem) | Kth Largest — Why This Problem? | 2 min |
| [9.8](#98-problem--kth-largest-in-a-stream) | Problem — Kth Largest in a Stream | 2 min |
| [9.9](#99-kth-largest-stream--hint) | Kth Largest Stream — Hint | 3 min |
| [9.10](#910-kth-largest-stream--solution) | Kth Largest Stream — Solution | 3 min |
| [9.11](#911-kth-largest-stream--pseudocode) | Kth Largest Stream — Pseudocode | 3 min |
| [9.12](#912-kth-largest-stream--implementation) | Kth Largest Stream — Implementation | 10 min |
| [9.13](#913-kth-largest-stream--why-this-problem) | Kth Largest Stream — Why This Problem? | 2 min |
| [9.14](#914-problem--find-median-from-data-stream) | Problem — Find Median from Data Stream | 3 min |
| [9.15](#915-find-median--hint) | Find Median — Hint | 3 min |
| [9.16](#916-find-median--solution) | Find Median — Solution | 4 min |
| [9.17](#917-find-median--pseudocode) | Find Median — Pseudocode | 3 min |
| [9.18](#918-find-median--implementation) | Find Median — Implementation | 10 min |
| [9.19](#919-find-median--why-this-problem) | Find Median — Why This Problem? | 2 min |
| [9.20](#920-problem--merge-k-sorted-lists) | Problem — Merge K Sorted Lists | 3 min |
| [9.21](#921-merge-k-sorted-lists--hint) | Merge K Sorted Lists — Hint | 3 min |
| [9.22](#922-merge-k-sorted-lists--solution) | Merge K Sorted Lists — Solution | 4 min |
| [9.23](#923-merge-k-sorted-lists--pseudocode) | Merge K Sorted Lists — Pseudocode | 3 min |
| [9.24](#924-merge-k-sorted-lists--implementation) | Merge K Sorted Lists — Implementation | 10 min |
| [9.25](#925-merge-k-sorted-lists--why-this-problem) | Merge K Sorted Lists — Why This Problem? | 2 min |
| [9.26](#926-section-recap) | Section Recap | 2 min |

---

## 9.1 Intro
**When to use heaps · 2 min**

### Why use a heap?
A sorted array gives you min in O(1) but inserts take O(n). A heap gives **O(log n) insert** and **O(1) peek** at min/max. When you need fast access to the extreme element from a changing dataset, heap is the right tool.

### When to use a heap?
| Signal | Pattern |
|--------|---------|
| "Kth largest/smallest" | Fixed-size min-heap of size K |
| "Top K elements" | Fixed-size min-heap |
| "Streaming median" | Two heaps (max + min) |
| "Merge K sorted" | Min-heap with K fronts |
| "K closest points" | Fixed-size max-heap of size K |

### How a heap works

A binary **min-heap** is a complete binary tree where every parent ≤ children. Root = global minimum.

```cpp
// C++ heap syntax
priority_queue<int> maxHeap;                           // max-heap (default)
priority_queue<int, vector<int>, greater<int>> minHeap; // min-heap

minHeap.push(val);   // O(log n)
minHeap.pop();       // O(log n) — removes top
minHeap.top();       // O(1)    — peek without removing
```

### The three heap patterns
1. **Fixed-size min-heap (size K)** → Stores top-K largest; top = Kth largest
2. **Two heaps** → O(1) median from running stream
3. **K-way merge** → One element from each of K sorted sources in heap

---

## 9.2 Problem — Kth Largest Element
**[LeetCode #215](https://leetcode.com/problems/kth-largest-element-in-an-array/) · 🟡 Medium · 3 min**

Find the **Kth largest** element in an unsorted array (Kth in sorted descending order).

```
[3,2,1,5,6,4], k=2  →  5
[3,2,3,1,2,4,5,5,6], k=4  →  4
```

---

## 9.3 Kth Largest — Hint
**The main idea · 3 min**

Maintain a **min-heap of size K**. The top of this heap is always the Kth largest seen so far. When heap grows past K, pop the minimum (it can't be in the top K). After all elements, `top()` is the answer.

---

## 9.4 Kth Largest — Solution
**The algorithm · 4 min**

**Why a min-heap?** We keep the K *largest* elements. To efficiently remove the element that's too small, we need fast access to the *minimum* of those K — that's a min-heap.

For each element `n`:
- Push onto min-heap
- If `heap.size() > k`: pop the smallest (no longer qualifies for top-K)

Final `heap.top()` = smallest of top-K = Kth largest.

**Alternative:** QuickSelect — O(n) average, O(n²) worst.

---

## 9.5 Kth Largest — Pseudocode

```
minHeap = []  (min-heap)

for each n in nums:
    minHeap.push(n)
    if minHeap.size() > k:
        minHeap.pop()      // too small to be in top-K

return minHeap.top()       // Kth largest
```

---

## 9.6 Kth Largest — Implementation

See full solution: [`kth_largest_element.cpp`](kth_largest_element.cpp)

```cpp
class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        priority_queue<int, vector<int>, greater<int>> minHeap;
        for (int n : nums) {
            minHeap.push(n);
            if ((int)minHeap.size() > k)
                minHeap.pop();
        }
        return minHeap.top();
    }
};
```

```bash
g++ -std=c++17 kth_largest_element.cpp && ./a.out
```

| | Time | Space |
|-|------|-------|
| **Complexity** | O(n log k) | O(k) |

**Edge cases:** `k=1` → max element. `k=n` → min element. Duplicates are fine.

**Common mistakes:** Using max-heap instead of min-heap → pops the largest, wrong answer.

---

## 9.7 Kth Largest — Why This Problem?
**Interview context · 2 min**

- Foundation for "Top K frequent elements" (LeetCode #347) — same fixed-size heap trick
- Mention both: min-heap O(n log k) for streaming, QuickSelect O(n) if the array is known upfront

---

## 9.8 Problem — Kth Largest in a Stream
**[LeetCode #703](https://leetcode.com/problems/kth-largest-element-in-a-stream/) · 🟢 Easy · 2 min**

Design a class: `add(val)` inserts a new number and returns the current Kth largest.

```
KthLargest kl(3, [4,5,8,2]);
kl.add(3) → 4,  kl.add(5) → 5,  kl.add(10) → 5
```

---

## 9.9 Kth Largest Stream — Hint
**The main idea · 3 min**

A **persistent min-heap of size K**. Initialize by inserting `nums` and trimming to K. `add(val)` pushes and trims. `top()` is always the answer.

---

## 9.10 Kth Largest Stream — Solution
**The algorithm · 3 min**

The heap always holds the K largest seen. When a new element arrives smaller than the Kth largest, it's discarded. When larger, it replaces the old Kth largest (pop old top, push new).

---

## 9.11 Kth Largest Stream — Pseudocode

```
init(k, nums):
    for n in nums: push(n); if size > k: pop()

add(val):
    push(val)
    if size > k: pop()
    return top()
```

---

## 9.12 Kth Largest Stream — Implementation

See full solution: [`kth_largest_stream.cpp`](kth_largest_stream.cpp)

```cpp
class KthLargest {
    priority_queue<int, vector<int>, greater<int>> minHeap;
    int k;
public:
    KthLargest(int k, vector<int>& nums) : k(k) {
        for (int n : nums) {
            minHeap.push(n);
            if ((int)minHeap.size() > k) minHeap.pop();
        }
    }
    int add(int val) {
        minHeap.push(val);
        if ((int)minHeap.size() > k) minHeap.pop();
        return minHeap.top();
    }
};
```

| | Time | Space |
|-|------|-------|
| **add()** | O(log k) | O(k) |

**Edge cases:** Initial `nums` may have fewer than K elements — early `add()` calls build up the heap to K.

---

## 9.13 Kth Largest Stream — Why This Problem?
**Interview context · 2 min**

- Shows **stateful design** — heap persists across calls
- Maps directly to real systems: leaderboards, online ranking

---

## 9.14 Problem — Find Median from Data Stream
**[LeetCode #295](https://leetcode.com/problems/find-median-from-data-stream/) · 🔴 Hard · 3 min**

`addNum(num)` — add a number. `findMedian()` — return the current median.

```
add(1); add(2); findMedian() → 1.5
add(3); findMedian() → 2.0
```

---

## 9.15 Find Median — Hint
**The main idea · 3 min**

**Two heaps:** `lo` = max-heap of the lower half, `hi` = min-heap of the upper half. Keep them balanced (differ by at most 1). Median = `lo.top()` (odd) or average of tops (even).

---

## 9.16 Find Median — Solution
**The algorithm · 4 min**

**Why two heaps?** A single sorted structure needs O(n) inserts. Two heaps give O(log n) insert and O(1) median.

**Invariants:**
1. `lo.top() <= hi.top()` (smaller half ≤ larger half)
2. `|lo.size() - hi.size()| <= 1`

**On addNum:**
1. Push to `lo` (max-heap)
2. If `lo.top() > hi.top()`: move lo's top to hi (fix ordering)
3. Rebalance: if sizes differ by more than 1, move top of larger to smaller

---

## 9.17 Find Median — Pseudocode

```
lo = max-heap, hi = min-heap

addNum(num):
    lo.push(num)
    if hi not empty and lo.top() > hi.top():
        hi.push(lo.top()); lo.pop()
    if lo.size() > hi.size() + 1:
        hi.push(lo.top()); lo.pop()
    elif hi.size() > lo.size():
        lo.push(hi.top()); hi.pop()

findMedian():
    if lo.size() > hi.size(): return lo.top()
    if hi.size() > lo.size(): return hi.top()
    return (lo.top() + hi.top()) / 2.0
```

---

## 9.18 Find Median — Implementation

See full solution: [`find_median_stream.cpp`](find_median_stream.cpp)

```cpp
class MedianFinder {
    priority_queue<int> lo;                               // max-heap: lower half
    priority_queue<int,vector<int>,greater<int>> hi;      // min-heap: upper half
public:
    void addNum(int num) {
        lo.push(num);
        if (!hi.empty() && lo.top() > hi.top()) { hi.push(lo.top()); lo.pop(); }
        if ((int)lo.size() > (int)hi.size() + 1) { hi.push(lo.top()); lo.pop(); }
        else if ((int)hi.size() > (int)lo.size()) { lo.push(hi.top()); hi.pop(); }
    }
    double findMedian() {
        if (lo.size() > hi.size()) return lo.top();
        if (hi.size() > lo.size()) return hi.top();
        return (lo.top() + hi.top()) / 2.0;
    }
};
```

| | Time | Space |
|-|------|-------|
| **addNum** | O(log n) | O(n) |
| **findMedian** | O(1) | — |

**Common mistakes:** Not checking `hi.empty()` before comparing tops → null reference crash.

---

## 9.19 Find Median — Why This Problem?
**Interview context · 2 min**

- The "two heaps" pattern appears in any problem needing O(1) access to both the max-of-lower and min-of-upper halves
- Sliding Window Median (LC #480) is the harder variant

---

## 9.20 Problem — Merge K Sorted Lists
**[LeetCode #23](https://leetcode.com/problems/merge-k-sorted-lists/) · 🔴 Hard · 3 min**

Merge K sorted linked lists into one sorted list.

```
[1→4→5, 1→3→4, 2→6]  →  1→1→2→3→4→4→5→6
```

---

## 9.21 Merge K Sorted Lists — Hint
**The main idea · 3 min**

Min-heap of size K — always holds one node from each list (the current front). Pop the minimum, attach to result, push that node's `next`. Gives the globally smallest at each step in O(log K).

---

## 9.22 Merge K Sorted Lists — Solution
**The algorithm · 4 min**

**Why not pairwise merge?** Pairwise: O(NK). Heap approach: O(N log K) where N = total nodes.

1. Push head of each non-null list into min-heap as `(val, list_idx, node*)`
2. Pop minimum → append to result → push `node->next` if it exists
3. Continue until heap is empty

---

## 9.23 Merge K Sorted Lists — Pseudocode

```
dummy = ListNode(0); tail = dummy
minHeap = []
for i, list in lists:
    if list: push (list.val, i, list)

while heap not empty:
    val, i, node = pop_min()
    tail.next = node; tail = node
    if node.next: push (node.next.val, i, node.next)

return dummy.next
```

---

## 9.24 Merge K Sorted Lists — Implementation

See full solution: [`merge_k_sorted_lists.cpp`](merge_k_sorted_lists.cpp)

```cpp
class Solution {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        using T = tuple<int,int,ListNode*>;
        priority_queue<T, vector<T>, greater<T>> minHeap;
        for (int i = 0; i < (int)lists.size(); i++)
            if (lists[i]) minHeap.push({lists[i]->val, i, lists[i]});

        ListNode dummy(0); ListNode* tail = &dummy;
        while (!minHeap.empty()) {
            auto [val, i, node] = minHeap.top(); minHeap.pop();
            tail->next = node; tail = tail->next;
            if (node->next) minHeap.push({node->next->val, i, node->next});
        }
        return dummy.next;
    }
};
```

| | Time | Space |
|-|------|-------|
| **Complexity** | O(N log K) | O(K) |

**Common mistakes:** Comparing raw `ListNode*` pointers → use `(val, idx, ptr)` tuple so idx breaks ties.

---

## 9.25 Merge K Sorted Lists — Why This Problem?
**Interview context · 2 min**

- K-way merge appears in external sort, log aggregation, database merge-joins
- Divide and conquer pairwise merge is also O(N log K) — mention as alternative

---

## 9.26 Section Recap

| Problem | Pattern | Time |
|---------|---------|------|
| Kth Largest Element | Fixed min-heap size K | O(n log k) |
| Kth Largest Stream | Persistent min-heap | O(log k) per add |
| Median from Stream | Two heaps | O(log n) add, O(1) median |
| Merge K Sorted Lists | K-way merge min-heap | O(N log K) |

**Pattern selector:**
- "Kth largest" → min-heap size K
- "Streaming median" → two heaps
- "Merge K sorted" → K-way merge heap

**Next section →** [10 · Dynamic Programming](../10_Dynamic_Programming/README.md)
