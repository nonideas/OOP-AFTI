#include "gtest/gtest.h"
#include "strategy/bfs.h"
#include "strategy/dfs.h"
#include "work_with_graph/print_unique_vertices.h"
#include "traversal.h"

void print_bfs() {
    graph g;
    g.add_edge({ vertex(1) }, { vertex(2) });
    g.add_edge({ vertex(1) }, { vertex(3) });
    g.add_edge({ vertex(2) }, { vertex(3) });
    auto work = std::make_shared<print_unique_vertices>();
    auto s = std::make_shared<bfs>(work);
    traversal tr(s);
    tr.bypass(g, { vertex(1) });
    std::cout << std::endl;
}

void print_bfs_double() {
    graph g;
    g.add_edge({ vertex(1) }, { vertex(2) });
    g.add_edge({ vertex(1) }, { vertex(3) });
    g.add_edge({ vertex(2) }, { vertex(3) });
    g.add_edge({ vertex(2) }, { vertex(1) });
    g.add_edge({ vertex(3) }, { vertex(1) });
    g.add_edge({ vertex(3) }, { vertex(2) });
    g.add_edge({ vertex(3) }, { vertex(4) });
    auto work = std::make_shared<print_unique_vertices>();
    auto s = std::make_shared<bfs>(work);
    traversal tr(s);
    tr.bypass(g, { vertex(1) });
    std::cout << std::endl;
}

void print_dfs() {
    graph g;
    g.add_edge({ vertex(1) }, { vertex(2) });
    g.add_edge({ vertex(1) }, { vertex(3) });
    g.add_edge({ vertex(2) }, { vertex(3) });
    auto work = std::make_shared<print_unique_vertices>();
    auto s = std::make_shared<dfs>(work);
    traversal tr(s);
    tr.bypass(g, { vertex(1) });
    std::cout << std::endl;
}

void print_dfs_double() {
    graph g;
    g.add_edge({ vertex(1) }, { vertex(2) });
    g.add_edge({ vertex(1) }, { vertex(3) });
    g.add_edge({ vertex(2) }, { vertex(3) });
    g.add_edge({ vertex(2) }, { vertex(1) });
    g.add_edge({ vertex(3) }, { vertex(1) });
    g.add_edge({ vertex(3) }, { vertex(2) });
    g.add_edge({ vertex(3) }, { vertex(4) });
    auto work = std::make_shared<print_unique_vertices>();
    auto s = std::make_shared<dfs>(work);
    traversal tr(s);
    tr.bypass(g, { vertex(1) });
    std::cout << std::endl;
}

int main(int argc, char** argv) {
    print_bfs();
    print_bfs_double();
    print_dfs();
    print_dfs_double();
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}