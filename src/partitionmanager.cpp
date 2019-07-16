#include "partitionmanager.h"
#include "kerniganlin.h"
#include "fiducciamattheyses.h"
#include "simulatedannealing.h"

PartitionManager* PartitionManager::s_instance = nullptr;
std::mutex PartitionManager::s_mutex;

PartitionManager* PartitionManager::get_instance()
{
    std::lock_guard<std::mutex> lcok(s_mutex);
    if (nullptr == s_instance) {
        s_instance = new PartitionManager();
    }
    return s_instance;
}

void PartitionManager::remove_instance()
{
    std::lock_guard<std::mutex> lcok(s_mutex);
    delete s_instance;
    s_instance = nullptr;
}

GraphPartition* PartitionManager::create_algorithm(partition_type pt, Graph* G)
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

PartitionManager::~PartitionManager()
{
    for (auto iter : m_algorithms) {
        delete iter;
    }
}
