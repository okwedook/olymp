template<class F, class C> struct MCMF {
    struct Edge {
        int v, rev, ind;
        F flow, cap;
        C cost;
        Edge(int _v, int _rev, F _cap, C _cost, int _ind) :
            v(_v), rev(_rev), flow(0), cap(_cap), cost(_cost), ind(_ind) {};
        F left() const { return cap - flow; }
        bool sat() const { return cap == flow; }
        bool unsat() const { return cap != flow; }
        void addFlow(F x) { flow += x; }
    };
    int n;
    vector<vector<Edge>> G;
    MCMF(int _n) : n(_n) { G.resize(n); }
    void addEdge(int u, int v, F cap, C cost, int ind = -1) {
        int iu = sz(G[u]), iv = sz(G[v]);
        G[u].pb({v, iv, cap, cost, ind});
        G[v].pb({u, iu, 0, -cost, ind});
    }
    int s, t;
    vector<C> cost;
    vector<F> flow;
    vector<int> p;
    bool FordBellman() {
        cost.assign(n, numeric_limits<C>::max());
        flow.assign(n, 0);
        p.assign(n, -1);
        cost[s] = 0;
        flow[s] = numeric_limits<F>::max();
        auto cmp = [&](int i, int j) { return cost[i] > cost[j]; };
        priority_queue<int, vector<int>, decltype(cmp)> que(cmp);
        que.push(s);
        while (sz(que)) {
            auto f = que.top(); que.pop();
            for (auto &e : G[f]) {
                if (e.unsat() && chmin(cost[e.v], cost[f] + e.cost)) {
                    flow[e.v] = min(flow[f], e.left());
                    p[e.v] = e.rev;
                    que.push(e.v);
                }
            }
        }
        return flow[t] > 0;
    }
    void sendFlow(F d) {
        int v = t;
        while (v != s) {
            auto &rev = G[v][p[v]];
            rev.addFlow(-d);
            G[rev.v][rev.rev].addFlow(d);
            v = rev.v;
        }
    }
    pair<F, C> findFlow(int _s, int _t, F k = numeric_limits<F>::max()) {
        s = _s, t = _t;
        F ansf = 0;
        C ansc = 0;
        while (FordBellman() && k > 0) {
            F d = min(flow[t], k);
            ansf += d;
            ansc += cost[t] * d;
            k -= d;
            sendFlow(d);
        }
        return {ansf, ansc};
    }
        vector<bool> used;
    F findPath(int v, F mn, vector<int> &ans) {
        if (v == t) {
            ans.pb(t);
            return mn;
        }
        used[v] = true;
        for (auto &e : G[v]) {
            if (e.cap > 0 && e.flow > 0 && !used[e.v]) {
                F x = findPath(e.v, min(mn, e.flow), ans);
                if (x > 0) {
                    ans.pb(v);
                    e.addFlow(-x);
                    return x;
                }
            }
        }
        return -1;
    }
    pair<pair<F, C>, vector<pair<F, vector<int>>>> decompose(int _s, int _t, F k = numeric_limits<F>::max()) {
        auto x = findFlow(_s, _t, k);
        vector<pair<F, vector<int>>> ans;
        while (true) {
            used.assign(n, 0);
            ans.pb({0, vector<int>()});
            ans.back().f = findPath(s, numeric_limits<F>::max(), ans.back().s);
            if (sz(ans.back().s) == 0) {
                ans.popb();
                break;
            } else {
                reverse(ans.back().s);
            }
        }
        return {x, ans};
    }
};
