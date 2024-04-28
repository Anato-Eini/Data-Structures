#include "AdjacencyMap.h"

std::vector<std::string> AdjacencyMap::vertices() const {
    std::vector<std::string> vertices;
    for(const std::pair<const std::string, std::unordered_map<std::string, std::string>> &p : Vertices)
        vertices.emplace_back(p.first);
    return vertices;
}

std::vector<std::string> AdjacencyMap::edges() const {
    std::vector<std::string> edges;
    for(const std::pair<const std::string, std::unordered_map<std::string, std::string>> &p : Vertices)
        for(const std::pair<const std::string, std::string> &vertexEdge: p.second) {
            if(std::any_of(edges.begin(), edges.end(), [&p](const std::string& string) -> bool {
                return p.second.contains(string);
            }))
                continue;
            edges.emplace_back(vertexEdge.first);
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
    //TODO Minimize codes here
    if(Vertices[vertex1].size() < Vertices[vertex2].size()){
        auto it =
                std::find_if(Vertices[vertex1].begin(), Vertices[vertex1].end(),
                               [&vertex2](const std::pair<const std::string, std::string> &edgeVertex) -> bool {
                                   return edgeVertex.second == vertex2;
                               });
        if(it != Vertices[vertex1].end())
            return it->first;
    }else{
        auto it =
                std::find_if(Vertices[vertex2].begin(), Vertices[vertex2].end(),
                               [&vertex1](const std::pair<const std::string, std::string> &edgeVertex) -> bool {
                                   return edgeVertex.second == vertex1;
                               });
        if(it != Vertices[vertex2].end())
            return it->first;
    }
    return {};
}

std::vector<std::string> AdjacencyMap::opposite(const std::string &vertex) {
    if(!containVertex(vertex))
        throw std::logic_error(vertex + " vertex doesn't exists\n");
    std::vector<std::string> vertices;
    for(const std::pair<const std::string, std::unordered_map<std::string, std::string>> &pair : Vertices){
        if(pair.first == vertex){
            for(const std::pair<const std::string, std::string> &edges : pair.second)
                vertices.emplace_back(edges.second);
            return vertices;
        }
    }
    return {};
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
    for(std::pair<const std::string, std::unordered_map<std::string, std::string>> & edges: Vertices)
        if(edges.second.contains(edge))
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
    std::unordered_set<std::string> edges;
    for(const std::pair<const std::string, std::unordered_map<std::string, std::string>> &pair: Vertices)
        for(const std::pair<const std::string, std::string> &pair1 : pair.second)
            edges.insert(pair1.first);
    return edges.size();
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
