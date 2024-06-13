#include "Graph.hpp"
#include <iostream>
#include <sstream>

// id:322522806
// email:oriyaperel18@gmail.com

namespace ariel
{
    Graph::Graph()
    {
        this->directed = true;
    }

    Graph::Graph(bool directed)
    {
        this->directed = directed;
    }

    Graph::Graph(std::vector<std::vector<int>> matrix)
    {
        this->AdjacencyMatrix = matrix;
        this->numVertices = matrix.size();
        this->directed = true;
    }

    const std::vector<std::vector<int>> &Graph::getGraph() const
    {
        return this->AdjacencyMatrix;
    }

    bool Graph::isdirected() const
    {
        return this->directed;
    }

    int Graph::getNumEdge() const
    // return the number of edges in the graph if the graph is directed return the number of edges
    // if the graph is undirected return the number of edges divided by 2
    {
        int count = 0;
        int V = this->numVertices;
        for (size_t i = 0; i < V; i++)
        {
            for (size_t j = 0; j < V; j++)
            {
                if (AdjacencyMatrix[i][j] != 0) // if the edge is exist
                {
                    count++;
                }
            }
        }
        if (this->directed)
        {
            return count;
        }
        return (count / 2);
    }

    size_t Graph::getNumVertices() const
    {
        return this->AdjacencyMatrix.size();
    }

    void Graph::printGraph() const
    {
        int V = this->numVertices;
        int E = this->getNumEdge();
        for (size_t i = 0; i < V; i++)
        {
            for (size_t j = 0; j < V; j++)
            {
                std::cout << AdjacencyMatrix[i][j] << " ";
            }
            std::cout << std::endl;
        }
        if (this->directed == true)
        {
            std::cout << "Graph with " << numVertices << " vertices and " << E << " edges" << std::endl;
        }
        else
        {
            std::cout << "Graph with " << numVertices << " vertices and " << E / 2 << " edges" << std::endl;
        }
    }

    void Graph::loadGraph(std::vector<std::vector<int>> inputgraph)
    {
        if (inputgraph.empty())
        {
            throw std::invalid_argument("Invalid graph: The graph is empty");
            return;
        }
        size_t r = inputgraph.size();

        for (size_t i = 0; i < r; ++i)
        {
            if (inputgraph[i].size() != r)
            {
                throw std::invalid_argument("Invalid graph: The graph is not a square matrix.");
                return;
            }
        }
        this->AdjacencyMatrix = inputgraph;
        this->numVertices = r;
    }

    std::string Graph::toString() const
    {
        std::stringstream output;

        for (size_t i = 0; i < numVertices; i++)
        {
            output << "[";
            for (size_t j = 0; j < numVertices; j++)
            {
                if (j != 0)
                {
                    output << ", ";
                }
                output << getGraph()[i][j];
            }
            output << "]" << '\n';
        }

        return output.str();
    }

    Graph Graph::operator+(const Graph &other)
    {
        if (this->numVertices != other.numVertices) // if the size of the graphs is different we can't add them
        {
            throw std::invalid_argument("can't add two graphs with different size");
        }
        std::vector<std::vector<int>> g((size_t)this->numVertices, std::vector<int>((size_t)this->numVertices));
        for (size_t i = 0; i < this->numVertices; i++)
        {
            for (size_t j = 0; j < this->numVertices; j++)
            {
                g[i][j] = this->getGraph()[i][j] + other.getGraph()[i][j];
            }
        }
        return Graph(g);
    }
    
    Graph Graph::operator-(const Graph &other)
    {
        if (this->numVertices != other.numVertices) // if the size of the graphs is different we can't subtract them
        {
            throw std::invalid_argument("can't add two graphs with different size");
        }
        std::vector<std::vector<int>> result((size_t)this->numVertices, std::vector<int>((size_t)this->numVertices));
        for (size_t i = 0; i < this->numVertices; i++)
        {
            for (size_t j = 0; j < this->numVertices; j++)
            {
                result[i][j] = this->getGraph()[i][j] - other.getGraph()[i][j];
            }
        }
        return Graph(result);
    }

    Graph &Graph::operator-() // unary operator  -g
    {
        return *this *= (-1);
    }

    Graph &Graph::operator+() // unary operator +g
    {
        return *this *= 1;
    }

    Graph &Graph::operator/=(int num)
    {

        for (size_t i = 0; i < numVertices; i++)
        {
            for (size_t j = 0; j < numVertices; j++)
            {
                this->AdjacencyMatrix[i][j] /= num;
            }
        }
        return *this;
    }

    Graph &Graph::operator+=(int scalar)
    {
        for (size_t i = 0; i < this->numVertices; ++i)
        {
            for (size_t j = 0; j < this->numVertices; ++j)
            {
                if (this->AdjacencyMatrix[i][j] != 0)
                { // add scalar only to edge that existed
                    this->AdjacencyMatrix[i][j] += scalar;
                }
            }
        }
        return *this; // Return a reference to the modified graph
    }
    Graph &Graph::operator-=(int scalar)
    {
        for (size_t i = 0; i < this->numVertices; ++i)
        {
            for (size_t j = 0; j < this->numVertices; ++j)
            {
                if (this->AdjacencyMatrix[i][j] != 0)
                { // sub scalar only to edge that existed
                    this->AdjacencyMatrix[i][j] -= scalar;
                }
            }
        }
        return *this; // Return a reference to the modified graph
    }

    Graph &Graph::operator++()
    {
        return *this += 1; // using the += operator
    }

    Graph &Graph::operator--()
    {
        return *this -= 1; // using the -= operator
    }

    Graph Graph::operator++(int num) // g++
    {
        Graph oldGrap;                      // copy the graph
        oldGrap.loadGraph(AdjacencyMatrix); // load the graph
        *this += (1);                       // using the += operator and add 1 to the graph
        return oldGrap;                     // return the old graph
    }
    Graph Graph::operator--(int num) // g--
    {
        Graph oldGrap;                      // copy the graph
        oldGrap.loadGraph(AdjacencyMatrix); // load the graph
        *this -= (1);                       // using the -= operator and subtract 1 from the graph
        return oldGrap;                     // return the old graph
    }

    bool Graph::operator==(const Graph &other)
    {
        if (this->numVertices == other.numVertices) // the matrix in the seem size and the same values
        {
            for (size_t i = 0; i < this->numVertices; i++)
            {
                for (size_t j = 0; j < this->numVertices; j++)
                {
                    if (this->AdjacencyMatrix[i][j] != other.AdjacencyMatrix[i][j])
                    {
                        return false;
                    }
                }
            }
            return true;
        }

        else if (!(*this < other) && !(*this > other)) // if the graphs are not equal and the size is different
        {
            return true;
        }

        return false;
    }

    bool Graph::operator!=(const Graph &other)
    {
        if (this->numVertices == other.numVertices) // the matrix in the seem size
        {
            for (size_t i = 0; i < this->numVertices; i++)
            {
                for (size_t j = 0; j < this->numVertices; j++)
                {
                    if (this->AdjacencyMatrix[i][j] != other.AdjacencyMatrix[i][j])
                    {
                        return true;
                    }
                }
            }
            return false;
        }

        else if (this->getNumEdge() != other.getNumEdge()) // if the number of edges is different
        {
            return true;
        }
        return true;
    }

    bool contain(const Graph &g1, const Graph &g2)
    {                                                  // if g1 contained in g2 (g1<g2)
        if (g1.getNumVertices() > g2.getNumVertices()) // if the size of g1 is bigger than g2 it can't be contained
        {
            return false;
        }

        for (size_t i = 0; i < g1.getNumVertices(); i++)
        {
            for (size_t j = 0; j < g1.getNumVertices(); j++) // Iterate over the columns of this
            {
                if (g1.getGraph()[i][j] != 0 && g2.getGraph()[i][j] == 0) // if the edge in g1 is not in g2
                {
                    return false;
                }
            }
        }
        return true;
    }

    bool Graph::operator>(const Graph &other) // this>other
    {
        if ((contain(other, *this) == true) && (*this != other)) // if other contianed in this -> this>other
        {
            return true;
        }
        else if (!contain(*this, other) && !contain(other, this) && *this != other)
        {
            // if neither of the graphs is conteined by the other and
            // they aren't equal we need to check the number of edges
            if (this->getNumEdge() > other.getNumEdge())
            {
                return true;
            }
            else if (this->getNumEdge() == other.getNumEdge())
            {
                if (this->numVertices > other.numVertices)
                {
                    return true;
                }
            }
        }
        return false;
    }

    bool Graph::operator<(const Graph &other)
    {
        return (*this != other) && (!(*this > other));
    }

    bool Graph::operator<=(const Graph &other)
    {
        if (*this < other || *this == other)
        {
            return true;
        }
        return false;
    }

    bool Graph::operator>=(const Graph &other)
    {
        if (*this > other || *this == other)
        {
            return true;
        }
        return false;
    }

    std::ostream &operator<<(std::ostream &output, const Graph &g)
    {
        output << "graph" << "\n";
        for (size_t i = 0; i < g.numVertices; i++)
        {
            output << "[";
            for (size_t j = 0; j < g.numVertices; j++)
            {
                if (j != 0)
                {
                    output << ", ";
                }
                output << g.getGraph()[i][j];
            }
            output << "]" << "\n";
        }

        return output;
    }

    Graph &Graph::operator*=(int scalar)
    {
        for (size_t i = 0; i < numVertices; ++i)
        {
            for (size_t j = 0; j < numVertices; ++j)
            {
                this->AdjacencyMatrix[i][j] *= scalar;
            }
        }
        return *this;
    }

    Graph &Graph::operator+=(const Graph &other)
    {
        for (size_t i = 0; i < numVertices; ++i)
        {
            for (size_t j = 0; j < numVertices; ++j)
            {
                this->AdjacencyMatrix[i][j] += other.AdjacencyMatrix[i][j];
            }
        }
        return *this; // Return the modified graph
    }

    Graph &Graph::operator-=(const Graph &other)
    {
        for (size_t i = 0; i < numVertices; ++i)
        {
            for (size_t j = 0; j < numVertices; ++j)
            {
                this->AdjacencyMatrix[i][j] -= other.AdjacencyMatrix[i][j];
            }
        }
        return *this; // Return the modified graph
    }

    Graph Graph::operator*(const Graph &other)
    {
        // Check if the dimensions of the graphs are compatible for multiplication
        if (this->numVertices != other.numVertices)
        {
            throw std::invalid_argument("Can not multiply graphs with differnt size");
        }

        std::vector<std::vector<int>> result((size_t)this->numVertices, std::vector<int>((size_t)other.numVertices));
        for (size_t i = 0; i < this->numVertices; ++i)
        {
            for (size_t j = 0; j < other.numVertices; ++j)
            {
                for (size_t k = 0; k < this->numVertices; ++k)
                {
                    result[i][j] += this->AdjacencyMatrix[i][k] * other.AdjacencyMatrix[k][j];
                }
            }
        }
        for (size_t i = 0; i < this->numVertices; i++) // the diagonal should be 0
        {
            result[i][i] = 0;
        }

        return Graph(result); // Return the resulting graph
    }

}
