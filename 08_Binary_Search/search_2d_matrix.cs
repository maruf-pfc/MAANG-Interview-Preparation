public class Solution {
    public bool SearchMatrix(int[][] matrix, int target) {
        if (matrix == null || matrix.Length == 0 || matrix[0].Length == 0) {
            return false;
        }
        
        int rows = matrix.Length;
        int cols = matrix[0].Length;
        
        int top = 0;
        int bottom = rows - 1;
        while (top <= bottom) {
            int row = top + (bottom - top) / 2;
            if (target > matrix[row][cols - 1]) {
                top = row + 1;
            } else if (target < matrix[row][0]) {
                bottom = row - 1;
            } else {
                break;
            }
        }
        
        if (top > bottom) {
            return false;
        }
        
        int targetRow = top + (bottom - top) / 2;
        int left = 0;
        int right = cols - 1;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (target == matrix[targetRow][mid]) {
                return true;
            } else if (target > matrix[targetRow][mid]) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        
        return false;
    }
}
