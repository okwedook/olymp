// Author: Mikhail Pogodin (okwedook)
//
// Fenwick tree implementation
// Uses linear space and O(logn) time per operation.
//
// Check tasks: https://codeforces.com/gym/100246/problem/A

template<class T>
struct Fenwick {
    vector<T> sum;
    Fenwick() {}
    Fenwick(int n) { sum.resize(n); }
    // Initializes Fenwick tree by given values in linear time
    template<class U>
    Fenwick(const U &a) {
        sum.assign(all(a));
        build();
    }
    // Makes values into fenwick values
    void build() {
        for (int r = 0; r < sz(sum); ++r)
            if ((r | r + 1) < sz(sum))
                sum[r | r + 1] += sum[r];
    }
    // Adds x to position r
    void add(int r, T x) {
        for (; r < sz(sum); r |= r + 1)
            sum[r] += x;
    }
    // Sum at [0, r]
    T get(int r) {
        T ans = 0;
        for (; r >= 0; r = (r & r + 1) - 1)
            ans += sum[r];
        return ans;
    }
    // Sum at [l, r]
    T get(int l, int r) {
        return get(r) - get(l - 1);
    }
    // First index, which sum at [0, ans] is at least x
    int lb(T x) {
        int ans = -1;
        ll now = 0;
        for (int l = 31 - __builtin_clz(sz(sum)); l >= 0; --l) {
            int next = ans + (1 << l);
            if (next < sz(sum) && now + sum[next] < x) {
                ans = next;
                now += sum[next];
            }
        }
        return ans + 1;
    }
};
