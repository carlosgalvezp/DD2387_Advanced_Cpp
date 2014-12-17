#ifndef VECTOR_H
#define VECTOR_H

#include <cstdlib>
#include <cmath>
#include <iostream>
#include <stdexcept>
#include <iterator>
#include <type_traits>

#define INITIAL_SIZE 10

template <typename T>
class Vector
{       
public:
    typedef T* iterator_t;

    /**
     * @brief Default constructor
     */
    Vector();

    /**
     * @brief Constructor with size
     * @param size
     */
    explicit Vector(const std::size_t size);

    /**
     * @brief Copy-constructor
     * @param src
     */
    Vector(const Vector<T>& src);

    /**
     * @brief Constructor using initializer_list
     * @param src
     */
    explicit Vector(const std::initializer_list<T>& src);

    /**
     * @brief Creates a vector of "size" elements, all with the value of "src"
     * @param size the number of elements
     * @param src the value to be copied to every element
     */
    explicit Vector(const std::size_t size, const T& src);

    /**
     * @brief Move-constructor
     * @param src
     */
    explicit Vector(Vector<T>&& src);

    /**
     * @brief Copy-assignment operator
     * @param src
     * @return
     */
    Vector<T>& operator= (const Vector<T>& src);

    /**
     * @brief Move-assignment operator
     * @param src
     * @return
     */
    Vector<T>& operator= (Vector<T>&& src);

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
    ~Vector();

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

    T* data_;
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
Vector<T>::Vector()
{
    check_type();

    // ** Allocate space
    size_ = 0;
    capacity_ = computeCapacity(size_);
    data_ = new T[capacity_];
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
    data_ = new T[capacity_];

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
Vector<T>::Vector(const Vector<T>& src)
{
    check_type();

    // ** Allocate space
    size_ = src.size();
    capacity_ = src.capacity();
    data_ = new T[capacity_];

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
Vector<T>::Vector(const std::initializer_list<T>& src)
{
    check_type();

    // ** Allocate space
    size_ = src.size();
    capacity_ = computeCapacity(size_);
    data_ = new T[capacity_];

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
Vector<T>::Vector(const std::size_t size, const T& src)
{
    check_type();

    // ** Allocate space
    size_ = size;
    capacity_ = computeCapacity(size_);
    data_ = new T[capacity_];

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
Vector<T>::Vector(Vector<T>&& src)
{
    check_type();

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
        // ** Reallocate space if needed
        if (src.size() > size_)
        {
            delete [] data_;
            data_ = new T[src.size()];
        }
        // ** Copy src resources
        for(std::size_t i = 0; i < src.size(); i++)
        {
            data_[i] = src.data_[i];
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
        delete [] data_;

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
    delete[] data_;
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
        data_[i] = T();
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
        data_[size_] = src;
        size_++;
    }
    else
    {
        // ** Reallocate data
        capacity_ = computeCapacity(capacity_);
        T* newData = new T[capacity_];

        // ** Move data
        for (std::size_t i = 0; i < size_; ++i)
        {
            newData[i] = data_[i];
        }

        // ** Add new element
        newData[size_] = src;
        size_++;

        // ** Delete old data
        delete [] data_;

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
        data_[idx] = src;
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

    // ** Shrink array
    shrink(idx);
}

/**
 * @brief Removes every element, making size == 0
 */
template<typename T>
void Vector<T>::clear()
{
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
typename Vector<T>::iterator_t Vector<T>::begin() const
{
    return data_;
}

/**
 * @brief Iterator to the end of the vector
 * @return
 */
template<typename T>
typename Vector<T>::iterator_t Vector<T>::end() const
{
    return data_ + size_;
}

/**
 * @brief Finds the position of the array where the object src is found
 * @param src
 * @return An iterator to the position, or end() if not found
 */
template<typename T>
typename Vector<T>::iterator_t Vector<T>::find(const T& src) const
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

    if (size_ >= capacity_)
    {
        capacity_ = computeCapacity(capacity_);
        newData = new T[capacity_];
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
        delete[] data_;

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
