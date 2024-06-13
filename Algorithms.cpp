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
        visited[v] = true; // mark the vertex v as visited
        for (size_t i = 0; i < g.getNumVertices(); ++i)
        {
            if (g.getGraph()[v][i] && !visited[i]) // check if there is an edge between v and i and i is not visited
            {
                DFS(g, i, visited);
            }
        }
    }

    bool directedConnected(const Graph &g)
    // check if directed graph is strongly connected
    //(run DFS from all vertices and check if all vertices are visited)
    {
        for (size_t i = 0; i < g.getNumVertices(); ++i)
        {
            std::vector<bool> visited(g.getNumVertices(), false); // update all the vertices to false
            DFS(g, i, visited);

            // Check if all vertices were visited during the DFS from vertex i
            for (bool v : visited)
            {
                if (!v)
                {
                    std::cout << "Graph is not strongly connected" << std::endl;
                    return false;
                }
            }
        }
        std::cout << "Graph is strongly connected" << std::endl;
        return true;
    }

    bool undirectedConnected(const ariel::Graph &g)
    // check if undirected graph is connected
    //(run DFS from a single vertex and check if all vertices are visited)
    {
        size_t numVertices = 0;
        numVertices = g.getNumVertices();
        std::vector<bool> visited(numVertices, false);

        DFS(g, 0, visited); // Start DFS from vertex 0

        for (size_t i = 0; i < numVertices; ++i) // check if all the vertices are visited
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

    bool isConnected(const Graph &g)
    { // check if the graph is connected or not
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

    bool bellmanFord(const Graph &g, size_t src, std::vector<int> &dist, std::vector<int> &parent)
    {
        // this function is a helper function to find the shortest path if there is negative cycle between two vertices
        // return true if there is path and false if there is a negative cycle
        size_t numVertices = g.getNumVertices();
        dist.assign(numVertices, INT_MAX);
        parent.assign(numVertices, -1);

        dist[src] = 0;

        // Relax edges n-1 times
        for (size_t i = 0; i < numVertices - 1; ++i)
        {
            for (size_t u = 0; u < numVertices; ++u)
            {
                for (size_t v = 0; v < numVertices; ++v)
                {
                    int weight = g.getGraph()[u][v];
                    if (weight && dist[u] != INT_MAX && dist[u] + weight < dist[v])
                    {
                        dist[v] = dist[u] + weight; // Update the distance
                        parent[v] = u;              // Update the parent
                    }
                }
            }
        }

        // Check for negative cycles
        for (size_t u = 0; u < numVertices; ++u)
        {
            for (size_t v = 0; v < numVertices; ++v)
            {
                int weight = g.getGraph()[u][v];
                if (weight != 0 && dist[u] != INT_MAX && dist[u] + weight < dist[v])
                {
                    std::cout << "Negative cycle found!" << std::endl;
                    return false;
                }
            }
        }

        return true;
    }

    std::string buildPath(std::vector<int> &parent, size_t src, size_t dest)
    { // this function is a helper function to build the path between two vertices
        std::vector<size_t> path;
        size_t v = dest; // this is the vertex we want to reach

        bool reachable = false;

        if (dest == src) // if the source and the destination are the same
        {
            return "this is the same vertex";
        }

        while (v != SIZE_MAX && v != parent[v]) // Check if destination is reachable by checking if src is in the parent path
        {
            if (v == src) // if we reach the source vertex
            {
                reachable = true;
                break;
            }
            path.push_back(v);                  // push the vertex to the path
            v = static_cast<size_t>(parent[v]); // update the vertex to the parent of the vertex
        }

        if (!reachable && src != dest)
        {
            return "No path found"; // Return if no path is found
        }
        path.push_back(src); // push the source vertex to the path

        // Reverse the path to get it from source to destination
        std::reverse(path.begin(), path.end());

        // Convert the path to a string
        std::string pathStr;
        for (size_t i = 0; i < path.size(); ++i)
        {
            pathStr += std::to_string(path[i]);
            if (i != path.size() - 1)
            {
                pathStr += "->";
            }
        }

        return pathStr;
    }

    std::string shortestPath(const Graph &g, size_t src, size_t dest)
    {
        if (g.getGraph().empty()) // check if the graph is empty
        {
            throw std::invalid_argument("Invalid graph: The graph is empty");
        }

        if (g.getNumVertices() <= src || g.getNumVertices() <= dest) // check if the vertices exist
        {
            throw std::invalid_argument("Invalid vertex: The vertex does not exist");
        }

        std::vector<int> dist, parent;
        if (bellmanFord(g, src, dist, parent) == false) // check if there is a path between the vertices
        {
            return "No path found"; // Return a message if no path is found
        }

        return buildPath(parent, src, dest); // build and return the path as a string
    }

    // this is a helper function to find a cycle and save it to the empty vector cycle in the input
    bool DFS1(const Graph &g, size_t v, int parent, std::vector<bool> &visited, std::vector<int> &cycle)
    {
        visited[v] = true; // mark the vertex as visited
        for (size_t i = 0; i < g.getNumVertices(); ++i)
        {
            if (g.getGraph()[v][i] != 0 && v != i)
            {
                if (!visited[i]) // if the vertex is not visited yet
                {
                    if (DFS1(g, i, v, visited, cycle)) // if there is a cycle from the vertex i to the vertex v
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
        if (g.getGraph().empty()) // check if the graph is empty
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
                if (DFS1(g, i, -1, visited, cycle)) // if there is a cycle
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
        if (g.getGraph().empty()) // check if the graph is empty
        {
            throw std::invalid_argument("Invalid graph: The graph is empty");
        }
        std::vector<int> colorArr(g.getNumVertices(), -1); // vector to save the color of each vertex
        std::vector<int> redElement, blueElement;          // vectors to red and blue vertices

        for (size_t start = 0; start < g.getNumVertices(); ++start)
        {
            if (colorArr[start] != -1) // if the vertex is already colored continue to the next vertex
                continue;

            std::queue<int> q;
            q.push(start);
            colorArr[start] = 0; // update the color of the vertex to red 
            redElement.push_back(start);
            while (!q.empty())
            {
                size_t u = 0;
                u = (size_t)q.front(); // get the vertex from the queue
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
                        q.push(v); // push the  new vertex that we found and colored to the queue
                    }
                    else if (g.getGraph()[u][v] != 0 && colorArr[v] == colorArr[u] && u != v)
                    {
                        return "not Bipartite";
                    }
                }
            }
        }
        std::stringstream ss; // create a string stream to return the result
        ss << "The graph is bipartite: ";
        ss << "A={";
        for (size_t i = 0; i < redElement.size(); ++i) // put the red vertices in the string
        {
            ss << redElement[i];
            if (i != redElement.size() - 1)
            {
                ss << ", ";
            }
        }
        ss << "}, B={";
        for (size_t i = 0; i < blueElement.size(); ++i) // put the blue vertices in the string
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
        if (g.getGraph().empty()) // check if the graph is empty
        {
            throw std::invalid_argument("Invalid graph: The graph is empty");
            return 0;
        }

        std::vector<int> dist;
        std::vector<int> parent;

        // Assume the source vertex is 0
        size_t source = 0;

        // Use bellmanFord to find shortest paths and check for negative cycles
        bool noNegativeCycle = bellmanFord(g, source, dist, parent);

        if (noNegativeCycle == true)
        {
            return "No negative cycle found.";
        }
        else
        {
            // Find the negative cycle
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
        }
        return "No negative cycle found";
    }
} // namespace Algorithms
