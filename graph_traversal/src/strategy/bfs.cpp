#include "bfs.h"
#include <unordered_map>

bfs::bfs(std::shared_ptr<work_with_graph> finder)
	: strategy(std::move(finder)) {}

vertex bfs::get_next_vertex() {
    const vertex cur_ver = queue_.front();
    queue_.pop();
    return cur_ver;
}

void bfs::push_vertex(const vertex& ver) {
    queue_.push(ver);
}

bool bfs::is_container_empty() {
    return queue_.empty();
}
