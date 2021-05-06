namespace SplayTree {
    typedef struct node* pnode;
    static const pnode null = nullptr;
    struct node {
#define PARAM(TYPE, NAME)                                                \
        TYPE NAME;                                                       \
        friend TYPE get##NAME(pnode v) { return v ? v->NAME : TYPE(); }
        PARAM(int, key);
        PARAM(pnode, p);
        PARAM(pnode, l);
        PARAM(pnode, r);
#undef PARAM
        node(int _key) : key(_key) {}
    };
    inline pnode newNode(int key) {
        return new node(key);
    }
    inline pnode getpp(pnode v) {
        return getp(getp(v));
    }
#define SIDE(SM, BG)                               \
    inline bool is##BG(pnode v) {                  \
        pnode p = getp(v);                         \
        return p && p->SM == v;                    \
    }                                              \
    inline void make##BG(pnode v, pnode p) {       \
        if (v) v->p = p;                           \
        if (p) p->SM = v;                          \
    }

    SIDE(l, Left);
    SIDE(r, Right);
#undef SIDE
    inline void upd(pnode v) {
        if (v) {

        }
    }
    void zig(pnode v) {
        pnode p = getp(v);
        pnode pp = getp(p);
        bool wasLeft = isLeft(p);
        if (isLeft(v)) {
            makeLeft(getr(v), p);
            makeRight(p, v);
        } else {
            makeRight(getl(v), p);
            makeLeft(p, v);
        }
        if (wasLeft) makeLeft(v, pp);
        else makeRight(v, pp);
        upd(p);
        upd(v);
        upd(pp);
    }
    void zigzig(pnode v) {
        zig(getp(v));
        zig(v);
    }
    void zigzag(pnode v) {
        zig(v);
        zig(v);
    }
    void splay(pnode v) {
        while (getp(v)) {
            if (getpp(v) == null) {
                zig(v);
            } else {
                if (isLeft(v) == isLeft(getp(v))) {
                    zigzig(v);
                } else {
                    zigzag(v);
                }
            }
        }
    }
    void printNode(pnode v) {
        if (!v) return;
        printNode(getl(v));
        print(getkey(v), ' ');
        printNode(getr(v));
    }
    struct Tree {
        pnode root = null;
        Tree() {}
        Tree(int key) {
            root = newNode(key);
        }
        Tree(pnode v) : root(v) {}
        pnode find(pnode v, int key) {
            if (!v) return null;
            if (getkey(v) > key && getl(v))
                return find(getl(v), key);
            if (getkey(v) < key && getr(v))
                return find(getr(v), key);
            splay(v);
            return v;
        }
        pnode find(int key) {
            return find(root, key);
        }
        pnode max() const {
            pnode ans = root;
            while (getr(ans)) ans = getr(ans);
            return ans;
        }
        pnode min() const {
            pnode ans = root;
            while (getl(ans)) ans = getl(ans);
            return ans;
        }
        void setRoot(pnode v) {
            splay(v);
            root = v;
        }
        friend Tree merge(Tree a, Tree b) {
            if (!a.root) return b;
            if (!b.root) return a;
            a.setRoot(a.max());
            b.setRoot(b.min());
            makeRight(b.root, a.root);
            upd(a.root);
            return a;
        }
        pair<Tree, Tree> split(int key) {
            if (!root) return {null, null};
            pnode v = find(key);
            setRoot(v);
            if (key > getkey(v)) {
                pair<Tree, Tree> ans = {v, getr(v)};
                makeLeft(ans.s.root, null);
                makeRight(null, ans.f.root);
                upd(ans.f.root);
                return ans;
            } else {
                pair<Tree, Tree> ans = {getl(v), v};
                makeRight(ans.f.root, null);
                makeLeft(null, ans.s.root);
                upd(ans.s.root);
                return ans;
            }
        }
        friend void printTree(Tree t) {
            printNode(t.root);
            print(' ');
        }
    };
};
