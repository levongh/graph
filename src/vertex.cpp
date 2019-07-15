#include <iostream>

#include "vertex.h"

int Vertex::internalCost() const
{
    unsigned result = 0;
    for (const auto& elem : m_adj) {
        if (elem.second->getLabel() == getLabel()) {
            result += elem.first;
        }
    }
    return result;
}

int Vertex::externalCost() const
{
    unsigned result = 0;
    for (const auto& elem : m_adj) {
        if (elem.second->getLabel() != getLabel()) {
            result += elem.first;
        }
    }
    return result;
}

int Vertex::moveCost() const
{
    return externalCost() - internalCost();
}

void Vertex::print() const
{
    std::cout <<  m_name <<' ';
    for (const auto& iter : m_adj) {
        std::cout << iter.first << " " << iter.second->m_name << "   ";
    }
    std::cout << std::endl;
}

