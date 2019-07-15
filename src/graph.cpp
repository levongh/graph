#include <iostream>
#include <queue>
#include <stack>
#include <algorithm>
#include <limits>
#include <fstream>

#include "graph.h"
#include "vertex.h"

namespace {

class CompareGreater
{
public:
    bool operator()(const std::pair<int, Vertex*> lhs,
                    const std::pair<int, Vertex*> rhs)
    {
        return (lhs.first > rhs.first);
    }
};


} // unnamed namespace

Graph::Graph(const std::set<unsigned>& vertexes,
        const std::set<std::pair<std::pair<unsigned, unsigned>, unsigned> >& edges, bool dir)
{
    for (const auto& iter : vertexes) {
        add_vertex(iter);
    }
    for (const auto& iter : edges) {
       add_edge(iter.first.first, iter.first.second, iter.second);
    }
}

Graph::~Graph()
{
    for (auto item : m_work) {
        delete item.second;
    }
    for (auto item : m_edges) {
        delete item;
    }
    std::cout << "destructor" << std::endl;
}

unsigned Graph::get_weight(Vertex* vert1, Vertex* vert2)
{
    const auto& iter = std::find_if(m_edges.begin(), m_edges.end(), [vert1, vert2] (const Edge* e) -> bool
            {
                return (vert1->m_name == e->m_vertex1->m_name)
                        && (vert2->m_name == e->m_vertex2->m_name);
            });
    if (iter != m_edges.end()) {
        return (*iter)->m_weight;
    } else {
        return 0;
    }
}

void Graph::initial_partition(std::vector<Vertex*>& label_1, std::vector<Vertex*>& label_2)
{
    const auto pivot = m_numvertexes/2;
    auto vert_iter = m_work.begin();
    for (unsigned  i = 0; i < pivot; ++i) {
        vert_iter->second->setLabel(0);
        label_1.push_back(vert_iter->second);
        ++vert_iter;
    }
    for (unsigned i = pivot; i < m_numvertexes; ++i) {
        vert_iter->second->setLabel(1);
        label_2.push_back(vert_iter->second);
        ++vert_iter;
    }
}

void Graph::initialize_buckets(std::multimap<int, Vertex*, std::greater<int> >& buckets)
{
    for (const auto& iter : m_work) {
        buckets.insert(std::make_pair(iter.second->internalCost(), iter.second));
    }
}


unsigned int Graph::get_index(const unsigned temp) const
{
    for (unsigned int i = 0; i < m_vertexes.size(); ++i) {
        if (m_vertexes[i] == temp) {
            return i;
        }
    }
    return m_numvertexes;
}

void Graph::add_vertex(const unsigned name)
{
    if (m_work.find(name) == m_work.end()) {
        m_work[name] = new Vertex(name);
        m_vertexes.push_back(name);
        ++m_numvertexes;
        return;
    }
    std::cout << "\nVertex already exists!";
}

void Graph::add_edge(const unsigned from, const unsigned to, double cost)
{
    auto iter = m_work.find(from);
    if (iter == m_work.end()) {
        std::cout << "\n Vertex '" << from <<"' doesn't exist!";
        return;
    }
    Vertex* from_v = iter->second;
    iter = m_work.find(to);
    if (iter == m_work.end()){
        std::cout << "\n Vertex '" << to << "' doesn't exist!";
        return;
    }
    Vertex* to_v = iter->second;
    m_edges.insert(new Edge(from_v, to_v, cost));
    from_v->addAdjecent(std::move(std::make_pair(cost, to_v)));
}

void Graph::BFS(const unsigned source)
{
    std::queue<unsigned> q;
    std::vector<bool> visited(m_numvertexes, false);
    visited[get_index(source)] = true;
    q.push(source);
    while(!q.empty()){
        unsigned str = q.front();
        std::cout << str << "->";
        q.pop();

        for(const auto& iter : m_work[str]->getAdjacent()) {
            if(!visited[get_index(iter.second->m_name)]){
                visited[get_index(iter.second->m_name)] = true;
                q.push(iter.second->m_name);
            }
        }
    }
    std::cout << "end" << std::endl;;
}

void Graph::DFS(const unsigned source)
{
    std::stack<unsigned> q;
    std::vector<bool> visited(m_numvertexes, false);
    visited[get_index(source)] = true;
    q.push(source);
    std::vector<std::pair<int, Vertex*> >::iterator iter;
    while(!q.empty()){
        unsigned str = q.top();
        std::cout << str << "->";
        q.pop();

        for(const auto& iter : m_work[str]->getAdjacent()) {
            if(!visited[get_index(iter.second->m_name)]){
                visited[get_index(iter.second->m_name)] = true;
                q.push(iter.second->m_name);
            }
        }
    }
    std::cout << "end" << std::endl;;
}

namespace {
/**
 * @brief this part is designed as a helper part for kruskal MST implementation
 */

std::map<Vertex * , Vertex * > PARENT;
std::map<Vertex * , int> RANK;

Vertex* find(Vertex* vertex)
{
    if (PARENT[vertex] == vertex) {
        return PARENT[vertex];
    } else {
        return find(PARENT[vertex]);
    }
}

} //unnamed namespace

void Graph::mst_kruskal()
{
    std::vector<Edge*> res;

    for (unsigned int i = 0; i < m_vertexes.size(); ++i) {
        Vertex* c = m_work[m_vertexes[i]];
        PARENT[c] = c;
        RANK[c] = 0;
    }

    for (const auto& e : m_edges) {
        Vertex* root1 = find(e->m_vertex1);
        Vertex* root2 = find(e->m_vertex2);
        if (root1 != root2) {
            res.push_back(e);
            if (RANK[root1] > RANK[root2]) {
                PARENT[root2] = root1;
                RANK[root1]++;
            } else {
                PARENT[root1] = root2;
                RANK[root2]++;
            }
        }
    }

    for (const auto& e : res) {
        std::cout << e->m_vertex1->m_name << " -- "
             << e->m_vertex2->m_name << "  " << e->m_weight << std::endl;
    }
}

unsigned Graph::get_vertex_count() const
{
    return m_numvertexes;
}

Vertex* Graph::get_vertex(unsigned index) const
{
    return (*m_work.find(index)).second;
}

void Graph::mst_prim(const unsigned root)
{
    std::map<Vertex*, Vertex*> res;
    std::map<Vertex*, Vertex*> PARENT;
    std::map<Vertex*, int> KEY;

    for (auto c : m_vertexes) {
        PARENT[m_work[c]] = nullptr;
        KEY[m_work[c]] = std::numeric_limits<int>::max();
    }
    KEY[m_work[root]] = 0;
    std::vector<unsigned> Q = m_vertexes;

    while (!Q.empty()) {
        unsigned temp = *std::min_element(Q.begin(), Q.end(), [&](unsigned x, unsigned y) {return KEY[m_work[x]] < KEY[m_work[y]];});
        Vertex *u= m_work[temp];
        auto iter = std::remove(Q.begin(), Q.end(), temp);
        Q.erase(iter, Q.end());
        if (PARENT[u] != nullptr) {
            res[u] = PARENT[u];
        }

        for(const auto& v : u->getAdjacent()){
            if (std::find(Q.begin(), Q.end(), (v.second)->m_name)!= Q.end()){
                if(v.first < KEY[v.second]){
                    PARENT[v.second] = u;
                    KEY[v.second] = v.first;
                }
            }
        }

    }
    for (const auto& e : res) {
        std::cout << e.first->m_name << " -- " << e.second->m_name << std::endl;
    }
}

std::map<unsigned, std::pair<int, unsigned> > Graph::Dijkstra(const unsigned start) {
    std::map<unsigned, int > weights;
    std::map<unsigned, unsigned > parents;
    for (unsigned int i = 0; i < m_vertexes.size(); ++i){
        weights[m_vertexes[i]] = std::numeric_limits<int>::max();
        parents[m_vertexes[i]] = 0;
    }

    std::priority_queue<std::pair<int, Vertex*>, std::vector<std::pair<int, Vertex*> >,CompareGreater> Q;

    weights[start] = 0;

    Q.push(std::make_pair(0, m_work[start]));
    std::pair<int, Vertex*> currentNode;
    while (!Q.empty()) {
        currentNode = Q.top();
        Q.pop();
        if (currentNode.first <= weights[(currentNode.second)->m_name]) {
            for(const auto& v : (currentNode.second)->getAdjacent() ){
                if (weights[(v.second)->m_name] > weights[(currentNode.second)->m_name] + v.first) {
                    parents[(v.second)->m_name] = (currentNode.second)->m_name;
                    weights[(v.second)->m_name] = weights[(currentNode.second)->m_name] + v.first;
                    Q.push(std::make_pair(weights[(v.second)->m_name], v.second));
                }
            }
        }
    }
    std::map<unsigned, std::pair<int, unsigned> > result;
    for (unsigned int i = 0; i < m_vertexes.size(); ++i){
        result[m_vertexes[i]] = std::make_pair(weights[m_vertexes[i]], parents[m_vertexes[i]]);
    }
    return std::move(result);
}

void Graph::print() const
{
    for (const auto& iter : m_work) {
        iter.second->print();
    }
}

void Graph::print_partition(std::ofstream& output_file) const
{
     for (const auto& iter : m_work) {
         output_file << iter.second->getLabel() << '\n';
     }
}
