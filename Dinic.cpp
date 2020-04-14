template<class F> struct Dinic {
	struct Edge { 
		int v, rev;
		F flow;
		Edge() {}
		Edge(int _v, F _cap, F _flow, int _rev) : 
			v(_v), flow(_flow - _cap), rev(_rev) {}
		inline bool sat() const { return flow >= 0; }
		inline bool unsat() const { return flow < 0; }
		inline F left() const { return -flow; }
		inline void addFlow(F x) { flow += x; }
	};
	vector<vector<Edge>> G;
	vector<int> layer, ptr;
	int n, s, t;
	Dinic(int _n) : n(_n) {
		G.resize(n);
		layer.resize(n);
	}
	void addEdge(int u, int v, F c) {
		int pu = sz(G[u]), pv = sz(G[v]);
		G[u].pb({v, c, 0, pv});
		G[v].pb({u, 0, 0, pu});
	}
	bool buildBfsTree() {
		for (int i = 0; i < n; ++i)
			layer[i] = -1;
		queue<int> que({s});
		layer[s] = 0;
		while (sz(que)) {
			auto f = que.front();
			que.pop();
			if (f == t) break;
			for (auto i : G[f])
				if (layer[i.v] == -1 && i.unsat()) {
					layer[i.v] = layer[f] + 1;
					que.push(i.v);
				}
		}
		return layer[t] >= 0;
	}
	F sendFlow(int v, F f) {
		if (v == t) return f;
		for (; ptr[v] < sz(G[v]); ++ptr[v]) {
			Edge& e = G[v][ptr[v]];
			if (layer[e.v] != layer[v] + 1 || e.sat()) continue;
			auto d = sendFlow(e.v, min(f, e.left()));
			if (d > 0) {
				e.addFlow(d);
				G[e.v][e.rev].addFlow(-d);
				return d;
			}
		}
		return 0;
	}
	F findFlow(int _s, int _t) {
		s = _s, t = _t;
		F ans = 0;
		while (buildBfsTree()) {
			ptr.assign(n, 0);
			while (F df = sendFlow(s, numeric_limits<F>::max()))
				ans += df;
		}
		return ans;
	}
};
