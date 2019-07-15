#include "partition_manager.h"
#include "kerniganlin.h"
#include "fiducciamattheyses.h"
#include "simulatedannealing.h"

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

GraphPartition* partition_manager::create_algorithm(partition_type pt, Graph* G)
{
    if (pt == partition_type::KERNIGAN_LIN) {
        m_algorithms.push_back(new KerniganLin{G});
        return m_algorithms.back();
    } else if (pt == partition_type::FETUCCIA_MATEISIS) {
        m_algorithms.push_back(new FiducciaMattheyses{G});
        return m_algorithms.back();
    } else if (pt == partition_type::SIMULATED_ANNEALING) {
        m_algorithms.push_back(new SimulatedAnnealing{G});
        return m_algorithms.back();
    } else {
        return nullptr;
    }
}

partition_manager::~partition_manager()
{
    for (auto iter : m_algorithms) {
        delete iter;
    }
}