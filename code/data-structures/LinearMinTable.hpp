#include "SparseIndexTable.hpp"

//works in linear time and memory online
template<class T>
struct mintable {
    typedef unsigned int mask;
    static const int B = 8 * sizeof(mask);
    static const int L = log2(B);
    vector<T> a;
    function<bool(T, T)> cmp;
    sparseind<T> sp;
    vector<int> ind;
    vector<int> masks;
    int minind(int l, int r) {
        return cmp(a[l], a[r]) ? l : r;
    }
    inline int last(mask m) { return B - __builtin_clz(m) - 1; }
    inline int first(mask m) { return __builtin_ctz(m); }
    mintable(const vector<T> &_a, function<bool(T, T)> _cmp = less<T>()) : a(_a), cmp(_cmp) {
        vector<T> v((sz(a) + B - 1) / B);
        ind.resize(sz(v));
        for (int i = 0; i < sz(v); ++i)
            ind[i] = i * B;
        for (int i = 0; i < sz(a); ++i)
            ind[i >> L] = minind(ind[i >> L], i);
        for (int i = 0; i < sz(v); ++i) v[i] = a[ind[i]];
        sp = sparseind<T>(v, cmp);
        masks.resize(sz(a));
        for (int i = 0; i < sz(v); ++i) {
            int from = i * B;
            mask que = 0;
            for (int j = from; j < from + B && j < sz(a); ++j) {
                while (que && cmp(a[j], a[last(que) + from]))
                    que ^= 1 << last(que);
                que ^= 1 << (j - from);
                masks[j] = que;
            }
        }
    }
    int getind(int i, int l, int r) {
        return first(masks[(i << L) + r] >> l) + (i << L) + l;
    }
    int getind(int l, int r) {
        int il = l >> L, ir = r >> L;
        if (il == ir)
            return getind(il, l & (B - 1), r & (B - 1));
        int ans = minind(getind(il, l & (B - 1), B - 1),
                            getind(ir, 0, r & (B - 1)));
        if (ir > il + 1)
            ans = minind(ans, ind[sp.getind(il + 1, ir - 1)]);
        return ans;
    }
    T getval(int l, int r) {
        return a[getind(l, r)];
    }
};
