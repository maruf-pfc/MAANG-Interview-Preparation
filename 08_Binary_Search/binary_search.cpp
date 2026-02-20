/**
 * Problem: Binary Search
 * LeetCode: #704
 * Difficulty: Easy
 * Pattern: Classic Binary Search Template
 *
 * Key: mid = left + (right - left) / 2 prevents integer overflow.
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
            int mid = left + (right - left) / 2; // safe mid
            if (nums[mid] == target) return mid;
            else if (nums[mid] < target) left = mid + 1;
            else right = mid - 1;
        }
        return -1;
    }
};

int main() {
    Solution sol;
    vector<int> n1 = {-1,0,3,5,9,12};
    assert(sol.search(n1, 9) == 4);   cout << "[PASS] target=9 → index 4\n";
    assert(sol.search(n1, 2) == -1);  cout << "[PASS] target=2 → -1\n";
    assert(sol.search(n1, -1) == 0);  cout << "[PASS] target=-1 → index 0\n";
    assert(sol.search(n1, 12) == 5);  cout << "[PASS] target=12 → index 5\n";
    cout << "\nAll tests passed!\n";
    return 0;
}
