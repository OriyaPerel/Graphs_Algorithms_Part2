#include "Graph.hpp"
#include <cstddef>
#include <iostream>
#include <vector>
#include <queue>
#include <string>

// id:322522806
// email:oriyaperel18@gmail.com

namespace Algorithms
{
        bool isConnected(const ariel::Graph &g);                                  // check if the graph is connected
        std::string shortestPath(const ariel::Graph &g, size_t src, size_t dest); // return the shortest path between two vertices
        std::string isContainsCycle(const ariel::Graph &g);                       // check if the graph contains a cycle
        std::string isBipartite(const ariel::Graph &g);                           // check if the graph is bipartite
        std::string negativeCycle(const ariel::Graph &g);                         // check if the graph contains a negative cycle
}
