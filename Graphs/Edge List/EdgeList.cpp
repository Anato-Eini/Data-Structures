#include <iostream>
#include "EdgeList.h"

std::vector<std::string> EdgeList::vertices() const{
    std::vector<std::string> vertices;
    for(const std::string &s: Vertices)
        vertices.push_back(s);
    return vertices;
}

std::vector<Edge*> EdgeList::edges() const{
    std::vector<Edge*> edges;
    for(const std::pair<std::string, Edge*> pairs: Edges)
        edges.push_back(pairs.second);
    return edges;
}

std::pair<std::string, std::string>* EdgeList::endVertices(const std::string& edge){
    if(Edges.contains(edge))
        return &Edges[edge]->pairVertex;
    return nullptr;
}

std::vector<Edge*> EdgeList::outgoingEdges(const std::string& vertex){
    std::vector<Edge*> outgoingEdges;
    for(const std::pair<std::string, Edge*> pair: Edges)
        if(pair.second->pairVertex.first == vertex || pair.second->pairVertex.second == vertex)
            outgoingEdges.push_back(pair.second);
    return outgoingEdges;
}

std::vector<Edge*> EdgeList::incomingEdges(const std::string& vertex){
    return outgoingEdges(vertex);
}

Edge* EdgeList::getEdge(const std::string& vertex1, const std::string& vertex2){
    for(const std::pair<std::string, Edge*> pair: Edges)
        if((pair.second->pairVertex.first == vertex1 || pair.second->pairVertex.first == vertex2) &&
            (pair.second->pairVertex.second == vertex1 || pair.second->pairVertex.second == vertex2))
            return pair.second;
    return nullptr;
}

std::string EdgeList::opposite(const std::string& vertex){
    for(const std::pair<std::string, Edge*> pair: Edges) {
        if (pair.second->pairVertex.first == vertex)
            return pair.second->pairVertex.second;
        else if(pair.second->pairVertex.second == vertex)
            return pair.second->pairVertex.first;
    }
    return "";
}

void EdgeList::addVertex(const std::string& name){
    Vertices.insert(name);
}

void EdgeList::addEdge(const std::string& name, int weight, const std::string& vertex1, const std::string& vertex2){
    if(Edges.contains(name))
        std::cout << "Vertex already exists\n";
    else
        Edges.insert({name, new Edge{{vertex1, vertex2}, weight}});
}

void EdgeList::removeVertex(const std::string& vertex){
    auto iterator = Vertices.find(vertex);
    if(iterator != Vertices.end()){
        Vertices.erase(*iterator);
        for(const std::pair<std::string, Edge*> pair: Edges){
            if(pair.second->pairVertex.first == vertex || pair.second->pairVertex.second == vertex){
                delete pair.second;
                Edges.erase(pair.first);
            }
        }
    }else std::cout << "Vertex doesn't exist\n";
}

void EdgeList::removeEdge(const std::string& edge){
    auto iterator = Edges.find(edge);
    if(iterator != Edges.end()){
        delete iterator->second;
        Edges.erase(iterator);
    }else std::cout << "Edge doesn't exist\n";
}

int EdgeList::numVertices(){
    return Vertices.size();
}

int EdgeList::numEdges(){
    return Edges.size();
}

int EdgeList::outDegree(const std::string& vertex){
    auto iterator = Vertices.find(vertex);
    if(iterator != Vertices.end()){
        int numOutDegree = 0;
        for(const std::pair<std::string, Edge*> pair: Edges)
            if(pair.second->pairVertex.first == vertex || pair.second->pairVertex.second == vertex)
                numOutDegree++;
        return numOutDegree;
    }
    return -1;
}

int EdgeList::inDegree(const std::string& vertex){
    return outDegree(vertex);
}

std::ostream& operator<<(std::ostream& os, EdgeList* edgeList){
    os << "Vertices:";
    for(const std::string& s: edgeList->Vertices)
        os << " " << s;
    os << "Edges:\n";
    for(const std::pair<std::string, Edge*> pair: edgeList->Edges)
        os << "Name: " << pair.first << " " << pair.second << '\n';
    return os;
}

std::ostream& operator<<(std::ostream& os, EdgeList& edgeList){
    os << "Vertices:";
    for(const std::string& s: edgeList.Vertices)
        os << " " << s;
    os << "Edges:\n";
    for(const std::pair<std::string, Edge*> pair: edgeList.Edges)
        os << "Name: " << pair.first << " " << pair.second << '\n';
    return os;
}
