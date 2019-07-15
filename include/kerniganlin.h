#pragma once

#include "partition.h"

/**
 * @file  kerniganlin.h
 * @title declaration of KerniganLin class
 * @description this class is designed to implement graph partitionin KL algorithm
 * @param m_subsets this container should keep partitioned grpah vertexes
 * @author Levon Ghukasyan
 */

class KerniganLin : public GraphPartition
{
public:
    KerniganLin(Graph* G, PartitionConfig config = PartitionConfig())
        : GraphPartition{G, config}
    {
    }

    virtual void runPartition() override;

private:
    /// @brief function to sum up moveing reduction
    int reduction(Vertex* vert1, Vertex* vert2) const;

    void acceptMoves(int index);

};
