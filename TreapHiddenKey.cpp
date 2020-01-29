typedef ll key;
typedef struct node* pnode;

struct node {
    key k;
    int cnt = 1, p = rand();
    pnode l = nullptr, r = nullptr;
    node(key k) { this->k = k; }
};

ostream& operator<<(ostream& str, pnode n) {
    if (!n) return str;
    return str << n->l << n->k << ' ' << n->r; 
}

int getcnt(pnode n) {
    return n ? n->cnt : 0;
}

void upd(pnode n) {
    if (n) n->cnt = 1 + getcnt(n->l) + getcnt(n->r);
}

pnode merge(pnode a, pnode b) {
    if (!a) return b;
    if (!b) return a;
    if (a->p > b->p) {
        a->r = merge(a->r, b);
        upd(a);
        return a;
    } else {
        b->l = merge(a, b->l);
        upd(b);
        return b;
    }
}

void splitval(pnode t, key k, pnode &l, pnode &r) {
    if (!t) return void(l = r = t);
    if (t->k > k) {
        splitval(t->l, k, l, t->l);
        r = t;
    } else {
        splitval(t->r, k, t->r, r);
        l = t;
    }
    upd(l); upd(r);
}

void splitind(pnode t, int ind, pnode &l, pnode &r) {
    if (!t) return void(l = r = t);
    if (getcnt(t->l) < ind) {
        splitind(t->r, ind - getcnt(t->l) - 1, t->r, r);
        l = t;
    } else {
        splitind(t->l, ind, l, t->l);
        r = t;
    }
    upd(l); upd(r);
}

int lower_bound(pnode t, key k) {
    if (!t) return 0;
    if (t->k >= k) return lower_bound(t->l, k);
    return lower_bound(t->r, k) + getcnt(t->l) + 1;
}

int upper_bound(pnode t, key k) {
    if (!t) return 0;
    if (t->k > k) return upper_bound(t->l, k);
    return upper_bound(t->r, k) + getcnt(t->l) + 1;
}

int count(pnode t, key k) {
    return upper_bound(t, k) - lower_bound(t, k);
}

key kth(pnode t, int ind) {
    if (ind == getcnt(t->l)) return t->k;
    if (getcnt(t->l) > ind) return kth(t->l, ind);
    return kth(t->r, ind - getcnt(t->l) - 1);
}

void insert(pnode &t, key k) {
    pnode r;
    splitval(t, k, t, r);
    t = merge(t, new node(k));
    t = merge(t, r);
}

void insert(pnode &t, int ind, key k) {
    pnode r;
    splitind(t, ind, t, r);
    t = merge(t, new node(k));
    t = merge(t, r);
}

void erase(pnode &t, key k) {
    pnode m, r;
    splitind(t, upper_bound(t, k), t, r);
    splitind(t, lower_bound(t, k), t, m);
    t = merge(t, r);
}

void eraseone(pnode &t, key k) {
    pnode m, r;
    splitind(t, lower_bound(t, k), t, r);
    splitind(r, 1, m, r);
    t = merge(t, r);
}
