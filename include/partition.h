#pragma once

#include <cassert>
#include <vector>
#include <mutex>
#include <iostream>

enum class partition_type
{
    KERNIGAN_LIN,
    FETUCCIA_MATEISIS,
    SIMULATED_ANNEALING,
    K_WAY
};


class Graph;
class Edge;
class Vertex;

/**
 *  @brief class for algorithm configuration
 *  @param m_type showing algorithm type this parameter should
 *         \use paritition_manager class object
 *  @param m_count showing partitions count
 *  @param m_allowMultithreading showing is it accepatable to use mutithread partition or not
 */
struct partition_config
{
public:
    partition_config(partition_type type = partition_type::KERNIGAN_LIN, unsigned short count = 2, bool allow = false)
        : m_type{type}
        , m_count{count}
        , m_allowMultithreading{allow}
    {
        assert(count >=2);
    }

    partition_type partitionType() const
    {
        return m_type;
    }

    unsigned short getPartitionCount() const
    {
        return m_count;
    }

    bool isMutithreaded() const
    {
        return m_allowMultithreading;
    }

private:
    partition_type m_type;
    unsigned short m_count;
    bool m_allowMultithreading;
};

/**
 * @class graph_partition
 * @brief this pure virtual class designed to get more generic 
 * @      \interface for graph partitioning all parition algorithms
 *        \should inherit from it
 * @param m_graph this is input graph on which algorithm should run
 * @param m_config this is paritition gonfigurations which algorithm should get from input file
 */

class graph_partition
{
public:
    graph_partition(Graph* G, partition_config config)
        : m_graph{G}
        , m_config{config}
        , m_buckets{config.getPartitionCount()}
    {
    }

    /// @brief virtual interface to run partitioning algorithm
    virtual void run_partition() = 0;

    virtual ~graph_partition()
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
    partition_config m_config;
    std::vector<std::vector<Vertex*> > m_buckets;

};

