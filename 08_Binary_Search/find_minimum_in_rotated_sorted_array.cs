using System;

public class Solution {
    public int FindMin(int[] nums) {
        int left = 0;
        int right = nums.Length - 1;
        int res = nums[0];
        
        while (left <= right) {
            if (nums[left] < nums[right]) {
                res = Math.Min(res, nums[left]);
                break;
            }
            
            int mid = left + (right - left) / 2;
            res = Math.Min(res, nums[mid]);
            
            if (nums[mid] >= nums[left]) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        
        return res;
    }
}
