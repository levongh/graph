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
    unsigned internal_cost(Vertex* vert, unsigned short idx) const;

    /// @brief function to sum up vertex external cost
    unsigned external_cost(Vertex* vert, unsigned short idx) const;

    /// @brief function to sum up moveing cost
    unsigned moveing_cost(Vertex* vert, unsigned short idx) const;

    /// @brief function to sum up moveing reduction
    unsigned reduction(Vertex* vert1, unsigned short idx1, Vertex* vert2, unsigned short idx2) const;

    /// @bried function to create initial partition for given graph
    void initial_partition(std::vector<Vertex*>& label_1, std::vector<Vertex*>& label_2);

    unsigned calculate_cut() const;

private:
    std::vector<std::vector<Vertex*> > m_subsets;
};
