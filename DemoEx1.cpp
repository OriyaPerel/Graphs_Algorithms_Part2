/*
 * Demo program for Exercise 2.
 * Author: Benjamin Saldman.
 */

#include "Graph.hpp"
#include "Algorithms.hpp"

#include <iostream>
#include <stdexcept>
#include <vector>

// id:322522806
// email:oriyaperel18@gmail.com

using namespace std;

int main()
{
    ariel::Graph g(true);
    // 3x3 matrix that represents a connected graph.
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g.loadGraph(graph); // Load the graph to the object.
    cout << "directed?:" << endl;
    cout << g.isdirected() << endl;

    g.printGraph();                                    // Should print: "Graph with 3 vertices and 4 edges."
    cout << Algorithms::isConnected(g) << endl;        // Should print: "1" (true).
    cout << Algorithms::shortestPath(g, 0, 2) << endl; // Should print: 0->1->2.
    cout << Algorithms::isContainsCycle(g) << endl;    // Should print: "0" (false).
    cout << Algorithms::isBipartite(g) << endl;        // Should print: "The graph is bipartite: A={0, 2}, B={1}."

    // 5x5 matrix that represents a non-connected graph with a cycle.
    vector<vector<int>> graph2 = {
        {0, 1, 1, 0, 0},
        {1, 0, 1, 0, 0},
        {1, 1, 0, 1, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0}};

    g.loadGraph(graph2); // Load the graph to the object.

    g.printGraph();                                    // Should print: "Graph with 5 vertices and 8 edges."
    cout << Algorithms::isConnected(g) << endl;        // Should print: "0" (false).
    cout << Algorithms::shortestPath(g, 0, 4) << endl; // Should print: "-1" (there is no path between 0 and 4).
    cout << Algorithms::isContainsCycle(g) << endl;    // Should print: "The cycle is: 0->1->2->0".
    cout << Algorithms::isBipartite(g) << endl;        // Should print: "0" (false).

    // 5x5 matrix that reprsents a connected weighted graph.
    vector<vector<int>> graph3 = {
        {0, 1, 0, 0, 0},
        {1, 0, 3, 0, 0},
        {0, 3, 0, 4, 0},
        {0, 0, 4, 0, 5},
        {0, 0, 0, 5, 0}};
    g.loadGraph(graph3); // Load the graph to the object.

    g.printGraph();                                    // Should print: "Graph with 5 vertices and 10 edges."
    cout << Algorithms::isConnected(g) << endl;        // Should print: "1" (true).
    cout << Algorithms::shortestPath(g, 0, 4) << endl; // Should print: 0->2->3->4.
    cout << Algorithms::isContainsCycle(g) << endl;    // Should print: "0" (false).
    cout << Algorithms::isBipartite(g) << endl;        // Should print: "The graph is bipartite: A={0, 2, 4}, B={1, 3}."

    // 5x4 matrix that reprsents invalid graph.
    vector<vector<int>> graph4 = {
        {0, 1, 2, 0},
        {1, 0, 3, 0},
        {2, 3, 0, 4},
        {0, 0, 4, 0},
        {0, 0, 0, 5}};
    try
    {
        g.loadGraph(graph4); // Load the graph to the object.
    }
    catch (const std::invalid_argument &e)
    {
        cout << e.what() << endl; // Should print: "Invalid graph: The graph is not a square matrix."
    }

    vector<vector<int>> graph5 = {
        {0, -1, 4, 0, 0},
        {0, 0, 3, 2, 2},
        {1, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {-3, 0, 0, 1, 0}};
    g.loadGraph(graph5);
    g.printGraph();
    cout << Algorithms::negativeCycle(g) << endl; // should print :"Negative cycle found! Cycle: 1 4 0 1"

    ariel::Graph g1(false);
    vector<vector<int>> graph6 = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g1.loadGraph(graph6);

    g1.printGraph();

    cout << g1.isdirected() << endl;
    cout << Algorithms::isContainsCycle(g1) << endl; // should print :"no cycle found"
    cout << g1.getNumEdge() << endl;                 // 2
    cout << Algorithms::isConnected(g1) << endl;     // this graph is connected

    ariel::Graph g2(true);
    vector<vector<int>> graph7 = {
        {0, 1, 0},
        {0, 0, 1},
        {0, 0, 0}};
    g2.loadGraph(graph7);

    g2.printGraph();
    cout << Algorithms::isConnected(g2) << endl; // this graph is  not connected

    return 0;
}