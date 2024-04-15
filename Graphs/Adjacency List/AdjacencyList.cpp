#include <iostream>
#include <algorithm>
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
        for(const std::string &edge : pair.second)
            edges.emplace_back(edge);
    return edges;
}

std::pair<std::string, std::string> AdjacencyList::endVertices(const std::string &edge) {
    std::pair<std::string, std::string> pairVertices("", "");
    for(const std::pair<const std::string, std::unordered_set<std::string>>& pair: list)
        for(const std::string& e: pair.second){
            if(pairVertices.first.empty() && e == edge)
                pairVertices.first = pair.first;
            else if(e == edge)
                pairVertices.second = pair.first;
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
    std::unordered_set<std::string> edgeV1, edgeV2;
    for(const std::pair<const std::string, std::unordered_set<std::string>>& pair: list){
        if(pair.first == vertex1)
            edgeV1 = pair.second;
        else if(pair.first == vertex2)
            edgeV2 = pair.second;
    }
    if(edgeV1.size() > edgeV2.size()) {
        for(const std::string& edge: edgeV2)
            if(edgeV1.contains(edge))
                return edge;
    }else{
        for(const std::string& edge: edgeV1)
            if(edgeV2.contains(edge))
                return edge;
    }
    return {};
}

std::vector<std::string> AdjacencyList::opposite(const std::string &vertex) {
    std::vector<std::string> oppositeVertices;
    for(const std::pair<const std::string, std::unordered_set<std::string>> &pair: list)
        if(pair.first != vertex){
            for(const std::string& edge: list[vertex])
                if(pair.second.contains(edge)){
                    oppositeVertices.emplace_back(pair.first);
                    break;
                }
        }
    return oppositeVertices;
}

void AdjacencyList::addVertex(const std::string &vertex) {
    list.insert({vertex, {}});
}

void
AdjacencyList::addEdge(const std::string &edge, const std::string &vertex1, const std::string &vertex2) {
    if(!list.contains(vertex1))
        throw std::logic_error(vertex1 + " doesn't exists");
    else if(!list.contains(vertex2))
        throw std::logic_error(vertex2 + " doesn't exists");
    else if(list[vertex1].contains(edge) || list[vertex2].contains(edge))
        throw std::logic_error (edge + " edge already exists");
    else{
        list[vertex1].insert(edge);
        list[vertex2].insert(edge);
    }
}

void AdjacencyList::removeVertex(const std::string &vertex) {
    if(!list.contains(vertex))
        throw std::logic_error(vertex + " vertex doesn't exist");
    list.erase(vertex);
}

void AdjacencyList::removeEdge(const std::string &edge) {
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
                std::cout << " " << edge;
                isFirst = false;
            }else
                std::cout << " -> " << edge;
        }
        isFirst = true;
        std::cout << '\n';
    }
}