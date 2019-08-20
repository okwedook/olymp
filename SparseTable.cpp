template<class T> struct sparse {
    static const int LOG = 18;
    static const int N = 2e5 + 10;
    int mx2[N];
    T v[LOG][N];
    sparse(vector<T> a) {
        for (int i = 2; i < N; ++i) mx2[i] = mx2[i >> 1] + 1;
        int n = sz(a);
        for (int i = 0; i < n; ++i) v[0][i] = a[i];
        for (int l = 1; l < LOG; ++l) 
            for (int i = 0; i + (1 << l) <= n; ++i)
                v[l][i] = min(v[l - 1][i], v[l - 1][i + (1 << l - 1)]);
    }
    T get(int l, int r) {
        int mx = mx2[r - l + 1];
        return min(v[mx][l], v[mx][r - (1 << mx) + 1]);
    }
};
