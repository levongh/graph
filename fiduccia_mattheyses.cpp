#include <algorithm>
#include <functional>

#include "graph.h"
#include "fiduccia_mattheyses.h"

void fiduccia_mattheyses::init_gains()
{
    std::multimap<int, Vertex*, std::greater<int> > buckets;
    m_graph->initialize_buckets(buckets);

    std::cout << calculate_cut(m_buckets[0]) << std::endl;;

    while (!buckets.empty()) {
        Vertex* highest = (*buckets.begin()).second;
        buckets.erase(buckets.begin());
        if (highest->moveing_cost() < 0) {
            move_vertex(highest);
        }
    }
    std::cout << calculate_cut(m_buckets[0]) << std::endl;;
}

void fiduccia_mattheyses::move_vertex(Vertex* vert)
{
    const auto label = vert->get_label();
    if (label == 0) {
        m_buckets[0].erase(std::remove(m_buckets[0].begin(), m_buckets[0].end(), vert));
        m_buckets[1].push_back(vert);
    } else if (label == 1) {
        m_buckets[1].erase(std::remove(m_buckets[1].begin(), m_buckets[1].end(), vert));
        m_buckets[0].push_back(vert);
    } else {
        return;
    }
}

void fiduccia_mattheyses::run_partition()
{
    std::cout << "FM algorithm starting ..." <<std::endl;
    initial_partition(m_buckets[0], m_buckets[1]);
    init_gains();
}

