template<class T> struct Fenv {
    int N, LOG;
    T *fenv;
    Fenv(int N) {
        this->N = N;
        LOG = log2(N);
        fenv = new T[N];
        for (int i = 0; i < N; ++i) fenv[i] = 0;
    }
	~Fenv() { delete [] fenv; }
    void add(int r, T x) { //adds x to a[r]
        for (; r < N; r |= r + 1) fenv[r] += x;
    }
    T get(int r) { //sum of [0, r]
        T ans = 0;
        for (; r >= 0; r = (r & r + 1) - 1) 
            ans += fenv[r];
        return ans;
    }
    T get(int l, int r) { //sum of [l, r]
        return get(r) - get(l - 1);
    }
    int lb(T k) { //first index which sum is >= k
        int ans = -1;
        for (int l = LOG; l >= 0; --l) {
            int next = ans + (1 << l);
            if (next < N && k > fenv[next]) {
                ans = next;
                k -= fenv[next];
            }
        }
        return ans + 1;
    }
};
