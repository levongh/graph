
#include "simulated_annealing.h"
#include "graph.h"

namespace {

const unsigned int ITERATION_NUMBER = 100;

} //! unnamed namespace

simulated_annealing::simulated_annealing(Graph* G, PartitionConfig config)
    : GraphPartition{G, config}
    , m_temperature{std::numeric_limits<unsigned int>::max()}
    , m_counter{0}
    , m_vertexCount{m_graph->getVertexCount()}
    , m_cutSize{0}
    , m_annealingType{annealing_type::FAST_ANNEALING}
    , m_device{}
    , m_engine{m_device()}
    , m_distribution{1, m_vertexCount}
{
}

double simulated_annealing::calculateMove(unsigned int index)
{
    auto toMove = m_graph->getVertex(index);
    return toMove->moveCost();
}

void simulated_annealing::applyMove(Vertex* toMove)
{
    if (toMove->getLabel() == 0) {
        toMove->setLabel(1);
    } else {
        toMove->setLabel(0);
    }
}

void simulated_annealing::sheduleAnnealing()
{
    switch(m_annealingType)
    {
        case annealing_type::FAST_ANNEALING:
            m_temperature = m_temperature / 1.02;
        case annealing_type::DETAILD_ANNEALING:
            m_temperature = m_temperature / 1.0095;
    }
}

void simulated_annealing::mutate()
{
    int index = m_distribution(m_engine);
    auto toMove = m_graph->getVertex(index);
    auto cutReduction = toMove->moveCost();
    if (cutReduction > 0) {
        applyMove(toMove);
        m_cutSize = m_cutSize - cutReduction;
    } else {
        double p = std::exp((m_cutSize - cutReduction) / m_temperature);
        std::uniform_int_distribution<unsigned> dist{0, 100};
        if (dist(m_engine) < p) {
            applyMove(toMove);
            m_cutSize = m_cutSize - cutReduction;
        }
    }
    sheduleAnnealing();
}

void simulated_annealing::runPartition()
{
    std::cout << "SM algorithm starting ..." << std::endl;
    initialPartition(m_buckets[0], m_buckets[1]);
    m_cutSize = calculateCut(m_buckets[0]);
    std::cout << "Initial cut size is: " << m_cutSize;
    while (m_temperature > 0 && m_counter < ITERATION_NUMBER) {
        mutate();
        ++m_counter;
    }
    writeGraph();
    std::cout << " Optimized cut size is: " << m_cutSize << std::endl;
}
