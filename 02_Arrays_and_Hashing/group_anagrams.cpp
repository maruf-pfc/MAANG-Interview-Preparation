/**
 * Problem: Group Anagrams
 * LeetCode: #49
 * Difficulty: Medium
 * Pattern: HashMap with Sorted Key
 *
 * Approach: Sort each string to get a canonical "anagram signature".
 *           Use sorted string as key in a map whose value is the group.
 *
 * Time Complexity:  O(n * k log k) — n strings, each sorted in O(k log k)
 * Space Complexity: O(n * k) — storing all strings in the map
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        unordered_map<string, vector<string>> groups;

        for (const string& s : strs) {
            string key = s;
            sort(key.begin(), key.end()); // sorted string = canonical anagram key
            groups[key].push_back(s);
        }

        vector<vector<string>> result;
        for (auto& [key, group] : groups) {
            result.push_back(group);
        }
        return result;
    }
};

// ─── Test Harness ────────────────────────────────────────────────────────────
int main() {
    Solution sol;

    // Test 1: Classic example
    vector<string> strs1 = {"eat","tea","tan","ate","nat","bat"};
    auto res1 = sol.groupAnagrams(strs1);
    cout << "[PASS] groupAnagrams([eat,tea,tan,ate,nat,bat]) → "
         << res1.size() << " groups\n";
    assert(res1.size() == 3); // [bat], [nat,tan], [ate,eat,tea]

    // Test 2: Single string
    vector<string> strs2 = {"a"};
    auto res2 = sol.groupAnagrams(strs2);
    assert(res2.size() == 1);
    cout << "[PASS] groupAnagrams([\"a\"]) → 1 group\n";

    // Test 3: All same (all in one group)
    vector<string> strs3 = {"abc", "bca", "cab"};
    auto res3 = sol.groupAnagrams(strs3);
    assert(res3.size() == 1);
    cout << "[PASS] groupAnagrams([abc,bca,cab]) → 1 group\n";

    cout << "\nAll tests passed!\n";
    return 0;
}
