/**
 * Problem: Word Break
 * LeetCode: #139
 * Difficulty: Medium
 * Pattern: 1D DP (String Segmentation)
 *
 * dp[i] = true if s[0..i-1] can be segmented into dictionary words
 *
 * Time Complexity:  O(n² × m) — n positions, m words, O(n) comparison
 * Space Complexity: O(n)
 */
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        unordered_set<string> words(wordDict.begin(), wordDict.end());
        int n = s.size();
        vector<bool> dp(n + 1, false);
        dp[0] = true; // empty string is always valid

        for (int i = 1; i <= n; i++) {
            for (const string& word : words) {
                int len = word.size();
                if (i >= len && dp[i - len] && s.substr(i - len, len) == word) {
                    dp[i] = true;
                    break;
                }
            }
        }
        return dp[n];
    }
};

int main() {
    Solution sol;
    vector<string> d1 = {"leet","code"};
    assert(sol.wordBreak("leetcode", d1) == true);
    cout << "[PASS] \"leetcode\" with [leet,code] → true\n";

    vector<string> d2 = {"apple","pen"};
    assert(sol.wordBreak("applepenapple", d2) == true);
    cout << "[PASS] \"applepenapple\" → true\n";

    vector<string> d3 = {"cats","dog","sand","and","cat"};
    assert(sol.wordBreak("catsandog", d3) == false);
    cout << "[PASS] \"catsandog\" → false\n";

    cout << "\nAll tests passed!\n";
    return 0;
}
