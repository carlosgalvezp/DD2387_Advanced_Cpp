#ifndef SAFE_VECTOR_H
#define SAFE_VECTOR_H

#include <cstdlib>
#include <cmath>
#include <iostream>
#include <stdexcept>
#include <iterator>
#include <type_traits>
#include <mutex>
#include <thread>
#include <vector>


#define INITIAL_SIZE 10

template <typename T>
class SafeVector
{
public:
    typedef T* iterator;

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
     * @brief Copy-assignment operator
     * @param src
     * @return
     */
    SafeVector<T>& operator= (const SafeVector<T>& src);

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
    iterator begin() const;

    /**
     * @brief Iterator to the end of the vector
     * @return
     */
    iterator end() const;

    /**
     * @brief Finds the position of the array where the object src is found
     * @param src
     * @return An iterator to the position, or end() if not found
     */
    iterator find(const T& src) const;

    /**
     * @brief Swaps 2 elements, thread-safe. It locks the whole vector
     * @param idx1
     * @param idx2
     */
    void safeswap(std::size_t idx1, std::size_t idx2);

    /**
     * @brief Swaps 2 elements, thread-safe. It only locks the elements
     * @param idx1
     * @param idx2
     */
    void safeswap2(std::size_t idx1, std::size_t idx2);

    /**
     * @brief Prints the vector contents
     */
    void print() const;

private:

    T* data_;
    std::size_t size_;
    std::size_t capacity_;
    std::mutex mutex_; // The problem is that mutexes are NOT movable, so the class becomes not-movable
    std::mutex* mutexes_; // Array of mutex for individual lock

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
    capacity_ = computeCapacity(size_);
    data_ = new T[capacity_];
    mutexes_ = new std::mutex[size_];
}

/**
 * @brief Constructor with size
 * @param size the initial size
 */
template<typename T>
SafeVector<T>::SafeVector(const std::size_t size)
{
    check_type();

    // ** Allocate space
    size_ = size;
    capacity_ = computeCapacity(size_);
    data_ = new T[capacity_];

    std::cout << "Initializing elements..."<<std::endl;

    // ** Initialize elements
    for(std::size_t i = 0; i < size_; ++i)
    {
        std::cout << i << std::endl;
        data_[i] = T();
    }
    mutexes_ = new std::mutex[size_];
}

/**
 * @brief Copy-constructor
 * @param src
 */
template<typename T>
SafeVector<T>::SafeVector(const SafeVector<T>& src)
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
    mutexes_ = new std::mutex[size_];
}

/**
 * @brief Constructor using initializer_list
 * @param src
 */
template<typename T>
SafeVector<T>::SafeVector(const std::initializer_list<T>& src)
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
    mutexes_ = new std::mutex[size_];
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

    // ** Allocate space
    size_ = size;
    capacity_ = computeCapacity(size_);
    data_ = new T[capacity_];

    // ** Copy elements
    for(std::size_t i = 0; i < size_; ++i)
    {
        data_[i] = src;
    }
    mutexes_ = new std::mutex[size_];
}

/**
 * @brief Move-constructor
 * @param src
 */
template<typename T>
SafeVector<T>::SafeVector(SafeVector<T>&& src)
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
SafeVector<T>& SafeVector<T>::operator= (const SafeVector<T>& src)
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
SafeVector<T>& SafeVector<T>::operator= (SafeVector<T>&& src)
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
    delete[] data_;
    delete[] mutexes_;
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
        data_[i] = T();
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
typename SafeVector<T>::iterator SafeVector<T>::begin() const
{
    return data_;
}

/**
 * @brief Iterator to the end of the vector
 * @return
 */
template<typename T>
typename SafeVector<T>::iterator SafeVector<T>::end() const
{
    return data_ + size_;
}

/**
 * @brief Finds the position of the array where the object src is found
 * @param src
 * @return An iterator to the position, or end() if not found
 */
template<typename T>
typename SafeVector<T>::iterator SafeVector<T>::find(const T& src) const
{
    for (auto it = begin(); it < end(); it++)
    {
        if (*it == src)
            return it;
    }
    return end();
}

/* This operation is much safer: other threads can't operate on the data
 * until the current thread has finished.
 * However, it will be slower: one could think of speeding the swap process
 * by having several threads swapping different positions of the vector.
 * This is not possible with this approach.
 **/
template<typename T>
void SafeVector<T>::safeswap(std::size_t idx1, std::size_t idx2)
{
    std::lock_guard<std::mutex> locker(mutex_); // Unlocks when the object is destroyed => no dead-locks if exception happens
    std::cout << "["<< std::this_thread::get_id() << "] Swapping " << idx1 << " and " << idx2 << "..."<<std::endl;
    check_bounds(idx1); check_bounds(idx2);

    T tmp = data_[idx1]; // Create a temporal copy
    data_[idx1] = std::move(data_[idx2]);
    data_[idx2] = std::move(tmp); // Don't need tmp => std::move
    std::cout << "["<< std::this_thread::get_id() << "] Finished swapping" << std::endl;
}

/*
 * This operation allows for multiple swapping at the same time, given that
 * the positions are different for every thread.
 *
 * This however poses a big deadlock problem, contrary to the previous approach,
 * which is deadlock-free. Say that a thread wants to swap 2 and 3 and other
 * thread will swap 3 and 2. They will acquire positions 2 and 3 in the first place.
 * However, when they need to acquire positions 3 and 2 respectively, these will
 * be already locked by the other thread. Therefore we have a deadlock.
 * */
template<typename T>
void SafeVector<T>::safeswap2(std::size_t idx1, std::size_t idx2)
{
    using std::swap;
    if(idx1 < idx2)
        swap(idx1,idx2);

    std::cout << "["<< std::this_thread::get_id() << "] Swapping " << idx1 << " and " << idx2 << "..."<<std::endl;
    check_bounds(idx1); check_bounds(idx2);

    std::lock_guard<std::mutex> locker1(mutexes_[idx1]);// Lock first element (no one can write while I read it)
    T tmp = data_[idx1];

    std::lock_guard<std::mutex> locker2(mutexes_[idx2]);// Lock first element (no one can write while I read it)
    data_[idx1] = std::move(data_[idx2]);
    data_[idx2] = std::move(tmp); // Don't need tmp => std::move
    std::cout << "["<< std::this_thread::get_id() << "] Finished swapping" << std::endl;
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
#endif // VECTOR_H
