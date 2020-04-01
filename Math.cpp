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
        for (int i = 1; 2 * i * (i + 1) < n; ++i)
            for (int j = i, v; v = 2 * i * j + i + j, v <= n; ++j)
                used[v] = false;
        for (int i = 1; i < sz(used); ++i)
            if (used[i]) ans.pb(2 * i + 1);
        return ans;
    }
};
