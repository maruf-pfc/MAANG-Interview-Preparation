using System.Collections.Generic;
using System.Linq;
using System.Text;

public class Solution {
    public IList<IList<string>> GroupAnagrams(string[] strs) {
        var map = new Dictionary<string, IList<string>>();

        foreach (var s in strs) {
            var count = new int[26];
            foreach (char c in s) {
                count[c - 'a']++;
            }

            var keyBuilder = new StringBuilder();
            foreach (int n in count) {
                keyBuilder.Append(n).Append('#');
            }
            string key = keyBuilder.ToString();

            if (!map.ContainsKey(key)) {
                map[key] = new List<string>();
            }
            map[key].Add(s);
        }

        return map.Values.ToList();
    }
}
