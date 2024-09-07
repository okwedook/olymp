struct DSUWithUnrolls {
    vector<int> p;
    vector<int> r;
    int comp;
    DSUWithUnrolls(int n) : p(n), r(n, 1), comp(n) {
        iota(all(p), 0);
    }
    vector<pii> queries;
    int getp(int v) {
        return v == p[v] ? v : getp(p[v]);
    }
    bool unite(int u, int v) {
        u = getp(u);
        v = getp(v);
        if (u == v) return false;
        if (r[u] > r[v]) {
            swap(u, v);
        }
        p[u] = v;
        r[v] += r[u];
        --comp;
        queries.pb({u, v});
        return true;
    }
    void unroll() {
        auto [u, v] = queries.back();
        queries.popb();
        r[v] -= r[u];
        p[u] = u;
        ++comp;
    }
};

struct DCPOffline {
    int ts = 0;
    map<pii, int> edges;
    DSUWithUnrolls dsu;
    DCPOffline(int n) : dsu(n) {}
    void addEdge(int u, int v) {
        if (u > v) swap(u, v);
        edges[{u, v}] = ++ts;
    }
    vector<pair<pii, pii>> segm;
    void delEdge(int u, int v) {
        if (u > v) swap(u, v);
        pii edge = {u, v};
        auto it = edges.find(edge);
        segm.pb({{it->s, ++ts}, edge});
        edges.erase(it);
    }
    vector<int> queries;
    vector<int> answers;
    int pq;
    void makeQuery() {
        queries.pb(ts);
    }
    void recAnswer(int tl, int tr, vector<pair<pii, pii>> segments) {
        int tm = (tl + tr) / 2;
        vector<pair<pii, pii>> lft, rgt;
        int cnt = 0;
        for (auto [lr, uv] : segments) {
            auto [l, r] = lr;
            if (r < tl || l >= tr) continue;
            if (l <= tl && r >= tr) {
                cnt += dsu.unite(uv.f, uv.s);
                continue;
            }
            if (l < tm) lft.pb({lr, uv});
            if (r > tm) rgt.pb({lr, uv});
        }
        if (tl + 1 == tr) {
            while (pq < sz(queries) && queries[pq] == tl) {
                answers.pb(dsu.comp);
                ++pq;
            }
        } else {
            recAnswer(tl, tm, lft);
            recAnswer(tm, tr, rgt);
        }
        while (cnt--) dsu.unroll();
    }
    void answerQueries() {
        for (auto [uv, t] : edges) {
            segm.pb({{t, ts + 1}, uv});
        }
        pq = 0;
        recAnswer(0, ts + 1, segm);
    }
};
