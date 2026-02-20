/**
 * Problem: Contains Duplicate
 * LeetCode: #217
 * Difficulty: Easy
 * Pattern: HashSet (Seen Tracking)
 *
 * Approach: Use an unordered_set to track seen elements.
 *           If element already in set → duplicate found.
 *
 * Time Complexity:  O(n)
 * Space Complexity: O(n)
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool containsDuplicate(vector<int>& nums) {
        unordered_set<int> seen;
        for (int num : nums) {
            if (seen.count(num)) return true; // already seen → duplicate
            seen.insert(num);
        }
        return false;
    }
};

// ─── Test Harness ────────────────────────────────────────────────────────────
int main() {
    Solution sol;

    vector<int> n1 = {1, 2, 3, 1};
    assert(sol.containsDuplicate(n1) == true);
    cout << "[PASS] [1,2,3,1] → true\n";

    vector<int> n2 = {1, 2, 3, 4};
    assert(sol.containsDuplicate(n2) == false);
    cout << "[PASS] [1,2,3,4] → false\n";

    vector<int> n3 = {1, 1, 1, 3, 3, 4, 3, 2, 4, 2};
    assert(sol.containsDuplicate(n3) == true);
    cout << "[PASS] [1,1,1,3,3,...] → true\n";

    vector<int> n4 = {1}; // single element
    assert(sol.containsDuplicate(n4) == false);
    cout << "[PASS] [1] → false\n";

    cout << "\nAll tests passed!\n";
    return 0;
}
