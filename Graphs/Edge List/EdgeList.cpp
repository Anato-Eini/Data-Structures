#include <iostream>
#include "EdgeList.h"

std::vector<std::string> EdgeList::vertices() const{
    std::vector<std::string> vertices;
    for(const std::string &s: Vertices)
        vertices.push_back(s);
    return vertices;
}

std::vector<std::pair<std::string, Edge*>> EdgeList::edges() const{
    std::vector<std::pair<std::string, Edge*>> edges;
    for(const std::pair<const std::string, Edge*> &pair: Edges)
        edges.emplace_back(pair);
    return edges;
}

std::pair<std::string, std::string>* EdgeList::endVertices(const std::string& edge){
    if(Edges.contains(edge))
        return &Edges[edge]->pairVertex;
    return nullptr;
}

std::vector<std::pair<std::string, Edge*>> EdgeList::outgoingEdges(const std::string& vertex){
    std::vector<std::pair<std::string, Edge*>> outgoingEdges;
    for(const std::pair<const std::string, Edge*> &pair: Edges)
        if(pair.second->pairVertex.first == vertex || pair.second->pairVertex.second == vertex)
            outgoingEdges.emplace_back(pair);
    return outgoingEdges;
}

std::vector<std::pair<std::string, Edge*>> EdgeList::incomingEdges(const std::string& vertex){
    return outgoingEdges(vertex);
}

std::string EdgeList::getEdge(const std::string& vertex1, const std::string& vertex2){
    for(const std::pair<const std::string, Edge*>& pair: Edges)
        if((pair.second->pairVertex.first == vertex1 || pair.second->pairVertex.first == vertex2) &&
            (pair.second->pairVertex.second == vertex1 || pair.second->pairVertex.second == vertex2))
            return pair.first;
    return "";
}

std::vector<std::string> EdgeList::opposite(const std::string& vertex){
    std::vector<std::string> oppositeVertices;
    for(const std::pair<const std::string, Edge*>& pair: Edges) {
        if (pair.second->pairVertex.first == vertex)
            oppositeVertices.emplace_back(pair.second->pairVertex.second);
        else if(pair.second->pairVertex.second == vertex)
            oppositeVertices.emplace_back(pair.second->pairVertex.first);
    }
    return oppositeVertices;
}

void EdgeList::addVertex(const std::string& name){
    Vertices.insert(name);
}

void EdgeList::addEdge(const std::string& name, int weight, const std::string& vertex1, const std::string& vertex2){
    if(Edges.contains(name))
        std::cout << name << " edge already exists\n";
    else if(!Vertices.contains(vertex1))
        std::cout << vertex1 << " vertex doesn't exist\n";
    else if(!Vertices.contains(vertex2))
        std::cout << vertex2 << " vertex doesn't exist\n";
    else
        Edges.insert({name, new Edge{{vertex1, vertex2}, weight}});
}

void EdgeList::removeVertex(const std::string& vertex){
    auto iterator = Vertices.find(vertex);
    if(iterator != Vertices.end()){
        Vertices.erase(*iterator);
        for(const std::pair<const std::string, Edge*>& pair: Edges){
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
        for(const std::pair<const std::string, Edge*>& pair: Edges)
            if(pair.second->pairVertex.first == vertex || pair.second->pairVertex.second == vertex)
                numOutDegree++;
        return numOutDegree;
    }
    return -1;
}

int EdgeList::inDegree(const std::string& vertex){
    return outDegree(vertex);
}

bool EdgeList::containEdge(const std::string& edge) const{
    return Edges.contains(edge);
}
bool EdgeList::containVertex(const std::string& vertex) const{
    return Vertices.contains(vertex);
}

std::ostream& operator<<(std::ostream& os, EdgeList* edgeList){
    os << "Vertices:";
    for(const std::string& s: edgeList->Vertices)
        os << " " << s;
    os << "\nEdges:\n";
    for(const std::pair<const std::string, Edge*>& pair: edgeList->Edges)
        os << "Name: " << pair.first << "\t" << pair.second << '\n';
    return os;
}

std::ostream& operator<<(std::ostream& os, EdgeList& edgeList){
    os << "Vertices:";
    for(const std::string& s: edgeList.Vertices)
        os << " " << s;
    os << "\nEdges:\n";
    for(const std::pair<const std::string, Edge*>& pair: edgeList.Edges)
        os << "Name: " << pair.first << "\t" << pair.second << '\n';
    return os;
}

EdgeList::~EdgeList(){
    Vertices.clear();
    for(const std::pair<const std::string, Edge*>& pair: Edges)
        delete pair.second;
    Edges.clear();
}