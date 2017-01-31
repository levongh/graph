#pragma once

#include "partition.h"


class kernigan_lin : public graph_partition
{
public:
    kernigan_lin(Graph* G, partition_config config = partition_config())
        : graph_partition(G, config)
        , m_subsets(config.get_partition_count())
    {
    }

    virtual void run_partition() override;

private:
    /// @brief function to sum up vertex internal cost
    int internal_cost(Vertex* vert, unsigned short idx) const;

    /// @brief function to sum up vertex external cost
    int external_cost(Vertex* vert, unsigned short idx) const;

    /// @brief function to sum up moveing cost
    int moveing_cost(Vertex* vert, unsigned short idx) const;

    /// @brief function to sum up moveing reduction
    int reduction(Vertex* vert1, unsigned short idx1, Vertex* vert2, unsigned short idx2) const;

    /// @bried function to create initial partition for given graph
    void initial_partition(std::vector<Vertex*>& label_1, std::vector<Vertex*>& label_2);

    void accept_moves(int index);

    int calculate_cut() const;

    void print_subsets() const;

private:
    std::vector<std::vector<Vertex*> > m_subsets;
};
