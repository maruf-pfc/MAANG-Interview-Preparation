/**
 * Problem: Merge Two Sorted Lists
 * LeetCode: #21
 * Difficulty: Easy
 * Pattern: Dummy Node + Compare and Link
 *
 * Time Complexity:  O(n + m) — n and m are lengths of the two lists
 * Space Complexity: O(1) — in-place linking
 */
#include <bits/stdc++.h>
using namespace std;

struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(nullptr) {}
};

class Solution {
public:
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        ListNode dummy(0);        // dummy head avoids special-casing the result head
        ListNode* tail = &dummy;

        while (list1 != nullptr && list2 != nullptr) {
            if (list1->val <= list2->val) {
                tail->next = list1;
                list1 = list1->next;
            } else {
                tail->next = list2;
                list2 = list2->next;
            }
            tail = tail->next;
        }
        // attach remaining non-exhausted list
        tail->next = (list1 != nullptr) ? list1 : list2;
        return dummy.next;
    }
};

// ─── Helpers ─────────────────────────────────────────────────────────────────
ListNode* makeList(vector<int> vals) {
    ListNode dummy(0); ListNode* tail = &dummy;
    for (int v : vals) { tail->next = new ListNode(v); tail = tail->next; }
    return dummy.next;
}
vector<int> toVec(ListNode* head) {
    vector<int> v;
    while (head) { v.push_back(head->val); head = head->next; }
    return v;
}

int main() {
    Solution sol;

    auto r1 = sol.mergeTwoLists(makeList({1,2,4}), makeList({1,3,4}));
    assert(toVec(r1) == vector<int>({1,1,2,3,4,4}));
    cout << "[PASS] merge([1,2,4], [1,3,4]) = [1,1,2,3,4,4]\n";

    auto r2 = sol.mergeTwoLists(nullptr, nullptr);
    assert(r2 == nullptr);
    cout << "[PASS] merge([], []) = []\n";

    auto r3 = sol.mergeTwoLists(nullptr, makeList({0}));
    assert(toVec(r3) == vector<int>({0}));
    cout << "[PASS] merge([], [0]) = [0]\n";

    cout << "\nAll tests passed!\n";
    return 0;
}
