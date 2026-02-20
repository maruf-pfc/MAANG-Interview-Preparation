/**
 * Problem: House Robber
 * LeetCode: #198
 * Difficulty: Medium
 * Pattern: 1D DP with Constraint (skip adjacent)
 *
 * dp[i] = max(skip: dp[i-1], rob: dp[i-2] + nums[i])
 *
 * Time Complexity:  O(n)
 * Space Complexity: O(1)
 */
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int rob(vector<int>& nums) {
        int prev2 = 0, prev1 = 0;
        for (int num : nums) {
            int curr = max(prev1, prev2 + num); // skip or rob
            prev2 = prev1;
            prev1 = curr;
        }
        return prev1;
    }
};

int main() {
    Solution sol;
    vector<int> n1 = {1,2,3,1};
    assert(sol.rob(n1) == 4); cout << "[PASS] [1,2,3,1] → 4\n";
    vector<int> n2 = {2,7,9,3,1};
    assert(sol.rob(n2) == 12); cout << "[PASS] [2,7,9,3,1] → 12\n";
    vector<int> n3 = {1};
    assert(sol.rob(n3) == 1); cout << "[PASS] [1] → 1\n";
    vector<int> n4 = {0,0,0};
    assert(sol.rob(n4) == 0); cout << "[PASS] [0,0,0] → 0\n";
    cout << "\nAll tests passed!\n";
    return 0;
}
