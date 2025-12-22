#pragma once

#include <cstddef>
#include "types.hpp"
#include <vector>
#include <string>

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

    void add_edge(VertexId u, VertexId v) {
        validate_vertex(u);
        validate_vertex(v);
        adj_[u].push_back(Edge{v});
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
