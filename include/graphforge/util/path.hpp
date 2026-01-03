#pragma once

#include <vector>
#include <algorithm>

#include "graphforge/types.hpp"

namespace graphforge::util {

// 01/01/2026
// // Represents 'no parent" or invalid marker.
// static constexpr VertexId kInvalidVertex = static_cast<VertexId>(-1);

// Reconstructs the path from `source` to `target` using a parent array.
// Returns empty vector if no path exists.
inline std::vector<VertexId> reconstruct_path(
    VertexId source,
    VertexId target, 
    const std::vector<VertexId>& parent) 
{
    std::vector<VertexId> path;

    // Basic bounds check
    if (source >= parent.size() || target >= parent.size()) return path;

    // Walk backwards from target to source using parent pointers
    VertexId cur = target;

    while (cur != kInvalidVertex) {
        path.push_back(cur);

        if (cur == source) break;
        cur = parent[cur];
    }

    // If we did not end at source, target was not reachable
    if (path.back() != source) return {};

    // Reverse to get source -> target
    std::reverse(path.begin(), path.end());
    return path;
}

} //namespace graphforge::util