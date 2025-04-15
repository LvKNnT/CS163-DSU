#include <bits/stdc++.h>
using namespace std;
#define time __time

class DSU {
private:
	static const int SAVE_CHANGES = 2;
	int n;
	vector <int> sz, par;
	stack <pair <int*, int>> history;

	void create_checkpoint(array <int*, SAVE_CHANGES> saves) {
		for (int* save : saves) history.emplace(save, *save);
	}
public:
	DSU(void) { }
	void init(int _n) { n = _n ;sz.assign(n + 7, 1); par.resize(n + 7); iota(par.begin(), par.end(), 0); }

	inline bool is_root(int u) const { return u == par[u]; }
	inline int root(int u) const { return is_root(u) ? u : root(par[u]); }
	inline bool same_set(int u, int v) { return root(u) == root(v); }
	bool unite(int u, int v) {
		u = root(u), v = root(v);
		if (u == v) return false;
		if (sz[u] < sz[v]) swap(u, v);

		create_checkpoint({&sz[u], &par[v]});
		return sz[u] += sz[v], par[v] = u, true;
	}

	void undo(void) {
		for (int T = SAVE_CHANGES; T--; ) {
			int *var; int val;
			tie(var, val) = history.top(); history.pop();
			*var = val;
		}
	}
};

struct Edge {
	int u, v, sta, fin;
	bool used;
	Edge(int u = 0, int v = 0, int sta = 0, int fin = 0): u(u), v(v), sta(sta), fin(fin), used(false) { }
};

class QueryTree {
private:
	int T;
	vector <vector <Edge>> edges;
	vector <pair <int, int>> ask;
	DSU dsu;

	void add_edge(int id, int l, int r, const Edge &E) {
		if (l > r || E.sta > E.fin || E.sta > r || l > E.fin) return;
		if (E.sta <= l and r <= E.fin) return void(edges[id].push_back(E));

		int mid = (l + r) >> 1;
		add_edge(id << 1, l, mid, E);
		add_edge(id << 1 | 1, mid + 1, r, E);
	}

	void add_query(int id, int l, int r, int time, int u, int v) {
		if (l > r || l > time || time > r) return;
		if (l == r) return void(ask[id] = {u, v});

		int mid = (l + r) >> 1;
		add_query(id << 1, l, mid, time, u, v);
		add_query(id << 1 | 1, mid + 1, r, time, u, v);
	}

	void traverse(int id, int l, int r, vector <bool> &ans) {
		for (auto &E : edges[id]) E.used = dsu.unite(E.u, E.v);

		if (l == r) {
			int u, v; tie(u, v) = ask[id];
			if (u and v) ans.push_back(dsu.same_set(u, v));
		} else {
			int mid = (l + r) >> 1;
			traverse(id << 1, l, mid, ans);
			traverse(id << 1 | 1, mid + 1, r, ans);
		}

		for (auto E : edges[id]) if (E.used) dsu.undo();
	}
public:
	QueryTree(void) { }
	void init(int _T, int _n) {
		T = _T;
		dsu.init(_n);
		edges.resize(4 * T + 7);
		ask.resize(4 * T + 7);
	}

	void add_edge(const Edge &E) { add_edge(1, 1, T, E); }
	void add_query(int time, int u, int v) { add_query(1, 1, T, time, u, v); }
	vector <bool> solve(void) {
		vector <bool> ans;
		traverse(1, 1, T, ans);
		return ans;
	}
};

int main(void) {
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

	QueryTree qt;
	multimap <pair <int, int>, int> avaiable_time;
	int n, Q; cin >> n >> Q; qt.init(Q, n);
	for (int q = 1; q <= Q; q++) {
		int t, u, v; cin >> t >> u >> v;
		if (u > v) swap(u, v);
		if (t == 1) avaiable_time.emplace(make_pair(u, v), q);
		if (t == 2) {
			auto it = avaiable_time.find({u, v}); if (it == avaiable_time.end()) continue;
			qt.add_edge(Edge(u, v, it->second, q));
			avaiable_time.erase(it);
		}
		if (t == 3) qt.add_query(q, u, v);
	}

	for (auto [e, time] : avaiable_time)
		qt.add_edge(Edge(e.first, e.second, time, Q));

	vector <bool> ans = qt.solve();
	for (auto x : ans) cout << x;

	return 0;
}
//problem: https://oj.vnoi.info/problem/voscomps
//submission from Phan Binh Nguyen Lam
