#ifndef VECTOR_H
#define VECTOR_H

#include <cstdlib>
#include <cmath>
#include <iostream>
#include <stdexcept>
#include <iterator>
#include <type_traits>
#include <memory>

#define INITIAL_SIZE 10

template <typename T>
class SafeVector
{
    typedef typename std::unique_ptr<T[]> SmartPtr;

    template<typename S>
    friend void swap(SafeVector<S> &&v1, SafeVector<S> &&v2);

public:
    typedef T* iterator_t;

    /**
     * @brief Default constructor
     */
    SafeVector();

    /**
     * @brief Constructor with size
     * @param size
     */
    explicit SafeVector(const std::size_t size);

    /**
     * @brief Copy-constructor
     * @param src
     */
    SafeVector(const SafeVector<T>& src);

    /**
     * @brief Constructor using initializer_list
     * @param src
     */
    explicit SafeVector(const std::initializer_list<T>& src);

    /**
     * @brief Creates a vector of "size" elements, all with the value of "src"
     * @param size the number of elements
     * @param src the value to be copied to every element
     */
    explicit SafeVector(const std::size_t size, const T& src);

    /**
     * @brief Move-constructor
     * @param src
     */
    explicit SafeVector(SafeVector<T>&& src);

    /**
     * @brief Copy-assignment operator, using copy-and-swap idiom
     * @param src
     * @return
     */
    SafeVector<T>& operator= (SafeVector<T> src);

    /**
     * @brief Move-assignment operator
     * @param src
     * @return
     */
    SafeVector<T>& operator= (SafeVector<T>&& src);

    /**
     * @brief operator [] (read-only)
     * @param idx
     * @return
     */
    const T& operator[](const std::size_t idx) const;

    /**
     * @brief operator [] (read/write)
     * @param idx
     * @return
     */
    T& operator[](const std::size_t idx);

    /**
     * @brief Default destructor
     */
    ~SafeVector();

    /**
     * @brief reset Assigns every element of the vector the value T()
     */
    void reset();

    /**
     * @brief Adds an element at the end of the vector
     * @param src
     */
    void push_back(const T& src);

    /**
     * @brief Inserts an element before the position given by idx
     * @param idx
     * @param src
     */
    void insert(const std::size_t idx, const T& src);

    /**
     * @brief Erases the element at the position given by idx
     * @param idx
     */
    void erase(const std::size_t idx);

    /**
     * @brief Removes every element, making size == 0
     */
    void clear();

    /**
     * @brief The size of the array (number of elements)
     * @return
     */
    std::size_t size() const;

    /**
     * @brief The capacity of the array
     * @return
     */
    std::size_t capacity() const;

    /**
     * @brief Iterator to the beginning of the vector
     * @return
     */
    iterator_t begin() const;

    /**
     * @brief Iterator to the end of the vector
     * @return
     */
    iterator_t end() const;

    /**
     * @brief Finds the position of the array where the object src is found
     * @param src
     * @return An iterator to the position, or end() if not found
     */
    iterator_t find(const T& src) const;

    /**
     * @brief Prints the vector contents
     */
    void print() const;

private:

    SmartPtr data_;
    std::size_t size_;
    std::size_t capacity_;

    /**
     * @brief Computes the capacity of the array, as twice the size
     * @param size
     * @return
     */
    std::size_t computeCapacity(const std::size_t size) const;

    /**
     * @brief Checks whether idx is a valid index
     * @param idx
     */
    void check_bounds(const std::size_t idx) const;

    /**
     * @brief Checks whether the type T is both Move-Construtible and Move-Assignable
     */
    void check_type() const;

    /**
     * @brief Increases the array size and copies the content after idx
     * @param idx
     */
    void expand(const std::size_t idx);

    /**
     * @brief Shrinks the array starting from the idx position
     * @param idx
     */
    void shrink(const std::size_t idx);
};

// ====================================================================
// ====================================================================
// ====================================================================

/**
 * @brief Default constructor
 */
template<typename T>
SafeVector<T>::SafeVector()
{
    check_type();

    // ** Allocate space
    size_ = 0;
    capacity_ = 0;
    data_ = nullptr; // Needed for move-constructor
}

/**
 * @brief Constructor with size
 * @param size the initial size
 */
template<typename T>
SafeVector<T>::SafeVector(const std::size_t size)
{
    check_type();

    // ** First of all, try to allocate space
    std::size_t newCapacity = computeCapacity(size);
    data_ = SmartPtr(new T[newCapacity]);                       // Possible exception

    // ** Update next fields
    size_ = size;
    capacity_ = newCapacity;

    // ** Initialize elements
    for(std::size_t i = 0; i < size_; ++i)
    {
        data_[i] = T();
    }
}

/**
 * @brief Copy-constructor
 * @param src
 */
template<typename T>
SafeVector<T>::SafeVector(const SafeVector<T>& src)
{
    check_type();

    // ** First of all, try to allocate space
    data_ = SmartPtr(new T[src.capacity()]);                    // Possible exception

    // ** Update next fields
    size_ = src.size();
    capacity_ = src.capacity();

    // ** Copy elements
    for(std::size_t i = 0; i < size_; ++i)
    {
        data_[i] = src.data_[i];
    }
}

/**
 * @brief Constructor using initializer_list
 * @param src
 */
template<typename T>
SafeVector<T>::SafeVector(const std::initializer_list<T>& src)
{
    check_type();

    // ** First of all, try to allocate space
    std::size_t newCapacity = computeCapacity(src.size());
    data_ = SmartPtr(new T[newCapacity]);                      // Possible exception

    // ** Update next fields
    size_ = src.size();
    capacity_ = newCapacity;

    // ** Copy elements
    std::size_t i = 0;
    for(auto it = src.begin(); it < src.end(); it++, ++i)
    {
        data_[i] = *it;
    }
}

/**
 * @brief Creates a vector of "size" elements, all with the value of "src"
 * @param size the number of elements
 * @param src the value to be copied to every element
 */
template<typename T>
SafeVector<T>::SafeVector(const std::size_t size, const T& src)
{
    check_type();

    // ** First of all, try to allocate space
    std::size_t newCapacity = computeCapacity(size);
    data_ = SmartPtr(new T[newCapacity]);                      // Possible exception

    // ** Update next fields
    size_ = size;
    capacity_ = newCapacity;

    // ** Copy elements
    for(std::size_t i = 0; i < size_; ++i)
    {
        data_[i] = src;
    }
}

/**
 * @brief Move-constructor
 * @param src
 */
template<typename T>
SafeVector<T>::SafeVector(SafeVector<T>&& src)
    : SafeVector<T>() // Create something valid to be destroyed afterwards
{
    check_type();
    swap(*this, src);
}

/**
 * @brief Copy-assignment operator, using copy-and-swap idiom
 * @param src
 * @return
 */
template<typename T>
SafeVector<T>& SafeVector<T>::operator= (SafeVector<T> src)
{
    check_type();
    swap(*this, src);
    return *this;
}

/**
 * @brief Move-assignment operator, using copy-and-swap idiom
 * @param src
 * @return
 */
template<typename T>
SafeVector<T>& SafeVector<T>::operator= (SafeVector<T>&& src)
{
    check_type();

    data_ = nullptr; // To be deleted
    swap(*this, src);
    return *this;
}

/**
 * @brief operator [] (read-only)
 * @param idx
 * @return
 */
template<typename T>
const T& SafeVector<T>::operator[](const std::size_t idx) const
{
    check_bounds(idx);
    return data_[idx];
}

/**
 * @brief operator [] (read/write)
 * @param idx
 * @return
 */
template<typename T>
T& SafeVector<T>::operator[](const std::size_t idx)
{
    check_bounds(idx);
    return data_[idx];
}


/**
 * @brief Default destructor
 */
template<typename T>
SafeVector<T>::~SafeVector()
{
//    delete[] data_; // Already taken care of by the smart pointer
    size_ = 0;
    capacity_ = 0;
}

/**
 * @brief reset Assigns every element of the vector the value T()
 */
template<typename T>
void SafeVector<T>::reset()
{
    for(std::size_t i = 0; i < size_; ++i)
    {
        data_[i] = T();
    }
}

/**
 * @brief Adds an element at the end of the vector
 * @param src
 */
template<typename T>
void SafeVector<T>::push_back(const T& src)
{
    // ** Check size
    if (size_ < capacity_) //No need to allocate more memory
    {
        data_[size_] = src;
        size_++;
    }
    else
    {
        // ** First, try to reallocate data
        std::size_t newCapacity = computeCapacity(capacity_);
        std::unique_ptr<T[]> newData(new T[newCapacity]);           // Possible exception

        // Update other variables
        capacity_ = newCapacity;

        // ** Move data
        for (std::size_t i = 0; i < size_; ++i)
        {
            newData[i] = data_[i];
        }

        // ** Add new element
        newData[size_] = src;
        size_++;

        // ** Reassign data
        std::swap(this->data_, newData);
    }
}

/**
 * @brief Inserts an element before the position given by idx
 * @param idx
 * @param src
 */
template<typename T>
void SafeVector<T>::insert(const std::size_t idx, const T& src)
{
    if(idx == size_)
        push_back(src);
    else
    {
        // ** Check boundaries
        check_bounds(idx);

        // ** Expand array to make room for src
        expand(idx);

        // ** Put the element
        data_[idx] = src;
    }
}

/**
 * @brief Erases the element at the position given by idx
 * @param idx
 */
template<typename T>
void SafeVector<T>::erase(const std::size_t idx)
{
    // ** Check boundaries
    check_bounds(idx);

    // ** Shrink array
    shrink(idx);
}

/**
 * @brief Removes every element, making size == 0
 */
template<typename T>
void SafeVector<T>::clear()
{
    size_ = 0;
}


/**
 * @brief The size of the array (number of elements)
 * @return
 */
template<typename T>
std::size_t SafeVector<T>::size() const
{
    return size_;
}

/**
 * @brief The capacity of the array
 * @return
 */
template<typename T>
std::size_t SafeVector<T>::capacity() const
{
    return capacity_;
}

/**
 * @brief Iterator to the beginning of the vector
 * @return
 */
template<typename T>
typename SafeVector<T>::iterator_t SafeVector<T>::begin() const
{
    return data_;
}

/**
 * @brief Iterator to the end of the vector
 * @return
 */
template<typename T>
typename SafeVector<T>::iterator_t SafeVector<T>::end() const
{
    return data_ + size_;
}

/**
 * @brief Finds the position of the array where the object src is found
 * @param src
 * @return An iterator to the position, or end() if not found
 */
template<typename T>
typename SafeVector<T>::iterator_t SafeVector<T>::find(const T& src) const
{
    for (auto it = begin(); it < end(); it++)
    {
        if (*it == src)
            return it;
    }
    return end();
}

/**
 * @brief Prints the vector contents
 */
template<typename T>
void SafeVector<T>::print() const
{
    for(std::size_t i = 0; i < size_; ++i)
    {
        std::cout << data_[i] <<" ";
    }
    std::cout << "|| S: "<< size_ << " C: " << capacity_ << std::endl;
}

/**
 * @brief Computes the capacity of the array, as twice the size
 * @param size
 * @return
 */
template<typename T>
std::size_t SafeVector<T>::computeCapacity(const std::size_t size) const
{
    return size != 0? size*2 : INITIAL_SIZE;
}

/**
 * @brief Checks whether idx is a valid index
 * @param idx
 */
template<typename T>
void SafeVector<T>::check_bounds(const std::size_t idx) const
{
    if(idx < 0 || idx >= size_ )
    {
        throw std::out_of_range("Index out of bounds!");
    }
}

/**
 * @brief Checks whether the type T is both Move-Construtible and Move-Assignable
 */
template<typename T>
void SafeVector<T>::check_type() const
{
    static_assert(std::is_move_constructible<T>::value,
                  "The input type is not move-constructible!");
    static_assert(std::is_move_assignable<T>::value,
                  "The input type is not move-assignable!");
}

/**
 * @brief Increases the array size and copies the content after idx
 * @param idx
 */
template<typename T>
void SafeVector<T>::expand(const std::size_t idx)
{
    // ** Allocate more memory if needed
    std::unique_ptr<T[]> newData;
    bool allocated (false);

    if (size_ >= capacity_)
    {
        // ** Try to allocate new data
        std::size_t newCapacity = computeCapacity(capacity_);
        newData = std::unique_ptr<T[]>(new T[newCapacity]);     // Possible exception

        // Update other variables
        capacity_ = newCapacity;
        allocated = true;
    }    
    // ** Move old to new data
    for (std::size_t i = size_-1 ; i < size_; --i) // When i=0 and we do --i, it will become the max possible value of size_t!
    {
        if(i < idx)
        {
            if(allocated)
                newData[i] = std::move(data_[i]);
        }
        else
        {
            if(allocated)
                newData[i+1] = std::move(data_[i]);
            else
                data_[i+1] = std::move(data_[i]);
        }
    }

    // ** Reassign memory
    if(allocated)
        std::swap(data_, newData);

    size_++;
}

/**
 * @brief Shrinks the array starting from the idx position
 * @param idx
 */
template<typename T>
void SafeVector<T>::shrink(const std::size_t idx)
{
    // ** Move data
    for (std::size_t i = 0; i < size_-1; ++i)
    {
        if(i < idx)
            data_[i] = std::move(data_[i]);
        else
            data_[i] = std::move(data_[i+1]);
    }
    size_--;
}

template<typename T>
void swap(SafeVector<T> &v1, SafeVector<T> &v2)
{
    using std::swap;

    swap(v1.data_, v2.data_);
    swap(v1.size_, v2.size_);
    swap(v1.capacity_, v2.capacity_);
}

#endif // VECTOR_H
