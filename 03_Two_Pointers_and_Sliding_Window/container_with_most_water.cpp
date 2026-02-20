/**
 * Problem: Container With Most Water
 * LeetCode: #11
 * Difficulty: Medium
 * Pattern: Greedy Two Pointers
 *
 * Key insight: Move the shorter pointer — it's the bottleneck.
 *
 * Time Complexity:  O(n)
 * Space Complexity: O(1)
 */
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maxArea(vector<int>& height) {
        int left = 0, right = (int)height.size() - 1;
        int maxArea = 0;

        while (left < right) {
            int area = min(height[left], height[right]) * (right - left);
            maxArea = max(maxArea, area);
            // move the shorter line — it's the limiting factor
            if (height[left] < height[right]) left++;
            else right--;
        }
        return maxArea;
    }
};

int main() {
    Solution sol;
    vector<int> n1 = {1,8,6,2,5,4,8,3,7};
    assert(sol.maxArea(n1) == 49);
    cout << "[PASS] [1,8,6,2,5,4,8,3,7] → 49\n";

    vector<int> n2 = {1,1};
    assert(sol.maxArea(n2) == 1);
    cout << "[PASS] [1,1] → 1\n";

    vector<int> n3 = {4,3,2,1,4};
    assert(sol.maxArea(n3) == 16);
    cout << "[PASS] [4,3,2,1,4] → 16\n";

    cout << "\nAll tests passed!\n";
    return 0;
}
