/**
 * Problem: Course Schedule
 * LeetCode: #207
 * Difficulty: Medium
 * Pattern: Cycle Detection in Directed Graph (DFS with 3 States)
 *
 * States: 0=unvisited, 1=visiting (in current path), 2=fully explored (safe)
 *
 * Time Complexity:  O(V + E)
 * Space Complexity: O(V + E)
 */
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        vector<vector<int>> adj(numCourses);
        for (auto& pre : prerequisites) adj[pre[0]].push_back(pre[1]);

        vector<int> state(numCourses, 0); // 0=unvisited, 1=visiting, 2=safe
        for (int c = 0; c < numCourses; c++)
            if (!dfs(c, adj, state)) return false;
        return true;
    }
private:
    bool dfs(int course, vector<vector<int>>& adj, vector<int>& state) {
        if (state[course] == 1) return false; // back edge → cycle!
        if (state[course] == 2) return true;  // already verified safe
        state[course] = 1;
        for (int prereq : adj[course])
            if (!dfs(prereq, adj, state)) return false;
        state[course] = 2;
        return true;
    }
};

int main() {
    Solution sol;
    vector<vector<int>> p1 = {{1,0}};
    assert(sol.canFinish(2, p1) == true);
    cout << "[PASS] 2 courses, [[1,0]] → true\n";

    vector<vector<int>> p2 = {{1,0},{0,1}};
    assert(sol.canFinish(2, p2) == false);
    cout << "[PASS] 2 courses, [[1,0],[0,1]] → false (cycle)\n";

    vector<vector<int>> p3 = {};
    assert(sol.canFinish(5, p3) == true);
    cout << "[PASS] 5 courses, no prerequisites → true\n";

    cout << "\nAll tests passed!\n";
    return 0;
}
