// Author: Mikhail Pogodin (okwedook)
//
// Implementatin of Disjoint Set Union
// Works in O(alpha(n)) ~ const per query
//
// Check tasks: codeforces.com/edu/course/2/lesson/7/1/practice/contest/289390/problem/A

struct DSU {
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
    int comp = 0;
    DSU() {}
    DSU(int n) {
        p.resize(n);
        r.resize(n);
        iota(all(p), 0);
        comp = n;
    }
    // Returns head element in the set containing v
    int getp(int v) {
        return v == p[v] ? v : p[v] = getp(p[v]);
    }
    // True if a and b are in one component
    bool check(int a, int b) {
        return getp(a) == getp(b);
    }
    // Unites components containing a and b
    // Returns true if a and b are in diff components
    bool unite(int a, int b) {
        a = getp(a);
        b = getp(b);
        if (a == b) return false;
        --comp;
        if (r[a].get() > r[b].get()) swap(a, b);
        p[a] = b;
        r[b].add(r[a]);
        return true;
    }
};
