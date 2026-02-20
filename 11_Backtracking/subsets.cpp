/**
 * Problem: Subsets
 * LeetCode: #78
 * Difficulty: Medium
 * Pattern: Backtracking (Include/Exclude each element)
 *
 * Time Complexity:  O(2^n × n) — 2^n subsets, O(n) to copy each
 * Space Complexity: O(n) — recursion depth
 */
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<vector<int>> result;
        vector<int> current;
        backtrack(nums, 0, current, result);
        return result;
    }
private:
    void backtrack(vector<int>& nums, int index,
                   vector<int>& current, vector<vector<int>>& result) {
        if (index == (int)nums.size()) {
            result.push_back(current); // leaf: all include/exclude decisions made
            return;
        }
        // Decision 1: include nums[index]
        current.push_back(nums[index]);
        backtrack(nums, index + 1, current, result);

        // Decision 2: exclude nums[index] (the "backtrack")
        current.pop_back();
        backtrack(nums, index + 1, current, result);
    }
};

int main() {
    Solution sol;
    vector<int> n1 = {1,2,3};
    auto r1 = sol.subsets(n1);
    assert(r1.size() == 8); // 2^3 = 8
    cout << "[PASS] subsets([1,2,3]) → 8 subsets\n";

    vector<int> n2 = {};
    auto r2 = sol.subsets(n2);
    assert(r2.size() == 1 && r2[0].empty()); // just [[]]
    cout << "[PASS] subsets([]) → [[]]\n";

    vector<int> n3 = {0};
    auto r3 = sol.subsets(n3);
    assert(r3.size() == 2); // [[], [0]]
    cout << "[PASS] subsets([0]) → 2 subsets\n";

    cout << "\nAll tests passed!\n";
    return 0;
}
