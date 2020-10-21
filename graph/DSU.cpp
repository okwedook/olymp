struct dsu {
    struct rnk {
        int val = 1;
        int get() const {
            return val;
        }
        void add(const rnk &r) {
            val += r.val;
        }
    };
    vector<int> p;
    vector<rnk> r;
    int comp = 0, edge = 0;
    dsu() {}
    bool empty() const {
        return p.empty();
    }
    dsu(int n) {
        p = vector<int>(n);
        r = vector<rnk>(n);
        for (int i = 0; i < n; ++i)
            p[i] = i;
        comp = n;
    }
    int getp(int v) { // returns head element in a set
        return v == p[v] ? v : p[v] = getp(p[v]);
    }
    bool check(int a, int b) { // a and b are in one component
        return getp(a) == getp(b);
    }
    bool unite(int a, int b) { // a and b are in diff components
        a = getp(a);
        b = getp(b);
        if (a == b) return false;
        ++edge;
        --comp;
        if (r[a].get() > r[b].get()) swap(a, b);
        p[a] = b;
        r[b].add(r[a]);
        return true;
    }
};
