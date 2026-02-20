/**
 * Problem: Valid Parentheses
 * LeetCode: #20
 * Difficulty: Easy
 * Pattern: Stack (Bracket Matching)
 *
 * Time Complexity:  O(n)
 * Space Complexity: O(n)
 */
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool isValid(string s) {
        stack<char> st;
        unordered_map<char, char> closeToOpen = {{')', '('}, {'}', '{'}, {']', '['}};
        for (char c : s) {
            if (closeToOpen.count(c)) {
                if (st.empty() || st.top() != closeToOpen[c]) return false;
                st.pop();
            } else {
                st.push(c);
            }
        }
        return st.empty();
    }
};

int main() {
    Solution sol;
    assert(sol.isValid("()") == true);     cout << "[PASS] \"()\" → true\n";
    assert(sol.isValid("()[]{}") == true); cout << "[PASS] \"()[]{}\" → true\n";
    assert(sol.isValid("(]") == false);    cout << "[PASS] \"(]\" → false\n";
    assert(sol.isValid("([)]") == false);  cout << "[PASS] \"([)]\" → false\n";
    assert(sol.isValid("{[]}") == true);   cout << "[PASS] \"{[]}\" → true\n";
    cout << "\nAll tests passed!\n";
    return 0;
}
