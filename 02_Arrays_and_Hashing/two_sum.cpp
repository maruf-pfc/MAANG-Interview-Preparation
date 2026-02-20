/**
 * Problem: Two Sum
 * LeetCode: #1
 * Difficulty: Easy
 * Pattern: HashMap (Complement Lookup)
 *
 * Approach: For each element, check if (target - element) is in our map.
 *           If yes, we found the pair. Otherwise, store element → index.
 *
 * Time Complexity:  O(n) — single pass
 * Space Complexity: O(n) — hash map stores up to n elements
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int, int> seen; // value → index

        for (int i = 0; i < (int)nums.size(); i++) {
            int complement = target - nums[i];
            if (seen.count(complement)) {
                return {seen[complement], i};
            }
            seen[nums[i]] = i;
        }
        return {}; // guaranteed to find one solution
    }
};

// ─── Test Harness ────────────────────────────────────────────────────────────
int main() {
    Solution sol;

    // Test 1: Basic case
    vector<int> nums1 = {2, 7, 11, 15};
    auto res1 = sol.twoSum(nums1, 9);
    assert(res1 == vector<int>({0, 1}));
    cout << "[PASS] Test 1: twoSum([2,7,11,15], 9) = [0,1]\n";

    // Test 2: Answer uses non-first elements
    vector<int> nums2 = {3, 2, 4};
    auto res2 = sol.twoSum(nums2, 6);
    assert(res2 == vector<int>({1, 2}));
    cout << "[PASS] Test 2: twoSum([3,2,4], 6) = [1,2]\n";

    // Test 3: Duplicate values
    vector<int> nums3 = {3, 3};
    auto res3 = sol.twoSum(nums3, 6);
    assert(res3 == vector<int>({0, 1}));
    cout << "[PASS] Test 3: twoSum([3,3], 6) = [0,1]\n";

    // Test 4: Negative numbers
    vector<int> nums4 = {-1, -2, -3, -4, -5};
    auto res4 = sol.twoSum(nums4, -8);
    assert(res4 == vector<int>({2, 4}));
    cout << "[PASS] Test 4: twoSum([-1,-2,-3,-4,-5], -8) = [2,4]\n";

    cout << "\nAll tests passed!\n";
    return 0;
}
