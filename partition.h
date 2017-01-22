#pragma once

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
        //assert count >=2
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

    std::vector<graph*> run_partition();
private:
    void initial_partition();

private:
    graph* m_graph;
    partition_config m_config;
};

