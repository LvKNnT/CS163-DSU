#include <bits/stdc++.h>

class DisjointSet {
private:
    std::vector<int> parent;
    std::vector<int> rank;
    // std::vector<int> size;
public:
    void init(int);
    int find(int);
    bool join(int, int);
    bool sameSet(int, int);
};

int DisjointSet::find(int u) {
    return parent[u] = (u == parent[u] ? u : find(parent[u]));
}

void DisjointSet::init(int N) {
    // The original code
    rank.assign(N, 0);
}

bool DisjointSet::join(int u, int v) {
    u = find(u);
    v = find(v);
    if (u == v)
        return false;
    if (rank[u] > rank[v])
        std::swap(u, v);
    parent[u] = v;
    if (rank[u] == rank[v])
        rank[v] += 1;
    return true;
}

/*
void DisjointSet::init(int N) {
    // The original code
    size.assign(N, 1);
}

bool DisjointSet::join(int u, int v) {
    u = find(u);
    v = find(v);
    if (u == v)
    return false;
    if (size[u] > size[v])
    std::swap(u, v);
    parent[u] = v;
    size[v] += size[u];
    return true;
}
*/