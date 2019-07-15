#include <fstream>
#include <string>
#include <iostream>

#include "graph.h"
#include "graphinput.h"


namespace {

std::string whitespace(" \t");


size_t parse_edge_weight(const std::string& str, size_t pos, unsigned& weight, unsigned line_number)
{
    pos = str.find_first_not_of(whitespace, pos);
    if (pos == std::string::npos) {
        return pos;
    }
    size_t next_pos = str.find_first_of(whitespace, pos);
    auto weight_str = str.substr(pos, next_pos);
    try {
        weight = std::stoi(weight_str);
    } catch (const std::invalid_argument& ex) {
        std::cout << ex.what() << " : " << "In provided file graph edge weight is not correct: line"
                               << line_number << " between columns: " <<  pos << ':' << next_pos << std::endl;
        throw;
    }
    return next_pos;
}

Graph* create_graph(const reader::graph_data& data)
{
    if ((data.m_vert_count != data.m_vertex_list.size()) ||
            (2 * data.m_edge_count != data.m_edge_list.size()))
    {
        std::cout << "Provided file is not correct\n"
                  << "exppected vertex count: " << data.m_vert_count << " provided vertex count: " << data.m_vertex_list.size()
                  << "\nexppected edge count:   " << 2 * data.m_edge_count << " provided edge cout:    " << data.m_edge_list.size()
                  << std::endl;
        return nullptr;
    }

    return new Graph(data.m_vertex_list, data.m_edge_list);
}

}

namespace reader {

bool GraphReader::read_first_line(const std::string& str, unsigned& vert, unsigned& edge, size_t pos)
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

void GraphReader::parse_line(const std::string& str, size_t pos, unsigned line_number, graph_data& data)
{
    size_t initial_pos = str.find_first_not_of(whitespace, pos);
    if (initial_pos == std::string::npos) {
        return;
    }
    size_t next_pos = str.find_first_of(whitespace, initial_pos);
    auto vert_str = str.substr(initial_pos, next_pos);
    unsigned vert = std::stoi(vert_str);
    unsigned weight = 0;
    if (m_mode == mode::EDGE) {
        next_pos = parse_edge_weight(str, next_pos, weight, line_number);
    } else if (m_mode == mode::SIMPLE) {
        weight = 1;
    }
    data.m_edge_list.insert(std::make_pair(std::make_pair(line_number, vert), weight));
    if (next_pos == std::string::npos) {
        return;
    } else {
        parse_line(str, next_pos, line_number, data);
    }
}

Graph* GraphReader::parse()
{
    std::ifstream infile(m_file_name, std::ios_base::in);
    if (!infile.good()) {
        std::cout << "File is not exist, please provide correct filename" << std::endl;
        return nullptr;
    }
    std::string line;
    static int line_number = 0;

    graph_data data;
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
                return nullptr;
            }
            data.m_vert_count = vertex_count;
            data.m_edge_count = edge_count;
            ++line_number;
        } else {
            parse_line(line, 0, line_number, data);
            data.m_vertex_list.insert(line_number);
            ++line_number;
        }
    }
    return create_graph(data);
}

} // namespace reader
