<!-- # graphforge

A modular graph algorithms engine written in modern C++.

## Current features
- Adjacency list graph representation
- Robust file parser for edge-list graphs
- CMake-based build system
- CLI tool for loading and inspecting graphs

## Build
```bash
cmake -S . -B build
cmake --build build
./build/gf graphs/tiny.txt -->
# graphforge

**graphforge** is a modular graph algorithms engine written in modern C++ (C++20).  
The project is designed with clean separation between graph storage, parsing, algorithms, and CLI tooling, and includes automated tests.

This is an incremental, engineering-focused project — not a single-file demo.

---

## Features (current)

### Graph representation
- Adjacency list–based graph structure
- Supports undirected, unweighted graphs (v1)
- Safe vertex validation and clear ownership

### File parsing
- Robust edge-list parser
- Validates input format and vertex bounds
- Clean error handling with descriptive messages

### Algorithms
- **Breadth-First Search (BFS)**
  - Computes shortest-path distances (unweighted)
  - Records parent pointers
  - Supports path reconstruction
- **Depth-First Search (DFS)**
  - Preorder traversal
  - Records DFS tree parents
  - Supports path reconstruction (not guaranteed shortest)

### Path reconstruction
- Reconstructs a path from source to target using parent arrays
- Shared utility reused across algorithms

### Command-line interface
Run algorithms directly from the CLI:
```bash
./build/gf bfs <graph_file> <source> [target]
./build/gf dfs <graph_file> <source> [target]
```
example
```
./build/gf bfs graphs/tiny.txt 0 4
./build/gf dfs graphs/tiny.txt 0 
```
### Automated testing
- Tests run via CTest
- Validates VFS distances and path reconstruction
- Validates DFS traversal and path correctness
- Tests are decoupled from working directory via CMake configuration

### Project structure
```
graphforge/
├── include/graphforge/
│   ├── alg/            # Graph algorithms (BFS, DFS)
│   ├── io/             # File parsing
│   ├── util/           # Shared utilities (path reconstruction)
│   ├── adjacency_list.hpp
│   └── types.hpp
├── apps/
│   └── gf.cpp          # CLI entry point
├── graphs/
│   └── tiny.txt        # Sample graph inputs
├── tests/
│   ├── test_bfs.cpp
│   └── test_dfs.cpp
├── CMakeLists.txt
└── README.md

```

### Build and run
#### Build
```
cmake -S . -B build
cmake --build build

```
#### Run
```
./build/gf bfs graphs/tiny.txt 0
./build/gf bfs graphs/tiny.txt 0 4
./build/gf dfs graphs/tiny.txt 0 4
```
#### Run tests
```
ctest --test-dir build
```

More to come!