#include "Graph.hpp"
#include <iostream>
#include <sstream>

// id:322522806
// email:oriyaperel18@gmail.com

namespace ariel
{
    Graph::Graph()
    { // default constructor
        this->directed = true;
    }

    Graph::Graph(bool directed)
    {
        this->directed = directed;
    }

    Graph::Graph(std::vector<std::vector<int>> matrix)
    {
        this->AdjacencyMatrix = matrix;
        this->row = matrix.size();
        this->col = matrix[0].size();
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
    {
        int count = 0;
        int V = this->col;
        for (size_t i = 0; i < V; i++)
        {
            for (size_t j = 0; j < V; j++)
            {
                if (AdjacencyMatrix[i][j] != 0)
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
        int count = 0;
        int V = this->col;
        for (size_t i = 0; i < V; i++)
        {
            for (size_t j = 0; j < V; j++)
            {
                std::cout << AdjacencyMatrix[i][j] << " ";
                if (AdjacencyMatrix[i][j] != 0)
                {
                    count++;
                }
            }
            std::cout << std::endl;
        }
        if (this->directed == true)
        {
            std::cout << "Graph with " << row << " vertices and " << count << " edges" << std::endl;
        }
        else
        {
            std::cout << "Graph with " << row << " vertices and " << count / 2 << " edges" << std::endl;
        }
    }

    void Graph::loadGraph(std::vector<std::vector<int>> ingraph)
    {
        if (ingraph.empty())
        {
            throw std::invalid_argument("Invalid graph: The graph is empty");
            return;
        }
        size_t r = ingraph.size();
        size_t c = ingraph[0].size();

        for (size_t i = 0; i < r; ++i)
        {
            if (ingraph[i].size() != r)
            {
                throw std::invalid_argument("Invalid graph: The graph is not a square matrix.");
                return;
            }
        }
        this->AdjacencyMatrix = ingraph;
        this->row = r;
        this->col = c;
    }

    std::string Graph::toString() const
    {
        std::stringstream output;

        for (size_t i = 0; i < row; i++)
        {
            output << "[";
            for (size_t j = 0; j < col; j++)
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
        if (this->col != other.col || this->row != other.row)
        {
            throw std::invalid_argument("can't add two graphs with different size");
        }
        std::vector<std::vector<int>> g((size_t)this->row, std::vector<int>((size_t)this->col));
        for (size_t i = 0; i < this->row; i++)
        {
            for (size_t j = 0; j < this->col; j++)
            {
                g[i][j] = this->getGraph()[i][j] + other.getGraph()[i][j];
            }
        }
        return Graph(g);
    }
    Graph Graph::operator-(const Graph &other)
    {
        if (this->col != other.col || this->row != other.row)
        {
            throw std::invalid_argument("can't add two graphs with different size");
        }
        std::vector<std::vector<int>> result((size_t)this->row, std::vector<int>((size_t)this->col));
        for (size_t i = 0; i < this->row; i++)
        {
            for (size_t j = 0; j < this->col; j++)
            {
                result[i][j] = this->getGraph()[i][j] - other.getGraph()[i][j];
            }
        }
        return Graph(result);
    }

    Graph Graph::operator*(const Graph &other)
    {
        // Check if the dimensions of the graphs are compatible for multiplication
        if (this->col != other.row)
        {
            throw std::invalid_argument("Can not multiply graphs with differnt size");
        }

        std::vector<std::vector<int>> result((size_t)this->row, std::vector<int>((size_t)other.col));
        for (size_t i = 0; i < this->row; ++i)
        {
            for (size_t j = 0; j < other.col; ++j)
            {
                for (size_t k = 0; k < this->col; ++k)
                {
                    result[i][j] += this->AdjacencyMatrix[i][k] * other.AdjacencyMatrix[k][j];
                }
            }
        }
        for (size_t i = 0; i < this->row; i++)
        {
            result[i][i] = 0;
        }

        return Graph(result);
    }

    Graph &Graph::operator-()
    {
        return *this *= (-1);
    }

    Graph &Graph::operator+()
    {
        return *this *= 1;
    }

    Graph &Graph::operator+=(int scalar)
    {
        for (size_t i = 0; i < this->row; ++i)
        {
            for (size_t j = 0; j < this->col; ++j)
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
        for (size_t i = 0; i < this->row; ++i)
        {
            for (size_t j = 0; j < this->col; ++j)
            {
                if (this->AdjacencyMatrix[i][j] != 0)
                { // add scalar only to edge that existed
                    this->AdjacencyMatrix[i][j] -= scalar;
                }
            }
        }
        return *this; // Return a reference to the modified graph
    }

    Graph &Graph::operator++()
    {
        return *this += 1;
    }

    Graph &Graph::operator--()
    {
        return *this -= 1;
    }

    Graph &Graph::operator++(int)
    {
        return *this += 1;
    }

    Graph &Graph::operator--(int)
    {
        return *this -= 1;
    }

    bool Graph::operator==(const Graph &other)
    {
        if (this->row == other.row) // the matrix in the seem size
        {
            for (size_t i = 0; i < this->row; i++)
            {
                for (size_t j = 0; j < this->col; j++)
                {
                    if (this->AdjacencyMatrix[i][j] != other.AdjacencyMatrix[i][j])
                    {
                        return false;
                    }
                }
            }
            return true;
        }

        else if (!(*this < other) && !(*this > other))
        {
            return true;
        }

        return false;
    }

    bool Graph::operator!=(const Graph &other)
    {
        if (this->row == other.row) // the matrix in the seem size
        {
            for (size_t i = 0; i < this->row; i++)
            {
                for (size_t j = 0; j < this->col; j++)
                {
                    if (this->AdjacencyMatrix[i][j] != other.AdjacencyMatrix[i][j])
                    {
                        return true;
                    }
                }
            }
            return false;
        }

        else if (this->getNumEdge() != other.getNumEdge())
        {
            return true;
        }
        return true;
    }

    bool contain(const Graph &g1, const Graph &g2)
    { // if g1 contained in g2
        if (g1.getNumVertices() > g2.getNumVertices())
        {
            return false;
        }

        for (size_t i = 0; i < g1.getNumVertices(); i++)
        {
            for (size_t j = 0; j < g1.getNumVertices(); j++) // Iterate over the columns of this
            {
                if (g1.getGraph()[i][j] != 0 && g2.getGraph()[i][j] != 0)
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
            // they aren't equal we need to check the size
            if (this->getNumEdge() > other.getNumEdge())
            {
                return true;
            }
            else if (this->getNumEdge() == other.getNumEdge())
            {
                if (this->col > other.col)
                {
                    return true;
                }
            }
        }
        return false;
    }

    bool Graph::operator<(const Graph &other) // this<other
    {
        if (contain(*this, other) && *this != other) // if this contianed in this -> this<other
        {
            return true;
        }
        else if (!contain(*this, other) && !contain(other, *this) && *this != other)
        {
            // if neither of the graphs is conteined by the other and
            // they aren't equal we need to check the size
            if (other.getNumEdge() > this->getNumEdge())
            {
                return true;
            }
            else if (this->getNumEdge() == other.getNumEdge())
            {
                if (other.col > this->col)
                {
                    return true;
                }
            }
        }
        return false;
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
        for (size_t i = 0; i < g.row; i++)
        {
            output << "[";
            for (size_t j = 0; j < g.col; j++)
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
        for (size_t i = 0; i < row; ++i)
        {
            for (size_t j = 0; j < col; ++j)
            {
                this->AdjacencyMatrix[i][j] *= scalar;
            }
        }
        return *this;
    }

    Graph &Graph::operator+=(const Graph &other)
    {
        for (size_t i = 0; i < row; ++i)
        {
            for (size_t j = 0; j < col; ++j)
            {
                this->AdjacencyMatrix[i][j] += other.AdjacencyMatrix[i][j];
            }
        }
        return *this; // Return the modified graph
    }

    Graph &Graph::operator-=(const Graph &other)
    {
        for (size_t i = 0; i < row; ++i)
        {
            for (size_t j = 0; j < col; ++j)
            {
                this->AdjacencyMatrix[i][j] -= other.AdjacencyMatrix[i][j];
            }
        }
        return *this; // Return the modified graph
    }

}
