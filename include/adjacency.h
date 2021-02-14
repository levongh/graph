#pragma once

namespace graph {

template <typename T = size_t>
class Adjacency
{
public:
    using object_t = T;

    Adjacenc(const object_t vertexIdx = T(), const object_t edgeIdx = T());

    object_t getVertex() const;
    object_t& getVertex();

    object_t getEdge() const;
    object_t& getEdge();

    bool operator < (const Adjacency<object_t>& other) const
    bool operator <= (const Adjacency<object_t>& other) const

    bool operator > (const Adjacency<object_t>& other) const
    bool operator <= (const Adjacency<object_t>& other) const

    bool operator == (const Adjacency<object_t>& other) const
    bool operator != (const Adjacency<object_t>& other) const

private:
    object_t m_vertex;
    object_t m_edge;
};

#include "adjacency_impl.h"
}
