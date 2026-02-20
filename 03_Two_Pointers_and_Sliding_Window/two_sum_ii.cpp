/**
 * Problem: Two Sum II - Input Array Is Sorted
 * LeetCode: #167
 * Difficulty: Medium
 * Pattern: Two Pointers (Opposite Ends)
 *
 * Time Complexity:  O(n)
 * Space Complexity: O(1)
 */
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> twoSum(vector<int>& numbers, int target) {
        int left = 0, right = (int)numbers.size() - 1;
        while (left < right) {
            int sum = numbers[left] + numbers[right];
            if (sum > target)      right--;
            else if (sum < target) left++;
            else return {left + 1, right + 1}; // 1-indexed
        }
        return {};
    }
};

int main() {
    Solution sol;
    vector<int> n1 = {2, 7, 11, 15};
    assert(sol.twoSum(n1, 9) == vector<int>({1, 2}));
    cout << "[PASS] [2,7,11,15], target=9 → [1,2]\n";

    vector<int> n2 = {2, 3, 4};
    assert(sol.twoSum(n2, 6) == vector<int>({1, 3}));
    cout << "[PASS] [2,3,4], target=6 → [1,3]\n";

    vector<int> n3 = {-1, 0};
    assert(sol.twoSum(n3, -1) == vector<int>({1, 2}));
    cout << "[PASS] [-1,0], target=-1 → [1,2]\n";

    cout << "\nAll tests passed!\n";
    return 0;
}
