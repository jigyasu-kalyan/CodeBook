/**
 * =================================================================
 * Segment Tree (Generic, Point Update)
 * =================================================================
 *
 * Description:
 * A data structure for efficient range queries and point updates.
 * It's generic and can be adapted for sum, min, max, gcd, xor, etc.
 * This is the foundational version without lazy propagation.
 *
 * Complexity:
 * - Build: O(N)
 * - Range Query: O(log N)
 * - Point Update: O(log N)
 * - Space: O(4*N)
 *
 * How to Adapt for Different Problems:
 * 1.  Change the `IDENTITY` value. This is the value that doesn't affect
 * the merge operation (e.g., 0 for sum, infinity for min).
 * 2.  Change the `merge` function logic (e.g., use `a + b` for sum,
 * `std::min(a, b)` for min).
 *
 */

#include <bits/stdc++.h>

// The `long long` type can be changed to `int` or another type if needed.
using T = long long;

struct SegTree {
    int n;
    std::vector<T> t;

    // =========== MODIFY THESE TWO LINES FOR THE PROBLEM ===========
    const T IDENTITY = 0; // For sum. For min, use a large value (LLONG_MAX).
    T merge(T a, T b) {
        return a + b; // For sum. For min, use std::min(a, b).
    }
    // =================================================================

    // Constructor to build from a vector
    SegTree(const std::vector<int>& a) {
        n = a.size();
        t.resize(4 * n);
        build(a, 1, 0, n - 1);
    }

    // --- Private Helper Functions (the "engine") ---
private:
    void build(const std::vector<int>& a, int v, int tl, int tr) {
        if (tl == tr) {
            t[v] = a[tl];
        } else {
            int tm = tl + (tr - tl) / 2; // Avoids overflow
            build(a, v * 2, tl, tm);
            build(a, v * 2 + 1, tm + 1, tr);
            t[v] = merge(t[v * 2], t[v * 2 + 1]);
        }
    }

    T query_recursive(int v, int tl, int tr, int l, int r) {
        if (l > r) {
            return IDENTITY;
        }
        if (l == tl && r == tr) {
            return t[v];
        }
        int tm = tl + (tr - tl) / 2;
        T left_res = query_recursive(v * 2, tl, tm, l, std::min(r, tm));
        T right_res = query_recursive(v * 2 + 1, tm + 1, tr, std::max(l, tm + 1), r);
        return merge(left_res, right_res);
    }

    void update_recursive(int v, int tl, int tr, int pos, T new_val) {
        if (tl == tr) {
            t[v] = new_val;
        } else {
            int tm = tl + (tr - tl) / 2;
            if (pos <= tm) {
                update_recursive(v * 2, tl, tm, pos, new_val);
            } else {
                update_recursive(v * 2 + 1, tm + 1, tr, pos, new_val);
            }
            t[v] = merge(t[v * 2], t[v * 2 + 1]);
        }
    }

    // --- Public Functions (the "steering wheel") ---
public:
    // Query for a range [l, r]
    T query(int l, int r) {
        return query_recursive(1, 0, n - 1, l, r);
    }

    // Update a single position `pos` to `new_val`
    void update(int pos, T new_val) {
        update_recursive(1, 0, n - 1, pos, new_val);
    }
};

// --- Example Usage ---
// #include <iostream>
// int main() {
//     std::vector<int> initial_array = {1, 2, 3, 4, 5};
//     SegTree st(initial_array);
//
//      Query sum of range [1, 3] (should be 2+3+4 = 9)
//     std::cout << "Sum of [1, 3]: " << st.query(1, 3) << std::endl;
//
//      Update position 2 to value 10
//     st.update(2, 10);
//
//      Query sum of range [1, 3] again. New array is {1, 2, 10, 4, 5}
//      New sum should be 2 + 10 + 4 = 16
//     std::cout << "New sum of [1, 3]: " << st.query(1, 3) << std::endl;
// }