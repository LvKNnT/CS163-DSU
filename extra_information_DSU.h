#include <bits/stdc++.h>

class DisjointSet {
private:
    std::vector<int> parent;
    std::vector<int> size;
    std::vector<int> sum;
    std::vector<int> maxValue;
    std::vector<int> minValue;

public:
    void init(int, std::vector<int>);
    int find(int);
    bool join(int, int);
    bool sameSet(int, int);
};

void DisjointSet::init(int n, std::vector<int> value) {
    parent.assign(n, 0);
    std::iota(parent.begin(), parent.end(), 0);
    size.assign(n, 1);
    sum = maxValue = minValue = value; 
}

// Find operation implementation

bool DisjointSet::join(int u, int v) {
    u = find(u);
    v = find(v);
    if (u == v)
        return false;
    if (size[u] > size[v])
        std::swap(u, v);
    parent[u] = v;
    sum[v] += sum[u];
    maxValue[v] = 
        std::max(
            maxValue[v], 
            maxValue[u]
        );
    minValue[v] = 
        std::min(
            minValue[v], 
            minValue[u]
        );
    return true;
}
