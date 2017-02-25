#pragma once

/**
 * @file simulated_annealing.h
 * @class simulated_annealing
 * @description basic implementation of simulated anneling algorithm 
 *              \to solve graph partition problem
 * @data http://mathworld.wolfram.com/SimulatedAnnealing.html
 * @author Levon Ghukasyan
 */

#include <limits>
#include "partition.h"

#include "graph.h"


enum class annealing_type
{
    FAST_ANNEALING,
    DETAILD_ANNEALING
    //! sould add another anneling types
};

class simulated_annealing : public graph_partition
{
public:
    simulated_annealing(Graph* G, partition_config config = partition_config())
        : graph_partition{G, config}
        , m_temperature{std::numeric_limits<unsigned int>::max()}
        , m_counter{0}
        , m_vertex_count{m_graph->get_vertex_count()}
        , m_cut_size{0}
        , m_annealing_type{annealing_type::FAST_ANNEALING}
        , m_subsets{config.get_partition_count()}
    {
    }

    virtual void run_partition() override;

private:
    double calculate_move(unsigned int index);

    void mutate();

    void apply_move(Vertex* to_move);

    //! function to control temperature
    void shedule_annealing();

private:
    unsigned int m_temperature;
    unsigned int m_counter;
    unsigned int m_vertex_count;
    double m_cut_size;
    annealing_type m_annealing_type;
    std::vector<std::vector<Vertex*> > m_subsets;
};
