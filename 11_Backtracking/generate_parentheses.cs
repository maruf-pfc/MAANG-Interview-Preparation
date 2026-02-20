using System.Collections.Generic;

public class Solution {
    public IList<string> GenerateParenthesis(int n) {
        var result = new List<string>();
        Backtrack(0, 0, n, "", result);
        return result;
    }
    
    private void Backtrack(int openN, int closedN, int n, string current, IList<string> result) {
        if (current.Length == n * 2) {
            result.Add(current);
            return;
        }
        
        if (openN < n) {
            Backtrack(openN + 1, closedN, n, current + "(", result);
        }
        
        if (closedN < openN) {
            Backtrack(openN, closedN + 1, n, current + ")", result);
        }
    }
}
