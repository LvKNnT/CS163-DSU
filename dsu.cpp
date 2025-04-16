#include <atcoder/dsu.hpp>
using namespace atcoder;

int main() {
    dsu uf(10); // Create a DSU with 10 elements (0 to 9)

    uf.merge(1, 2);     // Union sets containing 1 and 2
    uf.merge(2, 3);     // Union sets containing 2 and 3

    bool connected = uf.same(1, 3); // Check if 1 and 3 are in the same set
    int leader = uf.leader(2);      // Get the representative of the set containing 2

    auto groups = uf.groups();      // Get all connected components
}