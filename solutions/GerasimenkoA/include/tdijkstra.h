// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// tdijkstra.h
//
// Copyright (c) Пинежанин Е.С.

#ifndef __TDijkstra_H__
#define __TDijkstra_H__

#include <vector>

// Тип для представления ребра: (вершина, вес)
using Edge = std::pair<int, int>;   // (neighbor, weight)

using Graph = std::vector<std::vector<Edge>>;

class TDijkstra {
private:
    const Graph& graph;
    std::vector<int> dist; // массив расстояний
    std::vector<int> prev; // массив предыдущих вершин на пути
    int start_; // последний использованный источник

public:
    TDijkstra(const Graph& graph_) : graph(graph_) {};

    // Запуск алгоритма от заданной начальной вершины
    void compute(int start);

    // Возвращает кратчайшее расстояние до вершины v (или -1, если недостижима)
    int getDistance(int v) const;

    // Возвращает вектор расстояний до всех вершин
    const std::vector<int>& getAllDistances() const;

    // Восстанавливает кратчайший путь от последнего старта до вершины v
    std::vector<int> getPath(int v) const;

    // Проверяет, достижима ли вершина v
    bool isReachable(int v) const;
};

#endif
