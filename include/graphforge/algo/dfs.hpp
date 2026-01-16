#pragma once

#include "graphforge/types.hpp"
#include "graphforge/adjacency_list.hpp"

// 01/07/26
namespace graphforge::alg{

struct DFSResult {
    std::vector<VertexId> preorder; // visitation order when discovered
    std::vector<uint8_t> visited; // 0/1 visited flag
    std::vector<VertexId> parent; // parent in DFS Tree, kInvalidVertex if none
};

namespace detail {
inline void dfs_visit(const AdjListGraph& g, VertexId u, DFSResult& res) {
    res.visited[u] = 1;
    res.preorder.push_back(u);

    for (const auto& e : g.neighbors(u)) {
        const auto v = e.to;
        if (!res.visited[v]) {
            res.parent[v] = u;
            dfs_visit(g, v, res);
        }
    }
}
}// namespace detail

inline DFSResult dfs(const AdjListGraph& g, VertexId source) {
    const size_t n = g.num_vertices();

    DFSResult res;
    res.preorder.clear();
    res.preorder.reserve(n);
    res.parent.assign(n, kInvalidVertex);
    res.visited.assign(n, 0);

    if (n == 0) return res;
    if (source >= n) return res; 

    detail::dfs_visit(g, source, res);
    return res;
}

} // end namespace graphforge::alg
