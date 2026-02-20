using System.Collections.Generic;

public class MedianFinder {
    private PriorityQueue<int, int> maxHeap; // Lower half
    private PriorityQueue<int, int> minHeap; // Upper half

    public MedianFinder() {
        maxHeap = new PriorityQueue<int, int>();
        minHeap = new PriorityQueue<int, int>();
    }
    
    public void AddNum(int num) {
        maxHeap.Enqueue(num, -num); // Add to lower half first
        
        // Ensure max in lower half <= min in upper half
        if (maxHeap.Count > 0 && minHeap.Count > 0 && maxHeap.Peek() > minHeap.Peek()) {
            int val = maxHeap.Dequeue();
            minHeap.Enqueue(val, val);
        }
        
        // Balance sizes
        if (maxHeap.Count > minHeap.Count + 1) {
            int val = maxHeap.Dequeue();
            minHeap.Enqueue(val, val);
        } else if (minHeap.Count > maxHeap.Count) {
            int val = minHeap.Dequeue();
            maxHeap.Enqueue(val, -val);
        }
    }
    
    public double FindMedian() {
        if (maxHeap.Count > minHeap.Count) {
            return maxHeap.Peek();
        }
        return (maxHeap.Peek() + minHeap.Peek()) / 2.0;
    }
}
