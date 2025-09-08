/**
 * =====================================================================================
 * Data Structure: Disjoint Set Union (DSU) / Union-Find
 * Description:    Maintains a collection of disjoint sets and supports efficient
 * merging of sets and finding the representative of a set.
 * =====================================================================================
 * * Time Complexity: Nearly Constant Time on Average per operation - O(α(N))
 * - α(N) is the Inverse Ackermann function, which is < 5 for any practical N.
 * * Space Complexity: O(N) for the parent and size arrays.
 * * =====================================================================================
 * * Optimizations Used:
 * 1. Path Compression: In find_set, we make every node on the path point directly
 * to the root. This flattens the tree.
 * 2. Union by Size: When merging sets, we always attach the smaller tree to the
 * root of the larger tree. This keeps the trees from becoming too deep.
 * * =====================================================================================
 * * How to Use:
 * - `DSU dsu(n);`             // Create a DSU structure for n elements (0 to n-1).
 * - `dsu.find_set(i);`        // Returns the representative of the set containing i.
 * - `dsu.union_sets(i, j);`   // Merges the sets containing i and j.
 * - `dsu.size[dsu.find_set(i)];` // Gets the size of the set containing i.
 * =====================================================================================
 */
#include <bits/stdc++.h>

struct DSU {
    std::vector<int> parent;
    std::vector<int> sz; // 'sz' stores the size of each set

    // Constructor to initialize the DSU for 'n' elements
    DSU(int n) {
        parent.resize(n);
        // std::iota fills the vector with 0, 1, 2, ...
        std::iota(parent.begin(), parent.end(), 0); 
        sz.assign(n, 1); // Each set initially has size 1
    }

    // Find the representative of the set containing 'v' with path compression
    int find_set(int v) {
        if (v == parent[v])
            return v;
        return parent[v] = find_set(parent[v]);
    }

    // Union the sets containing 'a' and 'b' with union by size
    void union_sets(int a, int b) {
        a = find_set(a);
        b = find_set(b);
        if (a != b) {
            // Attach the smaller tree to the root of the larger tree
            if (sz[a] < sz[b])
                std::swap(a, b);
            parent[b] = a;
            sz[a] += sz[b]; // Update the size of the new merged set
        }
    }
};

// --- Example Usage ---

int main() {
    // Let's say we have 5 elements, numbered 0 to 4
    int n = 5;
    DSU dsu(n);

    // Elements are initially in their own sets: {0}, {1}, {2}, {3}, {4}
    std::cout << "Find(0) == Find(1)? " << (dsu.find_set(0) == dsu.find_set(1) ? "Yes" : "No") << std::endl;

    std::cout << "Union(0, 1)" << std::endl;
    dsu.union_sets(0, 1);
    std::cout << "Find(0) == Find(1)? " << (dsu.find_set(0) == dsu.find_set(1) ? "Yes" : "No") << std::endl;
    
    std::cout << "Union(2, 3)" << std::endl;
    dsu.union_sets(2, 3);
    std::cout << "Union(0, 2)" << std::endl;
    dsu.union_sets(0, 2);

    std::cout << "Find(1) == Find(3)? " << (dsu.find_set(1) == dsu.find_set(3) ? "Yes" : "No") << std::endl;
    
    int root = dsu.find_set(3);
    std::cout << "Size of the set containing 3 is: " << dsu.sz[root] << std::endl;

    return 0;
}