struct SCC {
    graph G, rev;
    SCC(int n) { G.resize(n); rev.resize(n); }
    SCC(const graph &_G) : G(_G) {
        rev.resize(sz(G));
        for (int i = 0; i < sz(G); ++i)
            for (auto v : G[i])
                rev[v].pb(i);
    }
    // Edge from u to v
    void addEdge(int u, int v) {
        G[u].pb(v);
        rev[v].pb(u);
    }
    vector<int> order;
    vector<int> color;
    vector<bool> used;
    vector<vector<int>> comp;

    void dfsOrder(int v) {
        if (used[v]) return;
        used[v] = true;
        for (auto i : G[v])
            dfsOrder(i);
        order.pb(v);
    }
    void dfsMark(int v, int c) {
        if (color[v] != -1) return;
        color[v] = c;
        for (auto i : rev[v])
            dfsMark(i, c);
    }
    void dfsComp(int v, int c) {
        if (used[v]) return;
        used[v] = true;
        comp[c].pb(v);
        for (auto i : rev[v])
            dfsComp(i, c);
    }
    void getOrder() {
        used.assign(sz(G), false);
        order.clear();
        for (int i = 0; i < sz(G); ++i)
            dfsOrder(i);
        reverse(order);
    }
    void buildColors() {
        getOrder();
        color.assign(sz(G), -1);
        int ptr = 0;
        for (auto i : order)
            if (color[i] == -1)
                dfsMark(i, ptr++);
    }
    void buildComp() {
        getOrder();
        used.assign(sz(G), false);
        for (auto i : order)
            if (!used[i]) {
                comp.pb(vector<int>());
                dfsComp(i, sz(comp) - 1);
            }
    }
    graph condens;
    void buildCondensation(bool uni = false, bool self = false) {
        buildColors();
        condens.clear();
        condens.resize(*max_element(all(color)) + 1);
        for (int i = 0; i < sz(G); ++i)
            for (auto v : G[i]) {
                if (color[i] != color[v] || self)
                    condens[color[i]].pb(color[v]);
            }
        if (uni) {
            for (auto &i : condens) {
                sort(i);
                i.resize(unique(all(i)) - i.begin());
            }
        }
    }
};
