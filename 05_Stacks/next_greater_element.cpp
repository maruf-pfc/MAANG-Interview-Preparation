/**
 * Problem: Next Greater Element I
 * LeetCode: #496
 * Difficulty: Easy
 * Pattern: Monotonic Decreasing Stack + HashMap
 *
 * Time Complexity:  O(n + m)
 * Space Complexity: O(n)
 */
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> nextGreaterElement(vector<int>& nums1, vector<int>& nums2) {
        unordered_map<int, int> nextGreater;
        stack<int> st; // monotonic decreasing stack

        for (int num : nums2) {
            while (!st.empty() && st.top() < num) {
                nextGreater[st.top()] = num;
                st.pop();
            }
            st.push(num);
        }

        vector<int> result;
        for (int n : nums1) {
            result.push_back(nextGreater.count(n) ? nextGreater[n] : -1);
        }
        return result;
    }
};

int main() {
    Solution sol;
    vector<int> n1 = {4,1,2}, n2 = {1,3,4,2};
    assert(sol.nextGreaterElement(n1, n2) == vector<int>({-1,3,-1}));
    cout << "[PASS] nums1=[4,1,2], nums2=[1,3,4,2] → [-1,3,-1]\n";

    vector<int> n3 = {2,4}, n4 = {1,2,3,4};
    assert(sol.nextGreaterElement(n3, n4) == vector<int>({3,-1}));
    cout << "[PASS] nums1=[2,4], nums2=[1,2,3,4] → [3,-1]\n";

    cout << "\nAll tests passed!\n";
    return 0;
}
