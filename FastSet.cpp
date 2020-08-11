struct FastSet {
    int n, C, mx, mn, cnt;
    vector<int> pos, val;
    vector<vector<int>> ind;
    FastSet(int _n, int _C) : n(_n), C(_C), mx(C - 1), mn(0), cnt(0) {
        pos.resize(n);
        val.resize(n, -1);
        ind.resize(C);
    }
    FastSet(const vector<int> &a) : n(sz(a)), C(*max_element(all(a)) + 1), mx(C - 1), mn(0), cnt(0) {
        pos.resize(n);
        val.resize(n, -1);
        ind.resize(C);
        for (int i = 0; i < n; ++i) upd(i, a[i]);
    }
    void replace(int i, int j) {
        int v = val[i];
        swap(ind[v][pos[i]], ind[v][pos[j]]);
        swap(pos[i], pos[j]);
    }
    void up(int i) {
        int lst = ind[val[i]].back();
        replace(i, lst);
    }
    void del(int i) {
        if (val[i] != -1) {
            up(i);
            ind[val[i]].popb();
            val[i] = -1;
            --cnt;
        }
    }
    void upd(int i, int v) {
        del(i);
        ind[v].pb(i);
        val[i] = v;
        pos[i] = sz(ind[v]) - 1;
        ++cnt;
        chmax(mx, v);     
        chmin(mn, v); 
    }
    int getmx() {
        while (sz(ind[mx]) == 0) --mx;
        return ind[mx].back();
    }
    int getmn() {
        while (sz(ind[mn]) == 0) ++mn;
        return ind[mn].back();
    }
    int size() const { return cnt; }
    bool empty() const { return cnt == 0; }
};
