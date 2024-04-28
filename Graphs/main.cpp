#include <iostream>

#include "Edge List/EdgeList.h"
#include "Adjacency List/AdjacencyList.h"
#include "Adjacency Map/AdjacencyMap.h"
#include "Adjacency Matrix/AdjacencyMatrix.h"

int main(){
    //For testing different graphs implementation
    Graph* graph;
    char op;
    int number;
    std::string name, vertex1, vertex2;
    std::vector<std::string> array;
    std::pair<std::string, std::string> endVertices;
    do{
        std::cout << "1-Edge_List 2-Adjacency_List 3-Adjacency_Map 4-Adjacency_Matrix: ";
        std::cin >> number;
        switch (number) {
            case 1:
                graph = new EdgeList{};
                break;
            case 2:
                graph = new AdjacencyList{};
                break;
            case 3:
                graph = new AdjacencyMap{};
                break;
            case 4:
                graph = new AdjacencyMatrix{};
                break;
            default:
                std::cout << "Invalid operation\n";
        }
    } while (number < 1 || number > 4);
    do{
        std::cout << "Enter operation: ";
        std::cin >> op;
        try {
            switch (op) {
                case 'E':
                    std::cout << "Enter edge name: ";
                    std::cin >> name;
                    std::cout << "Enter the first vertex: ";
                    std::cin >> vertex1;
                    std::cout << "Enter the second vertex: ";
                    std::cin >> vertex2;
                    graph->addEdge(name, vertex1, vertex2);
                    break;
                case 'V':
                    std::cout << "Enter vertex name: ";
                    std::cin >> name;
                    graph->addVertex(name);
                    break;
                case 'P':
                    std::cout << graph;
                    break;
                case 'v':
                    array = graph->vertices();
                    std::cout << "Vertices:";
                    for (const std::string &s: array)
                        std::cout << " " << s;
                    break;
                case 'e':
                    array = graph->edges();
                    std::cout << "Edges:";
                    for (const std::string &pair: array)
                        std::cout << "\nName: " << pair;
                    break;
                case 'Q':
                    std::cout << "Enter edge: ";
                    std::cin >> name;
                    endVertices = graph->endVertices(name);
                    if (!endVertices.second.empty() && !endVertices.first.empty())
                        std::cout << "Vertex 1: " << endVertices.first << "\nVertex 2: " << endVertices.second;
                    else
                        std::cout << name << " edge doesn't exist";
                    break;
                case 'q':
                    std::cout << "Enter vertex: ";
                    std::cin >> name;
                    array = graph->outgoingEdges(name);
                    if (!array.empty()) {
                        std::cout << "Outgoing edges:";
                        for (std::string const &e: array)
                            std::cout << ' ' << e;
                    } else
                        std::cout << name << " doesn't have outgoing edges";
                    break;
                case 'I':
                    std::cout << "Enter vertex: ";
                    std::cin >> name;
                    array = graph->incomingEdges(name);
                    if (!array.empty()) {
                        std::cout << "Incoming edges:";
                        for (std::string const &e: array)
                            std::cout << ' ' << e;
                    } else
                        std::cout << name << " doesn't have incoming edges";
                    break;
                case 'G':
                    std::cout << "Enter vertex 1: ";
                    std::cin >> vertex1;
                    std::cout << "Enter vertex 2: ";
                    std::cin >> vertex2;
                    name = graph->getEdge(vertex1, vertex2);
                    if (!name.empty())
                        std::cout << "Edge: " << name;
                    else
                        std::cout << "Edge doesn't exist";
                    break;
                case 'o':
                    std::cout << "Enter vertex: ";
                    std::cin >> vertex1;
                    array = graph->opposite(vertex1);
                    if (array.empty())
                        std::cout << vertex1 << " doesn't exists";
                    else {
                        std::cout << "Opposite of " << vertex1 << ": ";
                        for (const std::string &s: array)
                            std::cout << s << ' ';
                    }
                    break;
                case 'R':
                    std::cout << "Enter vertex: ";
                    std::cin >> vertex1;
                    graph->removeVertex(vertex1);
                    break;
                case 'r':
                    std::cout << "Enter edge : ";
                    std::cin >> name;
                    graph->removeEdge(name);
                    break;
                case 'C':
                    std::cout << "Enter edge : ";
                    std::cin >> name;
                    std::cout << name << " edge" << (graph->containEdge(name) ? " " : " doesn't ") << "exists";
                    break;
                case 'c':
                    std::cout << "Enter vertex: ";
                    std::cin >> vertex1;
                    std::cout << vertex1 << " vertex" << (graph->containVertex(vertex1) ? " " : " doesn't ") <<
                                                                                                    "exists";
                    break;
                case 'N':
                    std::cout << "Number of vertices: " << graph->numVertices();
                    break;
                case 'n':
                    std::cout << "Number of edges: " << graph->numEdges();
                    break;
                case 'D':
                    std::cout << "Enter vertex: ";
                    std::cin >> vertex1;
                    number = graph->outDegree(vertex1);
                    std::cout << vertex1 << " vertex" << (number == -1 ? " doesn't exist" :
                                                                    " incoming edges: " + std::to_string(number));
                    break;
                case 'd':
                    std::cout << "Enter vertex: ";
                    std::cin >> vertex1;
                    number = graph->outDegree(vertex1);
                    std::cout << vertex1 << " vertex" << (number == -1 ? " doesn't exist" :
                                                                     " outgoing edges: " + std::to_string(number));
                    break;
                case 't':
                    delete graph;
                    do{
                        std::cout << "1-Edge_List 2-Adjacency_List 3-Adjacency_Map: ";
                        std::cin >> number;
                        switch (number) {
                            case 1:
                                graph = new EdgeList{};
                                break;
                            case 2:
                                graph = new AdjacencyList{};
                                break;
                            case 3:
                                graph = new AdjacencyMap{};
                                break;
                            default:
                                std::cout << "Invalid operation\n";
                        }
                    } while (number < 1 || number > 3);
                    break;
                default:
                    std::cout << "Invalid operation";
            }
        } catch (const std::exception& e) {
            std::cerr << e.what();
        }
        std::cout << '\n';
    }while(op != 'X' && op != 'x');
}