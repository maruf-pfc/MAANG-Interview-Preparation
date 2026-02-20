using System;
using System.Collections.Generic;

public class Solution {
    public IList<IList<int>> ThreeSum(int[] nums) {
        var result = new List<IList<int>>();
        Array.Sort(nums);
        
        for (int i = 0; i < nums.Length; i++) {
            if (i > 0 && nums[i] == nums[i - 1]) continue;
            
            int left = i + 1;
            int right = nums.Length - 1;
            
            while (left < right) {
                int sum = nums[i] + nums[left] + nums[right];
                
                if (sum > 0) {
                    right--;
                } else if (sum < 0) {
                    left++;
                } else {
                    result.Add(new List<int> { nums[i], nums[left], nums[right] });
                    left++;
                    while (left < right && nums[left] == nums[left - 1]) {
                        left++;
                    }
                }
            }
        }
        
        return result;
    }
}
