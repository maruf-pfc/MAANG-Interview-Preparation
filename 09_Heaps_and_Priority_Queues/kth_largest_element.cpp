/**
 * Problem: Kth Largest Element in an Array
 * LeetCode: #215
 * Difficulty: Medium
 * Pattern: Min-Heap of Size K
 *
 * Time Complexity:  O(n log k)
 * Space Complexity: O(k)
 */
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        priority_queue<int, vector<int>, greater<int>> minHeap; // min-heap
        for (int num : nums) {
            minHeap.push(num);
            if ((int)minHeap.size() > k) minHeap.pop(); // evict smallest
        }
        return minHeap.top(); // k-th largest
    }
};

int main() {
    Solution sol;
    vector<int> n1 = {3,2,1,5,6,4};
    assert(sol.findKthLargest(n1, 2) == 5); cout << "[PASS] k=2 → 5\n";
    vector<int> n2 = {3,2,3,1,2,4,5,5,6};
    assert(sol.findKthLargest(n2, 4) == 4); cout << "[PASS] k=4 → 4\n";
    vector<int> n3 = {1};
    assert(sol.findKthLargest(n3, 1) == 1); cout << "[PASS] k=1 → 1\n";
    cout << "\nAll tests passed!\n";
    return 0;
}
