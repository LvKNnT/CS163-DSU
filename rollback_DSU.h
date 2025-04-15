#include <bits/stdc++.h>

const int VAR_CHANGES = 2;

class DisjointSet {
private:
    int n;
    std::vector<int> parent;
    std::vector<int> size;
    std::stack<std::pair<int*, int>> history;
public:
    void init(int _n);
    int find(int u) const;
    bool join(int u, int v);
    void undo(void);
};

void DisjointSet::init(int _n) {
    n = _n;
    parent.assign(n, 0);
    std::iota(parent.begin(), parent.end(), 0);
    size.assign(n, 1);
    while(!history.empty()) {
        history.pop();
    }
}

int DisjointSet::find(int u) const {
    return u == parent[u] ? u : find(parent[u]);
}

bool DisjointSet::join(int u, int v) {
    u = find(u);
    v = find(v);
    if (u == v)
        return false;
    if (size[u] > size[v])
        std::swap(u, v);
    history.emplace(&parent[u], parent[u]);
    history.emplace(&size[v], size[v]);
    parent[u] = v;
    size[v] += size[u];
    return true;
}

void DisjointSet::undo(void) {
    for (int T = VAR_CHANGES; T--; ) {
        int* ptr;
        int val;
        std::tie(ptr, val) = history.top();
        history.pop();
        *ptr = val;
    }
}