/**
 * Problem: Lowest Common Ancestor of a Binary Search Tree
 * LeetCode: #235
 * Difficulty: Medium
 * Pattern: BST Navigation (Iterative)
 *
 * Key insight: Use BST ordering — if both p,q are left of root go left;
 *              both right go right; else root is the LCA (split point).
 *
 * Time Complexity:  O(h) — height of BST
 * Space Complexity: O(1) — iterative
 */
#include <bits/stdc++.h>
using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        TreeNode* curr = root;
        while (curr != nullptr) {
            if (p->val < curr->val && q->val < curr->val) {
                curr = curr->left;   // both in left subtree
            } else if (p->val > curr->val && q->val > curr->val) {
                curr = curr->right;  // both in right subtree
            } else {
                return curr;         // split point = LCA
            }
        }
        return nullptr;
    }
};

int main() {
    Solution sol;
    //        6
    //       / \
    //      2   8
    //     / \ / \
    //    0  4 7  9
    TreeNode* root = new TreeNode(6);
    TreeNode* n2 = new TreeNode(2);
    TreeNode* n8 = new TreeNode(8);
    root->left = n2; root->right = n8;
    n2->left = new TreeNode(0); n2->right = new TreeNode(4);
    n8->left = new TreeNode(7); n8->right = new TreeNode(9);

    TreeNode* lca1 = sol.lowestCommonAncestor(root, n2, n8);
    assert(lca1->val == 6);
    cout << "[PASS] LCA(2, 8) = 6\n";

    TreeNode* lca2 = sol.lowestCommonAncestor(root, n2, n2->right);
    assert(lca2->val == 2);
    cout << "[PASS] LCA(2, 4) = 2\n";

    cout << "\nAll tests passed!\n";
    return 0;
}
