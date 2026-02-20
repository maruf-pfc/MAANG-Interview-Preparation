/**
 * Problem: Longest Substring Without Repeating Characters
 * LeetCode: #3
 * Difficulty: Medium
 * Pattern: Sliding Window with HashSet
 *
 * Time Complexity:  O(n) — each char added and removed from set at most once
 * Space Complexity: O(min(n, 128)) — bounded by character set size
 */
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        unordered_set<char> window;
        int left = 0, maxLen = 0;

        for (int right = 0; right < (int)s.size(); right++) {
            // shrink window from left until duplicate is gone
            while (window.count(s[right])) {
                window.erase(s[left]);
                left++;
            }
            window.insert(s[right]);
            maxLen = max(maxLen, right - left + 1);
        }
        return maxLen;
    }
};

int main() {
    Solution sol;
    assert(sol.lengthOfLongestSubstring("abcabcbb") == 3);
    cout << "[PASS] \"abcabcbb\" → 3\n";

    assert(sol.lengthOfLongestSubstring("bbbbb") == 1);
    cout << "[PASS] \"bbbbb\" → 1\n";

    assert(sol.lengthOfLongestSubstring("pwwkew") == 3);
    cout << "[PASS] \"pwwkew\" → 3\n";

    assert(sol.lengthOfLongestSubstring("") == 0);
    cout << "[PASS] \"\" → 0\n";

    assert(sol.lengthOfLongestSubstring("au") == 2);
    cout << "[PASS] \"au\" → 2\n";

    cout << "\nAll tests passed!\n";
    return 0;
}
