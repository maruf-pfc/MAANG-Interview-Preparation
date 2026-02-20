/**
 * Problem: Unique Paths
 * LeetCode: #62
 * Difficulty: Medium
 * Pattern: 2D Grid DP
 *
 * dp[i][j] = dp[i-1][j] + dp[i][j-1] (from above + from left)
 *
 * Time Complexity:  O(m × n)
 * Space Complexity: O(n) — rolling 1D DP
 */
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int uniquePaths(int m, int n) {
        vector<int> dp(n, 1); // first row: all 1s
        for (int i = 1; i < m; i++)
            for (int j = 1; j < n; j++)
                dp[j] += dp[j - 1]; // from above + from left
        return dp[n - 1];
    }
};

int main() {
    Solution sol;
    assert(sol.uniquePaths(3, 7) == 28); cout << "[PASS] 3×7 → 28\n";
    assert(sol.uniquePaths(3, 2) == 3);  cout << "[PASS] 3×2 → 3\n";
    assert(sol.uniquePaths(1, 1) == 1);  cout << "[PASS] 1×1 → 1\n";
    assert(sol.uniquePaths(1, 5) == 1);  cout << "[PASS] 1×5 → 1\n";
    assert(sol.uniquePaths(7, 3) == 28); cout << "[PASS] 7×3 → 28\n";
    cout << "\nAll tests passed!\n";
    return 0;
}
