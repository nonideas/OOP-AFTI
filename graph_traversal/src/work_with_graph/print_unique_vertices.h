#pragma once
#include "work_with_graph.h"
#include <unordered_set>

class print_unique_vertices final : public work_with_graph {
	std::unordered_set<vertex> visited_;
public:
	void begin(const vertex& start_ver) override;
	void end() override;
	void visit_edge(const vertex& start_ver, const vertex& stop_ver) override;
	void visit_vertex(const vertex& vertex) override;

	print_unique_vertices() = default;
	~print_unique_vertices() override = default;
};

