#include "Algorithms.hpp"
#include "Graph.hpp"
#include <iostream>
#include <queue>
#include <stack>
#include <unordered_set>
#include <climits>
#include <cstddef>
#include <algorithm>
#include <iterator>
#include <string>
#include <sstream>

// id:322522806
// email:oriyaperel18@gmail.com

#define INFINITY 100000000

using namespace ariel;
namespace Algorithms
{
    void DFS(const Graph &g, size_t v, std::vector<bool> &visited)
    {
        visited[v] = true;
        for (size_t i = 0; i < g.getNumVertices(); ++i)
        {
            if (g.getGraph()[v][i] && !visited[i])
            {
                DFS(g, i, visited);
            }
        }
    }

    bool directedConnected(const Graph &g)
    {
        std::vector<bool> visited(g.getNumVertices(), false);
        // DFS from each vertex and mark reachable vertices
        for (size_t i = 0; i < g.getNumVertices(); ++i)
        {
            visited.assign(g.getNumVertices(), false); // update all the vertices to false
            DFS(g, i, visited);
        }
        for (bool v : visited)
        {
            if (!v)
            {
                std::cout << "Graph is not strongly connected" << std::endl;
                return false;
            }
        }
        std::cout << "Graph is strongly connected" << std::endl;
        return true;
    }

    bool undirectedConnected(const ariel:: Graph &g)
    {
        if (g.getGraph().empty())
        {
            throw std::invalid_argument("Invalid graph: The graph is empty");
            return false;
        }
        size_t numVertices = 0;
        numVertices = g.getNumVertices();
        std::vector<bool> visited(numVertices, false);

        DFS(g, 0, visited);

        for (size_t i = 0; i < numVertices; ++i)
        {
            if (!visited[i])
            {
                std::cout << "Graph is not connected" << std::endl;
                return false;
            }
        }
        std::cout << "Graph is connected" << std::endl;
        return true;
    }

    bool isConnected( const Graph &g)
    {
        if (g.getGraph().empty())
        {
            throw std::invalid_argument("Invalid graph: The graph is empty");
            return false;
        }
        if (g.isdirected())
        {
            return directedConnected(g);
        }
        else
        {
            return undirectedConnected(g);
        }
    }

    int printPath(std::vector<int> &parent, size_t src, size_t dest)
    {
        std::stack<size_t> path;
        size_t v = 0;
        v = dest;

        // Check if destination is reachable by checking if src is in the parent path
        bool reachable = false;
        while (v != SIZE_MAX && v != parent[v])
        {
            if (v == src && src != dest)
            {
                reachable = true;
                break;
            }
            path.push(v);
            v = static_cast<size_t>(parent[v]);
        }
        if (dest == src && path.size() > 3)
        {
            reachable = true;
        }

        if (!reachable && src != dest)
        {
            std::cout << "Shortest path not found between " << src << " to " << dest << std::endl;
            return 0;
        }

        // Print the shortest path
        std::cout << "Shortest path: " << src << " ";
        if (!path.empty())
        {
            std::cout << path.top();
            path.pop();
        }
        while (!path.empty())
        {
            std::cout << " " << path.top();
            path.pop();
        }
        std::cout << std::endl;
        return 1;
    }

    int shortestPath(const Graph &g, size_t src, size_t dest)
    {
        if (g.getGraph().empty())
        {
            throw std::invalid_argument("Invalid graph: The graph is empty");
            return 0;
        }
        size_t numVertices = g.getNumVertices();
        std::vector<int> dist(numVertices, INT_MAX);
        std::vector<int> parent(numVertices, -1);

        if (numVertices < src || numVertices < dest)
        {
            std::cout << "this vertex not exist" << std::endl;
            return 0;
        }

        dist[src] = 0;

        // Relax edges
        for (size_t i = 0; i < numVertices - 1; ++i)
        {
            for (size_t u = 0; u < numVertices; ++u)
            {
                for (size_t v = 0; v < numVertices; ++v)
                {
                    int weight = g.getGraph()[u][v];
                    if (weight && dist[u] != INT_MAX && dist[u] + weight < dist[v])
                    {
                        dist[v] = dist[u] + weight;
                        parent[v] = u;
                    }
                }
            }
        }
        for (size_t u = 0; u < g.getNumVertices(); ++u)
        {
            for (size_t v = 0; v < g.getNumVertices(); ++v)
            {
                int weight = g.getGraph()[u][v];
                if (weight != 0 && dist[u] != INT_MAX && dist[u] + weight < dist[v])
                {
                    std::cout << "Negative cycle found!" << std::endl;
                    return 0;
                }
            }
        }
        return printPath(parent, src, dest);
    }
    // this is a helper function to find a cycle and save it to the empty vector cycle in the input

    bool DFS1( const Graph &g, size_t v, int parent, std::vector<bool> &visited, std::vector<int> &cycle)
    {
        visited[v] = true;
        for (size_t i = 0; i < g.getNumVertices(); ++i)
        {
            if (g.getGraph()[v][i] != 0 && v != i)
            {
                if (!visited[i])
                {
                    if (DFS1(g, i, v, visited, cycle))
                    {
                        cycle.push_back(v);
                        return true; // Found a cycle
                    }
                }
                else if (i != parent)
                {
                    cycle.push_back(i);
                    cycle.push_back(v);
                    return true; // Cycle detected
                }
            }
        }
        return false; // No cycle found
    }

    std::string isContainsCycle(const Graph &g)
    {
        if (g.getGraph().empty())
        {
            throw std::invalid_argument("Invalid graph: The graph is empty");
            return 0;
        }

        if (!g.isdirected() && (g.getNumEdge() < 3) || (g.getNumVertices() < 3))
        // its cant be a undirected graph with less than 3 vertices or edge
        {
            return "No cycle found";
        }

        std::vector<bool> visited(g.getNumVertices(), false);
        std::vector<int> cycle;
        for (size_t i = 0; i < g.getNumVertices(); ++i)
        {
            if (!visited[i])
            {
                if (DFS1(g, i, -1, visited, cycle))
                {
                    std::string cycleStr = "Cycle: ";
                    std::reverse(cycle.begin(), cycle.end());
                    for (int vertex : cycle)
                    {
                        cycleStr += std::to_string(vertex) + " ";
                    }
                    return cycleStr;
                }
            }
        }
        return "No cycle found";
    }

    std::string isBipartite(const Graph &g)
    {
        if (g.getGraph().empty())
        {
            throw std::invalid_argument("Invalid graph: The graph is empty");
            return 0;
        }
        std::vector<int> colorArr(g.getNumVertices(), -1);
        std::vector<int> redElement, blueElement; // vectors to red and blue vertices

        std::queue<int> q;
        q.push(0);
        colorArr[0] = 0;
        redElement.push_back(0);
        while (!q.empty())
        {
            size_t u = 0;
            u = (size_t)q.front();
            q.pop();

            // Traverse adjacent vertices
            for (size_t v = 0; v < g.getNumVertices(); ++v)
            {
                if (g.getGraph()[u][v] != 0 && colorArr[v] == -1)
                {
                    colorArr[v] = 1 - colorArr[u]; // Assign alternate color to adjacent vertex
                    if (colorArr[v] == 0)
                    {
                        redElement.push_back(v);
                    }
                    else
                    {
                        blueElement.push_back(v);
                    }
                    q.push(v);
                }
                else if (g.getGraph()[u][v] != 0 && colorArr[v] == colorArr[u] && u != v)
                {
                    return "not Bipartite";
                }
            }
        }

        std::stringstream ss;
        ss << "The graph is bipartite: ";
        ss << "A={";
        for (size_t i = 0; i < redElement.size(); ++i)
        {
            ss << redElement[i];
            if (i != redElement.size() - 1)
            {
                ss << ", ";
            }
        }
        ss << "}, B={";
        for (size_t i = 0; i < blueElement.size(); ++i)
        {
            ss << blueElement[i];
            if (i != blueElement.size() - 1)
            {
                ss << ", ";
            }
        }
        ss << "}";

        return ss.str();
    }

    std::string negativeCycle(const Graph &g)
    {
        if (g.getGraph().empty())
        {
            throw std::invalid_argument("Invalid graph: The graph is empty");
            return 0;
        }
        
        std::vector<int> dist(g.getNumVertices(), INT_MAX);
        std::vector<int> parent(g.getNumVertices(), -1); // To store the parent vertex for each vertex

        // Assume the source vertex is 0
        size_t source = 0;
        dist[source] = 0;

        // Relax edges repeatedly
        for (size_t i = 0; i < g.getNumVertices() - 1; ++i)
        {
            for (size_t u = 0; u < g.getNumVertices(); ++u)
            {
                for (size_t v = 0; v < g.getNumVertices(); ++v)
                {
                    int weight = g.getGraph()[u][v];
                    if (weight != 0 && dist[u] != INT_MAX && dist[u] + weight < dist[v])
                    {
                        dist[v] = dist[u] + weight;
                        parent[v] = u; // Update parent of vertex v
                    }
                }
            }
        }

        // Check for negative cycles
        for (size_t u = 0; u < g.getNumVertices(); ++u)
        {
            for (size_t v = 0; v < g.getNumVertices(); ++v)
            {
                int weight = g.getGraph()[u][v];
                if (weight != 0 && dist[u] != INT_MAX && dist[u] + weight < dist[v])
                {
                    std::stringstream ss;
                    ss << "Negative cycle found! Cycle: ";

                    // Trace back to find the cycle
                    std::stack<size_t> cycle;
                    cycle.push(v);
                    size_t temp = static_cast<size_t>(parent[v]);
                    while (temp != v)
                    {
                        cycle.push(temp);
                        temp = static_cast<size_t>(parent[temp]);
                    }
                    cycle.push(v);

                    // put the vertices in the cycle to the string
                    while (!cycle.empty())
                    {
                        ss << cycle.top() << " ";
                        cycle.pop();
                    }
                    return ss.str(); // Return the string representing the negative cycle
                }
            }
        }
        return "No negative cycle found.";
    }
}