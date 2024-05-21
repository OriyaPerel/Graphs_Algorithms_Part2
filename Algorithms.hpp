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

        bool isConnected(const ariel::Graph &g);
        int shortestPath(const ariel::Graph &g, size_t start, size_t end);
        std::string isContainsCycle(const ariel::Graph &g);
        std::string isBipartite(const ariel::Graph &g);
        std::string negativeCycle(const ariel::Graph &g);
}