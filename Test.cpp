#include "doctest.h"
#include "Algorithms.hpp"
#include "Graph.hpp"

// id:322522806
// email:oriyaperel18@gmail.com

using namespace std;

TEST_CASE("Test graph addition subtraction")
{
    ariel::Graph g1;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g1.loadGraph(graph);
    ariel::Graph g2;
    vector<vector<int>> weightedGraph = {
        {0, 1, 1},
        {1, 0, 2},
        {1, 2, 0}};
    g2.loadGraph(weightedGraph);
    ariel::Graph g3 = g1 + g2;
    vector<vector<int>> expectedGraph = {
        {0, 2, 1},
        {2, 0, 3},
        {1, 3, 0}};
    CHECK(g3.toString() == "[0, 2, 1]\n[2, 0, 3]\n[1, 3, 0]\n");

    ariel::Graph g4 = g1 - g2;
    CHECK(g4.toString() == "[0, 0, -1]\n[0, 0, -1]\n[-1, -1, 0]\n");
}

TEST_CASE(" +=, -= operations")
{
    ariel::Graph g1;
    vector<vector<int>> graph1 = {
        {0, 1, 0},
        {0, 0, 1},
        {0, 1, 0}};
    g1.loadGraph(graph1);

    ariel::Graph g2;
    vector<vector<int>> graph2 = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g2.loadGraph(graph2);

    g1 += g2;
    CHECK(g1.toString() == "[0, 2, 0]\n[1, 0, 2]\n[0, 2, 0]\n");

    g1 -= g2;
    CHECK(g1.toString() == "[0, 1, 0]\n[0, 0, 1]\n[0, 1, 0]\n");
}

TEST_CASE("- and - unary")
{
    ariel::Graph g1;
    vector<vector<int>> graph = {
        {0, 2, 0},
        {2, 2, 2},
        {0, -1, 0}};
    g1.loadGraph(graph);

    g1 = -g1;
    CHECK(g1.toString() == "[0, -2, 0]\n[-2, -2, -2]\n[0, 1, 0]\n");
    g1 = +g1;
    CHECK(g1.toString() == "[0, -2, 0]\n[-2, -2, -2]\n[0, 1, 0]\n");
}

TEST_CASE("Test graph multiplication")
{
    ariel::Graph g1;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g1.loadGraph(graph);
    ariel::Graph g2;
    vector<vector<int>> weightedGraph = {
        {0, 1, 1},
        {1, 0, 2},
        {1, 2, 0}};
    g2.loadGraph(weightedGraph);
    ariel::Graph g4 = g1 * g2;

    CHECK(g4.toString() == "[0, 0, 2]\n[1, 0, 1]\n[1, 0, 0]\n");
    // cout<<g4;
}

TEST_CASE("Invalid operations")
{
    ariel::Graph g1;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g1.loadGraph(graph);
    ariel::Graph g2;
    vector<vector<int>> weightedGraph = {
        {0, 1, 1},
        {1, 0, 2},
        {1, 2, 0}};
    g2.loadGraph(weightedGraph);
    ariel::Graph g5;
    vector<vector<int>> graph2 = {
        {0, 1, 0, 0, 1},
        {1, 0, 1, 0, 0},
        {0, 1, 0, 1, 0},
        {0, 0, 1, 0, 1},
        {1, 0, 0, 1, 0}};
    g5.loadGraph(graph2);
    CHECK_THROWS(g5 * g1);

    // Addition of two graphs with different dimensions
    ariel::Graph g6;
    vector<vector<int>> graph3 = {
        {0, 1, 0, 0, 1},
        {1, 0, 1, 0, 0},
        {0, 1, 0, 1, 0},
        {0, 0, 1, 0, 1},
        {1, 0, 0, 1, 0}};
    g6.loadGraph(graph3);
    CHECK_THROWS(g1 + g6);
}

TEST_CASE("== and != operations")
{
    ariel::Graph g1;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g1.loadGraph(graph);

    ariel::Graph g2;
    vector<vector<int>> weightedGraph = {
        {0, 2, 0},
        {2, 0, 2},
        {0, 2, 0}};
    g2.loadGraph(weightedGraph);

    CHECK(g1 != g2); // seem size differnt edeg

    g2 -= g1; // subtract the graph so that they are identical
    CHECK(g1 == g2);

    ariel::Graph g3;
    vector<vector<int>> graph2 = {
        {0, 1, 0, 0},
        {1, 0, 1, 0},
        {0, 3, 0, 0},
        {0, 0, 0, 0}};
    g3.loadGraph(graph2);
    CHECK_FALSE(g1 == g3);
}

TEST_CASE("<,> ,=>,<=operations")
{
    ariel::Graph g1;
    vector<vector<int>> graph1 = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g1.loadGraph(graph1);

    ariel::Graph g2;
    vector<vector<int>> graph2 = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g2.loadGraph(graph2);

    CHECK_FALSE(g2 > g1); // the graphs are equel
    CHECK(g1 >= g2);

    ariel::Graph g3;
    vector<vector<int>> graph3 = {
        {0, 1, 1},
        {1, 0, 1},
        {1, 1, 0}};
    g3.loadGraph(graph3);

    ariel::Graph g4;
    vector<vector<int>> graph4 = {
        {0, 1, 1, 0},
        {3, 0, 1, 0},
        {2, 1, 0, 0},
        {0, 0, 0, 0}};
    g4.loadGraph(graph4);
    CHECK(g4 > g3);

    ariel::Graph g5;
    vector<vector<int>> graph5 = {
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0}};
    g5.loadGraph(graph5);

    CHECK_FALSE(g5 > g4); // graph 0 (g5) isn't contined graph
    CHECK_FALSE(g5 >= g4);
}

TEST_CASE("empty graph")
{
    ariel::Graph g1;
    vector<vector<int>> graph1 = {};
    CHECK_THROWS(g1.loadGraph(graph1));
}

TEST_CASE("-- and ++ oparator")
{
    // if the edeg is 0 this operator dose nothing to it
    ariel::Graph g1;
    vector<vector<int>> graph = {
        {0, 2, 0},
        {2, 0, 2},
        {0, -1, 0}};
    g1.loadGraph(graph);

    g1++;
    CHECK(g1.toString() == "[0, 3, 0]\n[3, 0, 3]\n[0, 0, 0]\n");

    g1--;
    CHECK(g1.toString() == "[0, 2, 0]\n[2, 0, 2]\n[0, 0, 0]\n");

    ariel::Graph g2;
    vector<vector<int>> graph2 = {
        {0, 0, 0},
        {2, 0, 2},
        {0, -1, 0}};
    g2.loadGraph(graph2);

    // cout<<g2;

    --g2;
    CHECK(g2.toString() == "[0, 0, 0]\n[1, 0, 1]\n[0, -2, 0]\n");

    ++g2;
    CHECK(g2.toString() == "[0, 0, 0]\n[2, 0, 2]\n[0, -1, 0]\n");
}

TEST_CASE("multiply by scalar")
{
    ariel::Graph g1;
    vector<vector<int>> graph = {
        {0, 2, 0},
        {2, 0, 2},
        {0, -1, 0}};
    g1.loadGraph(graph);

    g1 *= 2;
    CHECK(g1.toString() == "[0, 4, 0]\n[4, 0, 4]\n[0, -2, 0]\n");

    g1 *= -2; // negative scalar
    CHECK(g1.toString() == "[0, -8, 0]\n[-8, 0, -8]\n[0, 4, 0]\n");
}

TEST_CASE("divide by scalar")
{
    ariel::Graph g1;
    vector<vector<int>> graph = {
        {0, 2, 0},
        {2, 0, 2},
        {0, -2, 0}};
    g1.loadGraph(graph);

    g1 /= 2;
    CHECK(g1.toString() == "[0, 1, 0]\n[1, 0, 1]\n[0, -1, 0]\n");
}

TEST_CASE("algorithms")
{
    ariel::Graph g1;
    vector<vector<int>> mat3 = {
        {0, 1, 1},
        {1, 0, 1},
        {1, 1, 0}};
    g1.loadGraph(mat3);
    CHECK(Algorithms::shortestPath(g1, 1, 2) == "1->2");
    CHECK(Algorithms::negativeCycle(g1) == "No negative cycle found.");
    -g1;
    CHECK(Algorithms::negativeCycle(g1) == "Negative cycle found! Cycle: 1 2 1 ");
    CHECK(Algorithms::shortestPath(g1, 1, 2) == "No path found");
}
