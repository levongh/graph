#pragma once

#include "partition.h"


class kernigan_lin : public graph_partition
{
public:
    kernigan_lin(graph* G, partition_config config)
        : graph_partition(G, config)
    {
    }

    virtual std::vector<graph*> run_partition() override
    {
    }

private:
    /// @brief function to sum up vertex internal cost
    unsigned int internal_cost() const;

    /// @brief function to sum up vertex external cost
    unsigned int external_cost() const;

    /// @brief function to sum up moveing cost
    unsigned moveing_cost() const;

    /// @brief function to sum up moveing reduction
    unsigned reduction() const;

    /// @bried function to create initial partition for given graph
    void initial_partition();
};
