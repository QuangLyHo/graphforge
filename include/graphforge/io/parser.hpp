#pragma once
#include <stdexcept>
#include <string>
#include <fstream>
#include <cstdint>
#include <sstream>
#include <utility>

#include "graphforge/types.hpp"
#include "graphforge/adjacency_list.hpp"

namespace graphforge::io {

struct ParseError : std::runtime_error {
    using std::runtime_error::runtime_error;
};

inline std::pair<size_t, size_t> parse_header_or_throw(const std::string& line) {
    std::istringstream iss(line);
    long long n = -1, m = -1;
    if (!(iss >> n >> m)) {
        throw ParseError("Invalid header. Expected: `n m` on the first line.");
    }
    if (n < 0 || m < 0) {
        throw ParseError("Invalid header. `n` and `m` must be non-negative.");
    }
    return {static_cast<size_t>(n), static_cast<size_t>(m)};
}

inline void validate_vertex_or_throw(long long v, size_t n, size_t line_no) {
    if (v < 0) {
        throw ParseError("Line " + std::to_string(line_no) + ": vertex id cannot be negative.");
    }
    if (static_cast<size_t>(v) >= n) {
        throw ParseError("Line " + std::to_string(line_no) + 
                         ": vertex id " + std::to_string(v) +
                         " is out of range [0, " + std::to_string(n ? n - 1 : 0) + "].");
    }
}

// Parses an undirected, unweighted edge-list file:
// line 1: n m
// next m lines: u v
inline AdjListGraph parse_edge_list_undirected(const std::string& path) {
    std::ifstream in(path); 
    if (!in.is_open()) {
        throw ParseError("Could not open file: " + path);
    }

    std::string line;

    // -- Read header (first non-empty, non-comment line)
    size_t line_no = 0;
    size_t n = 0, m = 0;

    while (std::getline(in, line)) {
        ++line_no;

        //allow comments and blank lines
        auto pos = line.find_first_not_of(" \t\r\n");
        if (pos == std::string::npos) continue;
        if (line[pos] == '#') continue;

        auto [nn, mm] = parse_header_or_throw(line);
        n = nn;
        m = mm;
        break;
    }

    if (line_no == 0 || (n == 0 && m > 0)) {
        // If file was empty, line_no would still be 0; if n==0 but m>0 it's invalid
        if (line_no == 0) 
            throw ParseError("Empty file: " + path);
        throw ParseError("Header invalid: n=0 but m>0.");
    }

    AdjListGraph g(n);

    // --- Read edges ---
    size_t edges_read = 0;
    while (edges_read < m && std::getline(in, line)) {
        ++line_no;

        auto pos = line.find_first_not_of(" \t\r\n");
        if (pos == std::string::npos) continue; // skips blank
        if (line[pos] == '#') continue; // skips comment

        std::istringstream iss(line);
        long long u = -1, v = -1;
        if (!(iss >> u >> v)) {
            throw ParseError("Line " + std::to_string(line_no) +
                             ": invalid edge. Expected: `u v`.");
        }

        validate_vertex_or_throw(u, n, line_no);
        validate_vertex_or_throw(v, n, line_no);

        //undirected
        g.add_edge(static_cast<VertexId>(u), static_cast<VertexId>(v));
        g.add_edge(static_cast<VertexId>(v), static_cast<VertexId>(u));

        ++edges_read;
    }//end while

    if (edges_read != m) {
        throw ParseError("Expected " + std::to_string(m) +
                         " edges but only found " + std::to_string(edges_read) + ".");
    }

    return g;
}//end parse_edge_list_undirected
}//namespace graphforge::io