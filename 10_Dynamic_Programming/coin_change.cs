using System;

public class Solution {
    public int CoinChange(int[] coins, int amount) {
        int[] dp = new int[amount + 1];
        Array.Fill(dp, amount + 1);
        dp[0] = 0;
        
        for (int a = 1; a <= amount; a++) {
            foreach (int c in coins) {
                if (a - c >= 0) {
                    dp[a] = Math.Min(dp[a], 1 + dp[a - c]);
                }
            }
        }
        
        return dp[amount] > amount ? -1 : dp[amount];
    }
}
