#include <iostream>
#include <algorithm>

#include "graph.h"
#include "kernigan_lin.h"

namespace {

void swap_vertexes(Vertex*& vert1, Vertex*& vert2)
{
    const auto lbl = vert1->get_label();
    vert1->set_label(vert2->get_label());
    vert2->set_label(lbl);
    std::swap(vert1, vert2);
}

}

void kernigan_lin::run_partition()
{
    /// step 1
    initial_partition(m_subsets[0], m_subsets[1]);
    print_subsets();
    /// print initial cut size
    std::cout << calculate_cut(m_subsets[0]) << std::endl;
    /// step 2
    while (true) {
        for (unsigned i = 0; i < m_subsets.size(); ++i) {
            std::sort(m_subsets[i].begin(), m_subsets[i].end(),
                    [this] (Vertex* vert1, Vertex* vert2) -> bool
                    {
                        return internal_cost(vert1) > internal_cost(vert2);
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
            return;
        }
        accept_moves(max_gain_index);
        std::cout << calculate_cut(m_subsets[0]) << std::endl;
        print_subsets();
    }
}

void kernigan_lin::accept_moves(int index)
{
    for (int i = 0; i < index; ++i) {
        swap_vertexes(m_subsets[0][i], m_subsets[1][i]);
    }
}

void kernigan_lin::print_subsets() const
{
    for (const auto& it: m_subsets[0]) {
        std::cout <<it->m_name << " l" << it->get_label() << ' ';
    }
    std::cout<<std::endl;
    for (const auto& it: m_subsets[1]) {
        std::cout <<it->m_name << " l" << it->get_label() << ' ';
    }
    std::cout<<std::endl;
}

int kernigan_lin::reduction(Vertex* vert1, Vertex* vert2) const
{
    return moveing_cost(vert1) + moveing_cost(vert2) - 2 * m_graph->get_weight(vert1, vert2);
}
