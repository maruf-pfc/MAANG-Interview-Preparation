/**
 * Problem: Clone Graph
 * LeetCode: #133
 * Difficulty: Medium
 * Pattern: DFS with Old-to-New Node Mapping
 *
 * Time Complexity:  O(V + E)
 * Space Complexity: O(V)
 */
#include <bits/stdc++.h>
using namespace std;

class Node {
public:
    int val;
    vector<Node*> neighbors;
    Node(int v) : val(v) {}
};

class Solution {
    unordered_map<Node*, Node*> oldToNew;
public:
    Node* cloneGraph(Node* node) {
        if (!node) return nullptr;
        return dfs(node);
    }
private:
    Node* dfs(Node* node) {
        if (oldToNew.count(node)) return oldToNew[node]; // already cloned
        Node* clone = new Node(node->val);
        oldToNew[node] = clone; // register BEFORE recursing (handles cycles)
        for (Node* neighbor : node->neighbors)
            clone->neighbors.push_back(dfs(neighbor));
        return clone;
    }
};

int main() {
    // Build: 1 -- 2 -- 3 -- 4 -- 1 (square ring)
    Node* n1 = new Node(1); Node* n2 = new Node(2);
    Node* n3 = new Node(3); Node* n4 = new Node(4);
    n1->neighbors = {n2, n4}; n2->neighbors = {n1, n3};
    n3->neighbors = {n2, n4}; n4->neighbors = {n3, n1};

    Solution sol;
    Node* cloned = sol.cloneGraph(n1);

    assert(cloned != n1);            // different pointer
    assert(cloned->val == 1);        // same value
    assert(cloned->neighbors.size() == 2); // same structure
    cout << "[PASS] Graph cloned with correct structure\n";

    assert(sol.cloneGraph(nullptr) == nullptr);
    cout << "[PASS] nullptr → nullptr\n";

    cout << "\nAll tests passed!\n";
    return 0;
}
