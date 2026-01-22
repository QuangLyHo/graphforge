#include <iostream>
#include <string>

#include "graphforge/io/parser.hpp"
#include "graphforge/algo/bfs.hpp"
// 01/16/26
#include "graphforge/algo/dfs.hpp"
// 01/01/26
#include "graphforge/util/path.hpp"
// 01/20/26
#include "graphforge/algo/dijkstra.hpp"
#include "graphforge/io/weighted_parser.hpp"
#include <cmath>

int main(int argc, char** argv) {
    // 01/16/2026
    if (argc < 4) {
        std::cerr << "Usage: gf <bfs|dfs|dijkstra> <graph_file> <source> [target]\n";
        std::cerr << "Examples\n";
        std::cerr << "gf bfs graphs/tiny.txt 0\n";
        std::cerr << "gf bfs graphs/tiny.txt 0 3\n";
        std::cerr << "gf dfs graphs/tiny.txt 0 3\n";
        // 01/20/2026
        std::cerr << "gf dijkstra graphs/weighted_tiny.txt 0 4\n";
        return 1;
    }

    // 1/16/26
    const std::string command = argv[1];
    const std::string path = argv[2];
    const int source_int = std::stoi(argv[3]);


    if (source_int < 0) {
        std::cerr << "Error: source must be >= 0\n";
        return 2;
    }

    // 01/01/2026
    const bool has_target = (argc >= 5);
    int target_int = -1;

    if (has_target) {
        target_int = std::stoi(argv[4]);
        if (target_int < 0) {
            std::cerr << "Error: target must be >= 0\n";
            return 2;
        }
    }

    try {
        // 01/01/2026
        auto source = static_cast<VertexId> (source_int);
        
        // 01/20/2026
        if (command == "dijkstra") {
            // Parse weighted graph for Dijkstra
            auto g = graphforge::io::parse_edge_list_undirected_weighted(path);

            if (source >= g.num_vertices()) {
                std::cerr << "Error: source " << source << " is out of range.\n";
                return 2;
            }

            auto res = graphforge::alg::dijkstra(g, source);

            std::cout << "Loaded graph with " << g.num_vertices() << " vertices.\n";
            std::cout << "Dijkstra distances (cost):\n";
            for (VertexId v = 0; v < g.num_vertices(); v++) {
                if (std::isfinite(res.dist[v])) {
                    std::cout << v << ": " << res.dist[v] << "\n";
                }
                else {
                    std::cout << v << ": INF\n";
                }
            }

            if (has_target) {
                const auto target = static_cast<VertexId>(target_int);

                if (target >= g.num_vertices()) {
                    std::cout << "Target " << target << " is out of range.\n";
                }
                else if (!std::isfinite(res.dist[target])) {
                    std::cout << "No path from " << source << " to " << target << ".\n";
                }
                else {
                    auto path_vec = graphforge::util::reconstruct_path(source, target, res.parent);
                    std::cout << "Path " << source << " -> " << target << ": ";
                    for (size_t i = 0; i < path_vec.size(); i++) {
                        std::cout << path_vec[i];
                        if (i + 1 < path_vec.size()) std::cout << " -> ";
                    }
                    std::cout << "\n";
                    std::cout << "Total cost: " << res.dist[target] << "\n";
                }
            }

            return 0;
        }

        // bfs / dfs use the unweighted parser
        auto g = graphforge::io::parse_edge_list_undirected(path);

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

    } 
    catch (const std::exception& ex) {
        std::cerr << "Error: " << ex.what() << "\n";
        return 3;
    }

    return 0;
}