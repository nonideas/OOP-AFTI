#pragma once
#include "../graph.h"
#include "strategy.h"
#include <queue>

class bfs final : public strategy {
	std::queue<vertex> queue_;
public:
	explicit bfs(std::shared_ptr<work_with_graph> finder);
	bfs() = delete;
protected:
	vertex get_next_vertex() override;
	void push_vertex(const vertex& ver) override;
	bool is_container_empty() override;
};
