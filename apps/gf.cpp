#include <iostream>
#include "graphforge/io/parser.hpp"

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cerr << "Usage: gf <graph_file>\n";
        return 1;
    }
    try {
        auto g = graphforge::io::parse_edge_list_undirected(argv[1]);

        std::cout<< "Loaded graph with " << g.num_vertices() << " vertices\n";
        for (VertexId u = 0; u < g.num_vertices(); ++u) {
            std::cout << u << ": ";
            for (const auto& e : g.neighbors(u)) {
                std::cout << e.to << " ";
            }
            std::cout << std::endl;
        }
    } 
    catch (const std::exception& ex) {
        std::cerr << "Error: " << ex.what() << "\n";
        return 2;
    }

    return 0;
}