template<class T> 
struct sparseind {
    vector<T> a;
    vector<vector<int>> ind;
    function<bool(T, T)> cmp;
    int minind(int l, int r) {
        return cmp(a[l], a[r]) ? l : r;
    }
    sparseind() {}
    sparseind(const vector<T> &_a, function<bool(T, T)> _cmp = less<T>()) : a(_a), cmp(_cmp) {
        int log = log2(sz(a));
        ind.resize(log + 1);
        ind[0].resize(sz(a));
        iota(all(ind[0]), 0);
        for (int l = 1; l <= log; ++l) {
            int was = 1 << (l - 1);
            int len = 1 << l;
            ind[l].resize(sz(a) - len + 1);
            for (int i = 0; i + len <= sz(a); ++i) {
                dbg(l, i);
                ind[l][i] = minind(ind[l - 1][i], ind[l - 1][i + was]);
            }
        }
    }
    int getind(int l, int r) {
        ++r;
        int len = 31 - __builtin_clz(r - l);
        return minind(ind[len][l], ind[len][r - (1 << len)]);
    }
    T getval(int l, int r) {
        return a[getind(l, r)];
    }
};
