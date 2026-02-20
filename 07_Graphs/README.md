# 07 · Graphs
> **20 units · ~62 min · Patterns: DFS Flood Fill, DFS with Old→New Map, DFS Cycle Detection (3-State)**

Graphs model relationships between entities. Nodes are entities, edges are connections. The two main algorithms are **DFS** (explore as deep as possible before backtracking) and **BFS** (explore level by level). Master visited tracking, adjacency representation, and cycle detection — these patterns appear in every graph interview.

---

## Unit Map

| Unit | Title | Time |
|------|-------|------|
| [7.1](#71-intro) | Intro — Graph basics | 2 min |
| [7.2](#72-problem--number-of-islands) | Problem — Number of Islands | 3 min |
| [7.3](#73-number-of-islands--hint) | Number of Islands — Hint | 3 min |
| [7.4](#74-number-of-islands--solution) | Number of Islands — Solution | 4 min |
| [7.5](#75-number-of-islands--pseudocode) | Number of Islands — Pseudocode | 3 min |
| [7.6](#76-number-of-islands--implementation) | Number of Islands — Implementation | 10 min |
| [7.7](#77-number-of-islands--why-this-problem) | Number of Islands — Why This Problem? | 2 min |
| [7.8](#78-problem--clone-graph) | Problem — Clone Graph | 3 min |
| [7.9](#79-clone-graph--hint) | Clone Graph — Hint | 3 min |
| [7.10](#710-clone-graph--solution) | Clone Graph — Solution | 4 min |
| [7.11](#711-clone-graph--pseudocode) | Clone Graph — Pseudocode | 3 min |
| [7.12](#712-clone-graph--implementation) | Clone Graph — Implementation | 10 min |
| [7.13](#713-clone-graph--why-this-problem) | Clone Graph — Why This Problem? | 2 min |
| [7.14](#714-problem--course-schedule) | Problem — Course Schedule | 3 min |
| [7.15](#715-course-schedule--hint) | Course Schedule — Hint | 3 min |
| [7.16](#716-course-schedule--solution) | Course Schedule — Solution | 4 min |
| [7.17](#717-course-schedule--pseudocode) | Course Schedule — Pseudocode | 3 min |
| [7.18](#718-course-schedule--implementation) | Course Schedule — Implementation | 10 min |
| [7.19](#719-course-schedule--why-this-problem) | Course Schedule — Why This Problem? | 2 min |
| [7.20](#720-section-recap) | Section Recap | 2 min |

---

## 7.1 Intro
**Graph basics · 2 min**

Graphs model relationships between entities. Nodes = entities, edges = connections.

**Representations:**
- **Adjacency list** (`vector<vector<int>> adj`) — most common in interviews: O(V+E) space
- **Adjacency matrix** — O(V²) but O(1) edge lookup; only for dense graphs

**The two main algorithms:**
- **DFS**: Go deep before backtracking. Uses a stack (or recursion). Finds components, detects cycles, clones graphs.
- **BFS**: Explore level by level using a queue. Finds shortest paths in unweighted graphs.

**Key requirement:** Always track **visited** nodes to prevent infinite loops in cyclic graphs.

**Graph types in problems:**
| Type | Example Problem |
|------|----------------|
| Undirected | Number of Islands |
| Directed (DAG) | Course Schedule |
| With weights | Dijkstra (not covered here) |

---

## 7.2 Problem — Number of Islands
**Counting connected components · [LeetCode #200](https://leetcode.com/problems/number-of-islands/) · 🟡 Medium · 3 min**

Given an `m × n` grid of `'1'` (land) and `'0'` (water), count the number of **islands**. An island is surrounded by water and formed by connecting adjacent land cells horizontally or vertically.

```
Input:
11110
11010
11000
00000

Output: 1   ← all connected

Input:
11000
11000
00100
00011

Output: 3   ← three separate islands
```

---

## 7.3 Number of Islands — Hint
**The main idea · 3 min**

Count how many times you can start a fresh DFS on land. Each fresh DFS from a `'1'` cell that hasn't been visited marks an entire island — flood fill it to `'0'` or a visited set. Increment the island counter each time you start a fresh DFS.

---

## 7.4 Number of Islands — Solution
**The algorithm · 4 min**

Traverse every cell. When you find `grid[r][c] == '1'` (unvisited land):
1. Increment island count
2. Run DFS to flood-fill the entire island (mark all connected `'1'`s as `'0'` or visited)

**In-place modification trick:** Change `'1'` → `'0'` as you visit. This avoids a separate `visited` set. Fine when modifying the input is acceptable.

**DFS at each cell:** Try all 4 directions. Recurse only on in-bounds, unvisited `'1'` cells.

---

## 7.5 Number of Islands — Pseudocode
**The code · 3 min**

```
function dfs(r, c):
    if out-of-bounds or grid[r][c] != '1': return
    grid[r][c] = '0'        // mark visited (in-place)
    dfs(r+1,c); dfs(r-1,c); dfs(r,c+1); dfs(r,c-1)

count = 0
for each cell (r, c):
    if grid[r][c] == '1':
        dfs(r, c)           // flood-fill entire island
        count++

return count
```

---

## 7.6 Number of Islands — Implementation
**Code it yourself · 10 min**

### ✅ C++ & C# Solutions
See [`number_of_islands.cpp`](number_of_islands.cpp) | [`number_of_islands.cs`](number_of_islands.cs)

**C++ Implementation**
```cpp
class Solution {
public:
    int numIslands(vector<vector<char>>& grid) {
        int rows = grid.size(), cols = grid[0].size(), islands = 0;
        for (int r = 0; r < rows; r++)
            for (int c = 0; c < cols; c++)
                if (grid[r][c] == '1') {
                    dfs(grid, r, c, rows, cols);
                    islands++;
                }
        return islands;
    }
private:
    void dfs(vector<vector<char>>& grid, int r, int c, int rows, int cols) {
        if (r < 0 || r >= rows || c < 0 || c >= cols || grid[r][c] != '1') return;
        grid[r][c] = '0';  // mark visited
        dfs(grid, r+1,c,rows,cols); dfs(grid, r-1,c,rows,cols);
        dfs(grid, r,c+1,rows,cols); dfs(grid, r,c-1,rows,cols);
    }
};
```

**C# Implementation**
```csharp
using System.Collections.Generic;

public class Solution {
    public int NumIslands(char[][] grid) {
        if (grid == null || grid.Length == 0) return 0;
        
        int numIslands = 0;
        int rows = grid.Length;
        int cols = grid[0].Length;
        
        for (int r = 0; r < rows; r++) {
            for (int c = 0; c < cols; c++) {
                if (grid[r][c] == '1') {
                    numIslands++;
                    Dfs(grid, r, c);
                }
            }
        }
        
        return numIslands;
    }
    
    private void Dfs(char[][] grid, int r, int c) {
        int rows = grid.Length;
        int cols = grid[0].Length;
        
        if (r < 0 || c < 0 || r >= rows || c >= cols || grid[r][c] == '0') {
            return;
        }
        
        grid[r][c] = '0'; // mark as visited
        
        Dfs(grid, r - 1, c); // up
        Dfs(grid, r + 1, c); // down
        Dfs(grid, r, c - 1); // left
        Dfs(grid, r, c + 1); // right
    }
}
```

**Compile & run (C++):**
```bash
g++ -std=c++17 number_of_islands.cpp && ./a.out
```

| | Complexity |
|-|------------|
| **Time** | O(m × n) — every cell visited at most once |
| **Space** | O(m × n) — recursion stack in worst case (all land) |

**Edge cases:**
- Empty grid → 0
- All water → 0
- All land and connected → 1
- Single cell `'1'` → 1

**Common mistakes:**
- Infinite recursion without marking visited (or without the bounds check)
- Visiting diagonals (problem is only horizontal/vertical)
- Forgetting to restore the grid if modification is not allowed

---

## 7.7 Number of Islands — Why This Problem?
**Interview context · 2 min**

- Template for **connected components** in a grid — applies to dozens of problems (Pacific Atlantic Water Flow, Rotting Oranges, etc.)
- **Follow-up:** *"What if you can't modify the input?"* → Use a separate `unordered_set<int>` of visited (r*cols + c) or a boolean matrix
- **Follow-up:** *"BFS instead?"* → Use a queue; start at each unvisited `'1'`, enqueue neighbors
- **Variant:** Max area of island (LeetCode #695) — return size instead of count

---

## 7.8 Problem — Clone Graph
**Deep copying a graph · [LeetCode #133](https://leetcode.com/problems/clone-graph/) · 🟡 Medium · 3 min**

Given a reference to a node in a **connected undirected graph**, return a **deep copy** of the graph.

Each node has a `val` and a list of `neighbors`. A deep copy means new nodes with the same values and connectivity, but completely separate objects.

```cpp
class Node { public: int val; vector<Node*> neighbors; };
```

**C# Node Definition:**
```csharp
public class Node {
    public int val;
    public IList<Node> neighbors;

    public Node() { val = 0; neighbors = new List<Node>(); }
    public Node(int _val) { val = _val; neighbors = new List<Node>(); }
    public Node(int _val, List<Node> _neighbors) { val = _val; neighbors = _neighbors; }
}
```

---

## 7.9 Clone Graph — Hint
**The main idea · 3 min**

Use DFS with a hash map `oldNode → newNode`. Before recursing into neighbors, **register the clone in the map first** to handle cycles — this prevents infinite loops when revisiting nodes.

---

## 7.10 Clone Graph — Solution
**The algorithm · 4 min**

DFS with `unordered_map<Node*, Node*> oldToNew`:

1. If `node` is already in `oldToNew` → return `oldToNew[node]` (already cloned)
2. Create `clone = new Node(node->val)`
3. **Register immediately**: `oldToNew[node] = clone` (BEFORE recursing — handles cycles)
4. For each neighbor: `clone->neighbors.push_back(dfs(neighbor))`
5. Return `clone`

**Why register before recursing?** If there's a cycle (A → B → A), when we're cloning A's neighbors and we reach B, which then looks at A again — A is already in the map so we return the existing clone instead of infinitely recursing.

---

## 7.11 Clone Graph — Pseudocode
**The code · 3 min**

```
oldToNew = {}

function dfs(node):
    if node in oldToNew: return oldToNew[node]
    clone = new Node(node.val)
    oldToNew[node] = clone          // register BEFORE recursing
    for each neighbor of node:
        clone.neighbors.append(dfs(neighbor))
    return clone

return dfs(node) if node else null
```

---

## 7.12 Clone Graph — Implementation
**Code it yourself · 10 min**

### ✅ C++ & C# Solutions
See [`clone_graph.cpp`](clone_graph.cpp) | [`clone_graph.cs`](clone_graph.cs)

**C++ Implementation**
```cpp
class Solution {
    unordered_map<Node*, Node*> oldToNew;
public:
    Node* cloneGraph(Node* node) {
        if (!node) return nullptr;
        return dfs(node);
    }
private:
    Node* dfs(Node* node) {
        if (oldToNew.count(node)) return oldToNew[node]; // already cloned
        Node* clone = new Node(node->val);
        oldToNew[node] = clone;    // register BEFORE recursing into neighbors
        for (Node* neighbor : node->neighbors)
            clone->neighbors.push_back(dfs(neighbor));
        return clone;
    }
};
```

**C# Implementation**
```csharp
using System.Collections.Generic;

public class Solution {
    private Dictionary<Node, Node> visited = new Dictionary<Node, Node>();
    
    public Node CloneGraph(Node node) {
        if (node == null) return null;
        
        if (visited.ContainsKey(node)) {
            return visited[node];
        }
        
        Node cloneNode = new Node(node.val);
        visited[node] = cloneNode;
        
        foreach (var neighbor in node.neighbors) {
            cloneNode.neighbors.Add(CloneGraph(neighbor));
        }
        
        return cloneNode;
    }
}
```

| | Complexity |
|-|------------|
| **Time** | O(V + E) — visits each node and edge once |
| **Space** | O(V) — map + recursion stack |

**Edge cases:**
- `null` input → return `null`
- Single node with no neighbors → clone the node, empty neighbor list
- Self-loop — handled: node already in map when we revisit

**Common mistakes:**
- Shallow copy (copying the pointer to the original node's neighbors, not creating new nodes)
- Registering AFTER recursing → causes infinite loop on cycles

---

## 7.13 Clone Graph — Why This Problem?
**Interview context · 2 min**

- Tests your understanding of **reference vs. deep copy** and **cycle handling** in graph DFS
- Same "register before recursing" pattern appears in memoization (DP) with cycles
- **Real world:** Copying any graph-like data structure (ASTs, dependency graphs, object trees with back-references)

---

## 7.14 Problem — Course Schedule
**Cycle detection in directed graphs · [LeetCode #207](https://leetcode.com/problems/course-schedule/) · 🟡 Medium · 3 min**

You have `numCourses` labeled `0` to `numCourses-1`. `prerequisites[i] = [a, b]` means you must take course `b` before `a`. Return `true` if you can finish all courses.

```
numCourses=2, prerequisites=[[1,0]] → true   (take 0, then 1)
numCourses=2, prerequisites=[[1,0],[0,1]] → false   (cycle: 0→1→0)
```

---

## 7.15 Course Schedule — Hint
**The main idea · 3 min**

This is a **directed cycle detection** problem. If there's a cycle in the prerequisite graph, you can't finish all courses. Use DFS with **three states** per node:
- `0` = unvisited
- `1` = visiting (currently in this DFS path — finding it again means cycle)
- `2` = fully explored (safe)

---

## 7.16 Course Schedule — Solution
**The algorithm · 4 min**

Build an adjacency list from prerequisites. Run DFS for every unvisited node. During DFS:
- Mark node as `1` (visiting)
- DFS all its prerequisites; if any returns `false` → cycle detected
- Mark node as `2` (safe) when done
- If we encounter a node marked `1` during DFS → cycle!

After a node is marked `2` (fully explored), we don't need to re-explore it — memoization.

---

## 7.17 Course Schedule — Pseudocode
**The code · 3 min**

```
adj = adjacency list from prerequisites
state = [0] * numCourses    // 0=unvisited, 1=visiting, 2=safe

function dfs(course):
    if state[course] == 1: return false  // CYCLE!
    if state[course] == 2: return true   // already verified safe
    state[course] = 1
    for each prereq of course:
        if not dfs(prereq): return false
    state[course] = 2
    return true

for each course: if not dfs(course): return false
return true
```

---

## 7.18 Course Schedule — Implementation
**Code it yourself · 10 min**

### ✅ C++ & C# Solutions
See [`course_schedule.cpp`](course_schedule.cpp) | [`course_schedule.cs`](course_schedule.cs)

**C++ Implementation**
```cpp
class Solution {
public:
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        vector<vector<int>> adj(numCourses);
        for (auto& p : prerequisites) adj[p[0]].push_back(p[1]);

        vector<int> state(numCourses, 0); // 0=unvisited, 1=visiting, 2=safe

        for (int c = 0; c < numCourses; c++)
            if (!dfs(c, adj, state)) return false;
        return true;
    }
private:
    bool dfs(int course, vector<vector<int>>& adj, vector<int>& state) {
        if (state[course] == 1) return false; // back edge → cycle
        if (state[course] == 2) return true;  // already verified
        state[course] = 1;
        for (int prereq : adj[course])
            if (!dfs(prereq, adj, state)) return false;
        state[course] = 2;
    }
};
```

**C# Implementation**
```csharp
using System.Collections.Generic;

public class Solution {
    public bool CanFinish(int numCourses, int[][] prerequisites) {
        var preMap = new Dictionary<int, List<int>>();
        for (int i = 0; i < numCourses; i++) {
            preMap[i] = new List<int>();
        }
        foreach (var pre in prerequisites) {
            preMap[pre[0]].Add(pre[1]);
        }
        
        var visitedSet = new HashSet<int>();
        
        for (int c = 0; c < numCourses; c++) {
            if (!Dfs(c, preMap, visitedSet)) return false;
        }
        
        return true;
    }
    
    private bool Dfs(int crs, Dictionary<int, List<int>> preMap, HashSet<int> visited) {
        if (visited.Contains(crs)) return false; // Cycle detected
        if (preMap[crs].Count == 0) return true;
        
        visited.Add(crs);
        
        foreach (int pre in preMap[crs]) {
            if (!Dfs(pre, preMap, visited)) return false;
        }
        
        visited.Remove(crs);
        preMap[crs].Clear();
        
        return true;
    }
}
```

| | Complexity |
|-|------------|
| **Time** | O(V + E) — visits each course and each prerequisite edge once |
| **Space** | O(V + E) — adjacency list + state array + recursion stack |

**Edge cases:**
- No prerequisites → always `true`
- Self-loop (`[0,0]`) → detected immediately (state[0]=1, we see it again)
- Disconnected graph → outer loop covers all components

**Common mistakes:**
- Using only 2 states (visited/unvisited) → can't distinguish cycles from already-explored nodes
- Not handling disconnected components in the outer loop

---

## 7.19 Course Schedule — Why This Problem?
**Interview context · 2 min**

- Classic **topological sort** / DAG validation problem
- **Follow-up:** *"Return the ordering?"* → LeetCode #210 (Course Schedule II) — collect nodes in reverse finishing order
- **Alternative:** Kahn's algorithm (BFS-based topological sort using in-degree counts)
- **Real world:** Build systems, package dependency resolution (npm, apt), task scheduling

---

## 7.20 Section Recap
**What you learned · 2 min**

| Problem | Graph Type | Algorithm | Time | Space |
|---------|-----------|-----------|------|-------|
| Number of Islands | Undirected Grid | DFS Flood Fill | O(mn) | O(mn) |
| Clone Graph | Undirected | DFS + Old→New Map | O(V+E) | O(V) |
| Course Schedule | Directed | DFS 3-State Cycle Detection | O(V+E) | O(V+E) |

**Core takeaways:**
- 🔑 Always track visited nodes — without it, you risk infinite loops
- 🔑 Clone Graph: register clone BEFORE recursing to handle cycles
- 🔑 Cycle detection in directed graphs: use 3-state DFS (unvisited/visiting/safe)
- 🔑 Grid problems are just implicitly-defined graphs — same DFS/BFS applies

**Additional practice:**
- LeetCode #417 — Pacific Atlantic Water Flow
- LeetCode #994 — Rotting Oranges (BFS)
- LeetCode #210 — Course Schedule II (topological order)

**Next section →** [08 · Binary Search](../08_Binary_Search/README.md)
