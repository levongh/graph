#include <iostream>
#include <iomanip>

#include "graph_input.h"
#include "graph.h"
#include "kernigan_lin.h"
#include "fiduccia_mattheyses.h"

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
    std::cout<< std::endl;
    std::cout<< std::endl;

    //graph_partition* kl_part = new kernigan_lin(tmp);
    graph_partition* fm_part = new fiduccia_mattheyses(tmp);

    std::cout<< std::endl;
    std::cout<< std::endl;

    //kl_part->run_partition();
    fm_part->run_partition();

    //delete kl_part;
    delete fm_part;
    delete tmp;
    return 0;
}
