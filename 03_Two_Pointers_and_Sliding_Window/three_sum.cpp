/**
 * Problem: 3Sum
 * LeetCode: #15
 * Difficulty: Medium
 * Pattern: Sort + Two Pointers
 *
 * Time Complexity:  O(n²) — sort O(n log n) + outer loop O(n) * two pointers O(n)
 * Space Complexity: O(1) — output not counted
 */
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        vector<vector<int>> result;

        for (int i = 0; i < (int)nums.size() - 2; i++) {
            if (nums[i] > 0) break;                       // all positives → skip
            if (i > 0 && nums[i] == nums[i-1]) continue; // skip outer duplicates

            int left = i + 1, right = (int)nums.size() - 1;
            while (left < right) {
                int sum = nums[i] + nums[left] + nums[right];
                if (sum > 0) {
                    right--;
                } else if (sum < 0) {
                    left++;
                } else {
                    result.push_back({nums[i], nums[left], nums[right]});
                    left++; right--;
                    while (left < right && nums[left]  == nums[left-1])  left++;
                    while (left < right && nums[right] == nums[right+1]) right--;
                }
            }
        }
        return result;
    }
};

int main() {
    Solution sol;

    vector<int> n1 = {-1, 0, 1, 2, -1, -4};
    auto r1 = sol.threeSum(n1);
    assert(r1.size() == 2);
    cout << "[PASS] threeSum([-1,0,1,2,-1,-4]) → 2 triplets\n";

    vector<int> n2 = {0, 1, 1};
    auto r2 = sol.threeSum(n2);
    assert(r2.empty());
    cout << "[PASS] threeSum([0,1,1]) → []\n";

    vector<int> n3 = {0, 0, 0};
    auto r3 = sol.threeSum(n3);
    assert(r3.size() == 1 && r3[0] == vector<int>({0,0,0}));
    cout << "[PASS] threeSum([0,0,0]) → [[0,0,0]]\n";

    cout << "\nAll tests passed!\n";
    return 0;
}
