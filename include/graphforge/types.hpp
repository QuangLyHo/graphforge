#pragma once
#include <cstdint>

using VertexId = uint32_t;
// 1/20/2026
using Weight = double;

// Represents 'no parent" or invalid marker.
static constexpr VertexId kInvalidVertex = static_cast<VertexId>(-1);

struct Edge {
    VertexId to;
    // 1/20/2026
    Weight weight = 1.0; // default for unweighted graphs
};