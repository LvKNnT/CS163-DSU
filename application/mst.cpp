#include <bits/stdc++.h>
using namespace std;

class DSU {
private:
	int n;
	vector <int> par;
public:
	DSU(int n = 0): n(n) { par = vector <int> (n + 7, 0); iota(par.begin(), par.end(), 0); }

	int root(int u) { return u == par[u] ? u : par[u] = root(par[u]); }
	bool join(int u, int v) {
		u = root(u), v = root(v);
		if (u == v) return false;
		return par[v] = u, true;
	}
};

struct Edge {
	int u, v, w;

	Edge(int u = 0, int v = 0, int w = 0): u(u), v(v), w(w) { }
	bool operator < (const Edge &oth) const { return w < oth.w; }
};

int main(void) {
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

	int n, m; cin >> n >> m;
	vector <Edge> edges;
	while (m--) {
		int u, v, c; cin >> u >> v >> c;
		edges.emplace_back(u, v, c);
	}

	sort(edges.begin(), edges.end());
	DSU dsu(n);

	int ans = 0;
	for (const auto &e : edges)
		if (dsu.join(e.u, e.v)) ans += e.w;
	cout << ans << '\n';

	return 0;
}
//problem: https://oj.vnoi.info/problem/qbmst
//submission by Phan Binh Nguyen Lam
