#pragma once

#include <cstddef>
#include <vector>
#include <string>

#include "types.hpp"

namespace graphforge {

class AdjListGraph
{
private:
    std::vector<std::vector<Edge>> adj_;

    void validate_vertex(VertexId u) const {
        if (u >= adj_.size()) {
            throw std::out_of_range(
                "Vertex id " + std::to_string(u) + 
                " is out of range [0, " + 
                std::to_string(adj_.size() ? adj_.size() - 1 : 0) + "]"
            );
        }
    }
public:
    explicit AdjListGraph(size_t num_vertices) : adj_(num_vertices) {}
    
    // 1/20/2026 (added Weight w as parameter)
    void add_edge(VertexId u, VertexId v, Weight w = 1.0) {
        validate_vertex(u);
        validate_vertex(v);
        adj_[u].push_back(Edge{v, w});
    }

    const std::vector<Edge>& neighbors(VertexId u) const {
        validate_vertex(u);
        return adj_[u];
    }

    size_t num_vertices() const noexcept {
        return adj_.size();
    }
}; 

}// namespace graphforge
