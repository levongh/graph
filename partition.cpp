#include "graph.h"
#include "partition.h"

partition_manager* partition_manager::s_instance = nullptr;
std::mutex partition_manager::s_mutex;

int graph_partition::internal_cost(Vertex* vert) const
{
    unsigned result = 0;
    for (const auto& elem : vert->m_adj) {
        if (elem.second->get_label() == vert->get_label()) {
            result += elem.first;
        }
    }
    return result;
}

int graph_partition::external_cost(Vertex* vert) const
{
    unsigned result = 0;
    for (const auto& elem : vert->m_adj) {
        if (elem.second->get_label() != vert->get_label()) {
            result += elem.first;
        }
    }
    return result;
}

int graph_partition::calculate_cut(const std::vector<Vertex*>& set) const
{
    unsigned result = 0;
    for (const auto& elem : set) {
        result += external_cost(elem);
    }
    return result;
}

int graph_partition::moveing_cost(Vertex* vert) const
{
    return external_cost(vert) - internal_cost(vert);
}

void graph_partition::initial_partition(std::vector<Vertex*>& label_1, std::vector<Vertex*>& label_2)
{
    m_graph->initial_partition(label_1, label_2);
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
