#include <algorithm>
#include <functional>

#include "graph.h"
#include "fiducciamattheyses.h"

void FiducciaMattheyses::initGains()
{
    std::multimap<int, Vertex*, std::greater<int> > buckets;
    m_graph->initializeBuckets(buckets);

    std::cout << calculateCut(m_buckets[0]) << std::endl;;

    while (!buckets.empty()) {
        Vertex* highest = (*buckets.begin()).second;
        buckets.erase(buckets.begin());
        if (highest->moveCost() > 0) {
            moveVertex(highest);
        }
    }
    std::cout << calculateCut(m_buckets[0]) << std::endl;;
}

void FiducciaMattheyses::moveVertex(Vertex* vert)
{
    const auto label = vert->getLabel();
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

void FiducciaMattheyses::runPartition()
{
    std::cout << "FM algorithm starting ..." <<std::endl;
    initialPartition(m_buckets[0], m_buckets[1]);
    initGains();
    writeGraph();
}

