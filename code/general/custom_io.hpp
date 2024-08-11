struct InitIO {
    InitIO() {
        ios_base::sync_with_stdio(0);
        cin.tie(0);
        cout.tie(0);
        cout << fixed << setprecision(12);
    }
    ~InitIO() {
        #ifdef DEBUG
            cerr << "Runtime is: " << clock() * 1.0 / CLOCKS_PER_SEC << endl;
        #endif
    }
} Initter;

template<class T, class U> inline istream& operator>>(istream& str, pair<T, U> &p) { return str >> p.f >> p.s; }
template<class T> inline istream& operator>>(istream& str, vector<T> &a) { for (auto &i : a) str >> i; return str; }

void flush() { cout << flush; }
void flushln() { cout << endl; }
template<class T> void print(const T &x) { cout << x; }
template<class T> void read(T &x) { cin >> x; }
template<class T, class ...U> void read(T &x, U&... u) { read(x); read(u...); }
template<class T, class ...U> void print(const T &x, const U&... u) { print(x); print(u...); }
template<class ...T> void println(const T&... u) { print(u..., '\n'); }
