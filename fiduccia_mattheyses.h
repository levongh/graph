#pragma once

#include "partition.h"

/**
 * @file fiduccia_mattheyses.h
 * @title declaration of fiduccia_mattheyses class
 * @description implements FM algorithm
 * @author Levon Ghukasyan
 */

class fiduccia_mattheyses : public graph_partition
{
public:
    fiduccia_mattheyses(Graph* G, partition config = partition_config())
        : graph_partition{G, config}
   {
   }

   virtual void run_partition() override;
};
