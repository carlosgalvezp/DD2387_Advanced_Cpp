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
    explicit Hypercube(unsigned int m)    {data_ = Vector<Hypercube<n-1>>(m, Hypercube<n-1>(m)); }

          Hypercube<n-1>& operator[](std::size_t idx)       {  return data_[idx];  }
    const Hypercube<n-1>& operator[](std::size_t idx) const {  return data_[idx];  }

private:
    Vector<Hypercube<n-1>> data_; // Recursive inheritance
};

template <>             // Specialization
class Hypercube<1>      // Base case: n = 1
{
public:
    Hypercube(){}
    explicit Hypercube(unsigned int m)    {        data_ = Vector<int>(m);    }

          int& operator[](std::size_t idx)          {        return data_[idx];    }
    const int& operator[](std::size_t idx) const    {        return data_[idx];    }

private:
    Vector<int> data_;
};
#endif // HYPERCUBE_H
