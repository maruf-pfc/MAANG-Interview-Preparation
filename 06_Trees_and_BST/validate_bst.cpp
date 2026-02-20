/**
 * Problem: Validate Binary Search Tree
 * LeetCode: #98
 * Difficulty: Medium
 * Pattern: DFS with Valid Range Bounds (min, max)
 *
 * Key insight: Pass bounds downward. Left subtree values must be < current node.
 *              Right subtree values must be > current node.
 *
 * Time Complexity:  O(n)
 * Space Complexity: O(h)
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
    bool isValidBST(TreeNode* root) {
        return validate(root, LONG_MIN, LONG_MAX);
    }

private:
    bool validate(TreeNode* node, long minVal, long maxVal) {
        if (node == nullptr) return true;
        if (node->val <= minVal || node->val >= maxVal) return false;
        return validate(node->left,  minVal,    node->val)
            && validate(node->right, node->val, maxVal);
    }
};

int main() {
    Solution sol;
    //   2
    //  / \
    // 1   3
    TreeNode* t1 = new TreeNode(2);
    t1->left = new TreeNode(1);
    t1->right = new TreeNode(3);
    assert(sol.isValidBST(t1) == true);
    cout << "[PASS] [2,1,3] → valid BST\n";

    //   5
    //  / \
    // 1   4
    //    / \
    //   3   6
    TreeNode* t2 = new TreeNode(5);
    t2->left = new TreeNode(1);
    t2->right = new TreeNode(4);
    t2->right->left = new TreeNode(3);
    t2->right->right = new TreeNode(6);
    assert(sol.isValidBST(t2) == false);
    cout << "[PASS] [5,1,4,null,null,3,6] → invalid BST\n";

    cout << "\nAll tests passed!\n";
    return 0;
}
