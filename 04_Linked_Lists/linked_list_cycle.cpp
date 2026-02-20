/**
 * Problem: Linked List Cycle
 * LeetCode: #141
 * Difficulty: Easy
 * Pattern: Fast & Slow Pointers (Floyd's Tortoise and Hare)
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
    bool hasCycle(ListNode* head) {
        ListNode* slow = head;
        ListNode* fast = head;
        while (fast != nullptr && fast->next != nullptr) {
            slow = slow->next;
            fast = fast->next->next;
            if (slow == fast) return true; // pointers met → cycle detected
        }
        return false; // fast reached end → no cycle
    }
};

int main() {
    Solution sol;

    // Test 1: Cycle exists (3 → 2 → 0 → -4 → back to 2)
    ListNode* n1 = new ListNode(3);
    ListNode* n2 = new ListNode(2);
    ListNode* n3 = new ListNode(0);
    ListNode* n4 = new ListNode(-4);
    n1->next = n2; n2->next = n3; n3->next = n4; n4->next = n2; // cycle
    assert(sol.hasCycle(n1) == true);
    cout << "[PASS] List with cycle → true\n";

    // Test 2: No cycle
    ListNode* m1 = new ListNode(1);
    ListNode* m2 = new ListNode(2);
    m1->next = m2;
    assert(sol.hasCycle(m1) == false);
    cout << "[PASS] 1→2 (no cycle) → false\n";

    // Test 3: Single node, no cycle
    ListNode* s = new ListNode(1);
    assert(sol.hasCycle(s) == false);
    cout << "[PASS] Single node → false\n";

    cout << "\nAll tests passed!\n";
    return 0;
}
