#include <iostream>
#include <iomanip>
#include <memory>

#include "graph.h"
#include "timer.h"
#include "graphinput.h"
#include "partitionmanager.h"

int main(int argc, char** argv)
{
    std::shared_ptr<Graph> tmp = nullptr;
    if (argc == 1) {
        std::cout << std::setfill('_') << std::setw(57) << '\n'
                  << "|Usage: for programm correct working you sould provide |" << '\n'
                  << "|       Arg1 - input graph file_name.grap              |" << '\n'
                  << "|       Arg2 - input configuration file for partitioner|" << '\n'
                  << std::setfill('_') << std::setw(59) << "\n\n\n";
        return 1;
    } else if (argc == 2) {
        reader::GraphReader input_parser(argv[1]);
        tmp.reset(input_parser.parse());
    } else if (argc == 3) {
        reader::GraphReader input_parser(argv[1]);
        input_parser.parse();
        //reader::read_config input_config(argc[2]);
        //input_config.parse();
    }
    tmp->print();
    std::cout << std::endl;
    std::cout << "BFS" << std::endl;
    tmp->BFS(3);
    std::cout << "DFS" << std::endl;
    tmp->DFS(3);

    //auto mgr = PartitionManager::get_instance();

    //timer monitoring;
    //auto part = mgr->create_algorithm(partition_type::FETUCCIA_MATEISIS, tmp);
    //auto part = mgr->create_algorithm(partition_type::KERNIGAN_LIN, tmp);
    //auto part = mgr->create_algorithm(partition_type::SIMULATED_ANNEALING, tmp);

    //std::cout << std::endl;
    //std::cout << std::endl;

    //part->run_partition();

    //PartitionManager::remove_instance();
    return 0;
}
