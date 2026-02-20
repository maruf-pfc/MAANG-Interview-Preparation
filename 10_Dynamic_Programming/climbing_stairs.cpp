/**
 * Problem: Climbing Stairs
 * LeetCode: #70
 * Difficulty: Easy
 * Pattern: 1D DP (Fibonacci)
 *
 * Time Complexity:  O(n)
 * Space Complexity: O(1) — two rolling variables
 */
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int climbStairs(int n) {
        if (n <= 2) return n;
        int prev2 = 1, prev1 = 2;
        for (int i = 3; i <= n; i++) {
            int curr = prev1 + prev2;
            prev2 = prev1;
            prev1 = curr;
        }
        return prev1;
    }
};

int main() {
    Solution sol;
    assert(sol.climbStairs(1) == 1); cout << "[PASS] n=1 → 1\n";
    assert(sol.climbStairs(2) == 2); cout << "[PASS] n=2 → 2\n";
    assert(sol.climbStairs(3) == 3); cout << "[PASS] n=3 → 3\n";
    assert(sol.climbStairs(5) == 8); cout << "[PASS] n=5 → 8\n";
    assert(sol.climbStairs(10) == 89); cout << "[PASS] n=10 → 89\n";
    cout << "\nAll tests passed!\n";
    return 0;
}
