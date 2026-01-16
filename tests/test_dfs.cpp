#include <cassert>
#include <iostream>

#include "graphforge/io/parser.hpp"
#include "graphforge/algo/dfs.hpp"
#include "graphforge/util/path.hpp"
#include "graphforge/types.hpp"

//1/16/26
int main(int argc, char** argv) {
    if (argc < 2) {
        std::cerr << "Usage: test_dfs <graph_file>\n";
        return 1;
    }
    
    auto g = graphforge::io::parse_edge_list_undirected(argv[1]);
    auto res = graphforge::alg::dfs(g, 0);

    // DFS should visit all nodes in this connected tiny graph.
    assert(res.preorder.size() == g.num_vertices());

    // Parent for source should be invalid
    assert(res.parent[0] == kInvalidVertex ||
           res.parent[0] == static_cast<VertexId>(-1));

    // Path reconstruction using DFS parents yield *a* valid path tree path
    // from 0 to 4 (not necessarily shortest).
    auto path = graphforge::util::reconstruct_path(0, 4, res.parent);
    assert(!path.empty());
    assert(path.front() == 0);
    assert(path.back() == 4);

    std::cout << "test_dfs passed\n";
    return 0;
}