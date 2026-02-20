/**
 * Problem: Number of Islands
 * LeetCode: #200
 * Difficulty: Medium
 * Pattern: DFS Flood Fill (Connected Components)
 *
 * Time Complexity:  O(m × n)
 * Space Complexity: O(m × n) — recursion stack in worst case
 */
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int numIslands(vector<vector<char>>& grid) {
        if (grid.empty()) return 0;
        int rows = grid.size(), cols = grid[0].size(), islands = 0;
        for (int r = 0; r < rows; r++)
            for (int c = 0; c < cols; c++)
                if (grid[r][c] == '1') { dfs(grid, r, c, rows, cols); islands++; }
        return islands;
    }
private:
    void dfs(vector<vector<char>>& grid, int r, int c, int rows, int cols) {
        if (r < 0 || r >= rows || c < 0 || c >= cols || grid[r][c] != '1') return;
        grid[r][c] = '0'; // mark visited
        dfs(grid, r+1,c,rows,cols); dfs(grid, r-1,c,rows,cols);
        dfs(grid, r,c+1,rows,cols); dfs(grid, r,c-1,rows,cols);
    }
};

int main() {
    Solution sol;
    vector<vector<char>> g1 = {{'1','1','1','1','0'},{'1','1','0','1','0'},
                                {'1','1','0','0','0'},{'0','0','0','0','0'}};
    assert(sol.numIslands(g1) == 1);
    cout << "[PASS] Grid 1 → 1 island\n";

    vector<vector<char>> g2 = {{'1','1','0','0','0'},{'1','1','0','0','0'},
                                {'0','0','1','0','0'},{'0','0','0','1','1'}};
    assert(sol.numIslands(g2) == 3);
    cout << "[PASS] Grid 2 → 3 islands\n";

    cout << "\nAll tests passed!\n";
    return 0;
}
