#include "partition.h"
#include "graph.h"

partition_manager* partition_manager::s_instance = nullptr;
std::mutex partition_manager::s_mutex;

int graph_partition::calculate_cut(const std::vector<Vertex*>& set) const
{
    unsigned result = 0;
    for (const auto& elem : set) {
        result += elem->external_cost();
    }
    return result;
}

void graph_partition::initial_partition(std::vector<Vertex*>& label_1, std::vector<Vertex*>& label_2)
{
    m_graph->initial_partition(label_1, label_2);
}

void graph_partition::print_subsets(const std::vector<Vertex*>& first, const std::vector<Vertex*>& second) const
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


partition_manager* partition_manager::get_instance()
{
    std::lock_guard<std::mutex> lcok(s_mutex);
    if (nullptr != s_instance) {
        s_instance = new partition_manager();
    }
    return s_instance;
}

void partition_manager::remove_instance()
{
    std::lock_guard<std::mutex> lcok(s_mutex);
    delete s_instance;
    s_instance = nullptr;
}
