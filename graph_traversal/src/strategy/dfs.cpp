#include "dfs.h"
#include <unordered_map>

dfs::dfs(std::shared_ptr<work_with_graph> finder)
	: strategy(std::move(finder)) {}

vertex dfs::get_next_vertex() {
	const vertex cur_ver = stack_.top();
	stack_.pop();
	return cur_ver;
}

void dfs::push_vertex(const vertex& ver) {
	stack_.push(ver);
}

bool dfs::is_container_empty() {
	return stack_.empty();
}
