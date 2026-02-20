using System.Collections.Generic;

public class Solution {
    public int LastStoneWeight(int[] stones) {
        // MaxHeap implementation using PriorityQueue in C# 10+ (using negative priorities)
        var maxHeap = new PriorityQueue<int, int>();
        
        foreach (int stone in stones) {
            maxHeap.Enqueue(stone, -stone);
        }
        
        while (maxHeap.Count > 1) {
            int y = maxHeap.Dequeue();
            int x = maxHeap.Dequeue();
            
            if (x != y) {
                maxHeap.Enqueue(y - x, -(y - x));
            }
        }
        
        return maxHeap.Count == 0 ? 0 : maxHeap.Dequeue();
    }
}
