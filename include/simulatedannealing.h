#pragma once

/**
 * @file simulatedannealing.h
 * @class SimulatedAnnealing
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

class SimulatedAnnealing : public GraphPartition
{
public:
    SimulatedAnnealing(Graph* G, PartitionConfig config = PartitionConfig());

    virtual void runPartition() override;

private:
    double calculateMove(unsigned int index);

    void mutate();

    void applyMove(Vertex* toMove);

    //! function to control temperature
    void sheduleAnnealing();

private:
    unsigned int m_temperature;
    unsigned int m_counter;
    unsigned int m_vertexCount;
    double m_cutSize;
    annealing_type m_annealingType;
    std::random_device m_device;
    std::mt19937 m_engine;
    std::uniform_int_distribution<unsigned> m_distribution;
};
