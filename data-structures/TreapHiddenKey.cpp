typedef struct node* pnode;
typedef int key;

pnode null = nullptr;

struct node {
    key k;
    int x = gen();
    int cnt = 1;
    pnode l = null, r = null, p = null;
    node(key _k) : k(_k) {}
};

void print(pnode t) {
    if (t == null) return;
    print(t->l, t->k, ' ', t->r);
}

pnode newnode(const key &k) {
    return new node(k);
}

inline int getcnt(pnode n) {
    return n == null ? 0 : n->cnt;
}

inline void updparent(pnode son, pnode parent) {
    if (son != null) {
        son->p = parent;
    }
}

inline void upd(pnode n) {
    if (n) {
        n->cnt = 1 + getcnt(n->l) + getcnt(n->r);
        updparent(n->l, n);
        updparent(n->r, n);
    }
}

pnode merge(pnode a, pnode b) {
    if (a == null) return b;
    if (b == null) return a;
    if (a->x > b->x) {
        a->r = merge(a->r, b);
        upd(a);
        return a;
    } else {
        b->l = merge(a, b->l);
        upd(b);
        return b;
    }
}

void splitind(pnode t, int ind, pnode &l, pnode &r) {
    if (t == null) return void(l = r = null);
    if (getcnt(t->l) >= ind) {
        splitind(t->l, ind, l, t->l);
        r = t;
    } else {
        splitind(t->r, ind - getcnt(t->l) - 1, t->r, r);
        l = t;
    }
    upd(l);
    upd(r);
}

void splitval(pnode t, const key &k, pnode &l, pnode &r) {
    if (t == null) return void(l = r = null);
    if (k < t->k) {
        splitval(t->l, k, l, t->l);
        r = t;
    } else {
        splitval(t->r, k, t->r, r);
        l = t;
    }
    upd(l);
    upd(r);
}

void splitvalup(pnode t, const key &k, pnode &l, pnode &r) {
    if (t == null) return void(l = r = null);
    if (!(t->k < k)) {
        splitval(t->l, k, l, t->l);
        r = t;
        updparent(r, null);
    } else {
        splitval(t->r, k, t->r, r);
        l = t;
        updparent(l, null);
    }
    upd(l);
    upd(r);
}

void insert(pnode &t, const key &k) {
    pnode r;
    splitval(t, k, t, r);
    t = merge(t, newnode(k));
    t = merge(t, r);
}

void insert(pnode &t, int ind, const key &k) {
    pnode r;
    splitind(t, ind, t, r);
    t = merge(t, newnode(k));
    t = merge(t, r);
}

key min(pnode t) {
    assert(t != null);
    if (t->l != null) return min(t->l);
    return t->k;
}

key max(pnode t) {
    assert(t != null);
    if (t->r != null) return max(t->r);
    return t->k;
}

void eraseone(pnode &t, const key &k) {
    pnode r;
    splitval(t, k, t, r);
    assert(min(r) == k);
    pnode m;
    splitind(r, 1, m, r);
    t = merge(t, r);
}

void eraseall(pnode &t, const key &k) {
    pnode m, r;
    splitval(t, k, t, r);
    splitvalup(r, k, m, r);
    t = merge(t, r);
}

key kth(pnode t, int ind) {
    assert(ind >= 0 && ind < getcnt(t));
    if (ind == getcnt(t->l)) return t->k;
    if (ind < getcnt(t->l)) return kth(t->l, ind);
    return kth(t->r, ind - getcnt(t->l) - 1);
}

int lower_bound(pnode t, const key &k) {
    if (t == null) return 0;
    if (!(t->k < k)) return lower_bound(t->l, k);
    return lower_bound(t->r, k) + 1 + getcnt(t->l);
}

int upper_bound(pnode t, const key &k) {
    if (t == null) return 0;
    if (k < t->k) return upper_bound(t->l, k);
    return upper_bound(t->r, k) + 1 + getcnt(t->l);
}

int getind(pnode t) {
    assert(t != null);
    int ans = 1 + getcnt(t->l);
    pnode was = t;
    t = t->p;
    while (t != null) {
        if (t->l != was)
            ans += getcnt(t->l) + 1;
        was = t;
        t = t->p;
    }
    return ans;
}
