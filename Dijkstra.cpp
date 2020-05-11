vector<ll> dijkstra(vector<vector<pii>> &G, int v) {
    vector<ll> ans(sz(G), inf);
    ans[v] = 0;
    auto cmp = [&](int i, int j) { return ans[i] > ans[j]; };
    priority_queue<int, vector<int>, decltype(cmp)> que(cmp);
    que.push(v);
    while (!que.empty()) {
        auto f = que.top();
        que.pop();
        for (auto i : G[f])
            if (chmin(ans[i.f], ans[f] + i.s))
                que.push(i.f);
    }
    return ans;
}
