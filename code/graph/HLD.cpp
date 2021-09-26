struct node {
    int mx = 0;
    node() {}
    void a(int k) { mx += k; }
};

node merge(node a, node b) {
    node ans;
    ans.mx = max(a.mx, b.mx);
    return ans;
}

struct Tree {
    static const int n = 1 << 17;
    node t[2 * n + 5];
    void add(int r, int x) {
        r += n;
        t[r].a(x);
        r >>= 1;
        while (r > 0) {
            t[r] = merge(t[r + r], t[r + r + 1]);
            r >>= 1;
        }
    }
    node get(int l, int r) {
        l += n;
        r += n + 1;
        node left, right;
        while (l < r) {
            if (l & 1) left = merge(left, t[l++]);
            if (r & 1) right = merge(t[--r], right);
            l >>= 1;
            r >>= 1;
        }
        return merge(left, right);
    }
} t;

vector<int> h, sub, ind, head, par;
int curr = 0;
graph G;

void orient(int v = 0, int p = -1, int d = 0) {
    h[v] = d;
    par[v] = p;
    sub[v] = 1;
    for (auto i : G[v])
        if (i != p) {
            orient(i, v, d + 1);
            sub[v] += sub[i];
        }
    for (int i = 0; i < sz(G[v]); ++i)
        if (G[v][i] != p && sub[G[v][i]] * 2 >= sub[v])
            swap(G[v][0], G[v][i]);
}

void buildhld(int v = 0, int path = 0) {
    head[v] = path;
    ind[v] = curr++;
    for (auto i : G[v])
        if (i != par[v]) {
            if (sub[i] * 2 >= sub[v]) buildhld(i, path);
            else buildhld(i, i);
        }
}

int lca(int u, int v) {
    while (head[u] != head[v])
        if (h[head[u]] > h[head[v]]) u = par[head[u]];
        else v = par[head[v]];
    return h[u] < h[v] ? u : v;
}

node getw(int u, int v) {
    node ans;
    while (head[u] != head[v]) ans = merge(ans, t.get(ind[head[u]], ind[u])), u = par[head[u]];
    return merge(ans, t.get(ind[v], ind[u]));
}

node getwo(int u, int v) {
    node ans;
    while (head[u] != head[v]) ans = merge(ans, t.get(ind[head[u]], ind[u])), u = par[head[u]];
    if (ind[v] + 1 > ind[u]) return ans;
    return merge(ans, t.get(ind[v] + 1, ind[u]));
}
