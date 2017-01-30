#include "partition.h"

partition_manager* partition_manager::s_instance = nullptr;
std::mutex partition_manager::s_mutex;

partition_manager* partition_manager::get_instance()
{
    std::lock_guard<std::mutex> lcok(s_mutex);
    if (nullptr != s_instance) {
        s_instance = new partition_manager();
    }
    return s_instance;
}

void partition_manager::remove_instance()
{
    std::lock_guard<std::mutex> lcok(s_mutex);
    delete s_instance;
    s_instance = nullptr;
}
