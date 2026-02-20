/**
 * Problem: Kth Largest Element in a Stream
 * LeetCode: #703
 * Difficulty: Easy
 * Pattern: Min-Heap of Size K (Persistent)
 *
 * Time Complexity:  O(log k) per add
 * Space Complexity: O(k)
 */
#include <bits/stdc++.h>
using namespace std;

class KthLargest {
    priority_queue<int, vector<int>, greater<int>> minHeap;
    int k;
public:
    KthLargest(int k, vector<int>& nums) : k(k) {
        for (int num : nums) add(num);
    }
    int add(int val) {
        minHeap.push(val);
        if ((int)minHeap.size() > k) minHeap.pop();
        return minHeap.top();
    }
};

int main() {
    vector<int> init = {4, 5, 8, 2};
    KthLargest kl(3, init);
    assert(kl.add(3) == 4);  cout << "[PASS] add(3) → 4\n";
    assert(kl.add(5) == 5);  cout << "[PASS] add(5) → 5\n";
    assert(kl.add(10) == 5); cout << "[PASS] add(10) → 5\n";
    assert(kl.add(9) == 8);  cout << "[PASS] add(9) → 8\n";
    assert(kl.add(4) == 8);  cout << "[PASS] add(4) → 8\n";
    cout << "\nAll tests passed!\n";
    return 0;
}
