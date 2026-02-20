/**
 * Problem: Longest Common Subsequence
 * LeetCode: #1143
 * Difficulty: Medium
 * Pattern: 2D String DP
 *
 * dp[i][j] = LCS of text1[0..i-1] and text2[0..j-1]
 *
 * Time Complexity:  O(m × n)
 * Space Complexity: O(m × n) — can reduce to O(min(m,n)) with 2 rows
 */
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int longestCommonSubsequence(string text1, string text2) {
        int m = text1.size(), n = text2.size();
        vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

        for (int i = 1; i <= m; i++)
            for (int j = 1; j <= n; j++)
                if (text1[i-1] == text2[j-1])
                    dp[i][j] = 1 + dp[i-1][j-1]; // characters match
                else
                    dp[i][j] = max(dp[i-1][j], dp[i][j-1]); // skip one

        return dp[m][n];
    }
};

int main() {
    Solution sol;
    assert(sol.longestCommonSubsequence("abcde", "ace") == 3);
    cout << "[PASS] (abcde, ace) → 3\n";
    assert(sol.longestCommonSubsequence("abc", "abc") == 3);
    cout << "[PASS] (abc, abc) → 3\n";
    assert(sol.longestCommonSubsequence("abc", "def") == 0);
    cout << "[PASS] (abc, def) → 0\n";
    assert(sol.longestCommonSubsequence("", "abc") == 0);
    cout << "[PASS] (\"\", abc) → 0\n";
    cout << "\nAll tests passed!\n";
    return 0;
}
