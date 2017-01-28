#pragma once

#include <cassert>
#include <vector>
#include <mutex>

class graph;

enum class partition_type
{
    KERNIGAN_LIN,
    FETUCCIA_MATEISIS,
    K_WAY,
    SIMULATED_ANNEALING
};

struct partition_config
{
public:
    partition_config(partition_type type = partition_type::KERNIGAN_LIN, short count = 2, bool allow = false)
        : m_type{type}
        , m_count{count}
        , m_allow_multithreading{allow}
    {
        assert(count >=2);
    }
private:
    partition_type m_type;
    short m_count;
    bool m_allow_multithreading;
};


class graph_partition
{
public:
    graph_partition(graph* G, partition_config config)
        : m_graph{G}
        , m_config{config}
    {
    }

    virtual std::vector<graph*> run_partition() = 0;

protected:
    graph* m_graph;
    partition_config m_config;
};

class partition_manager
{

public:
    static partition_manager* get_instance();

    static void remove_instance();

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
};
