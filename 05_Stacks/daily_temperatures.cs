using System.Collections.Generic;

public class Solution {
    public int[] DailyTemperatures(int[] temperatures) {
        int n = temperatures.Length;
        int[] result = new int[n];
        var stack = new Stack<int>(); // stores indices
        
        for (int i = 0; i < n; i++) {
            while (stack.Count > 0 && temperatures[i] > temperatures[stack.Peek()]) {
                int prevDay = stack.Pop();
                result[prevDay] = i - prevDay;
            }
            stack.Push(i);
        }
        
        return result;
    }
}
