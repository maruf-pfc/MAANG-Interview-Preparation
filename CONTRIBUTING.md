# 🤝 Contributing to MAANG Interview Preparation

Thank you for contributing to this open-source interview preparation resource! Every contribution helps developers worldwide prepare for their MAANG interviews.

---

## 📋 Ways to Contribute

- **Add a new problem** with full documentation and C++ solution
- **Improve an existing explanation** — make it clearer or more beginner-friendly
- **Fix a bug** in a C++ solution
- **Add an alternative approach** with different time/space trade-offs
- **Improve test cases** in `.cpp` files
- **Report issues** — wrong complexity, incorrect edge cases, etc.

---

## 🗂️ Problem README Format

Every problem in a section's `README.md` must follow this exact template:

```markdown
---

## Problem N: Problem Name
> **LeetCode**: [#ID - Name](link) | **Difficulty**: Easy/Medium/Hard | **Pattern**: PatternName

### 📝 Problem Statement
[Full problem description]

**Example:**
```
Input: ...
Output: ...
Explanation: ...
```

### 💡 Intuition & Approach
[Plain English explanation of the key insight — WHY this approach works]

### 🔍 Hint
> [1-2 line hint that guides without spoiling — try solving before reading this!]

### 🗂️ Pseudocode
```
[Language-agnostic pseudocode]
```

### ✅ C++ Solution
```cpp
[Clean, well-commented C++ code]
```

### 📊 Complexity Analysis
| | Complexity | Explanation |
|-|------------|-------------|
| **Time** | O(...) | Reason |
| **Space** | O(...) | Reason |

### ⚠️ Edge Cases
- Edge case 1
- Edge case 2

### 🚫 Common Mistakes
- Mistake 1 and why it fails
- Mistake 2 and why it fails

### 🎯 Interview Tips
- What to say when explaining your approach
- Follow-up questions interviewers might ask
- Variations to be aware of
```

---

## 💻 C++ Solution File Format

Every `.cpp` file must:

1. **Include standard headers** at the top
2. **Be self-contained** — no external dependencies
3. **Have a `main()` function** with multiple test cases
4. **Print expected vs actual output** for verification
5. **Include complexity comment** near the solution

### Template

```cpp
/**
 * Problem: [Problem Name]
 * LeetCode: #[ID]
 * Difficulty: Easy/Medium/Hard
 * Pattern: [Pattern Name]
 *
 * Approach: [Brief description]
 * Time Complexity: O(...)
 * Space Complexity: O(...)
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    // [function signature] {
    //     [implementation]
    // }
};

// ─── Test Harness ───────────────────────────────────────────────────────────

int main() {
    Solution sol;
    
    // Test Case 1
    // ...
    
    // Test Case 2 (edge case)
    // ...
    
    cout << "All tests passed!" << endl;
    return 0;
}
```

---

## 🔄 Pull Request Process

1. **Fork** the repository
2. **Create a branch**: `git checkout -b add/topic-problem-name`
3. **Add your changes** following the formats above
4. **Compile your C++ file**: `g++ -std=c++17 -Wall your_file.cpp && ./a.out`
5. **Commit with a clear message**: `git commit -m "Add: Rotate Array (Arrays) with O(n) approach"`
6. **Push and open a PR** — describe what you added and why

---

## ✅ PR Checklist

Before submitting, verify:

- [ ] README entry follows the exact template format
- [ ] C++ file is self-contained and compiles with `g++ -std=c++17`
- [ ] Test cases cover normal case + at least 2 edge cases
- [ ] Time and Space complexity are correct and explained
- [ ] Common mistakes section is filled in
- [ ] Interview tips are practical and actionable
- [ ] No Python code — this repo is C++ only

---

## 📐 Code Style

- Use `camelCase` for variables and functions
- Use `PascalCase` for class names
- Prefer descriptive names over single letters (`left`, `right` over `l`, `r`)
- Comment non-obvious logic inline
- Keep functions focused and short

---

## 🐛 Reporting Issues

Use GitHub Issues with the following tags:
- `bug` — incorrect solution or complexity
- `improvement` — better explanation needed
- `new-problem` — request to add a problem
- `typo` — documentation error

---

## 📜 Code of Conduct

- Be respectful and constructive in all discussions
- Focus on the quality of the contribution, not the contributor
- Beginners are welcome — we all start somewhere

---

*Thank you for making this resource better for the entire developer community!* 🌍
