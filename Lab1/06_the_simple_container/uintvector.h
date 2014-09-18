#ifndef UINTVECTOR_H
#define UINTVECTOR_H

#include <cstdlib>
#include <stdexcept>
#include <string>
#include <iostream>
#include <initializer_list>

class UIntVector
{
public:

    /**
     * @brief Default constructor
     */
    UIntVector();

    /**
     * @brief Other constructor. It creates a vector of
     * "size" zero-initialized elements
     * @param size the initial size of the array
     */
    explicit UIntVector(const std::size_t size);

    /**
     * @brief Copy-constructor
     * @param src
     */
    UIntVector(const UIntVector& src);

    /**
     * @brief Constructor using initializer_list
     * @param src
     */
    explicit UIntVector(const std::initializer_list<unsigned int>& src);

    /**
     * @brief Move-constructor
     * @param src
     */
    explicit UIntVector(UIntVector&& src);


    /**
     * @brief Copy-assignment operator
     * @param src
     * @return
     */
    UIntVector& operator= (const UIntVector& src);

    /**
     * @brief Move-assignment operator
     * @param src
     * @return
     */
    UIntVector& operator= (UIntVector&& src);


    /**
     * @brief Default destructor
     */
    ~UIntVector();

    /**
     * @brief size
     * @return the size of the vector
     */
    std::size_t size() const;

    /**
     * @brief operator []
     * @param idx
     * @return a copy of the value at position idx
     * @throw std:out_of_range if idx not valid
     */
    unsigned int operator[](const std::size_t idx) const;

    /**
     * @brief operator []
     * @param idx
     * @return the reference to the idx-th component of the vector
     * @throw std:out_of_range if idx not valid
     */
    unsigned int& operator[](const std::size_t idx);

    /**
     * @brief resets all the elements of the vector to 0
     */
    void reset();


private:

    /**
     * @brief The array containing the data
     */
    unsigned int* data_;

    /**
     * @brief The current size of the vector
     */
    std::size_t size_;

    /**
     * @brief checks whether idx is a valid position of the array (starting at 0)
     * @param idx
     * @throw std::out_of_range if idx not valid
     */
    void check_inside(const std::size_t idx) const;
};

#endif // UINTVECTOR_H
