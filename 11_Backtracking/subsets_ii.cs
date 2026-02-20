using System;
using System.Collections.Generic;

public class Solution {
    public IList<IList<int>> SubsetsWithDup(int[] nums) {
        Array.Sort(nums);
        var result = new List<IList<int>>();
        var subset = new List<int>();
        
        Backtrack(nums, 0, subset, result);
        
        return result;
    }
    
    private void Backtrack(int[] nums, int i, List<int> subset, IList<IList<int>> result) {
        if (i == nums.Length) {
            result.Add(new List<int>(subset));
            return;
        }
        
        // Include nums[i]
        subset.Add(nums[i]);
        Backtrack(nums, i + 1, subset, result);
        subset.RemoveAt(subset.Count - 1);
        
        // Exclude nums[i] and all subsequent duplicates
        while (i + 1 < nums.Length && nums[i] == nums[i + 1]) {
            i++;
        }
        
        Backtrack(nums, i + 1, subset, result);
    }
}
