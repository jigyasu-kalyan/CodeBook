/**
 * =================================================================
 * Unified Graph Cycle Finder (Directed & Undirected)
 * =================================================================
 *
 * Description:
 * Finds a single cycle in a graph. It can be configured for either
 * directed or undirected graphs via a constructor flag.
 *
 * The logic uses a 3-color DFS. For the undirected case, it correctly
 * ignores the trivial 2-edge cycle back to the parent node.
 * Nodes are assumed to be 0-indexed.
 *
 * Complexity:
 * - Time: O(V + E)
 * - Space: O(V)
 *
 * =================================================================
 * HOW TO USE
 * =================================================================
 *
 * 1.  For a DIRECTED graph (default):
 * `CycleDetector detector(num_nodes);`
 *
 * 2.  For an UNDIRECTED graph:
 * `CycleDetector detector(num_nodes, true);`
 *
 * 3.  Add edges:
 * `detector.add_edge(u, v);`
 * (For undirected graphs, this automatically adds both u-v and v-u)
 *
 * 4.  Find a cycle:
 * `vector<int> cycle = detector.find_cycle();`
 *
 * 5.  Check if a cycle was found:
 * `if (cycle.empty()) { ... }`
 *
 */

#include <bits/stdc++.h>

struct CycleDetector {
    int n;
    bool is_undirected;
    std::vector<std::vector<int>> adj;
    std::vector<char> color; // 0: white, 1: gray, 2: black
    std::vector<int> parent;
    int cycle_start, cycle_end;

    // Constructor: specify if the graph is undirected
    CycleDetector(int num_nodes, bool undirected = false) : n(num_nodes), is_undirected(undirected) {
        adj.resize(n);
    }

    // Add an edge. For undirected, adds the reverse edge automatically.
    void add_edge(int u, int v) {
        adj[u].push_back(v);
        if (is_undirected) {
            adj[v].push_back(u);
        }
    }

private:
    // Internal DFS. `p` is the parent in the DFS tree.
    bool dfs(int v, int p) {
        color[v] = 1; // Mark as gray (visiting)
        parent[v] = p;

        for (int u : adj[v]) {
            // For undirected graphs, skip the edge back to the immediate parent
            if (is_undirected && u == p) {
                continue;
            }

            if (color[u] == 0) { // If neighbor is white (unvisited)
                if (dfs(u, v)) return true;
            } else if (color[u] == 1) { // Found a back edge to a gray node
                cycle_end = v;
                cycle_start = u;
                return true;
            }
        }
        color[v] = 2; // Mark as black (finished)
        return false;
    }

public:
    // Main method to find and return a cycle
    std::vector<int> find_cycle() {
        color.assign(n, 0);
        parent.assign(n, -1);
        cycle_start = -1;

        for (int v = 0; v < n; v++) {
            if (color[v] == 0 && dfs(v, -1)) {
                break;
            }
        }

        if (cycle_start == -1) {
            return {}; // No cycle found
        }

        std::vector<int> cycle;
        cycle.push_back(cycle_start);
        for (int v = cycle_end; v != cycle_start; v = parent[v]) {
            cycle.push_back(v);
        }
        cycle.push_back(cycle_start);
        std::reverse(cycle.begin(), cycle.end());

        return cycle;
    }
};