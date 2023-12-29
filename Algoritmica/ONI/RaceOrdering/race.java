import java.util.*;
 
public class RaceOrdering {
    final static long MOD = 1000003;
    long[][] c;
    int[] first;
    int[] second;
    boolean[] mark;
    List<Integer> cur;
    long res;
    long cres;
    int rem;
 
    public int countOrders(int n, int[] first, int[] second) {
        c = new long[n + 1][n + 1];
        c[0][0] = 1;
        for (int i = 1; i <= n; ++i) {
            c[i][0] = 1;
            for (int j = 1; j <= n; ++j)
                c[i][j] = (c[i - 1][j - 1] + c[i - 1][j]) % MOD;
        }
        mark = new boolean[n];
        this.first = first;
        this.second = second;
        res = 1;
        rem = n;
        for (int i = 0; i < n; ++i)
            if (!mark[i]) {
                cur = new ArrayList<Integer>();
                dfs(i);
                process();
                res = ((res * cres) % MOD * c[rem][cur.size()]) % MOD;
                rem -= cur.size();
            }
        return (int) res;
    }
 
    private void process() {
        int n = cur.size();
        int[] before = new int[n];
        for (int i = 0; i < first.length; ++i)
            if (cur.indexOf(second[i]) >= 0) {
                int a = cur.indexOf(first[i]);
                int b = cur.indexOf(second[i]);
                before[b] |= (1 << a);
            }
        int[] am = new int[1 << n];
        am[0] = 1;
        for (int i = 1; i < (1 << n); ++i) {
            for (int j = 0; j < n; ++j)
                if (((i >> j) & 1) != 0 && ((i & before[j]) == before[j])) {
                    am[i] += am[i ^ (1 << j)];
                    if (am[i] >= MOD)
                        am[i] -= MOD;
                }
        }
        cres = am[(1 << n) - 1];
    }
 
    private void dfs(int at) {
        if (mark[at])
            return;
        mark[at] = true;
        cur.add(at);
        for (int i = 0; i < first.length; ++i)
            if (first[i] == at)
                dfs(second[i]);
            else if (second[i] == at)
                dfs(first[i]);
    }
 
}
 
