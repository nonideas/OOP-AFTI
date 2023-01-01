#pragma once
#include "../graph.h"
#include "strategy.h"
#include <stack>

class dfs final : public strategy {
	std::stack<vertex> stack_;
public:
	explicit dfs(std::shared_ptr<work_with_graph> finder);
	dfs() = delete;
protected:
	vertex get_next_vertex() override;
	void push_vertex(const vertex& ver) override;
	bool is_container_empty() override;
};

