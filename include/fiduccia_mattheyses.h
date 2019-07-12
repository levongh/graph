#pragma once

#include "partition.h"
//! need to think is list acceptable for us
#include <list>


/**
 * @file fiduccia_mattheyses.h
 * @title declaration of fiduccia_mattheyses class
 * @description implements FM algorithm
 * @author Levon Ghukasyan
 */

/**
 * @brief FM algorithm
 * @param m_ratio ration of balance between blocks
 * @param m_pmax max number of pins per cell
 * @param m_buckets buckets for gain updateing
 * @param m_free free cells list
 * @param m_maxgain the maximum gain of any cell in each block
 * @param m_balance the balance of the partitions
 * @param m_passes the number of algorithm passes
 */
class fiduccia_mattheyses : public graph_partition
{
public:
    fiduccia_mattheyses(Graph* G, partition_config config = partition_config())
        : graph_partition{G, config}
   {
   }

   virtual void run_partition() override;

private:
    void initGains();
    Vertex* getHighest() const;
    void moveVertex(Vertex* vert);
    void fixGain();
    void print() const;

private:
   double m_ratio;
   int  m_pmax;
   std::list<Vertex*> m_free;
};
