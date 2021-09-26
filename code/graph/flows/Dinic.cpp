// Author: Mikhail Pogodin (okwedook)
//
// Implementation of simple, yet fast, Dinic algorithm
// Works in O(N^2M), O(Msqrt(N)) for graphs with binary capacity
// TODO: add optional binary lifting in template
//
// Check tasks: https://codeforces.com/contest/1198/problem/E, https://official.contest.yandex.ru/contest/18261/problems/E/

template<class F>
struct Dinic {
    int n;
    vector<int> layer;
    struct Edge {
        int v;
        int rev; // index of the reverse edge
        F cap, flow;
        Edge(int _v, int _rev, F _cap, F _flow) :
            v(_v), rev(_rev), cap(_cap), flow(_flow) {}
        inline bool sat() const { return flow >= cap; }
        inline bool unsat() const { return flow < cap; }
        inline F left() const { return cap - flow; }
        inline void addFlow(F df) { flow += df; }
    };
    Dinic(int _n) : n(_n) {
        layer.resize(n);
        ptr.resize(n);
        G.resize(n);
    }
    vector<vector<Edge>> G;
    // Adds edge u -> v with capacity cap
    void addEdge(int u, int v, F cap) {
        int pu = sz(G[u]), pv = sz(G[v]);
        G[u].pb({v, pv, cap, 0});
        G[v].pb({u, pu, 0, 0});
    }
    int s, t;
    // Builds layers for bfs tree
    bool buildBfsTree() {
        fill(all(layer), -1);
        static vector<int> que;
        que.clear();
        que.pb(s);
        layer[s] = 0;
        for (int i = 0; i < sz(que); ++i) {
            int v = que[i];
            for (const auto &e : G[v])
                if (e.unsat() && layer[e.v] == -1) {
                    layer[e.v] = layer[v] + 1;
                    que.pb(e.v);
                }
        }
        return layer[t] != -1;
    }
    vector<int> ptr;
    // Tries to find new flow with iterating over pointers
    F sendFlow(int v, F f) {
        if (v == t) {
            return f;
        }
        for (; ptr[v] < sz(G[v]); ++ptr[v]) {
            auto &e = G[v][ptr[v]];
            if (e.unsat() && layer[e.v] == layer[v] + 1) {
                if (F df = sendFlow(e.v, min(f, e.left()))) {
                    e.addFlow(df);
                    G[e.v][e.rev].addFlow(-df);
                    return df;
                }
            }
        }
        return 0;
    }
    // Returns the value of the maximal flow
    F findFlow(int _s, int _t, F limit = numeric_limits<F>::max()) {
        s = _s;
        t = _t;
        F ans = 0;
        while (buildBfsTree()) {
            fill(all(ptr), 0);
            while (F df = sendFlow(s, limit)) {
                ans += df;
                limit -= df;
            }
        }
        return ans;
    }
    vector<bool> used;
    // Tries to create a path from s to t with positive flow
    F findPath(int v, F f, vector<int> &ans) {
        if (v == t) {
            ans.pb(v); // Returns vertex path
            return f;
        }
        used[v] = true;
        for (auto &e : G[v])
            if (!used[e.v] && e.flow > 0) {
                F df = findPath(e.v, min(f, e.flow), ans);
                e.addFlow(-df);
                ans.pb(v);
                return df;
            }
        return 0;
    }
    // Returns the decomposition of the flow
    // Use only after findFlow
    vector<pair<F, vector<int>>> decompose() {
        vector<pair<F, vector<int>>> ans;
        used.resize(n);
        while (true) {
            fill(all(used), false);
            ans.pb({0, {}});
            ans.back().f = findPath(s, numeric_limits<F>::max(), ans.back().s);
            if (sz(ans.back().s) == 0) {
                ans.popb();
                break;
            } else {
                reverse(ans.back().s);
            }
        }
        return ans;
    }
};
