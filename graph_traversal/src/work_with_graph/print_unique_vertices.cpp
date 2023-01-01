#include "print_unique_vertices.h"
#include <iostream>

void print_unique_vertices::begin(const vertex& start_ver) {
    visited_.clear();
}

void print_unique_vertices::end() {}

void print_unique_vertices::visit_edge(const vertex& start_ver, const vertex& stop_ver) {}

void print_unique_vertices::visit_vertex(const vertex& vertex) {
    if (!visited_.contains(vertex)) {
        visited_.emplace(vertex);
        std::cout << vertex.get_id() << " ";
    }
}