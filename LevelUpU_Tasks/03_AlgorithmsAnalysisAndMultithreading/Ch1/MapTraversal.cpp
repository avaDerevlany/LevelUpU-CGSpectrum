/*
* Actually using Dijkstra's searching algorithm
2. Write an A* implementation that reads coordinates labeled (x,y,cost) where x & y are letters that define a
   connection, and cost is a number that represents the cost.

   Sample map to traverse:
      (a,b,5)
      (b,c,1)
      (a,d,7)
      (c,d,1)

   Sample path request:
      (a,d)

3. The program should determine if it's possible to reach a destination given the starting point.
   It should also find the cheapest path, making sure to output the cost of the path
*/

#include "..\Section3Header.h"
#include <string>
#include <vector>
#include <limits>
#include <iostream>

// The maps are directional. The traversal also cannot handle cyclical cases.
void MapTraversal(Node startingNode, Node endingNode)
{
    // return the path from start to end
    // if empty, there is no path

    std::vector<Node*> shortestPath;
    std::vector<Node*> currentPath = { &startingNode };
    int shortestCost = std::numeric_limits<int>::max();
    RecursveTraversal(shortestPath, shortestCost, startingNode, endingNode.name, currentPath);

    if (shortestPath.size() == 0)
    {
        // there was no route from start node to end node
        std::cout << "There is no path from " << startingNode.name << " to " << endingNode.name << "." << std::endl;
    }
    else
    {
        std::cout << "Cheapest path from " << startingNode.name << " to " << endingNode.name << " cost " << shortestCost << ". " << VectorToString(shortestPath) << std::endl;
    }
}

void RecursveTraversal(std::vector<Node*>& shortestPath, int& shortestCost, Node& node, std::string endNode, std::vector<Node*> currentPath, int currentCost)
{
    //std::cout << "Recursive Traversal of node " << node.name << " # children = " << std::to_string(node.connections.size()) << std::endl;

    if (node.name == endNode)
    {
        //std::cout << "Reached the end node path:" << VectorToString(currentPath) << " cost: " << std::to_string(currentCost) << std::endl;
        if (currentCost < shortestCost)
        {
            //std::cout << "Current is shorter then path:" << VectorToString(shortestPath) << " cost: " << std::to_string(shortestCost) << std::endl;
            shortestCost = currentCost;
            shortestPath = currentPath;
        }
    }

    else
    {
        // go though all of node's connections
        for (int i = 0; i < node.connections.size(); i++)
        {
            //std::cout << "Checking parent node " << node.name << "\'s child node " << node.connections[i].toNode->name << std::endl;
            currentPath.push_back(node.connections[i].toNode);
            currentCost += node.connections[i].cost;
            RecursveTraversal(shortestPath, shortestCost, *node.connections[i].toNode, endNode, currentPath, currentCost);
            currentPath.erase(currentPath.end() - 1);
            currentCost -= node.connections[i].cost;
        }
    }
}