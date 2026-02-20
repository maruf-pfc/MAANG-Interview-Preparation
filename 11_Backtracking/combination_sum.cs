using System.Collections.Generic;

public class Solution {
    public IList<IList<int>> CombinationSum(int[] candidates, int target) {
        var result = new List<IList<int>>();
        var currentRoute = new List<int>();
        
        Backtrack(candidates, target, 0, currentRoute, result);
        
        return result;
    }
    
    private void Backtrack(int[] candidates, int target, int i, List<int> currentRoute, IList<IList<int>> result) {
        if (target == 0) {
            result.Add(new List<int>(currentRoute));
            return;
        }
        
        if (target < 0 || i >= candidates.Length) {
            return;
        }
        
        // Include candidates[i]
        currentRoute.Add(candidates[i]);
        Backtrack(candidates, target - candidates[i], i, currentRoute, result);
        
        // Exclude candidates[i]
        currentRoute.RemoveAt(currentRoute.Count - 1);
        Backtrack(candidates, target, i + 1, currentRoute, result);
    }
}
