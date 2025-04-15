#include <bits/stdc++.h>

class DisjointSet {
private:
    std::vector<int> parent;
public:
    void init(int);
    int find(int);
    bool join(int, int);
    bool sameSet(int, int);
};

void DisjointSet::init(int n) {
    parent.assign(n, 0);
    for (int i = 0; i < n; i += 1) {
        parent[i] = i;
    }
}

void DisjointSet::init(int n) {
    parent.assign(n, 0);
    std::iota(parent.begin(), parent.end(), 0);
}

int DisjointSet::find(int u) {
    return (u == parent[u] ? u : find(parent[u]));
}

int DisjointSet::find(int u) {
    int root = u;
    while (parent[root] != root) {
        root = parent[root];
    }
    return root;
}

bool DisjointSet::sameSet(int u, int v) {
    return find(u) == find(v);
}

// Since that in C++ union is a keyword, so we will use join instead of union
bool DisjointSet::join(int u, int v) {
    u = find(u);
    v = find(v);
    if (u == v)
        return false;
    parent[u] = v;
    return true;
}