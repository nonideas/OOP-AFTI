#pragma once
#include "../graph.h"

class work_with_graph
{
protected:
	bool is_finished_ = false;
public:
	virtual void begin(const vertex& start_ver) = 0;
	virtual void end() = 0;
	virtual void visit_edge(const vertex& start_ver, const vertex& stop_ver) = 0;
	virtual void visit_vertex(const vertex& vertex) = 0;

	[[nodiscard]] bool is_finished() const noexcept;

	work_with_graph() = default;
	virtual ~work_with_graph() = default;
};

