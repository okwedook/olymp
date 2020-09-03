template<int md, int maxpw = 23>
struct NTT {
    int mul(int a, int b) {
        return a * (ll)b % md;
    }
    int sum(int a, int b) {
        a += b;
        if (a >= md) a -= md;
        return a;
    }
    int diff(int a, int b) {
        a -= b;
        if (a < 0) a += md;
        return a;
    }
    int mpow(int a, int n) {
        int ans = 1;
        for (; n > 0; n >>= 1, a = mul(a, a))
            if (n & 1) ans = mul(ans, a);
        return ans;
    }
    int lst(int n) const { return 31 - __builtin_clz(n); }
    vector<int> sq;
    NTT() {
        int rt = 2;
        while (mpow(rt, 1 << maxpw) != 1 || mpow(rt, 1 << maxpw - 1) == 1) ++rt;
        sq = vector<int>(maxpw + 1);
        sq[maxpw] = rt;
        for (int i = maxpw - 1; i >= 0; --i)
            sq[i] = mul(sq[i + 1], sq[i + 1]);
    }
    vector<int> ind;
    void dft(vector<int> &a, int n) {
        int LOG = lst(n);
        if (sz(ind) != n) {
            ind.resize(n);
            for (int i = 1; i < n; ++i) {
                int l = lst(i);
                ind[i] = ind[i ^ (1 << l)] | (1 << LOG - 1 - l);
            }
        }
        vector<int> cp(n);
        for (int i = 0; i < n; ++i) cp[i] = a[ind[i]];
        swap(a, cp);
        for (int len = 2; len <= n; len *= 2) {
            int w = sq[lst(len)];
            int l2 = len >> 1, msk = l2 - 1;
            for (int i = 0; i < n; i += len) {
                int c = 1;
                for (int j = 0; j < l2; ++j) {
                    int x = a[i + j], y = mul(a[i + l2 + j], c);
                    a[i + j] = sum(x, y);
                    a[i + j + l2] = diff(x, y);
                    c = mul(c, w);
                }
            }
        }
    }
    vector<int> multiply(vector<int> &a, vector<int> &b) {
        int n = 1;
        while (n < sz(a) || n < sz(b)) n *= 2;
        n *= 2;
        a.resize(n);
        b.resize(n);
        dft(a, n);
        dft(b, n);
        vector<int> ans(n);
        for (int i = 0; i < n; ++i) ans[i] = mul(a[i], b[i]);
        dft(ans, n);
        reverse(ans.begin() + 1, ans.end());
        int inv = mpow(n, md - 2);
        for (auto &i : ans) i = mul(i, inv);
        return ans;
    }
};
