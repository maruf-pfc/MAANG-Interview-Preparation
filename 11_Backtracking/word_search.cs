public class Solution {
    public bool Exist(char[][] board, string word) {
        int rows = board.Length;
        int cols = board[0].Length;
        
        for (int r = 0; r < rows; r++) {
            for (int c = 0; c < cols; c++) {
                if (Dfs(board, r, c, word, 0)) {
                    return true;
                }
            }
        }
        
        return false;
    }
    
    private bool Dfs(char[][] board, int r, int c, string word, int i) {
        if (i == word.Length) return true;
        
        if (r < 0 || c < 0 || r >= board.Length || c >= board[0].Length || board[r][c] != word[i]) {
            return false;
        }
        
        char temp = board[r][c];
        board[r][c] = '#'; // Mark as visited
        
        bool res = Dfs(board, r + 1, c, word, i + 1) ||
                   Dfs(board, r - 1, c, word, i + 1) ||
                   Dfs(board, r, c + 1, word, i + 1) ||
                   Dfs(board, r, c - 1, word, i + 1);
                   
        board[r][c] = temp; // Unmark
        
        return res;
    }
}
