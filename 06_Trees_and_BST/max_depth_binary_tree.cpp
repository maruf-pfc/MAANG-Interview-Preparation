/**
 * Problem: Maximum Depth of Binary Tree
 * LeetCode: #104
 * Difficulty: Easy
 * Pattern: DFS Recursion
 *
 * Time Complexity:  O(n)
 * Space Complexity: O(h) — recursion stack height
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
    int maxDepth(TreeNode* root) {
        if (root == nullptr) return 0;
        return 1 + max(maxDepth(root->left), maxDepth(root->right));
    }
};

int main() {
    Solution sol;
    //      3
    //     / \
    //    9  20
    //       / \
    //      15   7
    TreeNode* root = new TreeNode(3);
    root->left = new TreeNode(9);
    root->right = new TreeNode(20);
    root->right->left = new TreeNode(15);
    root->right->right = new TreeNode(7);
    assert(sol.maxDepth(root) == 3);
    cout << "[PASS] Tree depth = 3\n";

    assert(sol.maxDepth(nullptr) == 0);
    cout << "[PASS] null tree depth = 0\n";

    TreeNode* single = new TreeNode(1);
    assert(sol.maxDepth(single) == 1);
    cout << "[PASS] Single node depth = 1\n";

    cout << "\nAll tests passed!\n";
    return 0;
}
