#pragma once
#include <iostream>
#include "../work_with_graph/work_with_graph.h"

class strategy {
protected:
	std::shared_ptr<work_with_graph> work_with_graph_{};

	virtual vertex get_next_vertex() = 0;
	virtual void push_vertex(const vertex& ver) = 0;
	virtual bool is_container_empty() = 0;
public:
	explicit strategy(std::shared_ptr<work_with_graph> work_with_graph);

	void execute(const graph& graph, const vertex& start_ver);

	void set_work_with_graph(std::shared_ptr<work_with_graph> work_with_graph);

	strategy() = delete;
	strategy(const strategy&) = default;
	strategy(strategy&&) = default;
	strategy& operator=(const strategy&) = default;
	strategy& operator=(strategy&&) = default;

	virtual ~strategy() = default;
};
