# graphforge

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
./build/gf graphs/tiny.txt
