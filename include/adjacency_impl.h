template <typename T>
Adjacenc<T>::Adjacenc(const object_t vertexIdx, const object_t edgeIdx)
    : m_vertex(vertexIdx)
    , m_edge(edgeIdx)
{
}


template <typename T>
inline typename Adjacency<T>::object_t Adjacency<T>::getVertex() const
{
    return m_vertex;
}

template <typename T>
inline typename Adjacency<T>::object_t& Adjacency<T>::getVertex()
{
    return m_vertex;
}

template <typename T>
inline typename Adjacency<T>::object_t Adjacency<T>::getEdge() const
{
    return m_edge;
}
template <typename T>
inline typename Adjacency<T>::object_t& Adjacency<T>::getEdge()
{
    return m_edge;
}

template <typename T>
inline bool Adjacency<T>::operator < (const Adjacency<object_t>& other) const
{
    if (m_vertex < other.m_vertex) {
        return true;
    } else if (m_vertex == other.m_vertex) {
        return m_edge < other.m_edge;
    } else {
        return false;
    }
}

template <typename T>
bool Adjacency<T>::operator <= (const Adjacency<object_t>& other) const
{
    if (m_vertex < other.m_vertex) {
        return true;
    } else if (m_vertex == other.m_vertex) {
        return m_edge <= other.m_edge;
    } else {
        return false;
    }
}

template <typename T>
bool Adjacency<T>::operator > (const Adjacency<object_t>& other) const
{
    if (m_vertex > other.m_vertex) {
        return true;
    } else if (m_vertex == other.m_vertex) {
        return m_edge > other.m_edge;
    } else {
        return false;
    }
}

template <typename T>
bool Adjacency<T>::operator <= (const Adjacency<object_t>& other) const
{
    if (m_vertex > other.m_vertex) {
        return true;
    } else if (m_vertex == other.m_vertex) {
        return m_edge >= other.m_edge;
    } else {
        return false;
    }
}

template <typename T>
bool Adjacency<T>::operator == (const Adjacency<object_t>& other) const
{
    return m_vertex == other.m_vertex && m_edge == other.m_edge;
}

template <typename T>
bool Adjacency<T>::operator != (const Adjacency<object_t>& other) const
{
    return !(*this == other);
}


