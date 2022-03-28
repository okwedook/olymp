// Author: Mikhail Pogodin (okwedook)
//
// Processes a dictionary to a trie, which might be used to find occurences in a text
// Uses linear space and time to compute
//
// Check tasks: https://informatics.msk.ru/mod/statements/view.php?chapterid=111732#1

template<class String = string, class Char = char>
struct Aho {
    struct Node {
        map<Char, int> go;
        int p;
        Char c;
        int suff = -1;
        int supersuff = -1;
        vector<int> ind;
        Node(int _p, Char _c) : p(_p), c(_c) {}
        bool isSuper() const {
            return sz(ind);
        }
    };
    int ptr;
    int getGo(int v, Char c) {
        auto it = t[v].go.find(c);
        if (it == t[v].go.end()) {
            // Creates a new vertex in trie
            t.pb(Node(v, c));
            return t[v].go[c] = ptr++;
        }
        return it->s;
    }
    vector<Node> t;
    // Reserve sum of dict lengths + 1
    void reserve(size_t sz) {
        t.reserve(sz);
    }
    static const int root = 0;
    Aho() : ptr(1) {
        t.pb(Node(root, Char(0)));
        t[root].suff = root;
    }
    void addToTrie(String s, int i) {
        int v = root;
        for (auto c : s) {
            v = getGo(v, c);
        }
        t[v].ind.pb(i);
    }
    int goAutomaton(int v, Char c) {
        while (true) {
            if (t[v].go.count(c)) {
                return t[v].go[c];
            }
            if (v == root) {
                return root;
            }
            v = t[v].suff;
        }
    }
    vector<int> getBfsOrder() {
        vector<int> que = {root};
        que.reserve(sz(t));
        for (int i = 0; i < sz(t); ++i) {
            for (auto [_, son] : t[que[i]].go) {
                que.pb(son);
            }
        }
        return que;
    }
    void countAllSuff() {
        for (auto v : getBfsOrder()) {
            if (t[v].p == root) {
                t[v].suff = root;
            } else {
                t[v].suff = goAutomaton(t[t[v].p].suff, t[v].c);
            }
        }
    }
    // Needs countAllSuff beforehand
    void countAllSuperSuff() {
        for (auto v : getBfsOrder()) {
            if (t[t[v].suff].isSuper()) {
                t[v].supersuff = t[v].suff;
            } else {
                t[v].supersuff = t[t[v].suff].supersuff;
            }
        }
    }
    void dfsDebug(int v) {
        for (auto [c, son] : t[v].go) {
            dbg(son, c);
            dfs(son);
            msg("UP");
        }
    }
};