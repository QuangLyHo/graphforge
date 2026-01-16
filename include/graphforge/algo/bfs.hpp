#pragma once

#include "graphforge/types.hpp"
#include "graphforge/adjacency_list.hpp"
#include <queue>

namespace graphforge::alg {

// 01/01/2026
// static constexpr VertexId kInvalidVertex = static_cast<VertexId>(-1);

struct BFSResult {
    std::vector<VertexId> order; //visitation order
    std::vector<int> distance; //distance from source
    std::vector<VertexId> parent;   //parent in BFS Tree, kInvalidVertex if none
};

inline BFSResult bfs(const AdjListGraph& g, VertexId source) {
    const size_t n = g.num_vertices();

    BFSResult result;
    result.distance.assign(n, -1); // -1, not visited
    result.parent.assign(n, kInvalidVertex);
    result.order.clear();
    result.order.reserve(n);

    if (n == 0) return result;
    if (source >= n) return result;

    std::queue<VertexId> q;

    result.distance[source] = 0;
    result.parent[source] = kInvalidVertex;
    q.push(source);

    while (!q.empty()) {
        auto u = q.front();
        q.pop();

        result.order.push_back(u);

        for (const auto& e : g.neighbors(u)) {
            auto v = e.to;

            if (result.distance[v] == -1) { //unvisited
                result.distance[v] = result.distance[u] + 1;
                result.parent[v] = u;
                q.push(v);
            }
        }
    }

    return result;
}

} // namespace graphforge::alg

