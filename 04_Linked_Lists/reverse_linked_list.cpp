/**
 * Problem: Reverse Linked List
 * LeetCode: #206
 * Difficulty: Easy
 * Pattern: Iterative Pointer Reversal (prev, curr, next)
 *
 * Time Complexity:  O(n)
 * Space Complexity: O(1)
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
    ListNode* reverseList(ListNode* head) {
        ListNode* prev = nullptr;
        ListNode* curr = head;
        while (curr != nullptr) {
            ListNode* nextNode = curr->next; // save next
            curr->next = prev;              // reverse link
            prev = curr;                    // advance prev
            curr = nextNode;                // advance curr
        }
        return prev; // new head
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

    auto* list1 = makeList({1,2,3,4,5});
    assert(toVec(sol.reverseList(list1)) == vector<int>({5,4,3,2,1}));
    cout << "[PASS] 1→2→3→4→5 reversed = 5→4→3→2→1\n";

    auto* list2 = makeList({1,2});
    assert(toVec(sol.reverseList(list2)) == vector<int>({2,1}));
    cout << "[PASS] 1→2 reversed = 2→1\n";

    assert(sol.reverseList(nullptr) == nullptr);
    cout << "[PASS] nullptr reversed = nullptr\n";

    cout << "\nAll tests passed!\n";
    return 0;
}
