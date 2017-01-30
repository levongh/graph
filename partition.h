#pragma once

#include <cassert>
#include <vector>
#include <mutex>

class Graph;

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


class graph_partition
{
public:
    graph_partition(Graph* G, partition_config config)
        : m_graph{G}
        , m_config{config}
    {
    }

    virtual void run_partition() = 0;

    virtual ~graph_partition()
    {
    }

protected:
    Graph* m_graph;
    partition_config m_config;
};

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
