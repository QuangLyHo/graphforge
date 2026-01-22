#include <cassert>
#include <cmath>
#include <iostream>

#include "graphforge/io/weighted_parser.hpp"
#include "graphforge/algo/dijkstra.hpp"
#include "graphforge/util/path.hpp"

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cerr << "Usage: test_dijkstra <graph_file>\n";
        return 1;
    }

    auto g = graphforge::io::parse_edge_list_undirected_weighted(argv[1]);
    auto res = graphforge::alg::dijkstra(g, 0);

    // target 4 should be reachable with cost 4
    assert(std::isfinite(res.dist[4]));   
    assert(std::fabs(res.dist[4] - 4.0) < 1e-9);

    auto path = graphforge::util::reconstruct_path(0, 4, res.parent);
    assert(!path.empty());   
    assert(path.front() == 0);   
    assert(path.back() == 4);

    std::cout << "test_dijkstra passed.\n";
    return 0;
}