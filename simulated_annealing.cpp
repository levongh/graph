#include <cmath>
#include <cstdlib>

#include "simulated_annealing.h"
#include "graph.h"

namespace {

const unsigned int ITERATION_NUMBER = 100;

} //! unnamed namespace

double simulated_annealing::calculate_move(unsigned int index)
{
    auto to_move = m_graph->get_vertex(index);
    return to_move->moveing_cost();
}

simulated_annealing::simulated_annealing(Graph* G, partition_config config)
    : graph_partition{G, config}
    , m_temperature{std::numeric_limits<unsigned int>::max()}
    , m_counter{0}
    , m_vertex_count{m_graph->get_vertex_count()}
    , m_cut_size{0}
    , m_annealing_type{annealing_type::FAST_ANNEALING}
    , m_subsets{config.get_partition_count()}
{
}

void simulated_annealing::apply_move(Vertex* to_move)
{
    if (to_move->get_label() == 0) {
        to_move->set_label(1);
    } else {
        to_move->set_label(0);
    }
}

void simulated_annealing::shedule_annealing()
{
    switch(m_annealing_type)
    {
        case annealing_type::FAST_ANNEALING:
            m_temperature = m_temperature / 1.02;
        case annealing_type::DETAILD_ANNEALING:
            m_temperature = m_temperature / 1.0095;
    }
}

void simulated_annealing::mutate()
{
    int index = std::rand() % (m_vertex_count - 1) + 1;
    auto to_move = m_graph->get_vertex(index);
    auto cut_reduction = to_move->moveing_cost();
    if (cut_reduction < 0) {
        apply_move(to_move);
        m_cut_size = m_cut_size - cut_reduction;
    } else {
        double p = std::exp((m_cut_size - cut_reduction) / m_temperature);
        if (std::rand() % 100 < p * 100) {
            apply_move(to_move);
            m_cut_size = m_cut_size - cut_reduction;
        }
    }
    shedule_annealing();
}

void simulated_annealing::run_partition()
{
    std::cout << "SM algorithm starting ..." <<std::endl;
    initial_partition(m_subsets[0], m_subsets[1]);
    m_cut_size = calculate_cut(m_subsets[0]);
    std::cout << "Initial cut size is: " << m_cut_size;
    while (m_temperature > 0 && m_counter < ITERATION_NUMBER) {
        mutate();
        ++m_counter;
    }
    write_graph();
    std::cout << " Optimized cut size is: " << m_cut_size << std::endl;
}
