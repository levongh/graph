#pragma once

#include <vector>

/**
 * @brief class Vertex
 * @param m_adj cost of edge and destination vertex
 * @param m_name the name of vcertex
 */

class Vertex
{
public:
    /// @brief constructor
    Vertex(const unsigned name, unsigned short label = 0)
        : m_name{name}
        , m_label{label}
    {
    }

    unsigned short getLabel()const
    {
        return m_label;
    }

    void setLabel(unsigned short label)
    {
        m_label = label;
    }

    /// @brief function to sum up vertex internal cost
    int internalCost() const;

    /// @brief function to sum up vertex external cost
    int externalCost() const;

    /// @brief function to sum up move cost
    int moveCost() const;

    void print() const;

    const std::vector<std::pair<int, Vertex*>>& getAdjacent() const
    {
        return m_adj;
    }

    void addAdjecent(std::pair<int, Vertex*>&& adj)
    {
        m_adj.push_back(adj);
    }

    unsigned m_name;

private:
    std::vector<std::pair<int, Vertex*> > m_adj;

private:
    unsigned short m_label;
};

