#include <algorithm>

#include "kernigan_lin.h"
#include "graph.h"

namespace {

void swap_vertexes(Vertex*& vert1, Vertex*& vert2)
{
    const auto lbl = vert1->get_label();
    vert1->set_label(vert2->get_label());
    vert2->set_label(lbl);
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
    initial_partition(m_subsets[0], m_subsets[1]);
    print_subsets(m_subsets[0], m_subsets[1]);
    /// print initial cut size
    /// save initial cut size for algorithm report
    const auto initial_cut_size = calculate_cut(m_subsets[0]);

    while (true) {
        for (unsigned i = 0; i < m_subsets.size(); ++i) {
            std::sort(m_subsets[i].begin(), m_subsets[i].end(),
                    [this] (Vertex* vert1, Vertex* vert2) -> bool
                    {
                        return vert1->internal_cost() > vert2->internal_cost();
                    });
        }

        auto iter1 = m_subsets[0].begin();
        auto iter2 = m_subsets[1].begin();
        /// will use this container uring algorithm thase optimization
        std::vector<unsigned> gain_vector;//(m_subsets[0].size(), 0);

        while (iter1 != m_subsets[0].end() && iter2 != m_subsets[1].end()) {
            gain_vector.push_back(reduction(*iter1, *iter2));
            ++iter1;
            ++iter2;
        }
        /// do calculation and accept/or decline moveing
        int max_gain_index = -1;
        unsigned max_gain = 0;
        for (int i = 0; i < gain_vector.size(); ++i) {
            if (max_gain + gain_vector[i] > max_gain) {
                max_gain_index = i;
            }
            max_gain = max_gain + gain_vector[i];
        }
        if (max_gain_index == 0) {
            report_algorithm_result(initial_cut_size, calculate_cut(m_subsets[0]), "KL");
            return;
        }
        accept_moves(max_gain_index);
        print_subsets(m_subsets[0], m_subsets[1]);
    }
}

void kernigan_lin::accept_moves(int index)
{
    for (int i = 0; i < index; ++i) {
        swap_vertexes(m_subsets[0][i], m_subsets[1][i]);
    }
}

int kernigan_lin::reduction(Vertex* vert1, Vertex* vert2) const
{
    return vert1->moveing_cost() + vert2->moveing_cost() - 2 * m_graph->get_weight(vert1, vert2);
}
