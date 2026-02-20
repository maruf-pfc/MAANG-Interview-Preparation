using System.Collections.Generic;

public class Solution {
    public bool IsValid(string s) {
        var stack = new Stack<char>();
        var map = new Dictionary<char, char> {
            {')', '('},
            {'}', '{'},
            {']', '['}
        };
        
        foreach (char c in s) {
            if (map.ContainsKey(c)) {
                if (stack.Count == 0 || stack.Peek() != map[c]) {
                    return false;
                }
                stack.Pop();
            } else {
                stack.Push(c);
            }
        }
        
        return stack.Count == 0;
    }
}
