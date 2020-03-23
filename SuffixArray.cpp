template<class T>
vector<int> suffixarray(T s) {
    vector<int> val(all(s));
    auto x = val;
    sort(x);
    x.resize(unique(all(x)) - x.begin());
    for (auto &i : val)
        i = lower_bound(all(x), i) - x.begin();
    val.pb(-1);
    vector<int> p(sz(val));
    for (int i = 0; i < sz(p); ++i) p[i] = i + 1;
    p[sz(p) - 1] = sz(p) - 1;
    int lg = 0;
    vector<int> ans(sz(s));
    for (int i = 0; i < sz(ans); ++i) ans[i] = i;
    sort(all(ans), [&](int i, int j) {
        return val[i] < val[j];
    });
    while ((1 << lg) < sz(val)) {
        ++lg;
        int past = 0;
        for (int i = 0; i < sz(ans); ++i)
            if (val[ans[i]] != val[ans[past]]) {
                sort(ans.begin() + past, ans.begin() + i, [&](int i, int j) {
                    return pii(val[i], val[p[i]]) < pii(val[j], val[p[j]]);
                });
                past = i;
            }
        sort(ans.begin() + past, ans.end(), [&](int i, int j) {
            return pii(val[i], val[p[i]]) < pii(val[j], val[p[j]]);
        });
        vector<pii> coord;
        for (auto i : ans) coord.pb({val[i], val[p[i]]});
        coord.resize(unique(all(coord)) - coord.begin());
        int ptr = 0;
        vector<int> newval(sz(ans));
        newval.pb(-1);
        for (auto i : ans) {
            while (coord[ptr] < pii(val[i], val[p[i]])) ++ptr;
            newval[i] = ptr;
        }
        val = newval;
        for (int i = 0; i < sz(p); ++i)
            p[i] = p[p[i]];
    }
    return ans;
}
