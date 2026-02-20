# MAANG (FAANG) Interview Prep in C++

Welcome to the **MAANG Interview Prep** repository. This is a comprehensive, open-source guide designed to prepare you for coding interviews at Meta, Amazon, Apple, Netflix, and Google.

This repository is built upon the excellent curriculum from the **Repovive roadmap by Shayan Chashm Jahan**, but has been engineered as a **C++-first** resource. It transforms the roadmap into a series of comprehensive, highly detailed "notebooks" — each section folder contains a `README.md` that serves as a self-contained study guide.

---

## What Makes This Repository Special?

Instead of just linking out to LeetCode, every section in this repository is a **standalone notebook**. For every problem across all 11 topics, you will find:
1. **The Core Concept:** Why the technique matters, when to use it, and how it works.
2. **Problem Statement:** The exact scenario you'll face.
3. **The Hint:** A nudge in the right direction if you get stuck.
4. **Solution Explanation:** Step-by-step logic detailing the algorithm.
5. **Pseudocode:** Language-agnostic logic to help you internalize the pattern.
6. **Detailed C++ Implementation:** Production-ready C++ (C++17) code.
7. **Complexity Analysis:** Deep dive into Time and Space constraints.
8. **Edge Cases & Common Mistakes:** What will trip you up in a live interview.
9. **Interview Context:** Why MAANG companies ask this specific question.

---

## 🗺️ The Roadmap

The curriculum is divided into 11 strictly ordered sections. Do not skip around — the patterns build on each other.

### Fundamentals
* [**01 · Understanding MAANG Interviews**](01_Understanding_MAANG_Interviews/README.md) (6 units)
  * Format, expectations, and the "Pattern Approach."

### Data Structures & Patterns
* [**02 · Arrays & Hashing**](02_Arrays_and_Hashing/README.md) (32 units)
  * Hash maps, frequency counting, and O(1) lookups.
* [**03 · Two Pointers & Sliding Window**](03_Two_Pointers_and_Sliding_Window/README.md) (26 units)
  * Moving pointers to avoid nested loops, dynamic window expansion/contraction.
* [**04 · Linked Lists**](04_Linked_Lists/README.md) (20 units)
  * Pointer manipulation, cycle detection (Floyd's algorithm).
* [**05 · Stacks**](05_Stacks/README.md) (26 units)
  * LIFO processing, matching brackets, and the powerful **Monotonic Stack**.
* [**06 · Trees & BST**](06_Trees_and_BST/README.md) (20 units)
  * DFS recursion, BFS tree traversal, Binary Search Tree properties.

### Advanced Algorithmic Patterns
* [**07 · Graphs**](07_Graphs/README.md) (20 units)
  * Connected components, Deep Copying, cycle detection in DAGs.
* [**08 · Binary Search**](08_Binary_Search/README.md) (20 units)
  * Halving search spaces, rotated array navigation, finding minimums.
* [**09 · Heaps & Priority Queues**](09_Heaps_and_Priority_Queues/README.md) (26 units)
  * Top-K elements, streaming medians, K-way merges.

### Mastery
* [**10 · Dynamic Programming**](10_Dynamic_Programming/README.md) (44 units)
  * 1D sequences, unbounded knapsack, 2D Grid paths, String DP.
* [**11 · Backtracking**](11_Backtracking/README.md) (32 units)
  * Combinatorial search trees, subsets, permutations, constrained exploration.

---

## 💻 How to Use This Repository

1. **Follow the Order:** Start at `01_Understanding_MAANG_Interviews` and move sequentially.
2. **Read the Intros:** Every section `README.md` begins with a crucial **Why/When/How** guide mapping out the core pattern. Don't skip it.
3. **Try Before You Peek:** Read the problem statement and the hint. Try to write the C++ code yourself before looking at the provided Solution Explanation and Implementation.
4. **Compile & Run:** Every single implementation provided in the notebooks is also available as a standalone `.cpp` file in its respective directory.
   ```bash
   g++ -std=c++17 filename.cpp && ./a.out 
   ```
5. **Study the Edge Cases:** The "Edge Cases" and "Common Mistakes" sections are what separate a hired candidate from a rejected one. Memorize them.

---

## Running the Tests / Compiling

All solutions are self-contained C++ files with a `main()` validation entry point. You can compile any file individually:

```bash
cd 02_Arrays_and_Hashing
g++ -std=c++17 two_sum.cpp -o two_sum
./two_sum
```

Alternatively, you can run the top-level test script to verify that every single C++ solution in the repository compiles and passes its internal test cases:

```bash
chmod +x test_all.sh
./test_all.sh
```

---

## 🤝 Contributing

This is an open-source initiative. If you find a bug, want to add a new problem, or wish to expand on an explanation, please read our [CONTRIBUTING.md](CONTRIBUTING.md) guidelines and open a Pull Request. 

*Remember: All new contributions must match the exhaustive standard set in the existing notebooks (Hint, Pseudocode, C++, Edge Cases, Interview Context).*

---
*Based on the Repovive syllabus by Shayan Chashm Jahan. Implemented entirely in modern C++ for high-performance engineering interviews.*
