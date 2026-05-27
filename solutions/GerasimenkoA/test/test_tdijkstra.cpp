#include "tdijkstra.h"
#include <gtest.h>

using namespace std;

TEST(TDijkstra, can_compute_shortest_paths) {
    Graph graph(5);

    graph[0] = { {1,4}, {2,2} };
    graph[1] = { {2,1}, {3,5} };
    graph[2] = { {3,8}, {4,10} };
    graph[3] = { {4,2} };

    TDijkstra dijkstra(graph);

    ASSERT_NO_THROW(dijkstra.compute(0));

    EXPECT_EQ(dijkstra.getDistance(0), 0);
    EXPECT_EQ(dijkstra.getDistance(1), 4);
    EXPECT_EQ(dijkstra.getDistance(2), 2);
    EXPECT_EQ(dijkstra.getDistance(3), 9);
    EXPECT_EQ(dijkstra.getDistance(4), 11);
}

TEST(TDijkstra, can_restore_path) {
    Graph graph(5);

    graph[0] = { {1,4}, {2,2} };
    graph[1] = { {3,5} };
    graph[2] = { {3,1} };

    TDijkstra dijkstra(graph);

    dijkstra.compute(0);

    vector<int> expected = { 0, 2, 3 };

    EXPECT_EQ(dijkstra.getPath(3), expected);
}

TEST(TDijkstra, returns_minus_one_for_unreachable_vertex) {
    Graph graph(3);

    graph[0] = { {1,5} };

    TDijkstra dijkstra(graph);

    dijkstra.compute(0);

    EXPECT_EQ(dijkstra.getDistance(2), -1);
}

TEST(TDijkstra, unreachable_vertex_returns_empty_path) {
    Graph graph(3);

    graph[0] = { {1,5} };

    TDijkstra dijkstra(graph);

    dijkstra.compute(0);

    EXPECT_TRUE(dijkstra.getPath(2).empty());
}

TEST(TDijkstra, can_check_reachability) {
    Graph graph(3);

    graph[0] = { {1,5} };

    TDijkstra dijkstra(graph);

    dijkstra.compute(0);

    EXPECT_TRUE(dijkstra.isReachable(1));
    EXPECT_FALSE(dijkstra.isReachable(2));
}

TEST(TDijkstra, throws_for_invalid_start_vertex) {
    Graph graph(3);

    TDijkstra dijkstra(graph);

    ASSERT_ANY_THROW(dijkstra.compute(10));
}

TEST(TDijkstra, throws_for_invalid_vertex_in_get_distance) {
    Graph graph(3);

    TDijkstra dijkstra(graph);

    dijkstra.compute(0);

    ASSERT_ANY_THROW(dijkstra.getDistance(10));
}

TEST(TDijkstra, throws_for_invalid_vertex_in_get_path) {
    Graph graph(3);

    TDijkstra dijkstra(graph);

    dijkstra.compute(0);

    ASSERT_ANY_THROW(dijkstra.getPath(10));
}

TEST(TDijkstra, throws_for_negative_edge_weight) {
    Graph graph(2);

    graph[0] = { {1,-5} };

    TDijkstra dijkstra(graph);

    ASSERT_ANY_THROW(dijkstra.compute(0));
}

TEST(TDijkstra, can_get_all_distances) {
    Graph graph(3);

    graph[0] = { {1,2}, {2,7} };
    graph[1] = { {2,3} };

    TDijkstra dijkstra(graph);

    dijkstra.compute(0);

    vector<int> expected = { 0, 2, 5 };

    EXPECT_EQ(dijkstra.getAllDistances(), expected);
}
