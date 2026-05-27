// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// tdijkstra.cpp
//
// Copyright (c) Пинежанин Е.С.

#include <tdijkstra.h>
#include <queue>
#include <limits>
#include <stdexcept>
#include <algorithm>

using namespace std;

void TDijkstra::compute(int start) {
    if (start < 0 || start >= graph.size()) {
        throw out_of_range("Invalid start vertex");
    }

    start_ = start;

    int size = graph.size();

    dist.assign(size, numeric_limits<int>::max());
    prev.assign(size, -1);

    dist[start] = 0;

    using Node = pair<int, int>; // (distance, vertex)

    priority_queue< Node, vector<Node>, greater<Node> > pq;

    pq.push({ 0, start });

    while (!pq.empty()) {

        int current_dist = pq.top().first;
        int current_vertex = pq.top().second;

        pq.pop();

        if (current_dist > dist[current_vertex]) {
            continue;
        }

        for (const auto& edge : graph[current_vertex]) {

            int neighbor = edge.first;
            int weight = edge.second;

            if (weight < 0) {
                throw logic_error("Negative weight detected");
            }

            if (dist[current_vertex] + weight < dist[neighbor]) {

                dist[neighbor] = dist[current_vertex] + weight;

                prev[neighbor] = current_vertex;

                pq.push({ dist[neighbor], neighbor });
            }
        }
    }
}

int TDijkstra::getDistance(int v) const {
    if (v < 0 || v >= dist.size()) {
        throw out_of_range("Invalid vertex");
    }

    if (dist[v] == numeric_limits<int>::max()) {
        return -1;
    }

    return dist[v];
}

const vector<int>& TDijkstra::getAllDistances() const {
    return dist;
}


vector<int> TDijkstra::getPath(int v) const {
    if (v < 0 || v >= dist.size()) {
        throw out_of_range("Invalid vertex");
    }

    vector<int> path;

    if (!isReachable(v)) {
        return path;
    }

    int current = v;

    while (current != -1) {
        path.push_back(current);
        current = prev[current];
    }

    reverse(path.begin(), path.end());

    return path;
}

bool TDijkstra::isReachable(int v) const {
    if (v < 0 || v >= dist.size()) {
        throw out_of_range("Invalid vertex");
    }

    return dist[v] != numeric_limits<int>::max();
}
