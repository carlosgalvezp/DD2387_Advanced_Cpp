#ifndef HYPERCUBE_H
#define HYPERCUBE_H

#include <cstdlib>
#include <cmath>
#include <iostream>
#include <stdexcept>
#include <iterator>
#include <type_traits>

#include "../07_the_template_vector/kth_cprog_template_container.hpp"

template <unsigned int n>
class Hypercube
{
public:
    Hypercube(){}

    Hypercube(unsigned int m)
    {
        data = Vector<Hypercube<n-1>>(m, Hypercube<n-1>(m));
    }

    Hypercube<n-1>& operator[](std::size_t idx)
    {
        return data[idx];
    }

private:
    Vector<Hypercube<n-1>> data;
};

template <>
class Hypercube<1>
{
public:
    Hypercube(){}
    Hypercube(unsigned int m)
    {
        data = Vector<int>(m);
    }

    int& operator[](std::size_t idx)
    {
        return data[idx];
    }

private:
    Vector<int> data;
};


// ============================================================
// ============================================================

#endif // HYPERCUBE_H
