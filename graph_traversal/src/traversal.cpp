#include "traversal.h"

traversal::traversal(std::shared_ptr<strategy> strategy)
	: strategy_(std::move(strategy)) {}

void traversal::bypass(const graph& graph, const vertex& start) const {
	strategy_->execute(graph, start);
}

void traversal::set_strategy(std::shared_ptr<strategy> strategy) {
	strategy_ = std::move(strategy);
}
