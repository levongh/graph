#pragma once


enum class partition_type
{
    KERNIGAN_LIN,
    FETUCCIA_MATEISIS,
    SIMULATED_ANNEALING,
    K_WAY
};

/**
 *  @brief class for algorithm configuration
 *  @param m_type showing algorithm type this parameter should
 *         \use paritition_manager class object
 *  @param m_count showing partitions count
 *  @param m_allowMultithreading showing is it accepatable to use mutithread partition or not
 */
struct PartitionConfig
{
public:
    PartitionConfig(partition_type type = partition_type::KERNIGAN_LIN, unsigned short count = 2, bool allow = false)
        : m_type{type}
        , m_count{count}
        , m_allowMultithreading{allow}
    {
        assert(count >=2);
    }

    partition_type partitionType() const
    {
        return m_type;
    }

    unsigned short getPartitionCount() const
    {
        return m_count;
    }

    bool isMutithreaded() const
    {
        return m_allowMultithreading;
    }

private:
    partition_type m_type;
    unsigned short m_count;
    bool m_allowMultithreading;
};

