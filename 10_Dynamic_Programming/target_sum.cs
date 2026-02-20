using System;
using System.Collections.Generic;

public class Solution {
    public int FindTargetSumWays(int[] nums, int target) {
        int sum = 0;
        foreach (int num in nums) {
            sum += num;
        }
        
        // Impossible to reach target if sum < Math.Abs(target) or if (sum + target) is odd
        if (Math.Abs(target) > sum || (sum + target) % 2 == 1) {
            return 0;
        }
        
        int s1 = (sum + target) / 2;
        
        // dp[j] stores the number of ways to pick a subset of numbers that sum to j
        int[] dp = new int[s1 + 1];
        dp[0] = 1; // 1 way to get sum 0 (pick nothing)
        
        foreach (int num in nums) {
            for (int j = s1; j >= num; j--) {
                dp[j] += dp[j - num];
            }
        }
        
        return dp[s1];
    }
}
