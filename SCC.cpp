struct SCC {
    graph G, rev;
    SCC(int n) : G(graph(n)), rev(graph(n)) {}
    SCC(const graph &_G) : G(_G) {
        rev.resize(sz(G));
        for (int v = 0; v < sz(G); ++v)
            for (auto u : G[v])
                rev[u].pb(v);
    }
    void addEdge(int from, int to) {
        println(from, ' ', to);
        G[from].pb(to);
        rev[to].pb(from);
    }
    vector<int> order;
    vector<bool> used;
    void getorder(int v) {
        if (used[v]) return;
        used[v] = true;
        for (auto i : G[v])
            getorder(i);
        order.pb(v);
    }
    vector<int> color, cnt;
    int ptr = 0;
    void mark(int v) {
        if (used[v]) return;
        used[v] = true;
        color[v] = ptr;
        ++cnt[ptr];
        for (auto i : rev[v])
            mark(i);
    }
    pair<vector<int>, vector<int>> build() {
        used = vector<bool>(sz(G));
        order.clear();
        for (int i = 0; i < sz(G); ++i)
            getorder(i);
        reverse(order);
        dbg(order);
        used = vector<bool>(sz(G));
        color = vector<int>(sz(G));
        for (auto i : order)
            if (!used[i]) {
                cnt.pb(0);
                mark(i);
                ++ptr;
            }
        return {color, cnt};
    }
};
