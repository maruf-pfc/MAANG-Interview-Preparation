using System.Collections.Generic;

public class KthLargest {
    private PriorityQueue<int, int> minHeap;
    private int k;

    public KthLargest(int k, int[] nums) {
        this.k = k;
        minHeap = new PriorityQueue<int, int>();
        
        foreach (int num in nums) {
            Add(num);
        }
    }
    
    public int Add(int val) {
        minHeap.Enqueue(val, val);
        
        if (minHeap.Count > k) {
            minHeap.Dequeue();
        }
        
        return minHeap.Peek();
    }
}
