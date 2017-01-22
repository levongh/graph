#pragma once

#include <map>
#include <vector>
#include <string>

/**
 * @brief class Vertex
 * @param m_adj cost of edge and destination vertex
 * @param m_name the name of vcertex
 */

class Vertex
{
public:
    /// @brief constructor
    Vertex(const std::string& name)
        : m_name{name}
    {
    }

    /// @brief function to print all neighbors
    void print_neighbours() const;

//private:
    std::vector<std::pair<int, Vertex*> > m_adj;
    std::string m_name;
};

/**
 * @brief class CompareGreater
 * @brief class to compare two vertexes in priority queues
 */
class CompareGreater
{
public:
    bool operator()(const std::pair<int,Vertex *> lhs, const std::pair<int, Vertex *> rhs)
    {
        return (lhs.first > rhs.first);
    }
};

/* struct to store edges in the graph. */
/**
 * @brief class Edge
 * @brief class to store edges in the graph
 * @param m_vertex1 initial vertex
 * @param m_vertex2 final vertex
 * @param m_weight the wieght of this Edge
 */
class Edge
{
public:
	Edge(Vertex *vertex1, Vertex *vertex2, int weight)
        : m_vertex1{vertex1}
        , m_vertex2{vertex2}
        , m_weight{weight}
    {
    }

//private:
    Vertex* m_vertex1;                        //initial vertex
    Vertex* m_vertex2;                        //final vertex
    int m_weight;                             //cost/weight of the edge
};

/** 
 * @brief class graph
 * @brief this is a simple implementation of graph data structure
 * @param m_directed for checking is graph directed or not 
 * @param m_numvertexes number of vertexes
 * @param m_vetexes names of vetexs
 * @param m_edges stores all edges in graph
 */
class Graph
{
public:
    Graph(bool temp = false)
        : m_directed{temp}
        , m_numvertexes{0}
    {
    }

    /// @brief stores the map from name of vertex to Vertex class
    std::map<std::string, Vertex*> work;

    /// @brief returns thw index from name of vetex
    /// @brief index refers to vertex number in the graph
    unsigned int get_index(const std::string& name) const;

    /// @brief implements MST prim algorihm
    /// @brief prints out all the edges in the MST
    void mst_prim(const std::string& from);

    /// @brief implements MST Kruskal's algorithm
    /// @brief prints out all the edges in the MST
    void mst_kruskal();

    /// @brief implements BFS algorithm
    void BFS(const std::string& );

    /// @brief add new vertex to graph
    void add_vertex(const std::string& name);

    /// @brief add new edge to graph
    void add_edge(const std::string& from, const std::string& to, double cost);

    /// @brief implemaentaion of Dijkstra's algorithm
    std::map<std::string, std::pair<int, std::string> > Dijkstra(const std::string& start);

private:
    bool m_directed;
    unsigned int m_numvertexes;
    std::vector<std::string> m_vertexes;
    std::vector<Edge*> m_edges;
};
