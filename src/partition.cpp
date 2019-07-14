#include <fstream>

#include "partition.h"
#include "graph.h"

int GraphPartition::calculateCut(const std::vector<Vertex*>& set) const
{
    unsigned result = 0;
    for (const auto& elem : set) {
        result += elem->external_cost();
    }
    return result;
}

void GraphPartition::initialPartition(std::vector<Vertex*>& label_1, std::vector<Vertex*>& label_2)
{
    m_graph->initial_partition(label_1, label_2);
}

void GraphPartition::printSubsets(const std::vector<Vertex*>& first, const std::vector<Vertex*>& second) const
{
    for (const auto& it : first) {
        std::cout <<it->m_name << " l" << it->get_label() << ' ';
    }
    std::cout<<std::endl;
    for (const auto& it : second) {
        std::cout <<it->m_name << " l" << it->get_label() << ' ';
    }
    std::cout<<std::endl;
}

void GraphPartition::writeGraph() const
{
    std::ofstream out_file("after_part.txt", std::ofstream::out);
    m_graph->print_partition(out_file);
}
