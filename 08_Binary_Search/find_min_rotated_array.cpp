/**
 * Problem: Find Minimum in Rotated Sorted Array
 * LeetCode: #153
 * Difficulty: Medium
 * Pattern: Binary Search for Pivot
 *
 * Key: Compare mid with right. If mid > right, minimum is to the right.
 *
 * Time Complexity:  O(log n)
 * Space Complexity: O(1)
 */
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int findMin(vector<int>& nums) {
        int left = 0, right = (int)nums.size() - 1;
        while (left < right) {
            int mid = left + (right - left) / 2;
            if (nums[mid] > nums[right])
                left = mid + 1;  // minimum is in right half
            else
                right = mid;     // mid could be minimum, keep it
        }
        return nums[left];
    }
};

int main() {
    Solution sol;
    vector<int> n1 = {3,4,5,1,2};
    assert(sol.findMin(n1) == 1); cout << "[PASS] [3,4,5,1,2] → 1\n";
    vector<int> n2 = {4,5,6,7,0,1,2};
    assert(sol.findMin(n2) == 0); cout << "[PASS] [4,5,6,7,0,1,2] → 0\n";
    vector<int> n3 = {11,13,15,17};
    assert(sol.findMin(n3) == 11); cout << "[PASS] [11,13,15,17] → 11\n";
    cout << "\nAll tests passed!\n";
    return 0;
}
