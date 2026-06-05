#pragma once

#include <vector>
#include <queue>
#include <limits>
#include <optional>
#include <utility>

class TDijkstra {
public:
    using Vertex = int;
    using Weight = long long;
    using Edge = std::pair<Vertex, Weight>;  // {to_vertex, weight}
    using Graph = std::vector<std::vector<Edge>>;

    static constexpr Weight INF = std::numeric_limits<Weight>::max() / 2;

    explicit TDijkstra(size_t vertex_count);

    // Добавить ребро (ориентированное) с весом
    void AddEdge(Vertex from, Vertex to, Weight weight);

    // Найти кратчайшие расстояния от источника до всех вершин
    std::vector<Weight> FindShortestPaths(Vertex source) const;

    // Восстановить кратчайший путь от source до target
    std::optional<std::vector<Vertex>> GetPath(Vertex source, Vertex target) const;

    // Получить расстояние от source до target (после вызова FindShortestPaths)
    Weight GetDistance(Vertex source, Vertex target) const;

    // Очистить граф
    void Clear();

    size_t GetVertexCount() const { return vertex_count_; }

private:
    size_t vertex_count_;
    Graph graph_;
    mutable std::vector<Vertex> parent_;  // для восстановления пути
    mutable std::vector<Weight> dist_;    // кэшированные расстояния
    mutable bool paths_computed_ = false;
    mutable Vertex last_source_ = -1;

    void ComputePaths(Vertex source) const;
};