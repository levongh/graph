
#include "graph.h"
#include "fiduccia_mattheyses.h"

void fiduccia_mattheyses::run_partition()
{
    initial_partition(m_buckets[0], m_buckets[1]);
}

