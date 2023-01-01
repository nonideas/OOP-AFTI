#include "gtest/gtest.h"
#include "../src/graph.h"
#include "../src/work_with_graph/cycle_search.h"
#include "../src/work_with_graph/print_unique_vertices.h"
#include "../src/strategy/bfs.h"
#include "../src/strategy/dfs.h"
#include "../src/traversal.h"

TEST(graph, add_edge) {
    graph g;
    g.add_edge({ vertex(1)}, { vertex(2) });
    EXPECT_EQ(g.count_of_vertices(), 2);
    g.add_edge({ vertex(1) }, { vertex(2) });
    EXPECT_EQ(g.count_of_vertices(), 2);
    g.add_edge({ vertex(1) }, { vertex(3) });
    EXPECT_EQ(g.count_of_vertices(), 3);
    g.add_edge({ vertex(1) }, { vertex(3) });
    EXPECT_EQ(g.count_of_vertices(), 3);

    std::vector<vertex> v1 = { {vertex(2)}, {vertex(3)} };
    std::vector<vertex> v2 = {};
    std::vector<vertex> v3 = { {vertex(4)} };

    EXPECT_EQ(g.adjacent_vertices({ vertex(1) }), v1);
    EXPECT_EQ(g.adjacent_vertices({ vertex(2) }), v2);
    EXPECT_EQ(g.adjacent_vertices({ vertex(3) }), v2);
    g.add_edge({ vertex(2) }, { vertex(4) });
    EXPECT_EQ(g.adjacent_vertices({ vertex(2) }), v3);
}

TEST(bfs, empty_graph) {
    graph g;
    auto work = std::make_shared<cycle_search>();
    auto s = std::make_shared<bfs>(work);
    traversal tr(s);

    tr.bypass(g, { vertex(1) });
    EXPECT_FALSE(work->is_cycled());
}

TEST(bfs, cycled_graph) {
    graph g;
    g.add_edge({ vertex(1) }, { vertex(2) });
    g.add_edge({ vertex(1) }, { vertex(3) });
    g.add_edge({ vertex(2) }, { vertex(3) });
    g.add_edge({ vertex(2) }, { vertex(1) });
    g.add_edge({ vertex(3) }, { vertex(1) });
    g.add_edge({ vertex(3) }, { vertex(2) });
    auto work = std::make_shared<cycle_search>();
    auto s = std::make_shared<bfs>(work);
    traversal tr(s);

    tr.bypass(g, { vertex(1) });
    EXPECT_TRUE(work->is_cycled());
}

TEST(bfs, no_cycled_graph) {
    graph g;
    g.add_edge({ vertex(1) }, { vertex(2) });
    g.add_edge({ vertex(1) }, { vertex(3) });
    g.add_edge({ vertex(2) }, { vertex(4) });
    auto work = std::make_shared<cycle_search>();
    auto s = std::make_shared<bfs>(work);
    traversal tr(s);

    tr.bypass(g, { vertex(1) });
    EXPECT_FALSE(work->is_cycled());
}

TEST(dfs, empty_graph) {
    graph g;
    auto work = std::make_shared<cycle_search>();
    auto s = std::make_shared<dfs>(work);
    traversal tr(s);

    tr.bypass(g, { vertex(1) });
    EXPECT_FALSE(work->is_cycled());
}

TEST(dfs, cycled_graph) {
    graph g;
    g.add_edge({ vertex(1) }, { vertex(2) });
    g.add_edge({ vertex(1) }, { vertex(3) });
    g.add_edge({ vertex(2) }, { vertex(3) });
    auto work = std::make_shared<cycle_search>();
    auto s = std::make_shared<dfs>(work);
    traversal tr(s);

    tr.bypass(g, { vertex(1) });
    EXPECT_TRUE(work->is_cycled());
}

TEST(dfs, no_cycled_graph) {
    graph g;
    g.add_edge({ vertex(1) }, { vertex(2) });
    g.add_edge({ vertex(1) }, { vertex(3) });
    g.add_edge({ vertex(2) }, { vertex(4) });
    auto work = std::make_shared<cycle_search>();
    auto s = std::make_shared<dfs>(work);
    traversal tr(s);

    tr.bypass(g, { vertex(1) });
    EXPECT_FALSE(work->is_cycled());
}
