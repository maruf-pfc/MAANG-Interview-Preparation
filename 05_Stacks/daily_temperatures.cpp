/**
 * Problem: Daily Temperatures
 * LeetCode: #739
 * Difficulty: Medium
 * Pattern: Monotonic Stack (Index-Based)
 *
 * Time Complexity:  O(n) — each index pushed/popped at most once
 * Space Complexity: O(n)
 */
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> dailyTemperatures(vector<int>& temperatures) {
        int n = temperatures.size();
        vector<int> result(n, 0);
        stack<int> st; // indices of unresolved days

        for (int i = 0; i < n; i++) {
            while (!st.empty() && temperatures[i] > temperatures[st.top()]) {
                int prevDay = st.top(); st.pop();
                result[prevDay] = i - prevDay;
            }
            st.push(i);
        }
        return result;
    }
};

int main() {
    Solution sol;
    vector<int> t1 = {73,74,75,71,69,72,76,73};
    assert(sol.dailyTemperatures(t1) == vector<int>({1,1,4,2,1,1,0,0}));
    cout << "[PASS] [73,74,...] → [1,1,4,2,1,1,0,0]\n";

    vector<int> t2 = {30,40,50,60};
    assert(sol.dailyTemperatures(t2) == vector<int>({1,1,1,0}));
    cout << "[PASS] [30,40,50,60] → [1,1,1,0]\n";

    vector<int> t3 = {30,60,90};
    assert(sol.dailyTemperatures(t3) == vector<int>({1,1,0}));
    cout << "[PASS] [30,60,90] → [1,1,0]\n";

    cout << "\nAll tests passed!\n";
    return 0;
}
