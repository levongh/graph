#include <iostream>
#include <queue>
#include <algorithm>
#include <limits>

#include "graph.h"


int Vertex::internal_cost() const
{
    unsigned result = 0;
    for (const auto& elem : m_adj) {
        if (elem.second->get_label() == get_label()) {
            result += elem.first;
        }
    }
    return result;
}

int Vertex::external_cost() const
{
    unsigned result = 0;
    for (const auto& elem : m_adj) {
        if (elem.second->get_label() != get_label()) {
            result += elem.first;
        }
    }
    return result;
}

int Vertex::moveing_cost() const
{
    return external_cost() - internal_cost();
}

void Vertex::print() const
{
    std::cout <<  m_name <<' ';
    for (const auto& iter : m_adj) {
        std::cout << iter.first << " " << iter.second->m_name << "   ";
    }
    std::cout << std::endl;
}

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
    auto vert_iter = work.begin();
    for (unsigned  i = 0; i < pivot; ++i) {
        vert_iter->second->set_label(0);
        label_1.push_back(vert_iter->second);
        ++vert_iter;
    }
    for (unsigned i = pivot; i < m_numvertexes; ++i) {
        vert_iter->second->set_label(1);
        label_2.push_back(vert_iter->second);
        ++vert_iter;
    }
}

void Graph::initialize_buckets(std::multimap<int, Vertex*, std::greater<int> >& buckets)
{
    for (const auto& iter : work) {
        buckets.insert(std::make_pair(iter.second->internal_cost(), iter.second));
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
    if (work.find(name) == work.end()) {
        work[name] = new Vertex(name);
        m_vertexes.push_back(name);
        ++m_numvertexes;
        return;
    }
    std::cout << "\nVertex already exists!";
}

void Graph::add_edge(const unsigned from, const unsigned to, double cost)
{
    auto iter = work.find(from);
    if (iter == work.end()) {
        std::cout << "\n Vertex '" << from <<"' doesn't exist!";
        return;
    }
    Vertex* from_v = iter->second;
    iter = work.find(to);
    if (iter == work.end()){
        std::cout << "\n Vertex '" << to << "' doesn't exist!";
        return;
    }
    Vertex* to_v = iter->second;
    m_edges.insert(new Edge(from_v, to_v, cost));
    from_v->m_adj.push_back(std::make_pair(cost, to_v));
}

void Graph::BFS(const unsigned s){
    std::queue<unsigned> q;
    bool* visited = new bool[m_numvertexes];
    for(unsigned int i = 0; i < m_numvertexes; ++i) {
        visited[i] = false;
    }
    visited[get_index(s)] = true;
    q.push(s);
    std::vector<std::pair<int, Vertex*> >::iterator iter;
    while(!q.empty()){
        unsigned str = q.front();
        std::cout << str << "->";
        q.pop();

        for(iter = work[str]->m_adj.begin(); iter != work[str]->m_adj.end(); ++iter){
            if(!visited[get_index(iter->second->m_name)]){
                visited[get_index(iter->second->m_name)] = true;
                q.push(iter->second->m_name);
            }
        }
    }
    std::cout << "end";
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
        Vertex* c = work[m_vertexes[i]];
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

void Graph::mst_prim(const unsigned root)
{
    std::map<Vertex*, Vertex*> res;
    std::map<Vertex*, Vertex*> PARENT;
    std::map<Vertex*, int> KEY;

    for (auto c : m_vertexes) {
        PARENT[work[c]] = nullptr;
        KEY[work[c]] = std::numeric_limits<int>::max();
    }
    KEY[work[root]] = 0;
    std::vector<unsigned> Q = m_vertexes;

    while (!Q.empty()) {
        unsigned temp = *std::min_element(Q.begin(), Q.end(), [&](unsigned x, unsigned y) {return KEY[work[x]] < KEY[work[y]];});
        Vertex *u= work[temp];
        auto iter = std::remove(Q.begin(), Q.end(), temp);
        Q.erase(iter, Q.end());
        if (PARENT[u] != nullptr) {
            res[u] = PARENT[u];
        }

        for(const auto& v : u->m_adj ){
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

    Q.push(std::make_pair(0, work[start]));
    std::pair<int, Vertex*> currentNode;
    while (!Q.empty()) {
        currentNode = Q.top();
        Q.pop();
        if (currentNode.first <= weights[(currentNode.second)->m_name]) {
            for(const auto& v : (currentNode.second)->m_adj ){
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
    for (const auto& iter : work) {
        iter.second->print();
    }
}
