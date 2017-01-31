#include <iostream>
#include <iomanip>

#include "graph_input.h"
#include "graph.h"
#include "kernigan_lin.h"

int main(int argc, char** argv)
{
    if (argc == 1) {
        std::cout << std::setfill('_') << std::setw(57) << '\n'
                  << "|Usage: for programm correct working you sould provide |" << '\n'
                  << "|       Arg1 - input graph file_name.grap              |" << '\n'
                  << "|       Arg2 - input configuration file for partitioner|" << '\n'
                  << std::setfill('_') << std::setw(59) << "\n\n\n";
        return 1;
    } else if (argc == 2) {
        reader::read_graph input_parser(argv[1]);
        input_parser.parse();
    } else if (argc == 3) {
        reader::read_graph input_parser(argv[1]);
        input_parser.parse();
        //reader::read_config input_config(argc[2]);
        //input_config.parse();
    }
/*
    Graph *temp=new Graph();
    temp->add_vertex(1);
    temp->add_vertex(2);
    temp->add_vertex(3);
    temp->add_vertex(4);
    temp->add_vertex(5);
    temp->add_vertex(6);
    temp->add_vertex(7);
    temp->add_vertex(8);
    temp->add_edge(1, 2, 20);
    temp->add_edge(1, 4, 80);
    temp->add_edge(1, 7, 90);
    temp->add_edge(2, 6, 10);
    temp->add_edge(2, 5, 10);
    temp->add_edge(3, 6, 50);
    temp->add_edge(3, 8, 20);
    temp->add_edge(3, 4, 10);
    temp->add_edge(4, 7, 20);
    temp->add_edge(5, 7, 30);
    temp->add_edge(6, 4, 40);
    std::cout << std::endl;
    //temp->print();
    graph_partition* kl_part = new kernigan_lin(temp);
    std::cout<< std::endl;
    std::cout<< std::endl;
    //kl_part->run_partition();
    delete kl_part;
    delete temp; */
    return 0;
}
