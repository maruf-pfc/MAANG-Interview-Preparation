using System.Collections.Generic;

public class Solution {
    public int NumIslands(char[][] grid) {
        if (grid == null || grid.Length == 0) {
            return 0;
        }
        
        int numIslands = 0;
        int rows = grid.Length;
        int cols = grid[0].Length;
        
        for (int r = 0; r < rows; r++) {
            for (int c = 0; c < cols; c++) {
                if (grid[r][c] == '1') {
                    numIslands++;
                    Dfs(grid, r, c);
                }
            }
        }
        
        return numIslands;
    }
    
    private void Dfs(char[][] grid, int r, int c) {
        int rows = grid.Length;
        int cols = grid[0].Length;
        
        if (r < 0 || c < 0 || r >= rows || c >= cols || grid[r][c] == '0') {
            return;
        }
        
        grid[r][c] = '0'; // mark as visited
        
        Dfs(grid, r - 1, c); // up
        Dfs(grid, r + 1, c); // down
        Dfs(grid, r, c - 1); // left
        Dfs(grid, r, c + 1); // right
    }
}
