#pragma once
#include <vector>
#include <string>
#include <vector>

// Ch 1
void BubbleSort(int vectorToSort[], int size);

class Node;
class Traversal;
void MapTraversal(Node startingNode, Node endingNode);
void RecursveTraversal(std::vector<Node*>& shortestPath, int& shortestCost, Node& node, std::string endNode, std::vector<Node*> currentPath, int currentCost = 0);

// Helper funcitons
uint32_t GetNanos();
std::string VectorToString(std::vector<int> vectorToConvert);
std::string VectorToString(std::vector<Node*> vectorToConvert);
std::string ArrayToString(int vectorToConvert[], int size);



// Ch 1 classes
class Node
{
public:
    std::string name;
    std::vector<Traversal> connections;

    Node(std::string name = "", std::vector<Traversal> connections = {})
        : name(name), connections(connections)
    {

    }
    ~Node()
    {

    }
};

class Traversal
{
public:
    Node* toNode;
    int cost;

    Traversal()
        :cost(0)
    {

    }
    Traversal(Node* toNode, int cost)
        : toNode(toNode), cost(cost)
    {

    }
    ~Traversal()
    {

    }
};


// Ch 3
void HelloWorldThread();
void HelloWorldExample();
