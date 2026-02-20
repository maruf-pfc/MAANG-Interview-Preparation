/**
 * Problem: Combination Sum
 * LeetCode: #39
 * Difficulty: Medium
 * Pattern: Backtracking with Reuse (Unbounded)
 *
 * Each candidate can be used unlimited times.
 *
 * Time Complexity:  O(2^(target/min_coin)) × k where k = avg result length
 * Space Complexity: O(target/min_coin) — max recursion depth
 */
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        vector<vector<int>> result;
        vector<int> current;
        backtrack(candidates, 0, target, current, result);
        return result;
    }
private:
    void backtrack(vector<int>& candidates, int index, int remaining,
                   vector<int>& current, vector<vector<int>>& result) {
        if (remaining == 0) {
            result.push_back(current); // found valid combination
            return;
        }
        if (remaining < 0 || index >= (int)candidates.size()) return; // prune

        // Option 1: use candidates[index] again (reuse allowed)
        current.push_back(candidates[index]);
        backtrack(candidates, index, remaining - candidates[index], current, result);
        current.pop_back(); // undo

        // Option 2: move to next candidate
        backtrack(candidates, index + 1, remaining, current, result);
    }
};

int main() {
    Solution sol;
    vector<int> c1 = {2,3,6,7};
    auto r1 = sol.combinationSum(c1, 7);
    assert(r1.size() == 2); // [2,2,3] and [7]
    cout << "[PASS] candidates=[2,3,6,7], target=7 → 2 combinations\n";

    vector<int> c2 = {2,3,5};
    auto r2 = sol.combinationSum(c2, 8);
    assert(r2.size() == 3); // [2,2,2,2],[2,3,3],[3,5]
    cout << "[PASS] candidates=[2,3,5], target=8 → 3 combinations\n";

    vector<int> c3 = {2};
    auto r3 = sol.combinationSum(c3, 1);
    assert(r3.empty());
    cout << "[PASS] candidates=[2], target=1 → no combinations\n";

    cout << "\nAll tests passed!\n";
    return 0;
}
