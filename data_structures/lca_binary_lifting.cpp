/*
 * =====================================================================================
 * Algorithm:   Lowest Common Ancestor (LCA) with Binary Lifting
 * Description: Finds the lowest common ancestor of any two nodes u and v in a tree.
 * Binary lifting precomputes 2^i-th ancestors for each node.
 * =====================================================================================
 * * Time Complexity:
 * - Preprocessing (DFS): O(N * log N)
 * - Per Query (lca):    O(log N)
 * * Space Complexity: O(N * log N) for the 'up' table.
 * * =====================================================================================
 * * Prerequisites:
 * 1. An adjacency list 'adj' representing the tree.
 * 2. Global constants MAXN and LOGN must be set appropriately.
 * 3. Resize 'adj' and 'depth' vectors to N+1.
 * 4. Call the preprocessing function 'dfs(root, root)' once before any lca queries.
 * The parent of the root should be the root itself.
 * * =====================================================================================
 * * Functions:
 * - dfs(node, parent):   Performs DFS from the root to compute depths and the 'up' table.
 * - lca(u, v):           Returns the LCA of nodes u and v.
 * * =====================================================================================
 */

#include <bits/stdc++.h>

// Set constants based on problem constraints
const int MAXN = 200001;
const int LOGN = 18; // ceil(log2(MAXN)) is a safe value

std::vector<int> adj[MAXN];
int up[MAXN][LOGN];
int depth[MAXN];

// Preprocessing function to compute depth and build the 'up' table
void dfs(int node, int par, int d = 0) {
    depth[node] = d;
    up[node][0] = par;

    // Dynamic Programming to build the binary lifting table
    // up[node][i] is the 2^i-th ancestor of 'node'
    for (int i = 1; i < LOGN; ++i) {
        up[node][i] = up[up[node][i - 1]][i - 1];
    }

    for (int child : adj[node]) {
        if (child != par) {
            dfs(child, node, d + 1);
        }
    }
}

// Function to find the LCA of nodes u and v
int lca(int u, int v) {
    // Ensure u is the deeper node
    if (depth[u] < depth[v]) {
        std::swap(u, v);
    }

    // 1. Bring u to the same depth as v
    // We jump u up by 2^i steps until it's at the same level as v
    for (int i = LOGN - 1; i >= 0; --i) {
        if (depth[u] - (1 << i) >= depth[v]) {
            u = up[u][i];
        }
    }

    // If v was an ancestor of u, then u is now v
    if (u == v) {
        return u;
    }

    // 2. Lift u and v simultaneously until their parents are the same
    // We are looking for the highest ancestors of u and v that are NOT the same.
    for (int i = LOGN - 1; i >= 0; --i) {
        if (up[u][i] != up[v][i]) {
            u = up[u][i];
            v = up[v][i];
        }
    }

    // The LCA is the direct parent of the final u and v.
    return up[u][0];
}

/**
 * =====================================================================================
 * How to Use:
 * =====================================================================================
 */
int main() {
    // Fast I/O
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n, q; // Number of nodes and queries
    std::cin >> n >> q;

    // Read tree edges (assuming 1-based indexing)
    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        std::cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // --- Preprocessing Step ---
    // Call DFS from the root. Let's assume root is 1.
    // The parent of the root is the root itself.
    dfs(1, 1);

    // --- Process Queries ---
    for (int i = 0; i < q; ++i) {
        int u, v;
        std::cin >> u >> v;
        std::cout << lca(u, v) << "\n";
    }

    return 0;
}