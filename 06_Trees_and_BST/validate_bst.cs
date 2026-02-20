using System;

public class TreeNode {
    public int val;
    public TreeNode left;
    public TreeNode right;
    public TreeNode(int val=0, TreeNode left=null, TreeNode right=null) {
        this.val = val;
        this.left = left;
        this.right = right;
    }
}

public class Solution {
    public bool IsValidBST(TreeNode root) {
        return Validate(root, null, null);
    }
    
    private bool Validate(TreeNode node, int? min, int? max) {
        if (node == null) return true;
        
        if (min.HasValue && node.val <= min.Value) return false;
        if (max.HasValue && node.val >= max.Value) return false;
        
        return Validate(node.left, min, node.val) && Validate(node.right, node.val, max);
    }
}
