#pragma once

#include <map>
#include <vector>
#include <set>
#include <string>

#include "vertex.h"


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
 * @brief class EdgeComparator
 * @brief designed to sort eges with there weights
 */
class EdgeComparator
{
public:
    bool operator()(const Edge* lhs, const Edge* rhs)
    {
        return (lhs->m_vertex1->m_name < rhs->m_vertex1->m_name) &&
               (lhs->m_vertex2->m_name <= rhs->m_vertex2->m_name);
    }
};

/** 
 * @brief class graph
 * @brief this is a simple implementation of graph data structure
 * @param m_numvertexes number of vertexes
 * @param m_vetexes names of vetexs
 * @param m_edges stores all edges in graph
 */
class Graph
{
public:
    Graph(bool temp = false)
        : m_numvertexes{0}
    {
    }

    Graph(const std::set<unsigned>& vertexes,
            const std::set<std::pair<std::pair<unsigned, unsigned>, unsigned> >& edges, bool dir = false);

    ~Graph();

    void print() const;

    /// @brief returns the weight of specified edge
    unsigned get_weight(Vertex* vert1, Vertex* vert2);

    /// @brief returns the index from name of vetex
    /// @brief index refers to vertex number in the graph
    unsigned int get_index(const unsigned name) const;

    /// @brief make initial partition
    void initial_partition(std::vector<Vertex*>& label_1, std::vector<Vertex*>& label_2);

    /// @brief implements MST prim algorihm
    /// @brief prints out all the edges in the MST
    void mst_prim(const unsigned from);

    /// @brief implements MST Kruskal's algorithm
    /// @brief prints out all the edges in the MST
    void mst_kruskal();

    /// @brief implements BFS algorithm
    void BFS(const unsigned source);

    /// @brief implements DFS algorithm
    void DFS(const unsigned source);

    /// @brief add new vertex to graph
    void add_vertex(const unsigned name);

    /// @brief add new edge to graph
    void add_edge(const unsigned from, const unsigned to, double cost = 1);

    /// @brief implemaentaion of Dijkstra's algorithm
    std::map<unsigned, std::pair<int, unsigned> > Dijkstra(const unsigned start);

    /// @brief
    void initialize_buckets(std::multimap<int, Vertex*, std::greater<int> >& buckets);

    /// @brief
    void print_partition(std::ofstream& output_file) const;

    unsigned get_vertex_count() const;

    Vertex* get_vertex(unsigned index) const;

private:
    /// @brief stores the map from name of vertex to Vertex class
    std::map<unsigned, Vertex*> m_work;
    unsigned int m_numvertexes;
    std::vector<unsigned> m_vertexes;
    std::set<Edge*, EdgeComparator> m_edges;
};
