namespace math {
    bool isprime(int x) {
        for (int i = 2; i * i <= x; ++i)
            if (x % i == 0) return false;
        return x >= 2;
    }
    vector<int> genprimes(int n) {
        vector<int> ans;
        if (n >= 2) ans.pb(2);
        n = (n - 1) / 2;
        vector<bool> used(n + 1, 1);
        for (int i = 1; 2 * i * (i + 1) <= n; ++i)
            for (int j = i, v; v = 2 * i * j + i + j, v <= n; ++j)
                used[v] = false;
        for (int i = 1; i < sz(used); ++i)
            if (used[i]) ans.pb(2 * i + 1);
        return ans;
    }
    vector<int> mindiv(int n) {
        vector<int> ans(n + 1);
        for (int i = 2; i * i <= n; ++i)
            if (ans[i] == 0)
                for (int j = i * i; j <= n; j += i)
                    if (ans[j] == 0) ans[j] = i;
        for (int i = 1; i <= n; ++i)
            if (ans[i] == 0) ans[i] = i;
        return ans;
    }
    vector<int> dec(int x) {
        static const int MXNUMS = 1000000;
        static auto mn = mindiv(MXNUMS);
        vector<int> ans;
        while (x > 1) {
            ans.pb(mn[x]);
            x /= mn[x];
        }
        return ans;
    }
    vector<int> decbig(int x) {
        static const int MXNUMS = 2000000000;
        static auto pr = genprimes(int(sqrt(MXNUMS)) + 10);
        vector<int> ans;
        for (auto i : pr) {
            while (x % i == 0) {
                ans.pb(i);
                x /= i;
            }
        }
        if (x > 1) ans.pb(x);
        return ans;
    }
};
