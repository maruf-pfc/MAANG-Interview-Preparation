/**
 * Problem: Product of Array Except Self
 * LeetCode: #238
 * Difficulty: Medium
 * Pattern: Prefix + Suffix Products
 *
 * Approach:
 *   Pass 1 (left→right): result[i] = product of all elements to the LEFT of i
 *   Pass 2 (right→left): multiply result[i] by product of all elements to the RIGHT of i
 *   No division used — handles zeros correctly.
 *
 * Time Complexity:  O(n)
 * Space Complexity: O(1) — output array not counted
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        int n = nums.size();
        vector<int> result(n, 1);

        // Left pass: result[i] = product of nums[0..i-1]
        int prefix = 1;
        for (int i = 0; i < n; i++) {
            result[i] = prefix;
            prefix *= nums[i];
        }

        // Right pass: multiply result[i] by product of nums[i+1..n-1]
        int suffix = 1;
        for (int i = n - 1; i >= 0; i--) {
            result[i] *= suffix;
            suffix *= nums[i];
        }

        return result;
    }
};

// ─── Test Harness ────────────────────────────────────────────────────────────
int main() {
    Solution sol;

    // Test 1: Basic
    vector<int> n1 = {1, 2, 3, 4};
    auto r1 = sol.productExceptSelf(n1);
    assert(r1 == vector<int>({24, 12, 8, 6}));
    cout << "[PASS] productExceptSelf([1,2,3,4]) = [24,12,8,6]\n";

    // Test 2: Contains zero (division would fail — prefix*suffix handles correctly)
    vector<int> n2 = {-1, 1, 0, -3, 3};
    auto r2 = sol.productExceptSelf(n2);
    assert(r2 == vector<int>({0, 0, 9, 0, 0}));
    cout << "[PASS] productExceptSelf([-1,1,0,-3,3]) = [0,0,9,0,0]\n";

    // Test 3: Two elements
    vector<int> n3 = {1, 0};
    auto r3 = sol.productExceptSelf(n3);
    assert(r3 == vector<int>({0, 1}));
    cout << "[PASS] productExceptSelf([1,0]) = [0,1]\n";

    cout << "\nAll tests passed!\n";
    return 0;
}
