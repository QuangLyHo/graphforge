#pragma once
#include <cstdint>

using VertexId = uint32_t;

// Represents 'no parent" or invalid marker.
static constexpr VertexId kInvalidVertex = static_cast<VertexId>(-1);

struct Edge {
    VertexId to;
};