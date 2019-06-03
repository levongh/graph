#include "partition_manager.h"

partition_manager* partition_manager::s_instance = nullptr;
std::mutex partition_manager::s_mutex;

partition_manager* partition_manager::get_instance()
{
    std::lock_guard<std::mutex> lcok(s_mutex);
    if (nullptr == s_instance) {
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

graph_partition* partition_manager::create_algorithm(partition_type pt, Graph* G)
{
    if (pt == partition_type::KERNIGAN_LIN) {
        part_algorithms.push_back(new kernigan_lin{G});
        return part_algorithms.back();
    } else if (pt == partition_type::FETUCCIA_MATEISIS) {
        part_algorithms.push_back(new fiduccia_mattheyses{G});
        return part_algorithms.back();
    } else if (pt == partition_type::SIMULATED_ANNEALING) {
        part_algorithms.push_back(new simulated_annealing{G});
        return part_algorithms.back();
    } else {
        return nullptr;
    }
}

partition_manager::~partition_manager()
{
    for (auto iter : part_algorithms) {
        delete iter;
    }
}
