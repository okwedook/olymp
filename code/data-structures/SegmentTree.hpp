struct node {
    int val = 0, ind = 0;
    int p = 0;
    node() {}
    void upd(int x) {
        val += x;
        p += x;
    }
    void upd(const node &t) {
        upd(t.p);
    }
    bool updated() const {
        return p != 0;
    }
    void unupdate() {
        p = 0;
    }
};

node merge(const node &a, const node &b) {
    node ans;
    if (a.val >= b.val) ans.val = a.val, ans.ind = a.ind;
    else ans.val = b.val, ans.ind = b.ind;
    return ans;
}

template<class node, node (*merge)(const node&, const node&) = merge>
struct Tree {
    int n = 1;
    vector<node> t;
    node& operator[](int ind) { return t[ind + n]; }
    const node& operator[](int ind) const { return t[ind + n]; }
    void submerge(int v) { // merge v's sons to v
        if (v >= n) return;
        t[v] = merge(t[v + v], t[v + v + 1]);
    }
    void resize(int sz) { // allocation
        while (n < sz) n <<= 1;
        t.resize(2 * n + 1);
    }
    void blank() { // default values
        for (int i = 0; i < 2 * n; ++i)
            t[i] = node();
    }
    void build() {
        for (int i = n - 1; i > 0; --i)
            submerge(i);
    }
    template<class T>
    void assign(const vector<T> &a) { // copy of a
        resize(sz(a));
        for (int i = 0; i < sz(a); ++i)
            t[i + n] = a[i];
        for (int i = sz(a); i < n; ++i)
            t[i + n] = node();
        build();
    }
    Tree() {} // empty
    Tree(int sz) { resize(sz); blank(); } // size, default values
    template<class T> Tree(const vector<T> &a) { assign(a); } // copy of a
    template<class T>
    void updup(int i, const T &val) { // upd at i with val, doesn't support push
        i += n;
        t[i].upd(val);
        for (i >>= 1; i > 0; i >>= 1)
            submerge(i);
    }
    node getup(int l, int r) { // get at [l, r), doesn't support push
        l += n;
        r += n;
        int cr = r;
        node left, right;
        bool lf = true, rf = true;
        for (; l < r; l >>= 1, r >>= 1) {
            if (l & 1) left = lf ? lf = false, t[l++] : merge(left, t[l++]);
            if (r & 1) right = rf ? rf = false, t[--r] : merge(t[--r], right);
        }
        if (lf) return right;
        if (rf) return left;
        return merge(left, right);
    }
    void push(int v) {
        if (t[v].updated()) {
            t[v + v].upd(t[v]);
            t[v + v + 1].upd(t[v]);
            t[v].unupdate();
        }
    }
    // update [l, r) with value x, supports push
    template<class T>
    void upd(int l, int r, const T &x, int v, int vl, int vr) { 
        if (vl >= r || vr <= l) return;
        if (vl >= l && vr <= r) return t[v].upd(x);
        push(v);
        int vm = vl + vr >> 1;
        upd(l, r, x, v + v, vl, vm);
        upd(l, r, x, v + v + 1, vm, vr);
        submerge(v);
    }
    template<class T>
    void upd(int l, int r, const T &x) { upd(l, r, x, 1, 0, n); } 
    
    // get at [l, r), supports push
    node get(int l, int r, int v, int vl, int vr) {
        if (vl >= r || vr <= l) return node();
        if (vl >= l && vr <= r) return t[v];
        push(v);
        int vm = vl + vr >> 1;
        if (r <= vm) return get(l, r, v + v, vl, vm);
        if (l >= vm) return get(l, r, v + v + 1, vm, vr);
        return merge(get(l, r, v + v, vl, vm), get(l, r, v + v + 1, vm, vr));
    }
    node get(int l, int r) { return get(l, r, 1, 0, n); } 
};
