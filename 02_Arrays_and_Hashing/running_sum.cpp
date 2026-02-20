/**
 * Problem: Running Sum of 1D Array
 * LeetCode: #1480
 * Difficulty: Easy
 * Pattern: Prefix Sum (In-Place)
 *
 * Approach: Each element becomes the cumulative sum of all elements up to it.
 *           Modify in-place: nums[i] += nums[i-1]
 *
 * Time Complexity:  O(n)
 * Space Complexity: O(1) — in-place (output array doesn't count)
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> runningSum(vector<int>& nums) {
        for (int i = 1; i < (int)nums.size(); i++) {
            nums[i] += nums[i - 1]; // accumulate prefix sum
        }
        return nums;
    }
};

// ─── Test Harness ────────────────────────────────────────────────────────────
int main() {
    Solution sol;

    vector<int> n1 = {1, 2, 3, 4};
    auto r1 = sol.runningSum(n1);
    assert(r1 == vector<int>({1, 3, 6, 10}));
    cout << "[PASS] runningSum([1,2,3,4]) = [1,3,6,10]\n";

    vector<int> n2 = {1, 1, 1, 1, 1};
    auto r2 = sol.runningSum(n2);
    assert(r2 == vector<int>({1, 2, 3, 4, 5}));
    cout << "[PASS] runningSum([1,1,1,1,1]) = [1,2,3,4,5]\n";

    vector<int> n3 = {3, 1, 2, 10, 1};
    auto r3 = sol.runningSum(n3);
    assert(r3 == vector<int>({3, 4, 6, 16, 17}));
    cout << "[PASS] runningSum([3,1,2,10,1]) = [3,4,6,16,17]\n";

    cout << "\nAll tests passed!\n";
    return 0;
}
