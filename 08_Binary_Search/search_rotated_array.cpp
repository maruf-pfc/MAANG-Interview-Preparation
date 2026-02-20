/**
 * Problem: Search in Rotated Sorted Array
 * LeetCode: #33
 * Difficulty: Medium
 * Pattern: Binary Search — determine which half is sorted
 *
 * Time Complexity:  O(log n)
 * Space Complexity: O(1)
 */
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int search(vector<int>& nums, int target) {
        int left = 0, right = (int)nums.size() - 1;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (nums[mid] == target) return mid;

            if (nums[left] <= nums[mid]) {
                // left half [left, mid] is sorted
                if (nums[left] <= target && target < nums[mid])
                    right = mid - 1; // target in sorted left half
                else
                    left = mid + 1;
            } else {
                // right half [mid, right] is sorted
                if (nums[mid] < target && target <= nums[right])
                    left = mid + 1;  // target in sorted right half
                else
                    right = mid - 1;
            }
        }
        return -1;
    }
};

int main() {
    Solution sol;
    vector<int> n1 = {4,5,6,7,0,1,2};
    assert(sol.search(n1, 0) == 4); cout << "[PASS] target=0 → 4\n";
    assert(sol.search(n1, 3) == -1); cout << "[PASS] target=3 → -1\n";
    vector<int> n2 = {1};
    assert(sol.search(n2, 0) == -1); cout << "[PASS] [1], target=0 → -1\n";
    vector<int> n3 = {1,3};
    assert(sol.search(n3, 3) == 1); cout << "[PASS] [1,3], target=3 → 1\n";
    cout << "\nAll tests passed!\n";
    return 0;
}
