// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Пинежанин Е.С.
//
// Тестирование работы алгоритма Дейкстры

#include <iostream>

#include "tdijkstra.h"

int main()
{
    // Граф: 5 вершин, рёбра (u, v, вес)
    Graph graph(5);

    graph[0] = {{1,4}, {2,2}};
    graph[1] = {{2,1}, {3,5}};
    graph[2] = {{3,8}, {4,10}};
    graph[3] = {{4,2}};
    graph[4] = {};

    TDijkstra dijkstra(graph);
    dijkstra.compute(0);

    for (int i = 0; i < 5; ++i) {
        std::cout << "0 -> " << i << " = " << dijkstra.getDistance(i) << ", path: ";
        auto path = dijkstra.getPath(i);
        for (int v : path) std::cout << v << " ";
        std::cout << std::endl;
    }
    return 0;
}
