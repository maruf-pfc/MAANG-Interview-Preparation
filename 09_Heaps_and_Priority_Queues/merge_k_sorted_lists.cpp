/**
 * Problem: Merge K Sorted Lists
 * LeetCode: #23
 * Difficulty: Hard
 * Pattern: Min-Heap (K-Way Merge)
 *
 * Time Complexity:  O(n log k) — n = total nodes, k = number of lists
 * Space Complexity: O(k)
 */
#include <bits/stdc++.h>
using namespace std;

struct ListNode {
    int val; ListNode* next;
    ListNode(int x) : val(x), next(nullptr) {}
};

class Solution {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        using T = tuple<int, int, ListNode*>; // (val, list_idx, node)
        priority_queue<T, vector<T>, greater<T>> minHeap;

        for (int i = 0; i < (int)lists.size(); i++)
            if (lists[i]) minHeap.push({lists[i]->val, i, lists[i]});

        ListNode dummy(0); ListNode* tail = &dummy;
        while (!minHeap.empty()) {
            auto [val, idx, node] = minHeap.top(); minHeap.pop();
            tail->next = node; tail = tail->next;
            if (node->next) minHeap.push({node->next->val, idx, node->next});
        }
        return dummy.next;
    }
};

// Helpers
ListNode* makeList(vector<int> v) {
    ListNode dummy(0); ListNode* t = &dummy;
    for (int x : v) { t->next = new ListNode(x); t = t->next; }
    return dummy.next;
}
vector<int> toVec(ListNode* h) {
    vector<int> v; while (h) { v.push_back(h->val); h = h->next; } return v;
}

int main() {
    Solution sol;
    vector<ListNode*> lists = {makeList({1,4,5}), makeList({1,3,4}), makeList({2,6})};
    assert(toVec(sol.mergeKLists(lists)) == vector<int>({1,1,2,3,4,4,5,6}));
    cout << "[PASS] merge 3 lists → [1,1,2,3,4,4,5,6]\n";

    vector<ListNode*> empty = {};
    assert(sol.mergeKLists(empty) == nullptr);
    cout << "[PASS] empty → nullptr\n";

    cout << "\nAll tests passed!\n";
    return 0;
}
