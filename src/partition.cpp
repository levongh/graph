#include <fstream>

#include "partition.h"
#include "graph.h"

int GraphPartition::calculateCut(const std::vector<Vertex*>& set) const
{
    unsigned result = 0;
    for (const auto& elem : set) {
        result += elem->externalCost();
    }
    return result;
}

void GraphPartition::initialPartition(std::vector<Vertex*>& label_1, std::vector<Vertex*>& label_2)
{
    m_graph->initialPartition(label_1, label_2);
}

void GraphPartition::printSubsets(const std::vector<Vertex*>& first, const std::vector<Vertex*>& second) const
{
    for (const auto& it : first) {
        std::cout <<it->m_name << " l" << it->getLabel() << ' ';
    }
    std::cout<<std::endl;
    for (const auto& it : second) {
        std::cout <<it->m_name << " l" << it->getLabel() << ' ';
    }
    std::cout << std::endl;
}

void GraphPartition::writeGraph() const
{
    std::ofstream out_file("after_part.txt", std::ofstream::out);
    m_graph->printPartition(out_file);
}
