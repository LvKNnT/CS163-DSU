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
	int getSum(int);
	int getMin(int);
	int getMax(int);
};

void DisjointSet::init(int n, std::vector<int> value) {
	parent.assign(n, 0);
	std::iota(parent.begin(), parent.end(), 0);
	size.assign(n, 1);
	sum = maxValue = minValue = value;
}

int DisjointSet::find(int u) {
	return parent[u] = (u == parent[u] ? u : find(parent[u]));
}

bool DisjointSet::sameSet(int u, int v) {
	return find(u) == find(v);
}

bool DisjointSet::join(int u, int v) {
	u = find(u);
	v = find(v);
	if (u == v)
		return false;
	if (size[u] > size[v])
		std::swap(u, v);
	parent[u] = v;
	sum[v] += sum[u];
	maxValue[v] = std::max(maxValue[v], maxValue[u]);
	minValue[v] = std::min(minValue[v], minValue[u]);
	return true;
}

int DisjointSet::getSum(int u) {
	return sum[find(u)];
}

int DisjointSet::getMin(int u) {
	return minValue[find(u)];
}

int DisjointSet::getMax(int u) {
	return maxValue[find(u)];
}

int main(void) {
	DisjointSet a;
	a.init(5, std::vector<int>{1, 2, 3, 4, 5});
	a.join(0, 3);
	a.join(2, 3);
	std::cout << a.sameSet(0, 2) << std::endl;
	std::cout << a.getMin(2) << std::endl;
	std::cout << a.getMax(2) << std::endl;
	std::cout << a.getSum(2) << std::endl;
	return 0;
}
