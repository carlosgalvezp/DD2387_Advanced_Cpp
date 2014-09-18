#ifndef VECTOR_H
#define VECTOR_H

#include <cstdlib>
#include <cmath>
#include <iostream>
#include <stdexcept>
#include <iterator>
#include <type_traits>

#define SIZE_INCREMENT 10   //Initial size and increment of the array

template <class T>
class Vector
{       
public:
    typedef T* unspecified;
    /**
     * @brief Default constructor
     */
    Vector()
    {
        check_type();

        std::cout << "Default constructor" << std::endl;
        capacity_ = SIZE_INCREMENT;
        data_ = new T[capacity_];
        size_ = 0;
    }

    /**
     * @brief Constructor with size
     * @param size the initial size
     */
    explicit Vector(const std::size_t size)
    {
        check_type();

        // ** Allocate space
        capacity_ = computeCapacity(size);
        data_ = new T[capacity_];
        size_ = size;

        // ** Initialize elements
        for(std::size_t i = 0; i < size; i++)
        {
            data_[i] = T();
        }
    }

    /**
     * @brief Copy-constructor
     * @param src
     */
    Vector(const Vector<T>& src)
    {
        check_type();

        std::cout<<"Copy constructor"<<std::endl;

        // ** Allocate space
        capacity_ = src.capacity();
        size_ = src.size();
        data_ = new T[capacity()];

        // ** Copy elements
        for(std::size_t i = 0; i < size_; i++)
        {
            data_[i] = src.data_[i];
        }
    }

    /**
     * @brief Constructor using initializer_list
     * @param src
     */
    explicit Vector(const std::initializer_list<T>& src)
    {
        check_type();

        // ** Allocate space
        data_ = new T[src.size()];
        size_ = src.size();

        // ** Copy elements
        std::size_t i = 0;
        for(auto it = src.begin(); it != src.end(); it++, i++)
        {
            data_[i] = *it;
        }
    }

    /**
     * @brief Creates a vector of "size" elements, all with the value of "src"
     * @param size the number of elements
     * @param src the value to be copied to every element
     */
    explicit Vector(const std::size_t size, const T& src)
    {
        check_type();

        // ** Allocate space
        capacity_ = computeCapacity(size);
        size_ = size;
        data_ = new T[capacity_];

        // ** Copy elements
        for(std::size_t i = 0; i < size_; i++)
        {
            data_[i] = src;
        }
    }

    /**
     * @brief Move-constructor
     * @param src
     */
    explicit Vector(Vector<T>&& src)
    {
        check_type();

        // ** Move the data
        data_ = std::move(src.data_);
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
    Vector<T>& operator= (const Vector<T>& src)
    {
        check_type();

        if(&src != this) // Check self-assignment
        {
            // ** Rellocate space
            capacity_ = src.capacity();
            size_ = src.size();
            T* newData = new T[src.capacity()];

            // ** Get sec resources
            for(std::size_t i = 0; i < size_; i++)
            {
                newData[i] = src.data_[i];
            }

            // ** Anulate src resources
            delete [] data_;
            data_ = newData;
        }
        return *this;
    }

    /**
     * @brief Move-assignment operator
     * @param src
     * @return
     */
    Vector<T>& operator= (Vector<T>&& src)
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
    T operator[](const std::size_t idx) const
    {
        check_inside(idx);
        return data_[idx];
    }

    /**
     * @brief operator [] (read/write)
     * @param idx
     * @return
     */
    T& operator[](const std::size_t idx)
    {
        check_inside(idx);
        return data_[idx];
    }


    /**
     * @brief Default destructor
     */
    ~Vector()
    {
        std::cout << "Default destructor" << std::endl;
        delete[] data_;
        size_ = 0;
        capacity_ = 0;
    }

    /**
     * @brief Adds an element at the end of the vector
     * @param src
     */
    void push_back(const T& src)
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
            capacity_ += SIZE_INCREMENT;
            T* newData = new T[capacity_];

            // ** Copy data
            for (std::size_t i = 0; i < size_; i++)
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
    void insert(const std::size_t idx, const T& src)
    {
        if(idx == size_)
            push_back(src);
        else
        {
            // ** Check boundaries
            check_inside(idx);

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
    void erase(const std::size_t idx)
    {
        // ** Check boundaries
        check_inside(idx);

        // ** Remove the element
        delete &data_[idx];

        // ** Shrink array
        shrink(idx);
    }

    /**
     * @brief Removes every element, making size == 0
     */
    void clear()
    {
        delete [] data_;
        size_ = 0;
        capacity_ = 0;
    }


    /**
     * @brief The size of the array (number of elements)
     * @return
     */
    std::size_t size() const
    {
        return size_;
    }

    /**
     * @brief The capacity of the array
     * @return
     */
    std::size_t capacity() const
    {
        return capacity_;
    }

    /**
     * @brief Iterator to the beginning of the vector
     * @return
     */
    unspecified begin() const
    {
        return data_;
    }

    /**
     * @brief Iterator to the end of the vector
     * @return
     */
    unspecified end() const
    {
        return data_ + size_;
    }

    /**
     * @brief Finds the position of the array where the object src is found
     * @param src
     * @return An iterator to the position, or end() if not found
     */
    unspecified find(const T& src)
    {
        for (auto it = begin(); it != end(); it++)
        {
            if (*it == src)
                return it;
        }
        return end();
    }

    /**
     * @brief Prints the vector contents
     */
    void print() const
    {
        for(std::size_t i = 0; i < size_; i++)
        {
            std::cout << data_[i] <<" ";
        }
        std::cout << std::endl;
    }

private:

    T* data_;
    std::size_t size_;
    std::size_t capacity_;

    /**
     * @brief Computes the capacity of the array, as the smallest multiple
     * of SIZE_INCREMENT that is greater than size
     * @param size
     * @return
     */
    std::size_t computeCapacity(const std::size_t size)
    {
        return (std::floor(size/SIZE_INCREMENT) + 1) * SIZE_INCREMENT;
    }

    /**
     * @brief Checks whether idx is a valid index
     * @param idx
     */
    void check_inside(const std::size_t idx) const
    {
        if(idx < 0 || idx > size_ ){
            throw std::out_of_range("Index out of bounds!");
        }
    }

    /**
     * @brief Checks whether the type T is both Move-Construtible and Move-Assignable
     */
    void check_type()
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
    void expand(const std::size_t idx)
    {
        // ** Allocate
        capacity_ = computeCapacity(size_+1);
        T* newData = new T[capacity_];

        // ** Copy data
        for (std::size_t i = 0; i < size_; i++)
        {
            if(i < idx)
                newData[i] = data_[i];
            else
                newData[i+1] = data_[i];
        }

        // ** Reassign memory
        delete[] data_;
        data_ = newData;
        size_++;
    }

    /**
     * @brief Shrinks the array starting from the idx position
     * @param idx
     */
    void shrink(const std::size_t idx)
    {
        // ** Allocate
        capacity_ = computeCapacity(size_-1);
        T* newData = new T[capacity_];

        // ** Copy data
        for (std::size_t i = 0; i < size_-1; i++)
        {
            if(i < idx)
                newData[i] = data_[i];
            else
                newData[i] = data_[i+1];
        }

        // ** Reassign memory
        delete[] data_;
        data_ = newData;
        size_--;
    }

};

#endif // VECTOR_H
