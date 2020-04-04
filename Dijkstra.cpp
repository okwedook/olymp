typedef ll F;
vector<F> dijkstra(vector<vector<pii>> &G, int v) {
    vector<F> ans(sz(G), inf);
    ans[v] = 0;
    auto cmp = [&](int i, int j) { return ans[i] > ans[j]; };
    priority_queue<int, vector<int>, decltype(cmp)> que(cmp);
    que.push(v);
    vector<bool> used(sz(G));
    while (!que.empty()) {
        auto f = que.top();
        que.pop();
        if (used[f]) continue;
        used[f] = true;
        for (auto i : G[f])
            if (ifmin(ans[i.f], ans[f] + i.s))
                que.push(i.f);
    }
    return ans;
}
