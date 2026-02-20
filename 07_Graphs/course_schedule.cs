using System.Collections.Generic;

public class Solution {
    public bool CanFinish(int numCourses, int[][] prerequisites) {
        var preMap = new Dictionary<int, List<int>>();
        for (int i = 0; i < numCourses; i++) {
            preMap[i] = new List<int>();
        }
        foreach (var pre in prerequisites) {
            preMap[pre[0]].Add(pre[1]);
        }
        
        var visitedSet = new HashSet<int>();
        
        for (int c = 0; c < numCourses; c++) {
            if (!Dfs(c, preMap, visitedSet)) {
                return false;
            }
        }
        
        return true;
    }
    
    private bool Dfs(int crs, Dictionary<int, List<int>> preMap, HashSet<int> visited) {
        if (visited.Contains(crs)) return false;
        if (preMap[crs].Count == 0) return true;
        
        visited.Add(crs);
        
        foreach (int pre in preMap[crs]) {
            if (!Dfs(pre, preMap, visited)) {
                return false;
            }
        }
        
        visited.Remove(crs);
        preMap[crs].Clear();
        
        return true;
    }
}
