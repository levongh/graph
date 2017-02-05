#pragma once

#include <cassert>
#include <vector>
#include <mutex>

class Graph;
class Edge;
class Vertex;

enum class partition_type
{
    KERNIGAN_LIN,
    FETUCCIA_MATEISIS,
    K_WAY,
    SIMULATED_ANNEALING
};

/**
 *  @brief class for algorithm configuration
 *  @param m_type showing algorithm type this parameter should
 *         \use paritition_manager class object
 *  @param m_count showing partitions count
 *  @param m_allow_multithreading showing is it accepatable to use mutithread partition or not
 */
struct partition_config
{
public:
    partition_config(partition_type type = partition_type::KERNIGAN_LIN, unsigned short count = 2, bool allow = false)
        : m_type{type}
        , m_count{count}
        , m_allow_multithreading{allow}
    {
        assert(count >=2);
    }

    partition_type get_partition_type() const
    {
        return m_type;
    }

    unsigned short get_partition_count() const
    {
        return m_count;
    }

    bool is_mutithreaded() const
    {
        return m_allow_multithreading;
    }

private:
    partition_type m_type;
    unsigned short m_count;
    bool m_allow_multithreading;
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

    /// @brief function to sum up vertex internal cost
    int internal_cost(Vertex* vert) const;

    /// @brief function to sum up vertex external cost
    int external_cost(Vertex* vert) const;

    /// @brief returns the cutsize
    int calculate_cut(const std::vector<Vertex*>& set) const;

    /// @brief function to sum up moveing cost
    int moveing_cost(Vertex* vert) const;



protected:
    Graph* m_graph;
    partition_config m_config;
};

/// @brief manager for partition alforithm creation
/// @brief should work like builder pattern
class partition_manager
{

public:
    static partition_manager* get_instance();

    static void remove_instance();

    /// @brief default constructor
    partition_manager() = default;

    /// @brief destructor
    ~partition_manager() = default;

    /// @brief copy constructor
    partition_manager(const partition_manager& other) = delete;

    /// @brief copy assignment operator
    partition_manager& operator=(const partition_manager& other) = delete;


    /// @brief move constructor
    partition_manager(partition_manager&& other) = delete;

    /// @brief copy assignment operator
    partition_manager& operator=(partition_manager&& other) = delete;

private:
    static partition_manager* s_instance;
    static std::mutex s_mutex;
};
