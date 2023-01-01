#include "cycle_search.h"

void cycle_search::begin(const vertex& start_ver) {
    visited_.clear();
	is_cycled_ = false;
	is_finished_ = false;
}

void cycle_search::end() {}

void cycle_search::visit_edge(const vertex& start_ver, const vertex& stop_ver) {}

void cycle_search::visit_vertex(const vertex& vertex) {
    if (visited_.contains(vertex)) {
        is_cycled_ = true;
        is_finished_ = true;
        return;
    }
    visited_.emplace(vertex);
}

bool cycle_search::is_cycled() const noexcept
{
    return is_cycled_;
}
