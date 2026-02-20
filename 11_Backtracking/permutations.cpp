/**
 * Problem: Permutations
 * LeetCode: #46
 * Difficulty: Medium
 * Pattern: Backtracking with Used[] array
 *
 * Time Complexity:  O(n! × n) — n! permutations, O(n) to copy each
 * Space Complexity: O(n) — recursion depth + current vector
 */
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<vector<int>> permute(vector<int>& nums) {
        vector<vector<int>> result;
        vector<int> current;
        vector<bool> used(nums.size(), false);
        backtrack(nums, current, used, result);
        return result;
    }
private:
    void backtrack(vector<int>& nums, vector<int>& current,
                   vector<bool>& used, vector<vector<int>>& result) {
        if (current.size() == nums.size()) {
            result.push_back(current); // complete permutation
            return;
        }
        for (int i = 0; i < (int)nums.size(); i++) {
            if (used[i]) continue;
            used[i] = true;
            current.push_back(nums[i]);
            backtrack(nums, current, used, result);
            current.pop_back(); // undo choice
            used[i] = false;    // undo used mark
        }
    }
};

int main() {
    Solution sol;
    vector<int> n1 = {1,2,3};
    auto r1 = sol.permute(n1);
    assert(r1.size() == 6); // 3! = 6
    cout << "[PASS] permute([1,2,3]) → 6 permutations\n";
    // Verify [1,2,3] and [3,2,1] are present
    assert(find(r1.begin(), r1.end(), vector<int>({1,2,3})) != r1.end());
    assert(find(r1.begin(), r1.end(), vector<int>({3,2,1})) != r1.end());
    cout << "[PASS] Contains [1,2,3] and [3,2,1]\n";

    vector<int> n2 = {0,1};
    auto r2 = sol.permute(n2);
    assert(r2.size() == 2); // 2!
    cout << "[PASS] permute([0,1]) → 2 permutations\n";

    cout << "\nAll tests passed!\n";
    return 0;
}
