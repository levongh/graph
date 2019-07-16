#pragma once

#include "partition.h"

/// @brief manager for partition alforithm creation
/// @brief should work like builder pattern
class PartitionManager
{
    /// @brief public interfaces
    /// @{
public:

    /// @brief default constructor
    PartitionManager()
        : m_algorithms{}
    {}

    /// @brief destructor
    ~PartitionManager();

    /// @brief copy constructor
    PartitionManager(const PartitionManager& other) = delete;

    /// @brief copy assignment operator
    PartitionManager& operator=(const PartitionManager& other) = delete;


    /// @brief move constructor
    PartitionManager(PartitionManager&& other) = delete;

    /// @brief copy assignment operator
    PartitionManager& operator=(PartitionManager&& other) = delete;

    /// @brief create and return required algorithm
    GraphPartition* create_algorithm(partition_type pt, Graph* g);
    /// @}

    /// @brief static interfaces
    /// @{
public:
    static PartitionManager* get_instance();

    static void remove_instance();

private:
    static PartitionManager* s_instance;
    static std::mutex s_mutex;
    /// @}

private:
    std::vector<GraphPartition*> m_algorithms;
};
