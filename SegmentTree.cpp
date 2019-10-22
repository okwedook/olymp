struct node {
	int mn, mx;
	node() : mn(mod), mx(-mod) {}
	node(int x) : mn(x), mx(x) {}
	node(int _mn, int _mx) : mn(_mn), mx(_mx) {}
	int get() const {
		return mx - mn;
	}
};
 
inline node merge(const node &a, const node &b) {
    return node(min(a.mn, b.mn), max(a.mx, b.mx));
}
 
template<class T> inline void merge(const T &a, const T &b, T &c) {
	c = move(merge(a, b));
}
 
template<class node>
class Tree {
private:
    node *t = nullptr;
    int n;
 
public:
    ~Tree() {
        delete [] t;
    }
    void resize(int sz) {
    	n = 1;
    	while (sz > n) n *= 2;
    	t = new node[2 * n + 1];
    }
    template<class T>
    void assign(const vector<T> &a) {
    	resize(sz(a));
        for (int i = 0; i < sz(a); ++i)
            t[i + n] = a[i];
        for (int i = sz(a); i < n; ++i)
        	t[i + n] = node();
        for (int i = n - 1; i > 0; --i)
            t[i] = merge(t[i + i], t[i + i + 1]);
    }
    template<class T>
    Tree(const vector<T> &a) {
    	assign(a);
    }
    Tree(int sz, node x = node()) {
    	resize(sz);
    	for (int i = 0; i < n; ++i)
    		t[i + n] = x;
    	for (int i = n - 1; i >= 0; --i)
    		t[i] = merge(t[i + i], t[i + i + 1]);
    }
    void updup(int r, node x) { //upd r-th element with x (w/o push)
        r += n;
        t[r] = x;
        for (r >>= 1; r > 1; r >>= 1)
            t[r] = merge(t[r + r], t[r + r + 1]);
    }
    node getup(int l, int r) { //get on [l, r] (w/o push)
        l += n;
        r += n + 1;
        node left = node(), right = node();
        for (; l < r; l >>= 1, r >>= 1) {
            if (l & 1) left = merge(left, t[l++]);
            if (r & 1) right = merge(t[--r], right);
        }
        return merge(left, right);
    }
    node get(int l, int r) {
    	return t[0].push();
    }
};
