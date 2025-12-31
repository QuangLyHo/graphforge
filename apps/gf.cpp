#include <iostream>
#include <string>

#include "graphforge/io/parser.hpp"
#include "graphforge/algo/bfs.hpp"

int main(int argc, char** argv) {    
    if (argc < 3) {
        std::cerr << "Usage: gf <graph_file> <source>\n";
        std::cerr << "Example: gf graphs/tiny.txt 0\n";
        return 1;
    }

    //12/31/2025
    const std::string path = argv[1];
    const int source_int = std::stoi(argv[2]); 

    if (source_int < 0) {
        std::cerr << "Error: source must be >= 0\n";
        return 2;
    }

    try {
        auto g = graphforge::io::parse_edge_list_undirected(path);

        //12/31/2025
        auto res = graphforge::alg::bfs(g, static_cast<VertexId>(source_int));

        
        std::cout << "Loaded graph with " << g.num_vertices() << " vertices\n";
        std::cout << "BFS order: ";

        for (auto v : res.order) std::cout << v << " ";
        std::cout << std::endl;

        std::cout << "Distances:\n";
        for (VertexId v = 0; v < g.num_vertices(); v++) {
            std::cout << v << ": " << res.distance[v] << "\n";
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