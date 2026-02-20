# 🔗 Section 04: Linked Lists

> **Units**: 20 | **Pattern**: Pointer Manipulation, Fast/Slow Pointers, Dummy Node | **Difficulty**: Easy–Medium

Linked lists test your ability to manage pointers without random access. Unlike arrays, you can't index into them — you must traverse from the `head`. Most linked list problems follow 3–4 reusable patterns that, once learned, make even hard problems straightforward.

**ListNode Definition (C++):**
```cpp
struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(nullptr) {}
};
```

**ListNode Definition (C#):**
```csharp
public class ListNode {
    public int val;
    public ListNode next;
    public ListNode(int val=0, ListNode next=null) {
        this.val = val;
        this.next = next;
    }
}
```

**Problems Covered:**
1. [Reverse Linked List](#problem-1-reverse-linked-list)
2. [Linked List Cycle](#problem-2-linked-list-cycle)
3. [Merge Two Sorted Lists](#problem-3-merge-two-sorted-lists)

---

## Problem 1: Reverse Linked List

> **LeetCode**: [#206 - Reverse Linked List](https://leetcode.com/problems/reverse-linked-list/) | **Difficulty**: 🟢 Easy | **Pattern**: Iterative Pointer Reversal

### 📝 Problem Statement

Given the `head` of a singly linked list, reverse the list, and return the reversed list's head.

**Example:**
```
Input:  1 → 2 → 3 → 4 → 5 → NULL
Output: 5 → 4 → 3 → 2 → 1 → NULL
```

### 💡 Intuition & Approach

Use three pointers: `prev`, `curr`, `next`. At each step, save `curr->next`, reverse the link (`curr->next = prev`), then advance all three. When `curr` is null, `prev` points to the new head.

**Visualize:**
```
prev=NULL  curr=1 → 2 → 3
           ↓ save next, reverse, advance
prev=1     curr=2 → 3
           ↓
prev=2→1   curr=3
           ↓
prev=3→2→1 curr=NULL → return prev
```

### 🔍 Hint
> Use `prev=null`, `curr=head`. In each step: save `curr->next`, make `curr->next = prev`, advance prev=curr, curr=saved.

### 🗂️ Pseudocode
```
prev = null
curr = head
while curr != null:
    next = curr.next
    curr.next = prev
    prev = curr
    curr = next
return prev
```

### ✅ C++ & C# Solutions
See [`reverse_linked_list.cpp`](reverse_linked_list.cpp) | [`reverse_linked_list.cs`](reverse_linked_list.cs)

**C++ Implementation**
```cpp
class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        ListNode* prev = nullptr;
        ListNode* curr = head;

        while (curr != nullptr) {
            ListNode* nextNode = curr->next; // save next
            curr->next = prev;               // reverse the link
            prev = curr;                     // advance prev
            curr = nextNode;                 // advance curr
        }
}
};
```

**C# Implementation**
```csharp
public class Solution {
    public ListNode ReverseList(ListNode head) {
        ListNode prev = null;
        ListNode curr = head;
        
        while (curr != null) {
            ListNode nxt = curr.next;
            curr.next = prev;
            prev = curr;
            curr = nxt;
        }
        
        return prev;
    }
}
```

### 📊 Complexity Analysis

| | Complexity | Explanation |
|-|------------|-------------|
| **Time** | O(n) | Visit each node once |
| **Space** | O(1) | Only three pointers |

### ⚠️ Edge Cases
- Empty list (`head = nullptr`) → return `nullptr`
- Single node → return same node (its `next` is already `nullptr`)

### 🚫 Common Mistakes
- Losing the `head` reference by not saving `next` first
- Using an extra array/stack — works but O(n) space unnecessarily

### 🎯 Interview Tips
- Be prepared to do this **recursively** too: `reverseList(head->next)` then fix links
- This is a building block for "Reverse K Nodes in Group" (LeetCode #25 — Hard)
- Draw the pointer diagram before coding — interviewers love to see your thinking

---

## Problem 2: Linked List Cycle

> **LeetCode**: [#141 - Linked List Cycle](https://leetcode.com/problems/linked-list-cycle/) | **Difficulty**: 🟢 Easy | **Pattern**: Fast & Slow Pointers (Floyd's Algorithm)

### 📝 Problem Statement

Given the `head` of a linked list, determine if the linked list has a **cycle** in it. A cycle exists if some node can be reached again by continuously following `next` pointers.

**Example:**
```
Input:  3 → 2 → 0 → -4 → (back to 2)
Output: true
```

### 💡 Intuition & Approach

**Floyd's Tortoise and Hare**: Use two pointers — `slow` moves 1 step at a time, `fast` moves 2 steps. If there's a cycle, `fast` will eventually lap `slow` and they'll meet. If `fast` reaches `null`, there's no cycle.

**Why does this work?** In a cycle, fast gains 1 step on slow per iteration. With a cycle of length `k`, they meet within `k` steps.

### 🔍 Hint
> Two pointers: slow moves 1 step, fast moves 2. If they ever meet, there's a cycle. If fast reaches null, no cycle.

### 🗂️ Pseudocode
```
slow = head, fast = head
while fast != null and fast.next != null:
    slow = slow.next
    fast = fast.next.next
    if slow == fast: return true
return false
```

### ✅ C++ & C# Solutions
See [`linked_list_cycle.cpp`](linked_list_cycle.cpp) | [`linked_list_cycle.cs`](linked_list_cycle.cs)

**C++ Implementation**
```cpp
class Solution {
public:
    bool hasCycle(ListNode* head) {
        ListNode* slow = head;
        ListNode* fast = head;

        while (fast != nullptr && fast->next != nullptr) {
            slow = slow->next;
            fast = fast->next->next;
            if (slow == fast) return true; // pointers met → cycle detected
        }
        return false; // fast reached end → no cycle
    }
};
```

**C# Implementation**
```csharp
public class Solution {
    public bool HasCycle(ListNode head) {
        if (head == null || head.next == null) return false;
        
        ListNode slow = head;
        ListNode fast = head.next;
        
        while (slow != fast) {
            if (fast == null || fast.next == null) {
                return false;
            }
            slow = slow.next;
            fast = fast.next.next;
        }
        
        return true;
    }
}
```

### 📊 Complexity Analysis

| | Complexity | Explanation |
|-|------------|-------------|
| **Time** | O(n) | Fast pointer reaches cycle in O(n); detection in O(k) |
| **Space** | O(1) | Only two pointers |

### ⚠️ Edge Cases
- Empty list → `false`
- Single node pointing to itself → `true`
- Cycle at the very beginning
- Very long list with no cycle

### 🚫 Common Mistakes
- Not checking `fast->next != null` before `fast->next->next` → null pointer exception
- Using a visited set (works but O(n) space — mention and then show O(1) approach)

### 🎯 Interview Tips
- Mention the hash set approach first ("simplest to code"), then optimize to O(1) space
- **Extension**: LeetCode #142 asks *where* the cycle begins — that requires a math proof about the meeting point
- This pattern also finds the **middle** of a linked list (when fast reaches end, slow is at middle)

---

## Problem 3: Merge Two Sorted Lists

> **LeetCode**: [#21 - Merge Two Sorted Lists](https://leetcode.com/problems/merge-two-sorted-lists/) | **Difficulty**: 🟢 Easy | **Pattern**: Dummy Node + Compare and Link

### 📝 Problem Statement

Given the heads of two sorted linked lists `list1` and `list2`, merge them into one sorted list. Return the head of the merged list.

**Example:**
```
Input:  list1 = 1 → 2 → 4
        list2 = 1 → 3 → 4
Output: 1 → 1 → 2 → 3 → 4 → 4
```

### 💡 Intuition & Approach

Use a **dummy node** as a placeholder for the head. Maintain a `tail` pointer. Compare the current nodes of both lists; attach the smaller to `tail` and advance that list's pointer. When one list is exhausted, attach the remaining list.

**Dummy node trick**: Avoids special-casing the head of the result — the actual result is `dummy->next`.

### 🔍 Hint
> Create a dummy node and a tail pointer. Always pick the smaller of the two current nodes and attach it to tail. Advance only that list's pointer.

### 🗂️ Pseudocode
```
dummy = new ListNode(0)
tail = dummy
while list1 and list2:
    if list1.val <= list2.val:
        tail.next = list1; list1 = list1.next
    else:
        tail.next = list2; list2 = list2.next
    tail = tail.next
tail.next = list1 or list2  // attach remainder
return dummy.next
```

### ✅ C++ & C# Solutions
See [`merge_two_sorted_lists.cpp`](merge_two_sorted_lists.cpp) | [`merge_two_sorted_lists.cs`](merge_two_sorted_lists.cs)

**C++ Implementation**
```cpp
class Solution {
public:
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        ListNode dummy(0);       // dummy head avoids edge cases
        ListNode* tail = &dummy;

        while (list1 != nullptr && list2 != nullptr) {
            if (list1->val <= list2->val) {
                tail->next = list1;
                list1 = list1->next;
            } else {
                tail->next = list2;
                list2 = list2->next;
            }
            tail = tail->next;
        }

        // attach the remaining (non-exhausted) list
        tail->next = (list1 != nullptr) ? list1 : list2;

}
};
```

**C# Implementation**
```csharp
public class Solution {
    public ListNode MergeTwoLists(ListNode list1, ListNode list2) {
        ListNode dummy = new ListNode();
        ListNode tail = dummy;
        
        while (list1 != null && list2 != null) {
            if (list1.val < list2.val) {
                tail.next = list1;
                list1 = list1.next;
            } else {
                tail.next = list2;
                list2 = list2.next;
            }
            tail = tail.next;
        }
        
        if (list1 != null) {
            tail.next = list1;
        } else if (list2 != null) {
            tail.next = list2;
        }
        
        return dummy.next;
    }
}
```

### 📊 Complexity Analysis

| | Complexity | Explanation |
|-|------------|-------------|
| **Time** | O(n + m) | Visit each node of both lists once |
| **Space** | O(1) | In-place linking, only the dummy node |

### ⚠️ Edge Cases
- One list is empty → return the other list
- Both lists are empty → return `nullptr`
- Lists of very different lengths

### 🚫 Common Mistakes
- Not attaching the remainder after the while loop
- Returning `dummy` instead of `dummy.next`
- Creating new nodes (unnecessary — reuse existing nodes)

### 🎯 Interview Tips
- Dummy node pattern is widely applicable: LeetCode #23 (Merge K Sorted Lists), #82 (Remove Duplicates)
- **Recursive solution** is elegant but O(n+m) stack space — mention trade-off
- Follow-up: "Merge K sorted lists" → Use a priority queue/heap (Section 09)

---

## 🔄 Section Recap

| Problem | Pattern | Time | Space |
|---------|---------|------|-------|
| Reverse Linked List | Three Pointers | O(n) | O(1) |
| Linked List Cycle | Fast/Slow Pointers | O(n) | O(1) |
| Merge Two Sorted Lists | Dummy Node + Compare | O(n+m) | O(1) |

**Key takeaways:**
- 🔑 **Three-pointer reversal**: prev, curr, next — essential template
- 🔑 **Fast/slow pointers**: cycle detection, finding middle, nth from end
- 🔑 **Dummy node**: eliminates edge cases when building result lists

**Next up**: [Stacks →](../05_Stacks/README.md)
