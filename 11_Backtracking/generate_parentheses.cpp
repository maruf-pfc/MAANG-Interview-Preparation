/**
 * Problem: Generate Parentheses
 * LeetCode: #22
 * Difficulty: Medium
 * Pattern: Constraint-Based Backtracking
 *
 * Add '(' if openCount < n. Add ')' if closeCount < openCount.
 * This generates ONLY valid strings — no post-filtering needed.
 *
 * Time Complexity:  O(4^n / sqrt(n)) — Catalan number
 * Space Complexity: O(n) — recursion depth = 2n
 */
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<string> generateParenthesis(int n) {
        vector<string> result;
        backtrack(n, 0, 0, "", result);
        return result;
    }
private:
    void backtrack(int n, int openCount, int closeCount,
                   string current, vector<string>& result) {
        if ((int)current.size() == 2 * n) {
            result.push_back(current);
            return;
        }
        if (openCount < n)
            backtrack(n, openCount + 1, closeCount, current + '(', result);
        if (closeCount < openCount)
            backtrack(n, openCount, closeCount + 1, current + ')', result);
    }
};

int main() {
    Solution sol;
    auto r1 = sol.generateParenthesis(1);
    assert(r1 == vector<string>({"()"}));
    cout << "[PASS] n=1 → [\"()\"]\n";

    auto r2 = sol.generateParenthesis(3);
    assert(r2.size() == 5); // Catalan(3) = 5
    cout << "[PASS] n=3 → 5 results: ";
    for (const auto& s : r2) cout << s << " ";
    cout << "\n";

    // Verify all are valid balanced parentheses
    for (const string& s : r2) {
        int bal = 0;
        for (char c : s) { bal += (c == '(' ? 1 : -1); assert(bal >= 0); }
        assert(bal == 0);
    }
    cout << "[PASS] All generated strings are valid\n";

    cout << "\nAll tests passed!\n";
    return 0;
}
