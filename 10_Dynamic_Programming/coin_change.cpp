/**
 * Problem: Coin Change
 * LeetCode: #322
 * Difficulty: Medium
 * Pattern: Unbounded Knapsack (Bottom-Up 1D DP)
 *
 * dp[a] = min coins to make amount a
 *
 * Time Complexity:  O(amount × len(coins))
 * Space Complexity: O(amount)
 */
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        const int INF = amount + 1;
        vector<int> dp(amount + 1, INF);
        dp[0] = 0;
        for (int a = 1; a <= amount; a++)
            for (int coin : coins)
                if (a - coin >= 0 && dp[a - coin] != INF)
                    dp[a] = min(dp[a], 1 + dp[a - coin]);
        return dp[amount] == INF ? -1 : dp[amount];
    }
};

int main() {
    Solution sol;
    vector<int> c1 = {1,5,10,25};
    assert(sol.coinChange(c1, 36) == 3); cout << "[PASS] coins=[1,5,10,25], amt=36 → 3\n";
    vector<int> c2 = {1,2,5};
    assert(sol.coinChange(c2, 11) == 3); cout << "[PASS] coins=[1,2,5], amt=11 → 3\n";
    vector<int> c3 = {2};
    assert(sol.coinChange(c3, 3) == -1); cout << "[PASS] coins=[2], amt=3 → -1\n";
    assert(sol.coinChange(c1, 0) == 0);  cout << "[PASS] amt=0 → 0\n";
    cout << "\nAll tests passed!\n";
    return 0;
}
