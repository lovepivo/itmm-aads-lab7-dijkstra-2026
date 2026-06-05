#include "dijkstra.h"
#include <iostream>

#ifdef _WIN32
#include <windows.h>
#endif

int main() {
#ifdef _WIN32
    // Переключаем вывод консоли Windows в UTF-8
    SetConsoleOutputCP(CP_UTF8);
#endif

    TDijkstra dijkstra(5);

    dijkstra.AddEdge(0, 1, 10);
    dijkstra.AddEdge(0, 4, 5);
    dijkstra.AddEdge(1, 2, 1);
    dijkstra.AddEdge(1, 4, 2);
    dijkstra.AddEdge(2, 3, 4);
    dijkstra.AddEdge(3, 0, 7);
    dijkstra.AddEdge(3, 2, 6);
    dijkstra.AddEdge(4, 1, 3);
    dijkstra.AddEdge(4, 2, 9);
    dijkstra.AddEdge(4, 3, 2);

    TDijkstra::Vertex source = 0;
    auto distances = dijkstra.FindShortestPaths(source);

    std::cout << "Кратчайшие расстояния от вершины " << source << ":\n";
    for (size_t i = 0; i < distances.size(); ++i) {
        std::cout << "  до " << i << ": ";
        if (distances[i] == TDijkstra::INF) {
            std::cout << "недостижимо\n";
        } else {
            std::cout << distances[i] << "\n";
        }
    }

    TDijkstra::Vertex target = 3;
    auto path = dijkstra.GetPath(source, target);
    if (path) {
        std::cout << "\nКратчайший путь от " << source << " до " << target << ": ";
        for (size_t i = 0; i < path->size(); ++i) {
            std::cout << (*path)[i];
            if (i + 1 < path->size()) std::cout << " -> ";
        }
        std::cout << "\n";
    } else {
        std::cout << "\nПуть от " << source << " до " << target << " не существует.\n";
    }

    return 0;
}