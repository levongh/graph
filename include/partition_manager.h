#pragma once

#include "kernigan_lin.h"
#include "fiduccia_mattheyses.h"
#include "simulated_annealing.h"

/// @brief manager for partition alforithm creation
/// @brief should work like builder pattern
class partition_manager
{
    /// @brief public interfaces
    /// @{
public:

    /// @brief default constructor
    partition_manager()
        : part_algorithms{}
    {}

    /// @brief destructor
    ~partition_manager();

    /// @brief copy constructor
    partition_manager(const partition_manager& other) = delete;

    /// @brief copy assignment operator
    partition_manager& operator=(const partition_manager& other) = delete;


    /// @brief move constructor
    partition_manager(partition_manager&& other) = delete;

    /// @brief copy assignment operator
    partition_manager& operator=(partition_manager&& other) = delete;

    /// @brief create and return required algorithm
    graph_partition* create_algorithm(partition_type pt, Graph* g);
    /// @}

    /// @brief static interfaces
    /// @{
public:
    static partition_manager* get_instance();

    static void remove_instance();

private:
    static partition_manager* s_instance;
    static std::mutex s_mutex;
    /// @}

private:
    std::vector<graph_partition*> part_algorithms;
};
