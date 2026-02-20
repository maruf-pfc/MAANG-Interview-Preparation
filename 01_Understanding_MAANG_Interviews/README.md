# 🎯 Section 01: Understanding MAANG Interviews

> **Units**: 6 | **Estimated Time**: ~14 minutes | **Code Required**: None

Understanding *how* MAANG interviews work is as important as solving problems. This section gives you the full picture: what to expect, how you'll be evaluated, and how to use this roadmap effectively.

---

## 1.1 What This Roadmap Covers

About **68% of questions overlap** across Meta, Amazon, Apple, Netflix, and Google. This roadmap covers the patterns — not individual problems — so learning them prepares you for any of these companies.

The roadmap is structured as:
1. Learn a topic's core pattern
2. See it applied to 3–5 representative problems
3. Practice until the pattern becomes instinct

---

## 1.2 The Interview Format

A standard MAANG coding interview:

| Phase | Duration | Description |
|-------|----------|-------------|
| **Introduction** | 5 min | Quick hello, background questions |
| **Problem Solving** | 30–40 min | 1–2 coding problems on a shared editor |
| **Q&A** | 5–10 min | Your questions for the interviewer |

**Key facts:**
- You'll code in a collaborative editor (CoderPad, Google Docs, or similar)
- You're expected to **think aloud** — silence is a red flag
- Behavioral questions often come at the start or end: "Tell me about a time you disagreed with a teammate"
- Some rounds are **system design** (more common for senior roles)

---

## 1.3 What Interviewers Look For

Interviewers evaluate you on **five dimensions**:

### 1. Problem-Solving Ability
- Can you decompose the problem into smaller parts?
- Do you start with a brute-force and then optimize?
- Do you spot patterns quickly?

### 2. Coding Proficiency
- Is your code clean, readable, and correct?
- Do you use appropriate data structures?
- Do you avoid unnecessary complexity?

### 3. Communication
- Do you explain your thinking as you code?
- Can you articulate trade-offs (time vs space)?
- Do you ask clarifying questions before diving in?

### 4. Optimization Instinct
- Can you identify bottlenecks in your solution?
- Do you suggest improvements without being prompted?

### 5. Edge Case Awareness
- Empty arrays, null inputs, negative numbers, integer overflow
- Off-by-one errors, duplicates, single-element arrays

---

## 1.4 The Pattern Approach

> **Insight**: There are ~15 core patterns. Master them and you can solve hundreds of problems.

When you see a new problem, ask:
- Does it involve finding pairs? → **Two Pointers or HashMap**
- Does it involve a subarray/substring? → **Sliding Window**
- Does it involve a tree? → **DFS or BFS**
- Does it need repeated min/max? → **Heap**
- Does it have overlapping subproblems? → **Dynamic Programming**
- Does it need all combinations? → **Backtracking**

**Practice recognizing patterns, not memorizing solutions.**

---

## 1.5 How to Use This Roadmap (Study Plan)

### The Right Workflow Per Problem
```
1. Read the problem statement
2. Clarify constraints (ask yourself: what are the bounds? edge cases?)
3. Verbalize your approach BEFORE coding
4. Code the solution
5. Test with the given example, then edge cases
6. Analyze time/space complexity
7. Consider optimizations
```

### Time Guidelines
- **Easy problems**: aim to solve in 10–15 minutes
- **Medium problems**: aim to solve in 20–30 minutes
- **Hard problems**: understand the approach in 45 minutes

### Spaced Repetition Schedule
| Day 1 | Day 3 | Day 7 | Day 14 | Day 30 |
|-------|-------|-------|--------|--------|
| Learn | Review | Re-solve from scratch | Timed practice | Final check |

---

## 1.6 Section Recap

**What you should know now:**
- ✅ Interview lasts 45–60 min with 1–2 problems
- ✅ Talking through your thought process is critical
- ✅ You're evaluated on problem-solving, coding, communication, optimization, and edge cases
- ✅ Learn patterns, not individual problems
- ✅ Always: brute-force → optimize → code → test

**Next up**: [Arrays & Hashing →](../02_Arrays_and_Hashing/README.md)

---

## 💬 Behavioral Question Bank

For non-coding rounds, prepare 2–3 stories for each:
- A time you solved a technically challenging problem
- A time you disagreed with your manager or teammate
- A time you delivered under a tight deadline
- A time you failed and what you learned
- A time you influenced a technical decision

Use the **STAR format**: Situation → Task → Action → Result.

---

## 📌 Common Mistakes to Avoid

| Mistake | Better Approach |
|---------|----------------|
| Jumping straight to code | Discuss approach first (2–3 min) |
| Staying silent while thinking | Narrate your thought process aloud |
| Giving up when stuck | Ask for hints; show how you debug |
| Only handling the happy path | Always check edge cases after initial solution |
| Not asking clarifying questions | Ask about constraints before you start |
