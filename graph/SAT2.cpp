struct SAT2 {
    int n;
    SCC scc;
    SAT2(int _n) : n(_n), scc(2 * n) {}
    inline int conv(pair<int, bool> v) {
        return v.f + v.s * n;
    }
    inline int neg(int v) {
        return v < n ? v + n : v - n;
    } 
    // second parameter is 1 if !v
    void addEdge(pair<int, bool> u, pair<int, bool> v) {
        scc.addEdge(conv({u.f, !u.s}), conv(v));
        scc.addEdge(conv({v.f, !v.s}), conv(u));
    }
    // returns empty if no solution
    pair<bool, vector<bool>> solve() {
        scc.buildColors();
        //return {false, vector<bool>()};
        for (int i = 0; i < n; ++i)
            if (scc.color[i] == scc.color[i + n])
                return {false, vector<bool>()};
        scc.buildComp();
        dbg(scc.comp);
        vector<bool> ans(2 * n);
        for (auto i : scc.comp) {
            if (ans[i[0]] == 1) continue;
            for (auto j : scc.comp[scc.color[neg(i[0])]])
                ans[j] = 1;
        }
        ans.resize(n);
        return {true, ans};
    }
};
