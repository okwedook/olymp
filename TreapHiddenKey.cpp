#pragma GCC optimize("O3", "unroll-loops")

#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm>
#include <deque>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <sstream>
#include <cmath>
#include <tuple>
#include <random>
#include <bitset>

using namespace std;

#define FIXED cout << fixed << setprecision(15)
#define FAST ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0)
#define RANDOM srand(85453532)
#define ll long long
#define ld long double
#define pii pair<int, int>
#define pll pair<ll, ll>
#define graph vector<vector<int>>
#define pb push_back
#define popb pop_back
#define pf push_front
#define popf pop_front
#define sz(a) int(a.size())
#define all(a) a.begin(), a.end()
#define rall(a) a.rbegin(), a.rend()
#define eps 1e-9
#define mod 1000000007
#define inf 4000000000000000007ll
#define f first
#define s second
#define shuffle(a) \
	for (int i = 0; i < sz(a); ++i) \
		swap(a[i], a[rand() % sz(a)])

template<class T, class U> inline void checkmin(T &x, U y) { if (y < x) x = y; }
template<class T, class U> inline void checkmax(T &x, U y) { if (y > x) x = y; }
template<class T, class U> inline bool ifmin(T &x, U y) { 
	if (y < x) return x = y, true;
	return false; 
}
template<class T, class U> inline bool ifmax(T &x, U y) { 
	if (y > x) return x = y, true;
	return false; 
}
template<class T> inline void sort(T &a) { sort(all(a)); }
template<class T> inline void rsort(T &a) { sort(rall(a)); }
template<class T> inline void reverse(T &a) { reverse(all(a)); }
template<class T> inline istream& operator>>(istream &stream, vector<T> &a) { 
	for (auto &i : a) stream >> i;
	return stream;
}

typedef ll key;
typedef struct node* pnode;

struct node {
	key k;
	int p = rand(), cnt = 1;
	pnode l = nullptr, r = nullptr;
	node() {}
	node(key k) {
		this->k = k;
	} 
};

ostream& operator<<(ostream& stream, pnode n) {
	if (n == nullptr) return stream;
	return stream << n->l << n->k << ' ' << n->r;
}

int getcnt(pnode n) {
	if (n == nullptr) return 0;
	return n->cnt;
}

void upd(pnode n) {
	if (n == nullptr) return;
	n->cnt = getcnt(n->l) + getcnt(n->r) + 1;
}

pnode merge(pnode a, pnode b) {
	if (a == nullptr) return b;
	if (b == nullptr) return a;
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

void split(pnode n, int ind, pnode &l, pnode &r) {
	if (n == nullptr) return void(l = r = n);
	if (getcnt(n->l) < ind) {
		split(n->r, ind - getcnt(n->l) - 1, n->r, r);
		l = n;
	} else {
		split(n->l, ind, l, n->l);
		r = n;
	}
	upd(l); upd(r);
}

void insert(pnode &n, int ind, key x) {
	pnode r;
	split(n, ind, n, r);
	n = merge(n, new node(x));
	n = merge(n, r);
}

int lower_bound(pnode n, key x) {
	if (n == nullptr) return 0;
	if (n->k < x) return getcnt(n->l) + 1 + lower_bound(n->r, x);
	return lower_bound(n->l, x);
}

int upper_bound(pnode n, key x) {
	if (n == nullptr) return 0;
	if (n->k <= x) return getcnt(n->l) + 1 + upper_bound(n->r, x);
	return upper_bound(n->l, x);
}

int count(pnode n, key x) {
	return upper_bound(n, x) - lower_bound(n, x);
}

void insert(pnode &n, key x) {
	insert(n, lower_bound(n, x), x);
}

key kth(pnode n, int ind) {
	int cnt = getcnt(n->l);
	if (cnt == ind) return n->k;
	if (cnt > ind) return kth(n->l, ind);
	return kth(n->r, ind - cnt - 1);
}

pnode t;

signed main() {
	FAST; FIXED; RANDOM;
	return 0;
}
