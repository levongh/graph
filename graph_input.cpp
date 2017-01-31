#include <fstream>
#include <sstream>
#include <string>
#include <iostream>

#include <vector>
#include <set>

#include "graph_input.h"

namespace {

std::string whitespace(" \t");

struct graph_line
{
    std::vector<unsigned> m_vertex_list;
    std::set<std::pair<unsigned, unsigned> > m_edge_list;
};

}

namespace reader {

bool read_graph::read_first_line(const std::string& str, unsigned& vert, unsigned& edge, size_t pos)
{
    try {
        size_t next_pos = str.find_first_of(whitespace, pos);
        const auto v_num_str = str.substr(pos, next_pos);
        vert = std::stoi(v_num_str);
        pos = str.find_first_not_of(whitespace, next_pos);
        if (pos == std::string::npos) {
            std::cout << "Provided file" << m_file_name << " is not match to Metis graph description" << std::endl;
            return false;
        }
        next_pos = str.find_first_of(whitespace, pos);
        const auto e_num_str = str.substr(pos, next_pos);
        edge = std::stoi(e_num_str);

        pos = str.find_first_not_of(whitespace, next_pos);
        if (pos == std::string::npos) {
            m_mode = mode::SIMPLE;
            return true;
        }
        next_pos = str.find_first_of(whitespace, pos);
        const auto m_mode_str = str.substr(pos, next_pos);
        auto data = std::stoi(m_mode_str);
        if (data == 1) {
            m_mode = mode::SIMPLE;
        } else if (data == 10) {
            m_mode = mode::EDGE;
        } else if(data == 11) {
            m_mode = mode::EDGE_NODE;
        } else {
            std::cout << "Provided file is not correct please check its data" << std::endl;
            return false;
        }
        return true;

    } catch (const std::invalid_argument& ex) {
        std::cout << ex.what() << ':' << "Provided file" << m_file_name << " is not match to Metis graph description" << std::endl;
        return false;
    }
    return true;
}

void read_graph::parse_line(const std::string& str, unsigned line_numer)
{
}

void read_graph::parse()
{
    std::ifstream infile(m_file_name, std::ios_base::in);
    if (!infile.good()) {
        std::cout << "File is not exist, please provide correct filename" << std::endl;
        return;
    }
    std::vector<graph_line> graph_data;
    std::string line;
    static int line_number = 0;

    while (std::getline(infile, line)) {
        if (line.empty()) {
            continue;
        }
        size_t initial_pos = line.find_first_not_of(whitespace);
        if (initial_pos == std::string::npos) {
            continue;
        }
        if (line[initial_pos] == '%') {
            continue;
        }

        if (line_number == 0) {
            unsigned vertex_count = 0;
            unsigned edge_count = 0;
            if (!read_first_line(line, vertex_count, edge_count, initial_pos)) {
                return;
            }
            ++line_number;
            std::cout << vertex_count << " " << edge_count << std::endl;
        } else {
            parse_line(line, line_number);
            ++line_number;
        }
    }
}

} // namespace reader
