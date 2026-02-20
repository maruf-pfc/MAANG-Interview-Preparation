/**
 * Problem: Word Search
 * LeetCode: #79
 * Difficulty: Medium
 * Pattern: Grid Backtracking (DFS with In-Place Visited Marking + Undo)
 *
 * Time Complexity:  O(m × n × 4^L) where L = word length
 * Space Complexity: O(L) — recursion stack depth
 */
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool exist(vector<vector<char>>& board, string word) {
        int rows = board.size(), cols = board[0].size();
        for (int r = 0; r < rows; r++)
            for (int c = 0; c < cols; c++)
                if (dfs(board, word, r, c, 0, rows, cols)) return true;
        return false;
    }
private:
    bool dfs(vector<vector<char>>& board, const string& word,
             int r, int c, int idx, int rows, int cols) {
        if (idx == (int)word.size()) return true; // matched all chars

        if (r < 0 || r >= rows || c < 0 || c >= cols) return false;
        if (board[r][c] != word[idx]) return false; // mismatch or visited ('#')

        char original = board[r][c];
        board[r][c] = '#'; // mark visited (in-place)

        bool found = dfs(board, word, r+1, c, idx+1, rows, cols)
                  || dfs(board, word, r-1, c, idx+1, rows, cols)
                  || dfs(board, word, r, c+1, idx+1, rows, cols)
                  || dfs(board, word, r, c-1, idx+1, rows, cols);

        board[r][c] = original; // restore (backtrack)
        return found;
    }
};

int main() {
    Solution sol;

    vector<vector<char>> b1 = {{'A','B','C','E'},{'S','F','C','S'},{'A','D','E','E'}};
    assert(sol.exist(b1, "ABCCED") == true);
    cout << "[PASS] \"ABCCED\" → true\n";

    vector<vector<char>> b2 = {{'A','B','C','E'},{'S','F','C','S'},{'A','D','E','E'}};
    assert(sol.exist(b2, "SEE") == true);
    cout << "[PASS] \"SEE\" → true\n";

    vector<vector<char>> b3 = {{'A','B','C','E'},{'S','F','C','S'},{'A','D','E','E'}};
    assert(sol.exist(b3, "ABCB") == false);
    cout << "[PASS] \"ABCB\" → false (can't reuse B)\n";

    vector<vector<char>> b4 = {{'a'}};
    assert(sol.exist(b4, "a") == true);
    cout << "[PASS] single cell match → true\n";

    cout << "\nAll tests passed!\n";
    return 0;
}
