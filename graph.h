#pragma once

#include <map>
#include <vector>
#include <set>
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
    Vertex(const std::string& name, unsigned short label = 0)
        : m_name{name}
        , m_label{label}
    {
    }

    unsigned short get_label()const
    {
        return m_label;
    }

    void set_label(unsigned short label)
    {
        m_label = label;
    }

    void print() const;

//private:
    std::vector<std::pair<int, Vertex*> > m_adj;
    std::string m_name;

private:
    unsigned short m_label;
};

/**
 * @brief class CompareGreater
 * @brief class to compare two vertexes in priority queues
 */
class CompareGreater
{
public:
    bool operator()(const std::pair<int, Vertex *> lhs, const std::pair<int, Vertex *> rhs)
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
	Edge(Vertex* vertex1, Vertex* vertex2, int weight = 1)
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
 * @brief class edge_compare
 * @brief designed to sort eges with there weights
 */
class edge_compare
{
public:
    bool operator()(const Edge* lhs, const Edge* rhs)
    {
        return (lhs->m_vertex1->m_name < rhs->m_vertex1->m_name)
                    && (lhs->m_vertex2->m_name <= rhs->m_vertex2->m_name);
//        return lhs->m_weight < rhs->m_weight;
    }
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

    void print() const;

    /// @brief returns the weight of specified edge
    unsigned get_weight(Vertex* vert1, Vertex* vert2);

    /// @brief returns thw index from name of vetex
    /// @brief index refers to vertex number in the graph
    unsigned int get_index(const std::string& name) const;

    /// @brief make initial partition
    void initial_partition(std::vector<Vertex*>& label_1, std::vector<Vertex*>& label_2);

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
    /// @brief stores the map from name of vertex to Vertex class
    std::map<std::string, Vertex*> work;
    bool m_directed;
    unsigned int m_numvertexes;
    std::vector<std::string> m_vertexes;
    //std::vector<Edge*> m_edges;
    std::set<Edge*, edge_compare> m_edges;
};
