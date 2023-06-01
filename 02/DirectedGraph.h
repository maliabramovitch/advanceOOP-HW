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
#include <iomanip>

/**
 * generic class for Graph
 * @tparam V - vertex
 * @tparam E - edge
 */
template<class V, class E>
class DirectedGraph;

template<class V, class E>
std::ostream &operator<<(std::ostream &os, const DirectedGraph<V, E> &dg);

template<class V, class E>
class DirectedGraph {
    std::deque<std::deque<E>> graph;
    std::deque<V> vertex; //
    E defaultValue;

    /**
    * returns the matching index of the v in the graph by using (deque) vertex.
    * @tparam V
    * @tparam E
    * @param v
    * @return the index of v if exist, -1 otherwise.
    */
    int getIndex(const V &v) const;

    /**
     * helper for- canBeReachedFromVertex(const V &v) const;
     * @param source
     * @param vertices
     */
    void recursiveHelper(const V &source, std::deque<V> &vertices) const;

public:
    /**
     * C'tor with rhs argument.
     * @param dv (default value) - default value for initialization and for Mark a removed edge.
     */
    explicit DirectedGraph(E &dv);

    /**
    * C'tor with lhs argument.
    * @param dv (default value) - default value for initialization and for Mark a removed edge.
    */
    explicit DirectedGraph(E &&dv);

    /**
     * copy C'tor.
     * @param other
     */
    DirectedGraph(const DirectedGraph &other);

    /**
     * move C'tor.
     * @param other
     */
    DirectedGraph(DirectedGraph &&other) noexcept;

    /**
     * default D'tor is enough. there is no dynamic allocations.
     */
    ~DirectedGraph() = default;

    /**
     * copy assignment.
     * @param other
     * @return
     */
    DirectedGraph &operator=(const DirectedGraph &other);

    /**
    * move assignment.
    * @param other
    * @return
    */
    DirectedGraph &operator=(DirectedGraph &&other) noexcept;

    /**
     * add vertex to the graph. if v exist nothing happened.
     * @param v
     */
    void addVertex(const V &v);

    /**
    * remove vertex from the graph. if v not exist nothing happened.
    * @param v
    */
    bool removeVertex(const V &v);

    /**
     * add edge to the graph with weight e. if (v1,v2) exist nothing happened.
     * @param v1
     * @param v2
     * @param e
     */
    void addEdge(const V &v1, const V &v2, E e);

    /**
     * remove edge fromm the graph. if (v1,v2) not exist nothing happened.
     * @param v1
     * @param v2
     * @return
     */
    bool removeEdge(const V &v1, const V &v2);

    /**
     * updating (v1,v2) with new wight e. If (v1,v2) does not exist, it will be added to the graph.
     * @param v1
     * @param v2
     * @param e
     */
    void updateEdge(const V &v1, const V &v2, E e);

    /**
     * Edge getter- const.
     * @param v1
     * @param v2
     * @return
     */
    const E &getEdge(const V &v1, const V &v2) const;

    /**
     * Edge getter.
     * @param v1
     * @param v2
     * @return
     */
    E &getEdge(const V &v1, const V &v2);

    /**
     * Returns deque<V> of vertices from which there is an ingoing edge to v
     * @param v
     * @return
     */
    std::deque<V> getInGoingVertices(const V &v) const;

    /**
    * Returns deque<V> of vertices from which there is an outgoing edge to v
    * @param v
    * @return
     */
    std::deque<V> getOutGoingVertices(const V &v) const;

    /**
     * Returns deque<V> of All the reachable vertices from v
     * @param v
     * @return
     */
    std::deque<V> canBeReachedFromVertex(const V &v) const;

    /**
     * return the edge (v1, v2)- const.
     * @param v1
     * @param v2
     * @return
     */
    const E &operator()(const V &v1, const V &v2) const;

    /**
     * return the edge (v1, v2)
     * @param v1
     * @param v2
     * @return
     */
    E &operator()(const V &v1, const V &v2);

    /**
     * printing thr graph as a Adjacency Matrix.
     */
    friend std::ostream &operator<<<>(std::ostream &os, const DirectedGraph<V, E> &dg);

    /**
     * returns true if v is in the graph, false otherwise.
     * @param v
     * @return true/false
     */
    bool isVertexExist(const V &v) const;

    /**
    * returns true if the edge (v1,v2) is in the graph, false otherwise.
    * @param v
    * @return true/false
    */
    bool isEdgeExist(const V &v1, const V &v2) const;
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
    auto outs = getOutGoingVertices(source);
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
    vertex = std::deque<V>(other.vertex);
    defaultValue = other.defaultValue;
}

template<class V, class E>
DirectedGraph<V, E>::DirectedGraph(DirectedGraph &&other) noexcept {
    graph = std::move(other.graph);
    vertex = std::move(other.vertex);
    defaultValue = std::move(other.defaultValue);
    other.graph = std::deque<std::deque<E>>();
    vertex = std::deque<V>();
    defaultValue = E(defaultValue);
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
        for (unsigned int i = 0; i < graph.size(); ++i) {
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
        return true;
    }
    return false;
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
std::deque<V> DirectedGraph<V, E>::getInGoingVertices(const V &v) const {
    std::deque<V> ret;
    int vIndex = getIndex(v);
    for (unsigned int i = 0; i < graph.size(); ++i) {
        if (graph[i][vIndex] != defaultValue) {
            ret.push_back(vertex[i]);
        }
    }
    return ret;
}

template<class V, class E>
std::deque<V> DirectedGraph<V, E>::getOutGoingVertices(const V &v) const {
    std::deque<V> ret;
    int vIndex = getIndex(v);
    for (unsigned int i = 0; i < graph.size(); ++i) {
        //std::cout << graph[vIndex][i] << vertex[i] << '\n';
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
    os << std::setw(18) << std::setfill(' ') << " ";
    for (const V &v: dg.vertex) {
        os << std::setw(18) << std::setfill(' ') << v << std::setw(0);
    }
    os << std::endl;
    for (unsigned int i = 0; i < dg.graph.size(); ++i) {
        os << std::setw(18) << std::setfill(' ') << dg.vertex[i];
        for (unsigned int j = 0; j < dg.graph[i].size(); ++j) {
            os << std::setw(18) << dg.graph[i][j];
        }
        os << std::endl;
    }
    return os;
}


template<class V, class E>
bool DirectedGraph<V, E>::isVertexExist(const V &v) const {
    return (getIndex(v) != -1);
}

template<class V, class E>
bool DirectedGraph<V, E>::isEdgeExist(const V &v1, const V &v2) const {
    return (getEdge(v1, v2) != defaultValue);
}

#endif //INC_02_DIRECTEDGRAPH_H