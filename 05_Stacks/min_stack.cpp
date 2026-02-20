/**
 * Problem: Min Stack
 * LeetCode: #155
 * Difficulty: Medium
 * Pattern: Augmented Stack — store (value, min_so_far) pairs
 *
 * Time Complexity:  O(1) all operations
 * Space Complexity: O(n)
 */
#include <bits/stdc++.h>
using namespace std;

class MinStack {
    stack<pair<int,int>> st; // (value, min_so_far)
public:
    void push(int val) {
        int currentMin = st.empty() ? val : min(val, st.top().second);
        st.push({val, currentMin});
    }
    void pop()    { st.pop(); }
    int top()     { return st.top().first; }
    int getMin()  { return st.top().second; }
};

int main() {
    MinStack ms;
    ms.push(-2); ms.push(0); ms.push(-3);
    assert(ms.getMin() == -3); cout << "[PASS] getMin() after push(-2,0,-3) = -3\n";
    ms.pop();
    assert(ms.top() == 0);    cout << "[PASS] top() after pop = 0\n";
    assert(ms.getMin() == -2); cout << "[PASS] getMin() after pop = -2\n";
    cout << "\nAll tests passed!\n";
    return 0;
}
