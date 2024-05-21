#pragma once

#include <vector>
#include <cstddef>
#include <iostream>

// id:322522806
// email:oriyaperel18@gmail.com

namespace ariel
{
    class Graph
    {
    private:
        std::vector<std::vector<int>> AdjacencyMatrix;
        int row;
        int col;
        bool directed;

    public:
        Graph();
        Graph(bool directed);
        const std::vector<std::vector<int>> &getGraph() const;
        void loadGraph(std::vector<std::vector<int>> AdjacencyMatrix);
        Graph(std::vector<std::vector<int>> AdjacencyMatrix);

        std::string toString() const;
        bool isdirected() const;
        void printGraph() const;
        int getNumEdge() const;
        size_t getNumVertices() const;

        Graph operator+(const Graph &other);
        Graph operator-(const Graph &other);
        Graph operator*(const Graph &other);
        Graph &operator+=(int scalar);
        Graph &operator-=(int scalar);

        Graph &operator+=(const Graph &other);
        Graph &operator-=(const Graph &other);
        Graph &operator-();
        Graph &operator+();
        Graph &operator*=(int scalar);
        Graph &operator--();           //--g
        Graph &operator++();           //++g
        Graph &operator--(int scalar); // g--
        Graph &operator++(int scalar); // g++

        bool operator<(const Graph &other);
        bool operator>(const Graph &other);
        bool operator==(const Graph &other);
        bool operator!=(const Graph &other);
        bool operator<=(const Graph &other);
        bool operator>=(const Graph &other);

        friend std::ostream &operator<<(std::ostream &output, const Graph &c);
    };
    bool contain(const Graph &g1, const Graph &g2);
}; // namespace ariel