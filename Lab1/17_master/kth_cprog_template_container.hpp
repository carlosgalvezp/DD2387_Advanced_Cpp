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
class Vector
{       
public:
    typedef T* iterator;
    typedef const T* const_iterator;

    Vector();
    Vector(const Vector<T>& src);
    explicit Vector(const std::size_t size);
    explicit Vector(const std::initializer_list<T>& src);
    explicit Vector(const std::size_t size, const T& src);
    explicit Vector(Vector<T>&& src);

    Vector<T>& operator= (const Vector<T>& src);
    Vector<T>& operator= (Vector<T>&& src);

    const T& operator[](const std::size_t idx) const;
    T& operator[](const std::size_t idx);

    ~Vector();

    void reset();

    void push_back(const T& src);
    void insert(const std::size_t idx, const T& src);
    void erase(const std::size_t idx);
    void clear();
    std::size_t size() const;
    std::size_t capacity() const;

    iterator begin();
    const_iterator begin() const;

    iterator end();
    const_iterator end() const;

    iterator find(const T& src);
    const_iterator find(const T& src) const;

    void print() const;

private:

    T* data_;
    std::size_t size_;
    std::size_t capacity_;
    std::allocator<T> allocator_; // Allows to allocate memory without constructing objects

    std::size_t computeCapacity(const std::size_t size) const;

    void check_bounds(const std::size_t idx) const;

    void check_type() const;

    void expand(const std::size_t idx);

    void shrink(const std::size_t idx);
};

// ====================================================================
// ====================================================================
// ====================================================================

/**
 * @brief Default constructor
 */
template<typename T>
Vector<T>::Vector()
{
    check_type();

    // ** Allocate space
    size_ = 0;
    capacity_ = computeCapacity(size_);
    data_ = allocator_.allocate(capacity_ * sizeof(T));
}

/**
 * @brief Constructor with size
 * @param size the initial size
 */
template<typename T>
Vector<T>::Vector(const std::size_t size)
{
    check_type();

    // ** Allocate space
    size_ = size;
    capacity_ = computeCapacity(size_);
    data_ = allocator_.allocate(capacity_ * sizeof(T));

    // ** Initialize elements
    for(std::size_t i = 0; i < size_; ++i)
    {
        data_[i] = *(new(data_ + i) T()); // Create new T at the address data_ + i
    }
}

/**
 * @brief Copy-constructor
 * @param src
 */
template<typename T>
Vector<T>::Vector(const Vector<T>& src)
{
    check_type();

    // ** Allocate space
    size_ = src.size();
    capacity_ = src.capacity();
    data_ = allocator_.allocate(capacity_ * sizeof(T));

    // ** Copy elements
    for(std::size_t i = 0; i < size_; ++i)
    {
        data_[i] = *(new(data_ + i) T(src.data_[i]));
    }
}

/**
 * @brief Constructor using initializer_list
 * @param src
 */
template<typename T>
Vector<T>::Vector(const std::initializer_list<T>& src)
{
    check_type();

    // ** Allocate space
    size_ = src.size();
    capacity_ = computeCapacity(size_);
    data_ = allocator_.allocate(capacity_ * sizeof(T));

    // ** Copy elements
    std::size_t i = 0;
    for(auto it = src.begin(); it < src.end(); it++, ++i)
    {
        data_[i] = *(new(data_ + i)T(*it));
    }
}

/**
 * @brief Creates a vector of "size" elements, all with the value of "src"
 * @param size the number of elements
 * @param src the value to be copied to every element
 */
template<typename T>
Vector<T>::Vector(const std::size_t size, const T& src)
{
    check_type();

    // ** Allocate space
    size_ = size;
    capacity_ = computeCapacity(size_);
    data_ = allocator_.allocate(capacity_ * sizeof(T));

    // ** Copy elements
    for(std::size_t i = 0; i < size_; ++i)
    {
        data_[i] = *(new(data_ + i) T(src));
    }
}

/**
 * @brief Move-constructor
 * @param src
 */
template<typename T>
Vector<T>::Vector(Vector<T>&& src)
{
    check_type();

    // ** Release own resources
    for(auto it = begin(); it < end(); ++it)
        it->~T();
    allocator_.deallocate(data_, capacity_);

    // ** Move the data    
    data_ = src.data_;
    size_ = src.size_;
    capacity_ = src.capacity_;

    // ** Remove old references
    src.size_ = 0;
    src.capacity_ = 0;
    src.data_ = nullptr;
}

/**
 * @brief Copy-assignment operator
 * @param src
 * @return
 */
template<typename T>
Vector<T>& Vector<T>::operator= (const Vector<T>& src)
{
    check_type();
    if(&src != this) // Check self-assignment
    {
        // Destroy current elements and free memory
        for(auto it = begin(); it < end(); ++it)
        {
            it->~T();
        }
        allocator_.deallocate(data_, capacity_);

        // ** Recompute capacity if needed
        if (src.size() > capacity_)
        {
            capacity_ = computeCapacity(src.capacity());
        }

        data_ = allocator_.allocate(capacity_ * sizeof(T));
        // ** Copy src resources
        for(std::size_t i = 0; i < src.size(); i++)
        {
            data_[i] = *(new(data_+i)T(src.data_[i]));
        }
        size_ = src.size();
    }
    return *this;
}

/**
 * @brief Move-assignment operator
 * @param src
 * @return
 */
template<typename T>
Vector<T>& Vector<T>::operator= (Vector<T>&& src)
{
    check_type();

    if(&src != this) // Self-assignment check
    {
        // ** Release own resources
        for(auto it = begin(); it < end(); ++it)
            it->~T();
        allocator_.deallocate(data_, capacity_);

        // ** Get src resources
        data_ = src.data_;
        size_ = src.size();
        capacity_ = src.capacity();

        // ** Anulate src resources
        src.data_ = nullptr;
        src.size_ = 0;
        src.capacity_ = 0;
    }
    return *this;
}

/**
 * @brief operator [] (read-only)
 * @param idx
 * @return
 */
template<typename T>
const T& Vector<T>::operator[](const std::size_t idx) const
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
T& Vector<T>::operator[](const std::size_t idx)
{
    check_bounds(idx);
    return data_[idx];
}


/**
 * @brief Default destructor
 */
template<typename T>
Vector<T>::~Vector()
{
    // ** Destruct every element
    for (auto it = begin(); it != end(); ++it)
        it->~T();

    // ** Free memory
    allocator_.deallocate(data_,capacity_);
    size_ = 0;
    capacity_ = 0;
}

/**
 * @brief reset Assigns every element of the vector the value T()
 */
template<typename T>
void Vector<T>::reset()
{
    for(std::size_t i = 0; i < size_; ++i)
    {
        data_[i].~T();
        data_[i] = *(new(data_ + i) T());
    }
}

/**
 * @brief Adds an element at the end of the vector
 * @param src
 */
template<typename T>
void Vector<T>::push_back(const T& src)
{
    // ** Check size
    if (size_ < capacity_) //No need to allocate more memory
    {
        data_[size_] = *(new(data_ + size_)T(src));
        size_++;
    }
    else
    {
        // ** Reallocate data
        std::size_t oldCapacity = capacity_;
        capacity_ = computeCapacity(capacity_);
        T* newData = allocator_.allocate(capacity_ * sizeof(T));

        // ** Move data
        for (std::size_t i = 0; i < size_; ++i)
        {
            newData[i] = std::move(data_[i]);
        }

        // ** Add new element
        newData[size_] = *(new(data_ + size_)T(src));
        size_++;

        // ** Delete old data
        allocator_.deallocate(data_, oldCapacity);

        // ** Reassign data
        data_ = newData;
    }
}

/**
 * @brief Inserts an element before the position given by idx
 * @param idx
 * @param src
 */
template<typename T>
void Vector<T>::insert(const std::size_t idx, const T& src)
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
        data_[idx] = *(new(data_ + idx)T(src));
    }
}

/**
 * @brief Erases the element at the position given by idx
 * @param idx
 */
template<typename T>
void Vector<T>::erase(const std::size_t idx)
{
    // ** Check boundaries
    check_bounds(idx);

    // ** Remove element
    T& x = data_[idx];
    x.~T();

    // ** Shrink array
    shrink(idx);
}

/**
 * @brief Removes every element, making size == 0
 */
template<typename T>
void Vector<T>::clear()
{
    // ** Remove elements
    for (auto it = begin(); it != end(); ++it)
        it->~T();

    size_ = 0;
}


/**
 * @brief The size of the array (number of elements)
 * @return
 */
template<typename T>
std::size_t Vector<T>::size() const
{
    return size_;
}

/**
 * @brief The capacity of the array
 * @return
 */
template<typename T>
std::size_t Vector<T>::capacity() const
{
    return capacity_;
}

/**
 * @brief Iterator to the beginning of the vector
 * @return
 */
template<typename T>
typename Vector<T>::iterator Vector<T>::begin()
{
    return data_;
}

/**
 * @brief Const iterator to the beginning of the vector
 * @return
 */
template<typename T>
typename Vector<T>::const_iterator Vector<T>::begin() const
{
    return data_;
}


/**
 * @brief Iterator to the end of the vector
 * @return
 */
template<typename T>
typename Vector<T>::iterator Vector<T>::end()
{
    return data_ + size_;
}

/**
 * @brief Iterator to the end of the vector
 * @return
 */
template<typename T>
typename Vector<T>::const_iterator Vector<T>::end() const
{
    return data_ + size_;
}

/**
 * @brief Finds the position of the array where the object src is found
 * @param src
 * @return An iterator to the position, or end() if not found
 */
template<typename T>
typename Vector<T>::iterator Vector<T>::find(const T& src)
{
    for (auto it = begin(); it < end(); it++)
    {
        if (*it == src)
            return it;
    }
    return end();
}

/**
 * @brief Finds the position of the array where the object src is found
 * @param src
 * @return An iterator to the position, or end() if not found
 */
template<typename T>
typename Vector<T>::const_iterator Vector<T>::find(const T& src) const
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
void Vector<T>::print() const
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
std::size_t Vector<T>::computeCapacity(const std::size_t size) const
{
    return size != 0? size*2 : INITIAL_SIZE;
}

/**
 * @brief Checks whether idx is a valid index
 * @param idx
 */
template<typename T>
void Vector<T>::check_bounds(const std::size_t idx) const
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
void Vector<T>::check_type() const
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
void Vector<T>::expand(const std::size_t idx)
{
    // ** Allocate more memory if needed
    T* newData;
    bool allocated(false);
    double oldCapacity = capacity_;

    if (size_ >= capacity_)
    {
        capacity_ = computeCapacity(capacity_);
        newData = allocator_.allocate(capacity_ * sizeof(T));
        allocated = true;
    }
    else
        newData = data_;

    // ** Move old to new data
    for (std::size_t i = size_-1 ; i < size_; --i) // When i=0 and we do --i, it will become the max possible value of size_t!
    {
        if(i < idx)
        {
            newData[i] = std::move(data_[i]);
        }
        else
        {
            newData[i+1] = std::move(data_[i]);
        }
    }

    // ** Reassign memory
    if(allocated)
        allocator_.deallocate(data_, oldCapacity);

    data_ = newData;
    size_++;
}

/**
 * @brief Shrinks the array starting from the idx position
 * @param idx
 */
template<typename T>
void Vector<T>::shrink(const std::size_t idx)
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
#endif // VECTOR_H
