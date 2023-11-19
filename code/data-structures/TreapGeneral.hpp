using pnode = int;
const pnode nullnode = -1;
template<bool has_field> struct Parent {
    void upd_parent(pnode n) {}
};
template<> struct Parent<true> {
    pnode parent = nullnode;
    void upd_parent(pnode n) {
        parent = n;
    }
};

template<bool has_field> struct Subsize {
    void upd_subsize(int sz) {}
    int get_size() const { return 0; }
};
template<> struct Subsize<true> {
    int size = 1;
    void upd_subsize(int sz) {
        size = sz;
    }
    int get_size() const {
        return size;
    }
};

template<class KeyClass, bool has_parent, bool has_subsize>
struct node_impl : Parent<has_parent>, Subsize<has_subsize> {
    using Key = KeyClass;
    Key key;
    int priority = gen();
    pnode l = nullnode, r = nullnode;
    node_impl() {}
    node_impl(const Key &k) : key(k) {}
    static constexpr bool HAS_PARENT = has_parent;
    static constexpr bool HAS_SUBSIZE = has_subsize;
    void upd() {}
};

template<class Node>
struct Treap {
    using Key = typename Node::Key;
    Treap() = delete;
    inline static vector<Node> pool;
    static void reserve_pool(size_t pool_size) {
        pool.reserve(pool_size);
    }
    template<class ...Args>
    static pnode new_node(Args... args) {
        pool.push_back(Node(args...));
        return sz(pool) - 1;
    }
    static int get_size(pnode n) {
        return n != nullnode ? pool[n].get_size() : 0;
    }
    static void upd_parent(pnode p, pnode parent) {
        if (p != nullnode) {
            pool[p].upd_parent(parent);
        }
    }
    static void upd(pnode p) {
        if (p == nullnode) return;
        auto &n = pool[p];
        n.upd_subsize(1 + get_size(n.r) + get_size(n.l));
        upd_parent(n.l, p);
        upd_parent(n.r, p);
        n.upd();
    }
    static pnode merge(pnode a, pnode b) {
        if (a == nullnode) return b;
        if (b == nullnode) return a;
        if (pool[a].priority > pool[b].priority) {
            pool[a].r = merge(pool[a].r, b);
            upd(a);
            return a;
        } else {
            pool[b].l = merge(a, pool[b].l);
            upd(b);
            return b;
        }
    }
    template<class Cmp>
    static void splitvalcmp(pnode tp, const Key &key, pnode &l, pnode &r, Cmp&& cmp) {
        if (tp == nullnode) {
            l = r = nullnode;
            return;
        }
        auto &t = pool[tp];
        if (cmp(key, t.key)) {
            splitvalcmp(t.l, key, l, t.l, forward<Cmp>(cmp));
            r = tp;
            if (r != nullnode) pool[r].upd_parent(nullnode);
        } else {
            splitvalcmp(t.r, key, t.r, r, forward<Cmp>(cmp));
            l = tp;
            if (l != nullnode) pool[l].upd_parent(nullnode);
        }
        upd(l);
        upd(r);
    }
    // l holds all values < than key
    static void splitval(pnode tp, const Key &key, pnode &l, pnode &r) {
        splitvalcmp(tp, key, l, r, less_equal<Key>());
    }
    // r holds all values > than key
    static void splitvalup(pnode tp, const Key &key, pnode &l, pnode &r) {
        splitvalcmp(tp, key, l, r, less<Key>());
    }
    static string to_string(pnode n) {
        string ans;
        to_string_impl(n, ans);
        return ans;
    }

private:
    static void to_string_impl(pnode n, string &ans) {
        if (n == nullnode) return;
        to_string_impl(pool[n].l, ans);
        auto nd = pool[n];
        ans += dbgout(nd.key) + " ";
        to_string_impl(pool[n].r, ans);
    }
};

template<class Key>
using node = node_impl<Key, true, true>;
