#include <algorithm>
#include <chrono>

#include "kernigan_lin.h"
#include "graph.h"

namespace {

void swap_vertexes(Vertex*& vert1, Vertex*& vert2)
{
    const auto lbl = vert1->getLabel();
    vert1->setLabel(vert2->getLabel());
    vert2->setLabel(lbl);
    std::swap(vert1, vert2);
}

void report_algorithm_result(const unsigned initial, const unsigned current, const std::string& algorithm)
{
    std::cout << "Initial cut size: " << initial << " after running the " << algorithm  << " algorithm cut size: " << current << std::endl;
}

}

void kernigan_lin::run_partition()
{
    std::cout << "KL algorithm starting ..." <<std::endl;
    /// step 1
    initialPartition(m_buckets[0], m_buckets[1]);
    /// print initial cut size
    /// save initial cut size for algorithm report
    const auto initialCutSize = calculateCut(m_buckets[0]);
    std::cout << calculateCut(m_buckets[0]) << std::endl;;

    while (true) {
        for (unsigned i = 0; i < m_buckets.size(); ++i) {
            std::sort(m_buckets[i].begin(), m_buckets[i].end(),
                    [this] (Vertex* vert1, Vertex* vert2) -> bool
                    {
                        return vert1->internalCost() > vert2->internalCost();
                    });
        }

        auto iter1 = m_buckets[0].begin();
        auto iter2 = m_buckets[1].begin();
        /// will use this container uring algorithm thase optimization
        std::vector<unsigned> gain_vector;//(m_subsets[0].size(), 0);

        while (iter1 != m_buckets[0].end() && iter2 != m_buckets[1].end()) {
            gain_vector.push_back(reduction(*iter1, *iter2));
            ++iter1;
            ++iter2;
        }
        /// do calculation and accept/or decline move
        int max_gain_index = -1;
        unsigned max_gain = 0;
        for (unsigned int i = 0; i < gain_vector.size(); ++i) {
            if (max_gain + gain_vector[i] > max_gain) {
                max_gain_index = i;
            }
            max_gain = max_gain + gain_vector[i];
        }
        if (max_gain_index == 0) {
            report_algorithm_result(initialCutSize, calculateCut(m_buckets[0]), "KL");
            break;
        }
        accept_moves(max_gain_index);
        std::cout << calculateCut(m_buckets[0]) <<std::endl;;
    }
    writeGraph();
}

void kernigan_lin::accept_moves(int index)
{
    for (int i = 0; i < index; ++i) {
        swap_vertexes(m_buckets[0][i], m_buckets[1][i]);
    }
}

int kernigan_lin::reduction(Vertex* vert1, Vertex* vert2) const
{
    return vert1->moveCost() + vert2->moveCost() - 2 * m_graph->get_weight(vert1, vert2);
}
