template<class T, const T& (*cmp)(const T&, const T&) = min>
struct sparse {
    int N, LOG;
    vector<int> mx;
    vector<vector<T>> val;
    //array a must not be empty
    sparse(const vector<T> &a) {
        N = sz(a), LOG = log2(N) + 1;
        mx = vector<int>(N + 1);
        for (int i = 2; i < sz(mx); ++i) mx[i] = mx[i >> 1] + 1;
        val = vector<vector<T>>(LOG, vector<T>(N));
        for (int i = 0; i < N; ++i) val[0][i] = a[i];
        for (int l = 1; l < LOG; ++l)
            for (int i = 0, next = 1 << (l - 1); next < N; ++i, ++next)
                val[l][i] = cmp(val[l - 1][i], val[l - 1][next]);
    }
    //[l, r] range query
    T get(int l, int r) {
        ++r;
        int len = mx[r - l];
        return cmp(val[len][l], val[len][r - (1 << len)]);
    }
};
