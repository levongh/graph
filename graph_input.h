#pragma once

/**
 * @file graph_input.h
 * @title declaration of graph_input
 * @description grap_reader is the cladd that pases input file parsing to graph
 * @author Levon Ghukasyan
 */

namespace reader {

    enum class mode
    {
        SIMPLE,
        EDGE,
        EDGE_NODE
    };

    class read_graph
    {
    public:
        explicit read_graph(const std::string& file_name)
            : m_file_name{file_name}
            , m_mode{mode::SIMPLE}
        {
        }

    public:
        read_graph(const read_graph& other) = delete;
        read_graph& operator=(const read_graph& other) = delete;

        read_graph(read_graph&& other) = delete;
        read_graph& operator=(read_graph&& other) = delete;

    public:
        void parse();

    private:
        bool read_first_line(const std::string& str, unsigned& vert, unsigned& edge, size_t pos);

    private:
        void parse_line(const std::string& str, unsigned line_numer);

    public:
        std::string m_file_name;
        mode m_mode;
    };

} // namespace reader
