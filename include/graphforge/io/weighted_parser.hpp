#pragma once

#include <fstream>
#include <cstddef>
#include <string>
#include <sstream>

#include "graphforge/types.hpp"
#include "graphforge/adjacency_list.hpp"
#include "graphforge/io/parser.hpp" // for parse error

// 1/20/2026
namespace graphforge::io {

//  Parses an undirected edge-list file that may be weighted.
//  Header: n m
//  Edge lines: u v w (w is required for this function)
inline graphforge::AdjListGraph parse_edge_list_undirected_weighted(const std::string& path) {
    std::ifstream in(path);
    if (!in.is_open()) throw ParseError("Could not open file: " + path);

    std::string line;
    size_t line_no = 0;

    // header
    size_t n = 0, m = 0;
    while (std::getline(in, line)) {
        ++line_no;
        auto pos = line.find_first_not_of(" \t\r\n");
        if (pos == std::string::npos) continue;
        if (line[pos] == '#') continue;

        auto [nn, mm] = parse_header_or_throw(line); // from parser.hpp
        n = nn, m = mm;
        break;
    }

    graphforge::AdjListGraph g(n);

    size_t edges_read = 0;
    while (edges_read < m && std::getline(in, line)) {
        ++line_no;
        auto pos = line.find_first_not_of(" \t\r\n");
        if (pos == std::string::npos) continue;
        if (line[pos] == '#') continue;

        std::istringstream iss(line);
        long long u = -1, v = -1;
        double w = 0.0;

        if (!(iss >> u >> v >> w)) {
            throw ParseError("Line " + std::to_string(line_no) + ": expected `u v w`.");
        }

        validate_vertex_or_throw(u, n, line_no);
        validate_vertex_or_throw(v, n, line_no);

        if (w < 0) {
            throw ParseError("Line " + std::to_string(line_no) + ": Djikstra's requires non-negative weights.");
        }

        g.add_edge( static_cast<VertexId>(u),
                    static_cast<VertexId>(v),
                    static_cast<Weight>(w) );

        g.add_edge( static_cast<VertexId>(v), 
                    static_cast<VertexId>(u), 
                    static_cast<Weight>(w) );

        ++edges_read;
    }

    if (edges_read != m) {
        throw ParseError("Expected " + std::to_string(m) + 
                         " edges but found " + std::to_string(edges_read) + ".");
    }

    return g;
}

} // namespace graphforge::io

