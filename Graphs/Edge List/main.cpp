#include <iostream>

#include "EdgeList.h"

int main(){
    //For testing graph edge list implementation
    auto* edgelist = new EdgeList{};
    char op;
    int weight, number;
    std::string name, vertex1, vertex2;
    std::vector<std::string> vertices, oppositeEdges;
    std::vector<std::pair<std::string, Edge*>> edges;
    std::vector<std::pair<std::string, Edge*>> outgoingEdges, incomingEdges;
    std::pair<std::string, std::string>* endVertices = nullptr;
    do{
        std::cout << "Enter operation: ";
        std::cin >> op;
        switch (op) {
            case 'E':
                std::cout << "Enter edge name: ";
                std::cin >> name;
                std::cout << "Enter edge weight: ";
                std::cin >> weight;
                std::cout << "Enter the first vertex: ";
                std::cin >> vertex1;
                do {
                    std::cout << "Enter the second vertex: ";
                    std::cin >> vertex2;
                    if(vertex1 == vertex2)
                        std:: cout << "Second vertex must be unique from the first vertex\n";
                }while(vertex1 == vertex2);
                edgelist->addEdge(name, weight, vertex1, vertex2);
                break;
            case 'V':
                std::cout << "Enter vertex name: ";
                std::cin >> name;
                edgelist->addVertex(name);
                break;
            case 'P':
                std::cout << edgelist;
                break;
            case 'v':
                vertices = edgelist->vertices();
                std::cout << "Vertices:";
                for(const std::string& s: vertices)
                    std::cout << " " << s;
                break;
            case 'e':
                edges = edgelist->edges();
                std::cout << "Edges:";
                for(const std::pair<std::string, Edge*>& pair: edges)
                    std::cout << "\nName: " << pair.first << "\t" << pair.second;
                break;
            case 'Q':
                std::cout << "Enter edge: ";
                std::cin >> name;
                endVertices = edgelist->endVertices(name);
                if(endVertices)
                    std::cout << "Vertex 1: " << endVertices->first << "\nVertex 2: " << endVertices->second;
                else
                    std::cout << name << " edge doesn't exist";
                break;
            case 'q':
                std::cout << "Enter vertex: ";
                std::cin >> name;
                if(edgelist->containVertex(name)) {
                    outgoingEdges = edgelist->outgoingEdges(name);
                    if (!outgoingEdges.empty()) {
                        std::cout << "Outgoing edges:";
                        for (std::pair<std::string, Edge*>const & e: outgoingEdges)
                            std::cout << ' ' << e.first;
                    } else
                        std::cout << name << " doesn't have outgoing edges";
                }else
                    std::cout << "Vertex doesn't exists";
                break;
            case 'I':
                std::cout << "Enter vertex: ";
                std::cin >> name;
                if(edgelist->containVertex(name)) {
                    incomingEdges = edgelist->incomingEdges(name);
                    if (!incomingEdges.empty()) {
                        std::cout << "Incoming edges:";
                        for (std::pair<std::string, Edge*>const & e: incomingEdges)
                            std::cout << ' ' << e.first;
                    } else
                        std::cout << name << " doesn't have incoming edges";
                }else
                    std::cout << "Vertex doesn't exists";
                break;
            case 'G':
                std::cout << "Enter vertex 1: ";
                std::cin >> vertex1;
                std::cout << "Enter vertex 2: ";
                std::cin >> vertex2;
                name = edgelist->getEdge(vertex1, vertex2);
                if(!name.empty())
                    std::cout << "Edge: " << name;
                else
                    std::cout << "Edge doesn't exist";
                break;
            case 'o':
                std::cout << "Enter vertex: ";
                std::cin >> vertex1;
                oppositeEdges = edgelist->opposite(vertex1);
                if(name.empty())
                   std::cout << vertex1 << " doesn't exists";
                else {
                    std::cout << "Opposite of " << vertex1 << ": ";
                    for(const std::string& s: oppositeEdges)
                        std::cout << s << ' ';
                }
                break;
            case 'R':
                std::cout << "Enter vertex: ";
                std::cin >> vertex1;
                edgelist->removeVertex(vertex1);
                break;
            case 'r':
                std::cout << "Enter edge : ";
                std::cin >> name;
                edgelist->removeEdge(name);
                break;
            case 'C':
                std::cout << "Enter edge : ";
                std::cin >> name;
                std::cout << name << " edge" << (edgelist->containEdge(name) ? " " : " doesn't ") << "exists";
                break;
            case 'c':
                std::cout << "Enter vertex: ";
                std::cin >> vertex1;
                std::cout << vertex1 << " vertex" << (edgelist->containVertex(vertex1) ? " " : " doesn't ") << "exists";
                break;
            case 'N':
                std::cout << "Number of vertices: " << edgelist->numVertices();
                break;
            case 'n':
                std::cout << "Number of edges: " << edgelist->numEdges();
                break;
            case 'D':
                std::cout << "Enter vertex: ";
                std::cin >> vertex1;
                number = edgelist->outDegree(vertex1);
                std::cout << vertex1 << " vertex" << (number == -1 ? " doesn't exist" : " incoming edges: " +
                                                                                        std::to_string(number));
                break;
            case 'd':
                std::cout << "Enter vertex: ";
                std::cin >> vertex1;
                number = edgelist->outDegree(vertex1);
                std::cout << vertex1 << " vertex " << (number == -1 ? " doesn't exist" : " outgoing edges: " +
                                                                                         std::to_string(number));
                break;
            default:
                std::cout << "Invalid operation";
        }
        delete endVertices;
        endVertices = nullptr;
        std::cout << '\n';
    }while(op != 'X' && op != 'x');
}