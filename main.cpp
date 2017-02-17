#include <iostream>
#include <iomanip>

#include "graph.h"
#include "graph_input.h"
#include "partition_manager.h"

int main(int argc, char** argv)
{
    Graph* tmp = nullptr;
    if (argc == 1) {
        std::cout << std::setfill('_') << std::setw(57) << '\n'
                  << "|Usage: for programm correct working you sould provide |" << '\n'
                  << "|       Arg1 - input graph file_name.grap              |" << '\n'
                  << "|       Arg2 - input configuration file for partitioner|" << '\n'
                  << std::setfill('_') << std::setw(59) << "\n\n\n";
        return 1;
    } else if (argc == 2) {
        reader::read_graph input_parser(argv[1]);
        tmp = input_parser.parse();
    } else if (argc == 3) {
        reader::read_graph input_parser(argv[1]);
        input_parser.parse();
        //reader::read_config input_config(argc[2]);
        //input_config.parse();
    }
    tmp->print();
    std::cout << std::endl;
    std::cout << std::endl;

    auto mgr = partition_manager::get_instance();

    auto fm_part = mgr->create_algorithm(partition_type::FETUCCIA_MATEISIS, tmp);

    std::cout << std::endl;
    std::cout << std::endl;

    fm_part->run_partition();

    partition_manager::remove_instance();
    delete tmp;
    return 0;
}
