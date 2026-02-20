/**
 * Problem: Longest Increasing Subsequence
 * LeetCode: #300
 * Difficulty: Medium
 * Pattern: 1D DP (LIS)
 *
 * dp[i] = length of LIS ending at index i
 *
 * Time Complexity:  O(n²)   [O(n log n) with binary search patience sorting]
 * Space Complexity: O(n)
 */
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        int n = nums.size();
        vector<int> dp(n, 1); // each element is LIS of length 1 by itself

        for (int i = 1; i < n; i++)
            for (int j = 0; j < i; j++)
                if (nums[j] < nums[i])
                    dp[i] = max(dp[i], dp[j] + 1);

        return *max_element(dp.begin(), dp.end());
    }
};

int main() {
    Solution sol;
    vector<int> n1 = {10,9,2,5,3,7,101,18};
    assert(sol.lengthOfLIS(n1) == 4); cout << "[PASS] [10,9,2,5,3,7,101,18] → 4\n";
    vector<int> n2 = {0,1,0,3,2,3};
    assert(sol.lengthOfLIS(n2) == 4); cout << "[PASS] [0,1,0,3,2,3] → 4\n";
    vector<int> n3 = {7,7,7,7,7};
    assert(sol.lengthOfLIS(n3) == 1); cout << "[PASS] all same → 1\n";
    vector<int> n4 = {1,2,3,4,5};
    assert(sol.lengthOfLIS(n4) == 5); cout << "[PASS] strictly increasing → 5\n";
    cout << "\nAll tests passed!\n";
    return 0;
}
