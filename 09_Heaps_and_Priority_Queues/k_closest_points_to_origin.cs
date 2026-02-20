using System.Collections.Generic;

public class Solution {
    public int[][] kClosest(int[][] points, int k) {
        // MaxHeap based on distance
        var maxHeap = new PriorityQueue<int[], int>();
        
        foreach (var point in points) {
            int dist = point[0] * point[0] + point[1] * point[1];
            maxHeap.Enqueue(point, -dist); // Negative for max heap
            
            if (maxHeap.Count > k) {
                maxHeap.Dequeue();
            }
        }
        
        int[][] result = new int[k][];
        for (int i = 0; i < k; i++) {
            result[i] = maxHeap.Dequeue();
        }
        
        return result;
    }
}
