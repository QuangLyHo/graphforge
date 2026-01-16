#include <cassert>
#include <iostream>
#include <vector>
#include <string>

#include "graphforge/io/parser.hpp"
#include "graphforge/util/path.hpp"
#include "graphforge/algo/bfs.hpp"

int main(int argc, char** argv) {
    // load file from CLI
    if (argc < 2) {
        std::cerr << "Usage: test_bfs <graph_file>\n";
        return 1;
    }

    auto g = graphforge::io::parse_edge_list_undirected(argv[1]);
    // run BFS from source 0
    auto res = graphforge::alg::bfs(g, 0);

    // expected distances from node 0 in tiny.txt:
    // 0:0, 1:1, 2:1, 3:2, 4:2
    assert(res.distance.size() == g.num_vertices());
    assert(res.distance[0] == 0);
    assert(res.distance[1] == 1);
    assert(res.distance[2] == 1);
    assert(res.distance[3] == 2);
    assert(res.distance[4] == 2);

    // path reconstruction check: shortest path 0 -> 4 should have 3 nodes.
    // it can be 0->1->4 OR 0->2->3->4 depending on adjacency order,
    // so we can check correctness by: 
    // - starts with 0
    // - ends at 4
    // - length is distance + 1
    auto path = graphforge::util::reconstruct_path(0, 4, res.parent);
    assert(!path.empty());
    assert(path.front() == 0);
    assert(path.back() == 4);
    assert(static_cast<int>(path.size()) == res.distance[4] + 1);

    std::cout << "test_bfs passed\n";
    return 0;
}