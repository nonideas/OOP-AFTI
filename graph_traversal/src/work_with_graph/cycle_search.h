#pragma once
#include "work_with_graph.h"
#include <unordered_set>

class cycle_search final : public work_with_graph {
	std::unordered_set<vertex> visited_;
	bool is_cycled_ = false;
public:
	void begin(const vertex& start_ver) override;
	void end() override;
	void visit_edge(const vertex& start_ver, const vertex& stop_ver) override;
	void visit_vertex(const vertex& vertex) override;

	[[nodiscard]] bool is_cycled() const noexcept;

	cycle_search() = default;
	~cycle_search() override = default;
};

