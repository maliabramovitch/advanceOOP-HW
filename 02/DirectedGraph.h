//
// Created by Mali Abramovitch on 24/05/2023.
//

#ifndef INC_02_DIRECTEDGRAPH_H
#define INC_02_DIRECTEDGRAPH_H

#include <string>
#include <memory>
#include <deque>
#include <algorithm>
#include <iostream>

template<class V, class E>
class DirectedGraph;

template<class V, class E>
std::ostream &operator<<(std::ostream &os, const DirectedGraph<V, E> &dg);

template<class V, class E>
class DirectedGraph {
    std::deque<std::deque<E>> graph;
    std::deque<V> vertex;
    E defaultValue;

    int getIndex(const V &v) const;

    void recursiveHelper(const V &source, std::deque<V> &vertices) const;

public:
    explicit DirectedGraph(E &dv);

    explicit DirectedGraph(E &&dv);

    DirectedGraph(const DirectedGraph &other);

    DirectedGraph(DirectedGraph &&other) noexcept;

    ~DirectedGraph() = default;

    DirectedGraph &operator=(const DirectedGraph &other);

    DirectedGraph &operator=(DirectedGraph &&other) noexcept;

    void addVertex(const V &v);

    bool removeVertex(const V &v);

    void addEdge(const V &v1, const V &v2, E e);

    bool removeEdge(const V &v1, const V &v2);

    void updateEdge(const V &v1, const V &v2, E e);

    const E &getEdge(const V &v1, const V &v2) const;

    E &getEdge(const V &v1, const V &v2);

    std::deque<V> getInGoingVertex(const V &v) const;

    std::deque<V> getOutGoingVertex(const V &v) const;

    std::deque<V> canBeReachedFromVertex(const V &v) const;

    const E &operator()(const V &v1, const V &v2) const;

    E &operator()(const V &v1, const V &v2);

    friend std::ostream &operator<<<>(std::ostream &os, const DirectedGraph<V, E> &dg);
};

template<class V, class E>
int DirectedGraph<V, E>::getIndex(const V &v) const {
    auto vIt = std::find(vertex.begin(), vertex.end(), v);
    if (vIt != vertex.end()) {
        int index = vIt - vertex.begin();
        return index;
    }
    return -1;
}


template<class V, class E>
void DirectedGraph<V, E>::recursiveHelper(const V &source, std::deque<V> &vertices) const {
    if (std::find(vertices.begin(), vertices.end(), source) != vertices.end()) {
        return;
    }
    vertices.push_back(source);
    auto outs = getOutGoingVertex(source);
    if (outs.empty()) {
        return;
    }
    for (int i = 0; i < outs.size(); ++i) {
        recursiveHelper(outs[i], vertices);
    }
}

template<class V, class E>
DirectedGraph<V, E>::DirectedGraph(E &dv) : defaultValue(dv) {}

template<class V, class E>
DirectedGraph<V, E>::DirectedGraph(E &&dv) : defaultValue(dv) {}

template<class V, class E>
DirectedGraph<V, E>::DirectedGraph(const DirectedGraph &other) : defaultValue(other.defaultValue) {
    graph = other.graph;
    vertex =std::deque<V>(other.vertex);
    defaultValue = other.defaultValue;
}

template<class V, class E>
DirectedGraph<V, E>::DirectedGraph(DirectedGraph &&other) noexcept {
    graph = std::move(other.graph);
    vertex = std::move(other.vertex);
    defaultValue = std::move(other.defaultValue);
}

template<class V, class E>
DirectedGraph<V, E> &DirectedGraph<V, E>::operator=(const DirectedGraph &other) {
    if (this != &other) {
        graph = other.graph;
        vertex = other.vertex;
        defaultValue = other.defaultValue;
    }
    return *this;
}

template<class V, class E>
DirectedGraph<V, E> &DirectedGraph<V, E>::operator=(DirectedGraph &&other) noexcept {
    if (this != &other) {
        graph = std::move(other.graph);
        vertex = std::move(other.vertex);
        defaultValue = std::move(other.defaultValue);
    }
    return *this;
}

template<class V, class E>
void DirectedGraph<V, E>::addVertex(const V &v) {
    if (getIndex(v) == -1) {
        vertex.push_back(v);
        for (int i = 0; i < graph.size(); ++i) {
            graph[i].push_back(defaultValue);
        }
        graph.push_back(std::deque<E>(graph.size() + 1, defaultValue));
    }
}

template<class V, class E>
bool DirectedGraph<V, E>::removeVertex(const V &v) {
    int index = getIndex(v);
    if (index != -1) {
        vertex.erase(vertex.begin() + index);
        graph.erase(graph.begin() + index);
        for (int i = 0; i < graph.size(); ++i) {
            graph[i].erase(graph[i].begin() + index);
        }
        return true;
    }
    return false;
}

template<class V, class E>
void DirectedGraph<V, E>::addEdge(const V &v1, const V &v2, E e) {
    addVertex(v1);
    addVertex(v2);
    int v1Index = getIndex(v1), v2Index = getIndex(v2);
    graph[v1Index][v2Index] = e;
}

template<class V, class E>
bool DirectedGraph<V, E>::removeEdge(const V &v1, const V &v2) {
    int v1Index = getIndex(v1), v2Index = getIndex(v2);
    if (v1Index != -1 && v2Index != -1) {
        graph[v1Index][v2Index] = defaultValue;
    }
}

template<class V, class E>
void DirectedGraph<V, E>::updateEdge(const V &v1, const V &v2, E e) {
    addEdge(v1, v2, e);
}

template<class V, class E>
E &DirectedGraph<V, E>::getEdge(const V &v1, const V &v2) {
    int v1Index = getIndex(v1), v2Index = getIndex(v2);
    if (v1Index != -1 && v2Index != -1) {
        return graph[v1Index][v2Index];
    }
    return defaultValue;
}


template<class V, class E>
const E &DirectedGraph<V, E>::getEdge(const V &v1, const V &v2) const {
    int v1Index = getIndex(v1), v2Index = getIndex(v2);
    if (v1Index != -1 && v2Index != -1) {
        return graph[v1Index][v2Index];
    }
    return defaultValue;
}

template<class V, class E>
std::deque<V> DirectedGraph<V, E>::getInGoingVertex(const V &v) const {
    std::deque<V> ret;
    int vIndex = getIndex(v);
    for (int i = 0; i < graph.size(); ++i) {
        if (graph[i][vIndex] != defaultValue) {
            ret.push_back(vertex[i]);
        }
    }
    return ret;
}

template<class V, class E>
std::deque<V> DirectedGraph<V, E>::getOutGoingVertex(const V &v) const {
    std::deque<V> ret;
    int vIndex = getIndex(v);
    for (int i = 0; i < graph.size(); ++i) {
        if (graph[vIndex][i] != defaultValue) {
            ret.push_back(vertex[i]);
        }
    }
    return ret;
}

template<class V, class E>
std::deque<V> DirectedGraph<V, E>::canBeReachedFromVertex(const V &v) const {
    std::deque<V> ret;
    recursiveHelper(v, ret);
    return ret;
}

template<class V, class E>
const E &DirectedGraph<V, E>::operator()(const V &v1, const V &v2) const {
    return getEdge(v1, v2);
}

template<class V, class E>
E &DirectedGraph<V, E>::operator()(const V &v1, const V &v2) {
    return getEdge(v1, v2);
}

template<class V, class E>
std::ostream &operator<<(std::ostream &os, const DirectedGraph<V, E> &dg) {
    for (unsigned int i = 0; i < dg.vertex.size(); ++i) {
        auto &element = dg.vertex[i];
        os << element << "->\t";
        std::deque<V> out = dg.getOutGoingVertex(element);
        if (!out.empty()) {
            for (unsigned int j = 0; j < out.size(); ++j) {
                V &v = out[j];
                os << v << ":" << dg.getEdge(element, v);
                if (j != out.size()-1)
                    os << ", ";
            }
        }
        os << std::endl;
    }
    return os;
}


#endif //INC_02_DIRECTEDGRAPH_H
