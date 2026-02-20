using System;

public class Solution {
    public int LengthOfLIS(int[] nums) {
        if (nums == null || nums.Length == 0) return 0;
        
        int[] dp = new int[nums.Length];
        Array.Fill(dp, 1);
        int maxLIS = 1;
        
        for (int i = 1; i < nums.Length; i++) {
            for (int j = 0; j < i; j++) {
                if (nums[j] < nums[i]) {
                    dp[i] = Math.Max(dp[i], 1 + dp[j]);
                }
            }
            maxLIS = Math.Max(maxLIS, dp[i]);
        }
        
        return maxLIS;
    }
}
