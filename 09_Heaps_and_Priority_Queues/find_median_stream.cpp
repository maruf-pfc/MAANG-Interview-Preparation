/**
 * Problem: Find Median from Data Stream
 * LeetCode: #295
 * Difficulty: Hard
 * Pattern: Two Heaps (Max-Heap for lower half, Min-Heap for upper half)
 *
 * Invariant: small.size() >= large.size(), diff ≤ 1
 *
 * Time Complexity:  O(log n) addNum, O(1) findMedian
 * Space Complexity: O(n)
 */
#include <bits/stdc++.h>
using namespace std;

class MedianFinder {
    priority_queue<int> small;                               // max-heap (lower half)
    priority_queue<int, vector<int>, greater<int>> large;   // min-heap (upper half)
public:
    void addNum(int num) {
        small.push(num);                      // always add to lower half first
        large.push(small.top()); small.pop(); // ensure small's max ≤ large's min
        if (large.size() > small.size()) {    // rebalance
            small.push(large.top()); large.pop();
        }
    }
    double findMedian() {
        if (small.size() > large.size()) return small.top();
        return (small.top() + large.top()) / 2.0;
    }
};

int main() {
    MedianFinder mf;
    mf.addNum(1); mf.addNum(2);
    assert(mf.findMedian() == 1.5); cout << "[PASS] median(1,2) = 1.5\n";
    mf.addNum(3);
    assert(mf.findMedian() == 2.0); cout << "[PASS] median(1,2,3) = 2.0\n";
    mf.addNum(4); mf.addNum(5);
    assert(mf.findMedian() == 3.0); cout << "[PASS] median(1..5) = 3.0\n";
    cout << "\nAll tests passed!\n";
    return 0;
}
