#pragma once

#include <cassert>
#include <vector>
#include <mutex>
#include <iostream>

#include "config.h"


class Graph;
class Vertex;

/**
 * @class GraphPartition
 * @brief this pure virtual class designed to get more generic 
 * @      \interface for graph partitioning all parition algorithms
 *        \should inherit from it
 * @param m_graph this is input graph on which algorithm should run
 * @param m_config this is paritition gonfigurations which algorithm should get from input file
 */

class GraphPartition
{
public:
    GraphPartition(Graph* G, PartitionConfig config)
        : m_graph{G}
        , m_config{config}
        , m_buckets{config.getPartitionCount()}
    {
    }

    /// @brief virtual interface to run partitioning algorithm
    virtual void run_partition() = 0;

    virtual ~GraphPartition()
    {
    }

protected:
    /// @bried function to create initial partition for given graph
    void initial_partition(std::vector<Vertex*>& label_1, std::vector<Vertex*>& label_2);

    /// @brief returns the cutsize
    int calculate_cut(const std::vector<Vertex*>& set) const;

    /// @brief helper function to check subsets
    void print_subsets(const std::vector<Vertex*>& first, const std::vector<Vertex*>& second) const;

    void write_graph() const;

protected:
    Graph* m_graph;
    PartitionConfig m_config;
    std::vector<std::vector<Vertex*> > m_buckets;

};

