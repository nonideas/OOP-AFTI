#include "graph.h"

graph::graph(const std::vector<std::pair<vertex, vertex>>& v) {
    for (const auto& [ver1, ver2] : v) {
        add_edge(ver1, ver2);
    }
}

void graph::add_edge(const vertex& start_edge, const vertex& end_edge) {
    if (graph_.contains(start_edge) && std::ranges::find(graph_[start_edge], end_edge) != graph_[start_edge].end()) {
        return;
    }
    graph_[start_edge].push_back(end_edge);
    graph_[end_edge];
}

const std::vector<vertex>& graph::adjacent_vertices(const vertex& vertex) const {
    return graph_.at(vertex);
}

size_t graph::count_of_vertices() const noexcept {
    return graph_.size();
}
