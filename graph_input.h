#pragma once

/**
 * @file graph_input.h
 * @title declaration of graph_input
 * @description grap_reader is the cladd that pases input file parsing to graph
 * @author Levon Ghukasyan
 */

namespace reader {

    class read_graph
    {
    public:
        explicit read_graph(const std::string& file_name)
            : m_file_name{file_name}
        {
        }

    public:
        read_graph(const read_graph& other) = delete;
        read_graph& operator=(const read_graph& other) = delete;

        read_graph(read_graph&& other) = delete;
        read_graph& operator=(read_graph&& other) = delete;

    public:
        void parse();


    public:
        std::string m_file_name;
    };

} // namespace reader
