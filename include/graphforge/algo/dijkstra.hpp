#pragma once

#include <vector>
#include <queue>
#include <limits>
#include <utility>

#include "graphforge/types.hpp"
#include "graphforge/adjacency_list.hpp"

namespace graphforge::alg {
struct DijkstraResult {
    std::vector<double> dist; // INF = unreachable
    std::vector<VertexId> parent; // for path reconstruction
};

inline DijkstraResult dijkstra(const graphforge::AdjListGraph& g,
                                 VertexId source) 
{
    const size_t n = g.num_vertices();
    const double INF = std::numeric_limits<double>::infinity();

    DijkstraResult res;
    res.dist.assign(n, INF);
    res.parent.assign(n, kInvalidVertex);

    if (n == 0) return res;
    if (source >= n) return res;

    using Item = std::pair<double, VertexId>; // (dist, vertex)
    // min-heap priority queue
    std::priority_queue<Item, std::vector<Item>, std::greater<Item>> pqueue;

    res.dist[source] = 0;
    pqueue.push({0.0, source});

    while (!pqueue.empty()) {
        auto [d, u] = pqueue.top();
        pqueue.pop();

        if (d != res.dist[u]) continue;

        for (const auto& e : g.neighbors(u)) {
            const auto v = e.to;
            const double nd = d + e.weight;

            if (nd < res.dist[v]) {
                res.dist[v] = nd;
                res.parent[v] = u;
                pqueue.push({nd, v});
            }
        }
    }

    return res;
}

}// namespace graphforge::alg