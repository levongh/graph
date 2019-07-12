
#include "simulated_annealing.h"
#include "graph.h"

namespace {

const unsigned int ITERATION_NUMBER = 100;

} //! unnamed namespace

simulated_annealing::simulated_annealing(Graph* G, partition_config config)
    : graph_partition{G, config}
    , m_temperature{std::numeric_limits<unsigned int>::max()}
    , m_counter{0}
    , m_vertexCount{m_graph->get_vertex_count()}
    , m_cutSize{0}
    , m_annealingType{annealing_type::FAST_ANNEALING}
    , m_device{}
    , m_engine{m_device()}
    , m_distribution{1, m_vertexCount}
{
}

double simulated_annealing::calculateMove(unsigned int index)
{
    auto to_move = m_graph->get_vertex(index);
    return to_move->move_cost();
}

void simulated_annealing::applyMove(Vertex* to_move)
{
    if (to_move->get_label() == 0) {
        to_move->set_label(1);
    } else {
        to_move->set_label(0);
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
    auto to_move = m_graph->get_vertex(index);
    auto cut_reduction = to_move->move_cost();
    if (cut_reduction > 0) {
        applyMove(to_move);
        m_cutSize = m_cutSize - cut_reduction;
    } else {
        double p = std::exp((m_cutSize - cut_reduction) / m_temperature);
        std::uniform_int_distribution<unsigned> dist{0, 100};
        if (dist(m_engine) < p) {
            applyMove(to_move);
            m_cutSize = m_cutSize - cut_reduction;
        }
    }
    sheduleAnnealing();
}

void simulated_annealing::run_partition()
{
    std::cout << "SM algorithm starting ..." <<std::endl;
    initial_partition(m_buckets[0], m_buckets[1]);
    m_cutSize = calculate_cut(m_buckets[0]);
    std::cout << "Initial cut size is: " << m_cutSize;
    while (m_temperature > 0 && m_counter < ITERATION_NUMBER) {
        mutate();
        ++m_counter;
    }
    write_graph();
    std::cout << " Optimized cut size is: " << m_cutSize << std::endl;
}
