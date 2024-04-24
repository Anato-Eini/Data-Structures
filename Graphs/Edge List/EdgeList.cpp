#include <iostream>
#include "EdgeList.h"

std::vector<std::string> EdgeList::vertices() const{
    std::vector<std::string> vertices;
    for(const std::string &s: Vertices)
        vertices.push_back(s);
    return vertices;
}

std::vector<std::string> EdgeList::edges() const{
    std::vector<std::string> edges;
    for(const std::pair<const std::string, std::pair<std::string, std::string>> &pair: Edges)
        edges.emplace_back(pair.first);
    return edges;
}

std::pair<std::string, std::string> EdgeList::endVertices(const std::string& edge){
    auto it = Edges.find(edge);
    if(it == Edges.end())
        throw std::logic_error(edge + " edge doesn't exist\n");
    return it->second;
}

std::vector<std::string> EdgeList::outgoingEdges(const std::string& vertex){
    if(!Vertices.contains(vertex))
        throw std::logic_error(vertex + " vertex doesn't exists\n");
    std::vector<std::string> outgoingEdges;
    for(const std::pair<const std::string, std::pair<std::string, std::string>> &pair: Edges)
        if(pair.second.first == vertex || pair.second.second == vertex)
            outgoingEdges.emplace_back(pair.first);
    return outgoingEdges;
}

std::vector<std::string> EdgeList::incomingEdges(const std::string& vertex){
    return outgoingEdges(vertex);
}

std::string EdgeList::getEdge(const std::string& vertex1, const std::string& vertex2){
    if(!containVertex(vertex1))
        throw std::logic_error(vertex1 + " vertex doesn't exist\n");
    else if(!containVertex(vertex2))
        throw std::logic_error(vertex2 + " vertex doesn't exist\n");
    for(const std::pair<const std::string, std::pair<std::string, std::string>>& pair: Edges)
        if((pair.second.first == vertex1 || pair.second.first == vertex2) &&
            (pair.second.second == vertex1 || pair.second.second == vertex2))
            return pair.first;
    return "";
}

std::vector<std::string> EdgeList::opposite(const std::string& vertex){
    if(!containVertex(vertex))
        throw std::logic_error(vertex + " vertex doesn't exist\n");
    std::vector<std::string> oppositeVertices;
    for(const std::pair<const std::string, std::pair<std::string, std::string>>& pair: Edges) {
        if (pair.second.first == vertex)
            oppositeVertices.emplace_back(pair.second.second);
        else if(pair.second.second == vertex)
            oppositeVertices.emplace_back(pair.second.first);
    }
    return oppositeVertices;
}

void EdgeList::addVertex(const std::string& vertex){
    if(Vertices.contains(vertex))
        throw std::logic_error(vertex + " vertex already exists\n");
    Vertices.insert(vertex);
}

void EdgeList::addEdge(const std::string& name, const std::string& vertex1, const std::string& vertex2){
    if(Edges.contains(name))
        throw std::logic_error(name + " edge already exists\n");
    else if(!Vertices.contains(vertex1))
        throw std::logic_error(vertex1 + " vertex doesn't exist\n");
    else if(!Vertices.contains(vertex2))
        throw std::logic_error(vertex2 + " vertex doesn't exist\n");
    else
        Edges.insert({name, {vertex1, vertex2}});
}

void EdgeList::removeVertex(const std::string& vertex){
    auto iterator = Vertices.find(vertex);
    if(iterator != Vertices.end()){
        Vertices.erase(*iterator);
        std::vector<std::string> to_be_deleted;
        for(std::pair<const std::string, std::pair<std::string, std::string>>& pair: Edges)
            if (pair.second.first == vertex || pair.second.second == vertex)
                to_be_deleted.emplace_back(pair.first);
        for(const std::string& edge: to_be_deleted)
            Edges.erase(edge);
    }else throw std::logic_error(vertex + " vertex doesn't exist\n");
}

void EdgeList::removeEdge(const std::string& edge){
    auto iterator = Edges.find(edge);
    if(iterator != Edges.end())
        Edges.erase(iterator);
    else
        throw std::logic_error(edge + " edge doesn't exist\n") ;
}

int EdgeList::numVertices(){
    return (int)Vertices.size();
}

int EdgeList::numEdges(){
    return (int)Edges.size();
}

int EdgeList::outDegree(const std::string& vertex){
    if(!containVertex(vertex))
        throw std::logic_error(vertex + " vertex doesn't exist\n");
    auto iterator = Vertices.find(vertex);
    if(iterator != Vertices.end()){
        int numOutDegree = 0;
        for(const std::pair<const std::string,std::pair<std::string, std::string> >& pair: Edges)
            if(pair.second.first == vertex || pair.second.second == vertex)
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

void EdgeList::print(std::ostream &ostream) {
    ostream << "Vertices:";
    for(const std::string& s: Vertices)
        ostream << " " << s;
    ostream << "\nEdges:\n";
    for(const std::pair<const std::string, std::pair<std::string, std::string>>& pair: Edges)
        ostream << "Name: " << pair.first << " <" << pair.second.first << ", " << pair.second.second << ">\n";
}