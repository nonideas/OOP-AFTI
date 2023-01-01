#pragma once
#include "strategy/strategy.h"

class traversal
{
	std::shared_ptr<strategy> strategy_;
public:
	explicit traversal(std::shared_ptr<strategy> strategy = {});

	void bypass(const graph& graph, const vertex& start) const;
	void set_strategy(std::shared_ptr<strategy> strategy);
};

