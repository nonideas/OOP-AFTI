#include "strategy.h"
#include <unordered_set>

strategy::strategy(std::shared_ptr<work_with_graph> work_with_graph = {})
	: work_with_graph_(std::move(work_with_graph)) {}

void strategy::execute(const graph& graph, const vertex& start_ver) {
    if (graph.count_of_vertices() == 0) {
        return;
    }
    std::unordered_map<vertex, std::vector<vertex>> visited;
    vertex prev_ver = start_ver;

    work_with_graph_->begin(start_ver);

    push_vertex(start_ver);
    while (!is_container_empty()) {
        vertex cur_ver = get_next_vertex();
        work_with_graph_->visit_edge(prev_ver, cur_ver);
        work_with_graph_->visit_vertex(cur_ver);
        prev_ver = cur_ver;

        if (work_with_graph_->is_finished()) {
            break;
        }
        for (const auto& adj_ver : graph.adjacent_vertices(cur_ver)) {
            if (std::ranges::find(visited[cur_ver], adj_ver) == visited[cur_ver].end()) {
                visited[cur_ver].push_back(adj_ver);
                push_vertex(adj_ver);
            }
        }
    }
    work_with_graph_->end();
}

void strategy::set_work_with_graph(std::shared_ptr<work_with_graph> work_with_graph) {
    work_with_graph_ = std::move(work_with_graph);
}
