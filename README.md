<div align="center">
  <img src="https://upload.wikimedia.org/wikipedia/commons/1/18/ISO_C%2B%2B_Logo.svg" alt="C++ Logo" width="80"/>
  <img src="https://upload.wikimedia.org/wikipedia/commons/4/4f/Csharp_Logo.png" alt="C# Logo" width="80"/>
  <h1>MAANG Interview Prep in C++ & C#</h1>
  <p><strong>A highly detailed, Open-Source Interactive Notebook Curriculum for cracking Meta, Amazon, Apple, Netflix, and Google.</strong></p>

  <p>
    <a href="https://github.com/maruf-pfc/MAANG-Interview-Preparation/actions/workflows/multi-lang-ci.yml">
      <img src="https://github.com/maruf-pfc/MAANG-Interview-Preparation/actions/workflows/multi-lang-ci.yml/badge.svg" alt="C++ & C# CI Tests">
    </a>
    <a href="https://github.com/maruf-pfc/MAANG-Interview-Preparation/issues">
      <img src="https://img.shields.io/github/issues/maruf-pfc/MAANG-Interview-Preparation?style=flat-square" alt="Issues">
    </a>
    <a href="https://github.com/maruf-pfc/MAANG-Interview-Preparation/pulls">
      <img src="https://img.shields.io/github/issues-pr/maruf-pfc/MAANG-Interview-Preparation?style=flat-square" alt="Pull Requests">
    </a>
    <a href="LICENSE">
      <img src="https://img.shields.io/github/license/maruf-pfc/MAANG-Interview-Preparation?style=flat-square" alt="License">
    </a>
  </p>
</div>

---

Welcome to the **MAANG Interview Prep** repository, a comprehensive, multi-language (C++ & C#) curriculum rewritten from the excellent **Repovive roadmap by Shayan Chashm Jahan**. 

This repository transforms the roadmap into a series of highly detailed "notebooks." It is designed specifically for high-performance software engineering candidates targeting top-tier tech companies. The inclusion of **C#** helps reinforce Object-Oriented Programming (OOP) principles and enterprise design patterns.

## 🚀 What Makes This Repository Special?

Instead of just linking out to LeetCode or dumping bare code files, every section in this repository is a **standalone notebook**. For all 41 problems across the 11 topics, you will find:

1. **The Core Concept:** Why the technique matters, when to use it, and how it works mechanically.
2. **Problem Statement:** The exact scenario you'll face.
3. **The Hint:** A nudge in the right direction if you get stuck without reading the answer.
4. **Solution Explanation:** Step-by-step logic detailing the algorithm.
5. **Pseudocode:** Language-agnostic logic to help you internalize the pattern.
6. **Detailed Code Implementation:** Production-ready C++ (C++17) code and idiomatic C# utilizing OOP paradigms.
7. **Complexity Analysis:** Deep dive into Time and Space constraints.
8. **Edge Cases & Common Mistakes:** What will actually trip you up in a live interview.
9. **Interview Context:** Why MAANG companies ask this specific question.

---

## 🗺️ The Roadmap

The curriculum is divided into 11 strictly ordered sections. Do not skip around — the patterns build sequentially.

### 🧱 Part 1: Fundamentals & Data Structures
* [**01 · Understanding MAANG Interviews**](01_Understanding_MAANG_Interviews/README.md)
  * Format, expectations, and the "Pattern Approach."
* [**02 · Arrays & Hashing**](02_Arrays_and_Hashing/README.md)
  * Hash maps, frequency counting, and O(1) lookups.
* [**03 · Two Pointers & Sliding Window**](03_Two_Pointers_and_Sliding_Window/README.md)
  * Moving pointers to avoid nested loops, dynamic window expansion/contraction.
* [**04 · Linked Lists**](04_Linked_Lists/README.md)
  * Pointer manipulation, cycle detection (Floyd's algorithm).
* [**05 · Stacks**](05_Stacks/README.md)
  * LIFO processing, matching brackets, and the powerful **Monotonic Stack**.
* [**06 · Trees & BST**](06_Trees_and_BST/README.md)
  * DFS recursion, BFS tree traversal, Binary Search Tree properties.

### 🧠 Part 2: Advanced Algorithmic Patterns
* [**07 · Graphs**](07_Graphs/README.md)
  * Connected components, Deep Copying, cycle detection in DAGs.
* [**08 · Binary Search**](08_Binary_Search/README.md)
  * Halving search spaces, rotated array navigation, finding minimums.
* [**09 · Heaps & Priority Queues**](09_Heaps_and_Priority_Queues/README.md)
  * Top-K elements, streaming medians, K-way merges.

### 👑 Part 3: Mastery
* [**10 · Dynamic Programming**](10_Dynamic_Programming/README.md)
  * 1D sequences, unbounded knapsack, 2D Grid paths, String DP.
* [**11 · Backtracking**](11_Backtracking/README.md)
  * Combinatorial search trees, subsets, permutations, constrained exploration.

### 🏗️ Part 4: System Design & Architecture
* [**12 · System Design**](12_System_Design/README.md)
  * Multi-tiered architectures, databases, load balancing, microservices, and Object-Oriented Design (OOD).

---

## 💻 How to Use This Guide

1. **Follow the Order:** Start at `01_Understanding_MAANG_Interviews` and move sequentially.
2. **Read the Intros:** Every section `README.md` begins with a crucial **Why/When/How** guide mapping out the core pattern. Don't skip it.
3. **Try Before You Peek:** Read the problem statement and the hint. Try to write the C++ code yourself before looking at the provided Solution Explanation and Implementation.
4. **Compile & Run:** Every single implementation provided in the notebooks is also available as a standalone `.cpp` file in its respective directory. You can test code locally with ease.
5. **Study the Edge Cases:** The "Edge Cases" and "Common Mistakes" sections are what separate a hired candidate from a rejected one. Internalize them.

---

## ⚙️ Running Locally & Testing

All solutions are self-contained files. C++ files include a `main()` validation entry point, while C# files are verified for compilation against .NET syntactical correctness.

**C++ Example:**
```bash
cd 02_Arrays_and_Hashing
g++ -std=c++17 two_sum.cpp -o two_sum
./two_sum
```

### Full Repository Verification
We maintain a zero-broken-code policy. You can run the top-level test scripts to globally verify that every single C++ solution in the repository compiles under `c++17` (and passes internal assertions) and every C# file is cleanly verified:

```bash
# Ensure scripts are executable
chmod +x test_all.sh test_all_cs.sh

# Run the full test suite via NPM
npm run test

# OR run manually
./test_all.sh
./test_all_cs.sh
```
*Note: This repository uses Husky pre-commit hooks to ensure no broken code can be pushed to the repository.*

---

## 🤝 Contributing

We welcome contributions from the open-source community! If you find a bug, want to add a new problem, or wish to expand on an explanation, please help us make this resource even better.

1. Fork the repository.
2. **Read our [CONTRIBUTING.md](CONTRIBUTING.md)** guidelines. All new contributions must match the exhaustive standard set in the existing notebooks *(Hint, Pseudocode, C++, Edge Cases, Interview Context)*.
3. Install dependencies: `npm install` (sets up pre-commit hooks).
4. Create a feature branch: `git checkout -b feature/new-problem`
5. Commit your changes: `git commit -m "feat: add missing problem"`
6. Push to the branch and open a Pull Request.

---

## 📜 License & Accreditation

This project is open-source and available under the terms of the MIT License. 

*The problem set and syllabus structure are based on the Repovive roadmap by Shayan Chashm Jahan. Implemented entirely in modern C++ and idiomatic C# for high-performance engineering interviews.*
