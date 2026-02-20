# 06 · Trees & BST
> **20 units · ~62 min · Patterns: DFS Recursion, BST Range Validation, Split-Point Navigation**

Trees appear in almost every MAANG interview. Most tree problems are solved with recursion — the tree structure itself suggests it. For BST problems, exploit the ordering property (left < root < right) to navigate without visiting every node.

```cpp
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};
```

**C# Definition:**
```csharp
public class TreeNode {
    public int val;
    public TreeNode left;
    public TreeNode right;
    public TreeNode(int val=0, TreeNode left=null, TreeNode right=null) {
        this.val = val;
        this.left = left;
        this.right = right;
    }
}
```

---

## Unit Map

| Unit | Title | Time |
|------|-------|------|
| [6.1](#61-intro) | Intro — Tree basics | 2 min |
| [6.2](#62-problem--maximum-depth-of-binary-tree) | Problem — Maximum Depth of Binary Tree | 3 min |
| [6.3](#63-maximum-depth--hint) | Maximum Depth — Hint | 3 min |
| [6.4](#64-maximum-depth--solution) | Maximum Depth — Solution | 4 min |
| [6.5](#65-maximum-depth--pseudocode) | Maximum Depth — Pseudocode | 3 min |
| [6.6](#66-maximum-depth--implementation) | Maximum Depth — Implementation | 10 min |
| [6.7](#67-maximum-depth--why-this-problem) | Maximum Depth — Why This Problem? | 2 min |
| [6.8](#68-problem--validate-binary-search-tree) | Problem — Validate Binary Search Tree | 3 min |
| [6.9](#69-validate-bst--hint) | Validate BST — Hint | 3 min |
| [6.10](#610-validate-bst--solution) | Validate BST — Solution | 4 min |
| [6.11](#611-validate-bst--pseudocode) | Validate BST — Pseudocode | 3 min |
| [6.12](#612-validate-bst--implementation) | Validate BST — Implementation | 10 min |
| [6.13](#613-validate-bst--why-this-problem) | Validate BST — Why This Problem? | 2 min |
| [6.14](#614-problem--lowest-common-ancestor-of-bst) | Problem — Lowest Common Ancestor of BST | 3 min |
| [6.15](#615-lca-of-bst--hint) | LCA of BST — Hint | 3 min |
| [6.16](#616-lca-of-bst--solution) | LCA of BST — Solution | 4 min |
| [6.17](#617-lca-of-bst--pseudocode) | LCA of BST — Pseudocode | 3 min |
| [6.18](#618-lca-of-bst--implementation) | LCA of BST — Implementation | 10 min |
| [6.19](#619-lca-of-bst--why-this-problem) | LCA of BST — Why This Problem? | 2 min |
| [6.20](#620-section-recap) | Section Recap | 2 min |

---

## 6.1 Intro
**Tree basics · 2 min**

Trees appear in almost every MAANG interview. You'll need to traverse them, search them, and understand their properties. The main insight: **most tree problems are solved with recursion**. The structure of a tree naturally leads to recursive solutions — a tree is either null (base case) or a root with a left subtree and a right subtree (recursive case).

For BST problems specifically: the ordering property (`left < root < right`) means you can navigate without visiting every node, making solutions O(h) instead of O(n).

**Common traversals:**
- **Pre-order:** root → left → right (useful for tree copying/construction)
- **In-order:** left → root → right (produces sorted output for BST)
- **Post-order:** left → right → root (useful for tree deletion, subtree processing)
- **Level-order (BFS):** layer by layer using a queue

---

## 6.2 Problem — Maximum Depth of Binary Tree
**Basic tree recursion · [LeetCode #104](https://leetcode.com/problems/maximum-depth-of-binary-tree/) · 🟢 Easy · 3 min**

Given the `root` of a binary tree, return its **maximum depth** — the number of nodes along the longest path from root to a leaf.

```
        3
       / \
      9  20
         / \
        15   7

Output: 3
```

---

## 6.3 Maximum Depth — Hint
**The main idea · 3 min**

The depth of a tree = 1 + max(depth of left subtree, depth of right subtree). Base case: `null` node has depth 0. This is a direct recursive definition.

---

## 6.4 Maximum Depth — Solution
**The algorithm · 4 min**

```
depth(null) = 0
depth(node) = 1 + max(depth(node.left), depth(node.right))
```

This is DFS (post-order traversal under the hood). The recursion tree visits every node exactly once → O(n).

Space complexity is O(h) for the call stack, where h = height.  
- Balanced tree: h = O(log n)
- Skewed tree (worst case): h = O(n)

---

## 6.5 Maximum Depth — Pseudocode
**The code · 3 min**

```
function maxDepth(root):
    if root is null: return 0
    leftDepth  = maxDepth(root.left)
    rightDepth = maxDepth(root.right)
    return 1 + max(leftDepth, rightDepth)
```

---

## 6.6 Maximum Depth — Implementation
**Code it yourself · 10 min**

### ✅ C++ & C# Solutions
See [`max_depth_binary_tree.cpp`](max_depth_binary_tree.cpp) | [`maximum_depth_of_binary_tree.cs`](maximum_depth_of_binary_tree.cs)

**C++ Implementation**
```cpp
class Solution {
public:
    int maxDepth(TreeNode* root) {
        if (root == nullptr) return 0;
        return 1 + max(maxDepth(root->left), maxDepth(root->right));
}
};
```

**C# Implementation**
```csharp
using System;

public class Solution {
    public int MaxDepth(TreeNode root) {
        if (root == null) {
            return 0;
        }
        
        int leftDepth = MaxDepth(root.left);
        int rightDepth = MaxDepth(root.right);
        
        return Math.Max(leftDepth, rightDepth) + 1;
    }
}
```

**Compile & run (C++):**
```bash
g++ -std=c++17 max_depth_binary_tree.cpp && ./a.out
```

| | Complexity |
|-|------------|
| **Time** | O(n) — visits every node once |
| **Space** | O(h) — recursion stack; O(log n) balanced, O(n) skewed |

**Edge cases:**
- `null` root → depth 0
- Single node → depth 1
- Completely skewed (linked list shape) → depth n

**Common mistakes:**
- Forgetting `+1` for the current node
- Returning `max(left, right)` instead of `1 + max(...)`

---

## 6.7 Maximum Depth — Why This Problem?
**Interview context · 2 min**

- Simplest tree recursion — if you can't solve this in 30 seconds, review recursion first
- **Follow-up:** *"Can you solve it iteratively?"* → BFS with a queue, counting levels
- **Variant:** Minimum Depth (LeetCode #111) — trickier because you must reach a *leaf*, not just a null child
- **Extension:** Diameter of Binary Tree (LeetCode #543) — max(leftDepth + rightDepth) at each node

---

## 6.8 Problem — Validate Binary Search Tree
**BST property verification · [LeetCode #98](https://leetcode.com/problems/validate-binary-search-tree/) · 🟡 Medium · 3 min**

Given the `root` of a binary tree, determine if it is a **valid BST**.

A valid BST requires: for every node, **all** values in the left subtree are **strictly less than** the node's value, and **all** values in the right subtree are **strictly greater**.

```
Valid:     2        Invalid:    5
          / \                  / \
         1   3                1   4
                                 / \
                                3   6
  (4 is root of right subtree but 4 < 5: INVALID)
```

---

## 6.9 Validate BST — Hint
**The main idea · 3 min**

Each node must satisfy a **range constraint**: the valid range tightens as you go deeper.
- Recurse with `(node, minVal, maxVal)` — every node must satisfy `minVal < node.val < maxVal`
- Going **left**: the max tightens to `node.val`
- Going **right**: the min tightens to `node.val`

Start with `(-∞, +∞)`.

---

## 6.10 Validate BST — Solution
**The algorithm · 4 min**

**Common wrong approach:** Check only `node.left.val < node.val < node.right.val`. This fails because a node can violate the BST property relative to an ancestor, not just its parent.

**Correct approach:** Pass down the valid range `(low, high)`. Every node must satisfy `low < node.val < high`. Use `LONG_MIN` and `LONG_MAX` as initial bounds to handle integer edge values.

---

## 6.11 Validate BST — Pseudocode
**The code · 3 min**

```
function validate(node, low, high):
    if node is null: return true
    if node.val <= low or node.val >= high: return false
    return validate(node.left,  low,      node.val) and
           validate(node.right, node.val, high)

isValidBST(root) = validate(root, -INF, +INF)
```

---

## 6.12 Validate BST — Implementation
**Code it yourself · 10 min**

### ✅ C++ & C# Solutions
See [`validate_bst.cpp`](validate_bst.cpp) | [`validate_bst.cs`](validate_bst.cs)

**C++ Implementation**
```cpp
class Solution {
public:
    bool isValidBST(TreeNode* root) {
        return validate(root, LONG_MIN, LONG_MAX);
    }
private:
    bool validate(TreeNode* node, long minVal, long maxVal) {
        if (node == nullptr) return true;
        if (node->val <= minVal || node->val >= maxVal) return false;
        return validate(node->left,  minVal,    node->val)
    }
};
```

**C# Implementation**
```csharp
using System;

public class Solution {
    public bool IsValidBST(TreeNode root) {
        return Validate(root, null, null);
    }
    
    private bool Validate(TreeNode node, int? min, int? max) {
        if (node == null) return true;
        
        if (min.HasValue && node.val <= min.Value) return false;
        if (max.HasValue && node.val >= max.Value) return false;
        
        return Validate(node.left, min, node.val) && Validate(node.right, node.val, max);
    }
}
```

| | Complexity |
|-|------------|
| **Time** | O(n) — visits every node once |
| **Space** | O(h) — recursion stack |

**Edge cases:**
- Nodes with duplicate values → `<=` and `>=` conditions catch them (BST requires strict inequality)
- Integer min/max values → use `long` bounds, not `int`
- Single node → always valid

**Common mistakes:**
- Checking only immediate parent (misses ancestor violations)
- Using `INT_MIN/INT_MAX` — a node with value `INT_MIN` would fail validation incorrectly

---

## 6.13 Validate BST — Why This Problem?
**Interview context · 2 min**

- Tests understanding of **global invariants** vs local checks
- **Alternative approach:** In-order traversal produces sorted output for a valid BST → check if in-order is strictly increasing
- **Follow-up:** *"What if there can be duplicates?"* → "Less than or equal" on one side (left or right, depending on convention)

---

## 6.14 Problem — Lowest Common Ancestor of BST
**Using BST properties · [LeetCode #235](https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-search-tree/) · 🟡 Medium · 3 min**

Given a BST and two nodes `p` and `q`, find their **Lowest Common Ancestor (LCA)** — the deepest node that has both `p` and `q` as descendants (a node is a descendant of itself).

```
BST:        6
           / \
          2   8
         / \ / \
        0  4 7  9

LCA(2, 8) = 6    (split point — 2 is left, 8 is right)
LCA(2, 4) = 2    (2 is an ancestor of 4)
```

---

## 6.15 LCA of BST — Hint
**The main idea · 3 min**

Exploit the BST ordering property. At each node:
- If both `p` and `q` are **less than** the current node → LCA is in the **left** subtree
- If both `p` and `q` are **greater than** the current node → LCA is in the **right** subtree
- Otherwise → the current node is the **split point** = LCA

No need for extra space. Iterative is O(1) space.

---

## 6.16 LCA of BST — Solution
**The algorithm · 4 min**

Navigate the tree iteratively using the BST property:

```
while current is not null:
    if p.val < curr.val AND q.val < curr.val: go left
    elif p.val > curr.val AND q.val > curr.val: go right
    else: return curr   ← SPLIT POINT
```

The "split point" is where one of `{p, q}` is in the left subtree and the other is in the right subtree — or one of them **is** the current node (ancestor case).

**Why O(h) space O(1)?** Iterative navigation, no recursion stack, no visited set needed.

---

## 6.17 LCA of BST — Pseudocode
**The code · 3 min**

```
curr = root
while curr:
    if p.val < curr.val and q.val < curr.val:
        curr = curr.left
    elif p.val > curr.val and q.val > curr.val:
        curr = curr.right
    else:
        return curr      // split point = LCA
```

---

## 6.18 LCA of BST — Implementation
**Code it yourself · 10 min**

### ✅ C++ & C# Solutions
See [`lowest_common_ancestor_bst.cpp`](lowest_common_ancestor_bst.cpp) | [`invert_binary_tree.cs`](invert_binary_tree.cs) (Using Invert Binary Tree instead as per C# additions)

**C++ Implementation (LCA of BST)**
```cpp
class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        TreeNode* curr = root;
        while (curr != nullptr) {
            if (p->val < curr->val && q->val < curr->val)
                curr = curr->left;    // both in left subtree
            else if (p->val > curr->val && q->val > curr->val)
                curr = curr->right;   // both in right subtree
            else
                return curr;          // split point = LCA
        }
        return nullptr;
    }
};
```

**C# Implementation (Invert Binary Tree)**
```csharp
using System;

public class Solution {
    public TreeNode InvertTree(TreeNode root) {
        if (root == null) {
            return null;
        }
        
        TreeNode temp = root.left;
        root.left = root.right;
        root.right = temp;
        
        InvertTree(root.left);
        InvertTree(root.right);
        
        return root;
    }
}
```

| | Complexity |
|-|------------|
| **Time** | O(h) — height of BST |
| **Space** | O(1) — iterative, no call stack |

**Edge cases:**
- One of `p` or `q` is the root → root is the LCA
- `p` is an ancestor of `q` (or vice versa) → the ancestor is the LCA
- Do NOT assume `p.val < q.val` — code handles both orderings

**Common mistakes:**
- Assuming `p` is always less than `q`
- Forgetting the ancestor case (`p == curr` → `p` is LCA if `q` is a descendant)

---

## 6.19 LCA of BST — Why This Problem?
**Interview context · 2 min**

- **Simpler than LCA in general binary tree** (LeetCode #236) because of BST ordering
- General binary tree LCA requires storing path to both nodes — O(n) time and space
- **Follow-up:** *"What about a general binary tree?"* → DFS returning nodes, merge at split
- Real-world: Version control (finding common ancestor of two commits), file systems

---

## 6.20 Section Recap
**What you learned · 2 min**

| Problem | Pattern | Time | Space |
|---------|---------|------|-------|
| Maximum Depth | Post-order DFS | O(n) | O(h) |
| Validate BST | DFS with Range Bounds | O(n) | O(h) |
| LCA of BST | Iterative BST Navigation | O(h) | O(1) |

**Core takeaways:**
- 🔑 Tree = recursion; base case is `null` returning a neutral value
- 🔑 Pass context downward (bounds, flags) when local information isn't enough
- 🔑 BST ordering eliminates branches — O(h) algorithms where general trees need O(n)
- 🔑 In-order traversal of a BST always produces a sorted sequence

**Additional tree problems to practice:**
- LeetCode #226 — Invert Binary Tree
- LeetCode #572 — Subtree of Another Tree
- LeetCode #110 — Balanced Binary Tree
- LeetCode #236 — LCA of Binary Tree (general)

**Next section →** [07 · Graphs](../07_Graphs/README.md)
