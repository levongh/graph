#pragma once

#include "partition.h"

/**
 * @file  kernigan_lin.h
 * @title declaration of kernigan_lin class
 * @description this class is designed to implement graph partitionin KL algorithm
 * @param m_subsets this container should keep partitioned grpah vertexes
 * @author Levon Ghukasyan
 */

class kernigan_lin : public GraphPartition
{
public:
    kernigan_lin(Graph* G, PartitionConfig config = PartitionConfig())
        : GraphPartition{G, config}
    {
    }

    virtual void run_partition() override;

private:
    /// @brief function to sum up moveing reduction
    int reduction(Vertex* vert1, Vertex* vert2) const;

    void accept_moves(int index);

};
