#include <iostream>
#include <algorithm>

#include "graph.h"
#include "kernigan_lin.h"

void kernigan_lin::run_partition()
{
    /// step 1
    initial_partition(m_subsets[0], m_subsets[1]);
    print_subsets();
    /// print initial cut size
    std::cout << calculate_cut() << std::endl;
    /// step 2
    for (unsigned i = 0; i < m_subsets.size(); ++i) {
        std::sort(m_subsets[i].begin(), m_subsets[i].end(),
                [this] (Vertex* vert1, Vertex* vert2) -> bool
                {
                    return internal_cost(vert1, vert1->get_label()) < internal_cost(vert2, vert2->get_label());
                });
    }


    auto iter1 = m_subsets[0].begin();
    auto iter2 = m_subsets[1].begin();
    /// will use this container uring algorithm thase optimization
    std::vector<unsigned> gain_vector;//(m_subsets[0].size(), 0);

    while (iter1 != m_subsets[0].end() || iter2 != m_subsets[1].end()) {
        gain_vector.push_back(reduction(*iter1, (*iter1)->get_label(), *iter2, (*iter2)->get_label()));
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
    print_subsets();
    accept_moves(max_gain_index);
    std::cout << calculate_cut() << std::endl;
    print_subsets();
}

void kernigan_lin::accept_moves(int index)
{
    for (int i = 0; i < index; ++i) {
        std::swap(m_subsets[0][i], m_subsets[1][i]);
    }
}

void kernigan_lin::print_subsets() const
{
    for (const auto& it: m_subsets[0]) {
        std::cout <<it->m_name <<' ';
    }
    std::cout<<std::endl;
    for (const auto& it: m_subsets[1]) {
        std::cout <<it->m_name <<' ';
    }
    std::cout<<std::endl;
}

int kernigan_lin::calculate_cut() const
{
    unsigned result = 0;
    for (const auto& elem : m_subsets[0]) {
        result += external_cost(elem, 0);
    }
    return result;
}

void kernigan_lin::initial_partition(std::vector<Vertex*>& label_1, std::vector<Vertex*>& label_2)
{
    m_graph->initial_partition(label_1, label_2);
}

int kernigan_lin::internal_cost(Vertex* vert, unsigned short idx) const
{
    unsigned result = 0;
    for (const auto& elem : vert->m_adj) {
        if (elem.second->get_label() == idx) {
            result += elem.first;
        }
    }
    return result;
}

int kernigan_lin::external_cost(Vertex* vert, unsigned short idx) const
{
    unsigned result = 0;
    for (const auto& elem : vert->m_adj) {
        if (elem.second->get_label() != idx) {
            result += elem.first;
        }
    }
    return result;
}

int kernigan_lin::moveing_cost(Vertex* vert, unsigned short idx) const
{
    return external_cost(vert, idx) - internal_cost(vert, idx);
}

int kernigan_lin::reduction(Vertex* vert1, unsigned short idx1, Vertex* vert2, unsigned short idx2) const
{
    return moveing_cost(vert1, idx1) + moveing_cost(vert2, idx2) - 2 * m_graph->get_weight(vert1, vert2);
}
