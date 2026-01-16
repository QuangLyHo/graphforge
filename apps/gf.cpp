#include <iostream>
#include <string>

#include "graphforge/io/parser.hpp"
#include "graphforge/algo/bfs.hpp"
// 01/16/26
#include "graphforge/algo/dfs.hpp"
// 01/01/26
#include "graphforge/util/path.hpp"

int main(int argc, char** argv) {
    // 01/16/2026
    // if (argc < 3) {
    //     std::cerr << "Usage: gf <graph_file> <source>\n";
    //     std::cerr << "Example: gf graphs/tiny.txt 0\n";
    //     std::cerr << "Example: gf graphs/tiny.txt 0 3\n";
    //     return 1;
    if (argc < 4) {
        std::cerr << "Usage: gf <bfs|dfs> <graph_file> <source> [target]\n";
        std::cerr << "Example: gf bfs graphs/tiny.txt 0\n";
        std::cerr << "Example: gf bfs graphs/tiny.txt 0 3\n";
        std::cerr << "Example: gf dfs graphs/tiny.txt 0 3\n";
        return 1;
    }

    // 1/16/26
    //12/31/2025
    // const std::string path = argv[1];
    // const int source_int = std::stoi(argv[2]); 
    const std::string command = argv[1];
    const std::string path = argv[2];
    const int source_int = std::stoi(argv[3]);


    if (source_int < 0) {
        std::cerr << "Error: source must be >= 0\n";
        return 2;
    }

    // 01/01/2026
    // const bool has_target = (argc >= 4);
    // 01/16/2026
    const bool has_target = (argc >= 5);
    int target_int = -1;

    if (has_target) {
        //01/16/26
        // target_int = std::stoi(argv[3]);
        target_int = std::stoi(argv[4]);
        if (target_int < 0) {
            std::cerr << "Error: target must be >= 0\n";
            return 2;
        }
    }

    try {
        auto g = graphforge::io::parse_edge_list_undirected(path);

        // 01/01/2026
        auto source = static_cast<VertexId> (source_int);
        // 12/31/2025
        // auto res = graphforge::alg::bfs(g, static_cast<VertexId>(source_int));
        if (source >= g.num_vertices()) {
            std::cerr << "Error: source " << source << " is out of range.\n";
            return 2;
        }
        //1/16/26
        if (command == "bfs") {
            auto res = graphforge::alg::bfs(g, source);

            std::cout << "Loaded graph with " << g.num_vertices() << " vertices\n";
            std::cout << "BFS order: ";

            for (auto v : res.order) std::cout << v << " ";
            std::cout << std::endl;

            std::cout << "Distances:\n";
            for (VertexId v = 0; v < g.num_vertices(); v++) {
                std::cout << v << ": " << res.distance[v] << "\n";
            }
                    // 01/01/2026
                    //1/16/26
            if (has_target) {
                auto target = static_cast<VertexId> (target_int);

                if (target >= g.num_vertices()) {
                    std::cout << "No path from " << source << " to " << target << "\n";
                }
                else {
                    auto path_vec = graphforge::util::reconstruct_path(source, target, res.parent);

                    std::cout << "Path " << source << " -> " << target << ": ";
                    for (size_t i = 0; i < path_vec.size(); ++i) {
                        std::cout << path_vec[i];
                        if (i + 1 < path_vec.size()) std::cout << " -> ";
                    }

                    std::cout << "\n";
                }
            }
        }
        else if (command == "dfs") {
            auto res = graphforge::alg::dfs(g, source);

            std::cout << "Loaded graph with " << g.num_vertices() << " vertices\n";
            std::cout << "DFS preorder: ";

            for (auto v : res.preorder) std::cout << v << " ";
            std::cout << "\n";

            if (has_target) {
                auto target = static_cast<VertexId> (target_int);

                if (target >= g.num_vertices()) {
                    std::cout << "No path from " << source << " to " << target << "\n";
                }
                else {
                    auto path_vec = graphforge::util::reconstruct_path(source, target, res.parent);

                    std::cout << "Path " << source << " -> " << target << ": ";
                    for (size_t i = 0; i < path_vec.size(); ++i) {
                        std::cout << path_vec[i];
                        if (i + 1 < path_vec.size()) std::cout << " -> ";
                    }

                    std::cout << "\n";
                }
            }
        } 
        else {
            std::cerr << "Error: unknown command `" << command << "`. Use bfs or dfs.\n";
            return 2;
        }




        //12/21/2025
        // for (VertexId u = 0; u < g.num_vertices(); ++u) {
        //     std::cout << u << ": ";
        //     for (const auto& e : g.neighbors(u)) {
        //         std::cout << e.to << " ";
        //     }
        //     std::cout << std::endl;
        // }
    } 
    catch (const std::exception& ex) {
        std::cerr << "Error: " << ex.what() << "\n";
        return 3;
    }

    return 0;
}