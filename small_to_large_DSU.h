#include <bits/stdc++.h>

class DSU{
private:
    std::vector<std::map<int, int>> color;
    std::vector<int> parent, size;
public:
    void init(int n, std::vector<int> _color);
    int find(int u);
    bool join(int a, int b);
    int query(int v, int c);
};

void DSU::init(int n, std::vector<int> _color) {
    parent.assign(n, 0);
    std::iota(parent.begin(), parent.end(), 0);
    size.assign(n, 1);
    color.clear();
    for (int i = 0; i < n; i += 1) {
        color[i][_color[i]] += 1;
    }
}

int DSU::find(int u) {
    return parent[u] = (
        u == parent[u]
        ? u
        : find(parent[u])
    );
}

bool DSU::join(int a, int b) {
    a = find(a);
    b = find(b);
    if (a == b)
        return false;
    if (size[a] < size[b]) 
        std::swap(a, b);
    parent[b] = a;
    size[a] += size[b];

    for (auto p : color[b]) color[a][p.first] += p.second;
    color[b].clear();
}

int DSU::query(int v, int c) {
    v = find(v);
    return 
        color[v].count(c)
        ? color[v][c] 
        : 0;
}