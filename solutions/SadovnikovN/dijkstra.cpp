#include "dijkstra.h"
#include <algorithm>
#include <stdexcept>

TDijkstra::TDijkstra(size_t vertex_count)
    : vertex_count_(vertex_count), graph_(vertex_count) {}

void TDijkstra::AddEdge(Vertex from, Vertex to, Weight weight) {
    if (from < 0 || from >= static_cast<Vertex>(vertex_count_) ||
        to < 0 || to >= static_cast<Vertex>(vertex_count_)) {
        throw std::out_of_range("Vertex index out of range");
    }
    if (weight < 0) {
        throw std::invalid_argument("Negative weights are not supported");
    }
    graph_[from].emplace_back(to, weight);
}

void TDijkstra::ComputePaths(Vertex source) const {
    if (paths_computed_ && last_source_ == source) {
        return;
    }

    dist_.assign(vertex_count_, INF);
    parent_.assign(vertex_count_, -1);
    dist_[source] = 0;

    // Мин-куча: {расстояние, вершина}
    using QueueItem = std::pair<Weight, Vertex>;
    std::priority_queue<QueueItem, std::vector<QueueItem>, std::greater<>> pq;
    pq.emplace(0, source);

    while (!pq.empty()) {
        auto [curr_dist, v] = pq.top();
        pq.pop();

        if (curr_dist > dist_[v]) continue;  // устаревшая запись

        for (const auto& [to, weight] : graph_[v]) {
            Weight new_dist = dist_[v] + weight;
            if (new_dist < dist_[to]) {
                dist_[to] = new_dist;
                parent_[to] = v;
                pq.emplace(new_dist, to);
            }
        }
    }

    paths_computed_ = true;
    last_source_ = source;
}

std::vector<TDijkstra::Weight> TDijkstra::FindShortestPaths(Vertex source) const {
    if (source < 0 || source >= static_cast<Vertex>(vertex_count_)) {
        throw std::out_of_range("Source vertex out of range");
    }
    ComputePaths(source);
    return dist_;
}

std::optional<std::vector<TDijkstra::Vertex>> TDijkstra::GetPath(Vertex source, Vertex target) const {
    if (source < 0 || source >= static_cast<Vertex>(vertex_count_) ||
        target < 0 || target >= static_cast<Vertex>(vertex_count_)) {
        throw std::out_of_range("Vertex index out of range");
    }
    ComputePaths(source);

    if (dist_[target] == INF) {
        return std::nullopt;  // путь не существует
    }

    std::vector<Vertex> path;
    for (Vertex v = target; v != -1; v = parent_[v]) {
        path.push_back(v);
    }
    std::reverse(path.begin(), path.end());
    return path;
}

TDijkstra::Weight TDijkstra::GetDistance(Vertex source, Vertex target) const {
    if (source < 0 || source >= static_cast<Vertex>(vertex_count_) ||
        target < 0 || target >= static_cast<Vertex>(vertex_count_)) {
        throw std::out_of_range("Vertex index out of range");
    }
    ComputePaths(source);
    return dist_[target];
}

void TDijkstra::Clear() {
    graph_.assign(vertex_count_, {});
    paths_computed_ = false;
    last_source_ = -1;
}