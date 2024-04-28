#include "AdjacencyList.h"

std::vector<std::string> AdjacencyList::vertices() const {
    std::vector<std::string> vertices;
    for(const std::pair<const std::string, std::unordered_set<std::string>>& pair: list)
        vertices.emplace_back(pair.first);
    return vertices;
}

std::vector<std::string> AdjacencyList::edges() const {
    std::vector<std::string> edges;
    for(const std::pair<const std::string, std::unordered_set<std::string>>& pair: list)
        for(const std::string &s : pair.second) {
            if (std::any_of(edges.begin(), edges.end(), [&s](const std::string &string) -> bool {
                return s == string;
            }))
                continue;
            edges.emplace_back(s);
        }
    return edges;
}

std::pair<std::string, std::string> AdjacencyList::endVertices(const std::string &edge) {
    if(!containEdge(edge))
        throw std::logic_error(edge + " edge doesn't exist\n");
    std::pair<std::string, std::string> pairVertices({}, {});
    for(const std::pair<const std::string, std::unordered_set<std::string>>& pair: list)
        for(const std::string& e: pair.second){
            if(e == edge){
                if(pairVertices.first.empty())
                    pairVertices.first = pair.first;
                else
                    pairVertices.second = pair.first;
            }
        }
    return pairVertices;
}

std::vector<std::string> AdjacencyList::outgoingEdges(const std::string &vertex) {
    std::vector<std::string> outgoingEdges;
    if(list.contains(vertex))
        for(const std::string& edges: list[vertex])
            outgoingEdges.emplace_back(edges);
    return outgoingEdges;
}

std::vector<std::string> AdjacencyList::incomingEdges(const std::string &vertex) {
    return outgoingEdges(vertex);
}

std::string AdjacencyList::getEdge(const std::string &vertex1, const std::string &vertex2) {
    if(!containVertex(vertex1))
        throw std::logic_error(vertex1 + " vertex doesn't exist\n");
    else if(!containVertex(vertex2))
        throw std::logic_error(vertex2 + " vertex doesn't exist\n");
    if(list[vertex1].size() > list[vertex2].size()) {
        for(const std::string& edge: list[vertex2])
            if(list[vertex1].contains(edge))
                return edge;
    }else{
        for(const std::string& edge: list[vertex1])
            if(list[vertex2].contains(edge))
                return edge;
    }
    return {};
}

std::vector<std::string> AdjacencyList::opposite(const std::string &vertex) {
    if(!containVertex(vertex))
        throw std::logic_error(vertex + " vertex doesn't exist\n");
    std::vector<std::string> oppositeVertices;
    for(const std::pair<const std::string, std::unordered_set<std::string>> &pair: list)
        if(pair.first != vertex)
            for(const std::string& edge: list[vertex])
                if(pair.second.contains(edge)){
                    oppositeVertices.emplace_back(pair.first);
                    break;
                }
    return oppositeVertices;
}

void AdjacencyList::addVertex(const std::string &vertex) {
    if(list.contains(vertex))
        throw std::logic_error(vertex + " vertex already exists\n");
    list.insert({vertex, {}});
}

void
AdjacencyList::addEdge(const std::string &edge, const std::string &vertex1, const std::string &vertex2) {
    if(!list.contains(vertex1))
        throw std::logic_error(vertex1 + " vertex doesn't exists\n");
    else if(!list.contains(vertex2))
        throw std::logic_error(vertex2 + " vertex doesn't exists\n");
    else if(list[vertex1].contains(edge) || list[vertex2].contains(edge))
        throw std::logic_error (edge + " edge already exists\n");
    else{
        list[vertex1].insert(edge);
        list[vertex2].insert(edge);
    }
}

void AdjacencyList::removeVertex(const std::string &vertex) {
    if(!list.contains(vertex))
        throw std::logic_error(vertex + " vertex doesn't exist\n");
    list.erase(vertex);
}

void AdjacencyList::removeEdge(const std::string &edge) {
    if(!containEdge(edge))
        throw std::logic_error(edge + " edge doesn't exist\n");
    for(std::pair<const std::string, std::unordered_set<std::string>> &p: list)
        if(p.second.contains(edge))
            p.second.erase(edge);
}

bool AdjacencyList::containEdge(const std::string &edge) const {
    return std::ranges::any_of(list, [&edge]
        (const std::pair<const std::string, std::unordered_set<std::string>> &p) -> bool {
        return p.second.contains(edge);
    });
}

bool AdjacencyList::containVertex(const std::string &vertex) const {
    return list.contains(vertex);
}

int AdjacencyList::numVertices() {
    return list.size();
}

int AdjacencyList::numEdges() {
    int numEdges = 0;
    for(const std::pair<const std::string, std::unordered_set<std::string>> &p: list)
        numEdges += p.second.size();
    return numEdges;
}

int AdjacencyList::outDegree(const std::string &vertex) {
    if(!list.contains(vertex))
        throw std::logic_error(vertex + " vertex doesn't exist");
    return list[vertex].size();
}

int AdjacencyList::inDegree(const std::string &vertex) {
    return outDegree(vertex);
}

void AdjacencyList::print(std::ostream &ostream) {
    bool isFirst = true;
    for(const std::pair<const std::string, std::unordered_set<std::string>> &p: list) {
        ostream << "Vertex " << p.first << "\t";
        for(const std::string& edge: p.second) {
            if(isFirst) {
                ostream << " " << edge;
                isFirst = false;
            }else
                ostream << " -> " << edge;
        }
        isFirst = true;
        ostream << '\n';
    }
}