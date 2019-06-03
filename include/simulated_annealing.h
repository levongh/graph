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
#include <random>

#include "partition.h"

class Graph;

enum class annealing_type
{
    FAST_ANNEALING,
    DETAILD_ANNEALING
    //! sould add another anneling types
};

class simulated_annealing : public graph_partition
{
public:
    simulated_annealing(Graph* G, partition_config config = partition_config());

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
    std::random_device m_device;
    std::mt19937 m_engine;
    std::uniform_int_distribution<unsigned> m_distribution;
    std::vector<std::vector<Vertex*> > m_subsets;
};
