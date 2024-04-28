#include "AdjacencyMap.h"

std::vector<std::string> AdjacencyMap::vertices() const {
    std::vector<std::string> vertices;
    for(const std::pair<const std::string, std::unordered_map<std::string, std::string>> &p : Vertices)
        vertices.emplace_back(p.first);
    return vertices;
}

std::vector<std::string> AdjacencyMap::edges() const {
    std::vector<std::string> edges;
    for(const std::pair<const std::string, std::unordered_map<std::string, std::string>> &p : Vertices) {
        auto it =
                std::find_if_not(p.second.begin(), p.second.end(),
                                   [&edges](const std::pair<const std::string, std::string> &edgeVertices) -> bool {
                                       return std::any_of(edges.begin(), edges.end(),
                                                          [edgeVertices](const std::string &s) -> bool {
                                           return edgeVertices.first == s;
                                       });
                                   });
        if(it != p.second.end())
            edges.emplace_back(it->first);
    }
    return edges;
}

std::pair<std::string, std::string> AdjacencyMap::endVertices(const std::string &edge) {
    if(!containEdge(edge))
        throw std::logic_error(edge + " edge doesn't exist\n");
    std::pair<std::string, std::string> pairOfVertices{{}, {}};
    for(const std::pair<const std::string, std::unordered_map<std::string, std::string>> &vertexEdge: Vertices)
        if(vertexEdge.second.contains(edge)){
            if(pairOfVertices.first.empty())
                pairOfVertices.first = vertexEdge.first;
            else
                pairOfVertices.second = vertexEdge.first;
        }
    return pairOfVertices;
}

std::vector<std::string> AdjacencyMap::outgoingEdges(const std::string &vertex) {
    if(!containVertex(vertex))
        throw std::logic_error(vertex + " vertex doesn't exist\n");
    std::vector<std::string> edges;
    std::transform(Vertices[vertex].begin(), Vertices[vertex].end(), std::back_inserter(edges),
                   [](const std::pair<const std::string, std::string> &edge) -> std::string {
        return edge.first;
    });
    return edges;
}

std::vector<std::string> AdjacencyMap::incomingEdges(const std::string &vertex) {
    return outgoingEdges(vertex);
}

std::string AdjacencyMap::getEdge(const std::string &vertex1, const std::string &vertex2) {
    if(!containVertex(vertex1))
        throw std::logic_error(vertex1 + " vertex doesn't exist\n");
    else if(!containVertex(vertex2))
        throw std::logic_error(vertex2 + " vertex doesn't exist\n");
    std::string large = Vertices[vertex1].size() > Vertices[vertex2].size() ? vertex1 : vertex2
            , small = Vertices[vertex1].size() > Vertices[vertex2].size() ? vertex2 : vertex1;
    auto it =
            std::find_if(Vertices[small].begin(), Vertices[small].end(),
                         [&large](const std::pair<const std::string, std::string> &edgeVertex) -> bool {
                             return edgeVertex.second == large;
                         });
    if(it != Vertices[small].end())
        return it->first;
    return {};
}

std::vector<std::string> AdjacencyMap::opposite(const std::string &vertex) {
    if(!containVertex(vertex))
        throw std::logic_error(vertex + " vertex doesn't exists\n");
    std::vector<std::string> vertices;
    std::transform(Vertices[vertex].begin(), Vertices[vertex].end(), std::back_inserter(vertices),
                   [](const std::pair<const std::string, std::string> &edges) -> std::string{
        return edges.second;
    });
    return vertices;
}

void AdjacencyMap::addVertex(const std::string &vertex) {
    if(containVertex(vertex))
        throw std::logic_error(vertex + " vertex already exists\n");
    Vertices.insert({vertex, {}});
}

void AdjacencyMap::addEdge(const std::string &edge, const std::string &vertex1, const std::string &vertex2) {
    if(containEdge(edge))
        throw std::logic_error(edge + " edge already exists\n");
    else if(!containVertex(vertex1))
        throw std::logic_error(vertex1 + " vertex doesn't exists\n");
    else if(!containVertex(vertex2))
        throw std::logic_error(vertex2 + " vertex doesn't exists\n");
    Vertices[vertex1].insert({edge, vertex2});
    Vertices[vertex2].insert({edge, vertex1});
}

void AdjacencyMap::removeVertex(const std::string &vertex) {
    if(!containVertex(vertex))
        throw std::logic_error(vertex + " vertex doesn't exists\n");
    Vertices.erase(vertex);
    for(std::pair<const std::string, std::unordered_map<std::string, std::string>> & vertex1 : Vertices){
        auto it = std::ranges::find_if(
                vertex1.second, [&vertex](const std::pair<const std::string, std::string> &edgeVertex) -> bool {
            return edgeVertex.second == vertex;
        });
        if(it != vertex1.second.end())
            vertex1.second.erase(it->first);
    }
}

void AdjacencyMap::removeEdge(const std::string &edge) {
    if(!containEdge(edge))
        throw std::logic_error(edge + " edge doesn't exists\n");
    for(std::pair<const std::string, std::unordered_map<std::string, std::string>> & edges: Vertices)
        edges.second.erase(edge);
}

bool AdjacencyMap::containEdge(const std::string &edge) const {
    return std::ranges::any_of(Vertices, [&edge]
    (const std::pair<std::string, std::unordered_map<std::string, std::string>> &pair) -> bool {
        return pair.second.contains(edge);
    });
}

bool AdjacencyMap::containVertex(const std::string &vertex) const {
    return Vertices.contains(vertex);
}

int AdjacencyMap::numVertices() {
    return Vertices.size();
}

int AdjacencyMap::numEdges() {
    return edges().size();
}

int AdjacencyMap::outDegree(const std::string &vertex) {
    if(!containVertex(vertex))
        throw std::logic_error(vertex + " vertex doesn't exist\n");
    return Vertices[vertex].size();
}

int AdjacencyMap::inDegree(const std::string &vertex) {
    return outDegree(vertex);
}

void AdjacencyMap::print(std::ostream &ostream) {
    ostream << "Size: " << Vertices.size() << '\n';
    for(const std::pair<const std::string, std::unordered_map<std::string, std::string>> &pair: Vertices) {
        ostream << "Vertex " << pair.first << "\nEdges:\n";
        for (const std::pair<const std::string, std::string> &edgeVertex: pair.second)
            ostream << edgeVertex.first << " -> " << edgeVertex.second << '\n';
    }
}
