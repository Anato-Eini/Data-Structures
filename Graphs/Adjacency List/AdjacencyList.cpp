#ifndef DATA_STRUCTURES_ADJACENCYLIST_CPP
#define DATA_STRUCTURES_ADJACENCYLIST_CPP

#include "AdjacencyList.h"
#include "thread"
#include "mutex"

namespace Graph {

    std::mutex mutex;

    template<typename V, typename E>
    AdjacencyList<V, E>::AdjacencyList() : list(new std::list<Vertex>()), sizeEdge(0){}

    template<typename V, typename E>
    std::vector<V> * AdjacencyList<V, E>::vertices() const {
        std::vector<V> * vertices = new std::vector<V>();

        std::transform(list->begin(), list->end(), std::back_inserter(*vertices),
                       [](const Vertex & vertex) -> V { return vertex.name; });

        return vertices;
    }

    template<typename V, typename E>
    std::vector<E> * AdjacencyList<V, E>::edges() const {

        std::vector<E> * arr_edges = new std::vector<E>();

        std::for_each(list->begin(), list->end(), [& arr_edges] (const Vertex & vertex) -> void {
            arr_edges->insert(arr_edges->end(), vertex.outEdges.begin(), vertex.outEdges.end());
        });

        return arr_edges;
    }

    template<typename V, typename E>
    std::vector<std::pair<V, V>> * AdjacencyList<V, E>::endVertices(const E &edge) const {

        auto * end_vertices = new std::vector<std::pair<V, V>>();

        size_t i = 0;
        size_t j = 0;

        //Destination thread
        std::thread threadIn([this, & edge, & i, end_vertices] () -> void {
            std::for_each(list->begin(), list->end(), [this, & edge, & i, end_vertices](const Vertex &v) -> void {
                std::list<Vertex> &cList = v.inEdges;
                if (std::find(cList.begin(), cList.end(), edge) != cList.end()) {
                    std::lock_guard<std::mutex> lockGuard(mutex);
                    if (i++ == end_vertices->size())
                        end_vertices->emplace_back({}, v.name);
                    else
                        end_vertices[i - 1].first = v.name;
                }
            });
        });

        //Origin thread
        std::thread threadOut([this, & edge, & j, end_vertices] () -> void {
            std::for_each(list->begin(), list->end(), [this, & edge, & j, end_vertices](const Vertex &v) -> void {
                std::list<Vertex> &cList = v.outEdges;
                if (std::find(cList.begin(), cList.end(), edge) != cList.end()) {
                    std::lock_guard<std::mutex> lockGuard(mutex);
                    if (j++ == end_vertices->size())
                        end_vertices->emplace_back(v.name, {});
                    else
                        end_vertices[j - 1].second = v.name;
                }
            });
        });

        threadIn.join();
        threadOut.join();

        return end_vertices;
    }

    template<typename V, typename E>
    std::vector<E> * AdjacencyList<V, E>::outgoingEdges(const V &vertex) const {
        std::vector<E> * outgoingEdges = new std::vector<E>();

        std::for_each(list->begin(), list->end(), [outgoingEdges, & vertex] (const Vertex & v) -> void {
            if(v.name == vertex)
                outgoingEdges->insert(outgoingEdges->end(), v.outEdges.begin(), v.outEdges.end());
        });

        return outgoingEdges;
    }

    template<typename V, typename E>
    std::vector<E> * AdjacencyList<V, E>::incomingEdges(const V &vertex) const {
        std::vector<E> * incomingEdges = new std::vector<E>();

        std::for_each(list->begin(), list->end(), [incomingEdges, & vertex] (const Vertex & v) -> void {
            if(v.name == vertex)
                incomingEdges->insert(incomingEdges->end(), v.inEdges.begin(), v.inEdges.end());
        });

        return incomingEdges;
    }

    template<typename V, typename E>
    E AdjacencyList<V, E>::getEdge(const V &vertex1, const V &vertex2) const {
        typename std::list<Vertex>::iterator i_vertex_1 = std::find(list->begin(), list->end(), vertex1);
        typename std::list<Vertex>::iterator i_vertex_2 = std::find(list->begin(), list->end(), vertex2);

        if(i_vertex_1 != list->end() && i_vertex_2 != list->end()){
            std::set<E> edges;

            std::list<E> & v1 = i_vertex_1->outEdges;
            std::list<E> & v2 = i_vertex_2->inEdges;

            std::for_each(v1.begin(), v1.end(), [&edges] (const E & edge) -> E {
                return edge;
            });

            for (const E & e : v2)
                if (edges.contains(e))
                    return e;
        }

        throw std::logic_error("Edge doesn't exist\n");
    }

    template<typename V, typename E>
    std::vector<V> * AdjacencyList<V, E>::opposite(const V &vertex) const {

    }

    template<typename V, typename E>
    GraphAbstract<V, E> &AdjacencyList<V, E>::addVertex(const V &vertex) {
        if (list.contains(vertex))
            throw std::logic_error(vertex + " vertex already exists\n");
        list.insert({vertex, {}});

        return *this;
    }

    template<typename V, typename E>
    GraphAbstract<V, E> &AdjacencyList<V, E>::addEdge(const E &edge, const V &vertex1, const V &vertex2) {
        if (!list.contains(vertex1))
            throw std::logic_error(vertex1 + " vertex doesn't exists\n");
        if(!list.contains(vertex2))
            throw std::logic_error(vertex2 + " vertex doesn't exists\n");

        list[vertex1].insert(edge);
        list[vertex2].insert(edge);

        return *this;
    }

    template<typename V, typename E>
    GraphAbstract<V, E> &AdjacencyList<V, E>::removeVertex(const V &vertex) {
        if (!list.contains(vertex))
            throw std::logic_error(vertex + " vertex doesn't exist\n");

        list.erase(vertex);

        return *this;
    }

    template<typename V, typename E>
    GraphAbstract<V, E> &AdjacencyList<V, E>::removeEdge(const E &edge) {
        if (!containEdge(edge))
            throw std::logic_error(edge + " edge doesn't exist\n");
        for (std::pair<const V, std::unordered_set<E>> &p: list)
            if (p.second.contains(edge))
                p.second.erase(edge);

        return *this;
    }

    template<typename V, typename E>
    bool AdjacencyList<V, E>::containEdge(const E &edge) const {
        return std::ranges::any_of(list, [&edge]
                (const std::pair<const V, std::unordered_set<E>> &p) -> bool {
            return p.second.contains(edge);
        });
    }

    template<typename V, typename E>
    bool AdjacencyList<V, E>::containVertex(const V &vertex) const {
        return list.contains(vertex);
    }

    template<typename V, typename E>
    size_t AdjacencyList<V, E>::numVertices() {
        return list.size();
    }

    template<typename V, typename E>
    size_t AdjacencyList<V, E>::numEdges() {
        size_t numEdges = 0;
        for (const std::pair<const V, std::unordered_set<E>> &p: list)
            numEdges += p.second.size();
        return numEdges;
    }

    template<typename V, typename E>
    size_t AdjacencyList<V, E>::outDegree(const V &vertex) {
        if (!list.contains(vertex))
            throw std::logic_error(vertex + " vertex doesn't exist");
        return list[vertex].size();
    }

    template<typename V, typename E>
    size_t AdjacencyList<V, E>::inDegree(const V &vertex) {
        return outDegree(vertex);
    }

    template<typename V, typename E>
    GraphAbstract<V, E> &AdjacencyList<V, E>::print(std::ostream &ostream) {
        bool isFirst = true;
        for (const std::pair<const V, std::unordered_set<E>> &p: list) {
            ostream << "Vertex " << p.first << "\t";
            for (const E &edge: p.second) {
                if (isFirst) {
                    ostream << " " << edge;
                    isFirst = false;
                } else
                    ostream << " -> " << edge;
            }
            isFirst = true;
            ostream << '\n';
        }
        return *this;
    }

    template<typename V, typename E>
    AdjacencyList<V, E>::~AdjacencyList(){
        delete list;
    }
}

#endif