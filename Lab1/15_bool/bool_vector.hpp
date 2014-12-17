#ifndef VECTOR_BOOL_H
#define VECTOR_BOOL_H

#include <cstdlib>
#include <cmath>
#include <iostream>
#include <stdexcept>
#include <iterator>
#include <type_traits>
#include <cstddef>
#include "../07_the_template_vector/kth_cprog_template_container.hpp"

#include <iterator>

typedef unsigned int storage_type;

template<> // Template class specialization
class Vector<bool>
{
public:
    typedef bool value_type;
    template<bool is_const> class iterator_;

// =============================================================================
// =============================================================================

    template<bool is_const>
    class reference_
    {
        friend class iterator_<true>;
        friend class iterator_<false>;

        public:
            typedef typename std::conditional<is_const, const Vector<bool>*,
                                                              Vector<bool>*>::type ref_data_type;

            explicit reference_(ref_data_type ptr, std::size_t idx)
            {
                ptr_ = ptr;
                idx_ = idx;
                update(idx_);
            }

            reference_(const reference_& src) //Allows from implicit conversion non-const to const
            {
                ptr_    = src.ptr_;
                mask_   = src.mask_;
                idx_    = src.idx_;
                n_elem_ = src.n_elem_;
            }

            ~reference_()
            {
                ptr_ = nullptr;
                idx_ = mask_ = n_elem_ = 0;
            }

            operator bool() const                               // Implicit conversion from reference_ to bool
            {
                return ptr_->data_[n_elem_] & mask_;
            }

            reference_<false>& operator=(bool x)                // This can only be done with non-const ref
            {
                if(x)   ptr_->data_[n_elem_] |=   mask_;
                else    ptr_->data_[n_elem_] &=  ~mask_;
                return *this;
            }

            reference_<false>& operator=(const reference_& src) // This can only be done with non-const ref
            {
                if(src) ptr_->data_[n_elem_] |=   mask_;
                else    ptr_->data_[n_elem_] &=  ~mask_;
                return *this;
            }

            bool operator==(const reference_& src) const
            {
                return ptr_ == src.ptr_ && idx_ == src.idx_;
            }

        private:
            ref_data_type ptr_;
            std::size_t idx_;
            storage_type mask_;
            std::size_t n_elem_;

            void update(std::size_t idx)
            {
                // ** Compute mask and n_element
                n_elem_ = idx_/sizeof(storage_type);
                std::size_t position = idx % sizeof(storage_type);
                mask_ = 1 << position;
            }
        };
    typedef reference_<true> const_reference;
    typedef reference_<false>      reference;

// =============================================================================
// =============================================================================

    template<bool is_const>
    class iterator_ : std::iterator<std::random_access_iterator_tag, bool>
    {
    public:
        friend class iterator_<!is_const>; // For implicit conversion non-const to const

        typedef typename std::conditional<is_const, Vector<bool>::const_reference,
                                                    Vector<bool>::reference>::type reference_type;
        // ** Iterator traits
        typedef bool                                value_type;
        typedef std::random_access_iterator_tag     iterator_category;
        typedef std::ptrdiff_t                      difference_type;
        typedef reference_type                      reference;
        typedef void*                               pointer;

        iterator_(){}

        iterator_(const reference_type& ref)
            : ref_(ref){}

        iterator_(const iterator_& src)
            : ref_(src.ref_){}

        bool operator== (const iterator_& other) const
        {
            return ref_ == other.ref_;
        }

        bool operator!= (const iterator_& other) const
        {
            return !(*this == other);
        }

//        iterator_& operator++()
        iterator_ operator++()
        {
            ref_.idx_++;
            ref_.update(ref_.idx_);
            return *this;
        }

//        iterator_& operator--()
        iterator_ operator--()
        {
            ref_.idx_--;
            ref_.update(ref_.idx_);
            return *this;
        }

        iterator_ operator++(int)
        {
            iterator_ tmp(*this);
            ++(*this);
            return tmp;
        }

        bool operator< (const iterator_& src)   const {  return ref_.idx_ <  src.ref_.idx_;}
        bool operator> (const iterator_& src)   const {  return ref_.idx_ >  src.ref_.idx_;}
        bool operator<=(const iterator_& src)   const {  return ref_.idx_ <= src.ref_.idx_;}
        bool operator>=(const iterator_& src)   const {  return ref_.idx_ >= src.ref_.idx_;}

        reference_type& operator*()                   {  return ref_;}

        iterator_ operator-(const std::size_t size)
        {
            ref_.idx_ -= size;
            ref_.update(ref_.idx_);
            return *this;
        }

        difference_type operator-(const iterator_& src)
        {
            return ref_.idx_ - src.ref_.idx_;
        }

        iterator_ operator-(const std::size_t size)  const
        {
            iterator_ tmp(*this);
            tmp.ref_.idx_ -= size;
            tmp.ref_.update(tmp.ref_.idx_);
            return tmp;
        }

        iterator_& operator-=(const std::size_t size)
        {
            ref_.idx_ -= size;
            ref_.update(ref_.idx_);
            return *this;
        }

        iterator_ operator+(const std::size_t size)
        {
            iterator_ tmp(*this);
            tmp.ref_.idx_ += size;
            tmp.ref_.update(tmp.ref_.idx_);
            return tmp;
        }

        iterator_& operator+=(const std::size_t size)
        {
            ref_.idx_ += size;
            ref_.update(ref_.idx_);
            return *this;
        }

        reference_type operator[](const std::size_t idx)
        {
            return *(*this + idx);
        }

    private:
        reference_type ref_;
    };

// =============================================================================
// =============================================================================

    typedef iterator_<true>  const_iterator;
    typedef iterator_<false>       iterator;

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
    Vector(const Vector<bool>& src);

    /**
     * @brief Constructor using initializer_list
     * @param src
     */
    explicit Vector(const std::initializer_list<bool>& src);

    /**
     * @brief Creates a vector of "size" elements, all with the value of "src"
     * @param size the number of elements
     * @param src the value to be copied to every element
     */
    explicit Vector(const std::size_t size, const bool& src);

    /**
     * @brief Move-constructor
     * @param src
     */
    explicit Vector(Vector<bool>&& src);

    /**
     * @brief Copy-assignment operator
     * @param src
     * @return
     */
    Vector<bool>& operator= (const Vector<bool>& src);

    /**
     * @brief Move-assignment operator
     * @param src
     * @return
     */
    Vector<bool>& operator= (Vector<bool>&& src);

    /**
     * @brief operator [] (read-only)
     * @param idx
     * @return
     */
    const_reference operator[](const std::size_t idx) const;

    /**
     * @brief operator [] (read/write)
     * @param idx
     * @return
     */
    reference operator[](const std::size_t idx);

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
    void push_back(const bool& src);

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
    iterator begin();

    /**
     * @brief Const-iterator to the beginning of the vector
     * @return
     */
    const_iterator begin() const;

    /**
     * @brief Iterator to the end of the vector
     * @return
     */
    iterator end();

    /**
     * @brief Const-iterator to the end of the vector
     * @return
     */
    const_iterator end() const;

    /**
     * @brief Finds the position of the array where the object src is found
     * @param src
     * @return An iterator to the position, or end() if not found
     */
    iterator find(const bool& src); // const;

    /**
     * @brief Finds the position of the array where the object src is found
     * @param src
     * @return A const-iterator to the position, or end() if not found
     */
    const_iterator find(const bool& src) const;

    /**
     * @brief Prints the vector contents
     */
    void print() const;

private:
    storage_type* data_;
    std::size_t size_;
    std::size_t capacity_;
    std::size_t n_elements_;
    /**
     * @brief Computes the capacity of the array, as twice the size
     * @param size
     * @return
     */
    std::size_t computeCapacity(const std::size_t size) const;

    /**
     * @brief Computes the number of unsigned ints to fulfill the desired capacity
     * @param capacity
     * @return
     */
    std::size_t computeStorage(const std::size_t capacity) const;

    /**
     * @brief Checks whether idx is a valid index
     * @param idx
     */
    void check_bounds(const std::size_t idx) const;

    /**
     * @brief Increases the array size and copies the content after idx
     * @param idx
     */
    void expand(const std::size_t idx);
};


// ======================================================================
// ======================================================================
// ======================================================================

Vector<bool>::Vector()
{
    // ** Allocate space
    size_ = 0;
    capacity_ = sizeof(storage_type) * 8;                  //Sizeof() returns the number of BYTES
    n_elements_ = computeStorage(capacity_);
    data_ = new storage_type[n_elements_];   // Can allocate 32 bits
}

Vector<bool>::Vector(const std::size_t size)
{
    // ** Allocate space
    size_ = size;
    capacity_ = computeCapacity(size_);
    n_elements_ = computeStorage(capacity_);
    data_ = new storage_type[n_elements_];

    // ** Initialize elements
    for(std::size_t i = 0; i < n_elements_; ++i)
    {
        data_[i] = 0; // All the bits set to false
    }
}

Vector<bool>::Vector(const Vector<bool>& src)
{
    // ** Allocate space
    size_ = src.size();
    capacity_ = src.capacity();
    n_elements_ = src.n_elements_;
    data_ = new storage_type[n_elements_];

    // ** Copy elements
    for(std::size_t i = 0; i < n_elements_; ++i)
    {
        data_[i] = src.data_[i];
    }
}

Vector<bool>::Vector(const std::initializer_list<bool>& src)
{
    // ** Allocate space
    size_ = src.size();
    capacity_ = computeCapacity(size_);
    n_elements_ = computeStorage(capacity_);
    data_ = new storage_type[capacity_];

    // ** Copy elements
    std::size_t i = 0;
    for(auto it = src.begin(); it < src.end(); it++, ++i)
    {
        (*this)[i] = *it;
    }
}

Vector<bool>::Vector(const std::size_t size, const bool& src)
{
    // ** Allocate space
    size_ = size;
    n_elements_ = computeStorage(capacity_);
    data_ = new storage_type[capacity_];

    // ** Copy elements
    for(std::size_t i = 0; i < size_; ++i)
    {
        (*(this))[i] = src;
    }
}

Vector<bool>::Vector(Vector<bool>&& src)
{
    // ** Move the data
    data_ = src.data_;
    size_ = src.size_;
    capacity_ = src.capacity_;
    n_elements_ = src.n_elements_;

    // ** Remove old references
    src.size_ = 0;
    src.capacity_ = 0;
    src.n_elements_ = 0;
    src.data_ = nullptr;
}

Vector<bool>& Vector<bool>::operator= (const Vector<bool>& src)
{
    if(&src != this) // Check self-assignment
    {
        // ** Reallocate space if needed
        if (src.size() > size_)
        {
            delete [] data_;
            data_ = new storage_type[src.n_elements_];
        }
        // ** Copy src resources
        for(std::size_t i = 0; i < src.n_elements_; i++)
        {
            data_[i] = src.data_[i];
        }
        size_ = src.size();
    }
    return *this;
}

Vector<bool>& Vector<bool>::operator= (Vector<bool>&& src)
{
    if(&src != this) // Self-assignment check
    {
        // ** Release own resources
        delete [] data_;

        // ** Get src resources
        data_ = src.data_;
        size_ = src.size();
        capacity_ = src.capacity();
        n_elements_ = src.n_elements_;

        // ** Anulate src resources
        src.data_ = nullptr;
        src.size_ = 0;
        src.capacity_ = 0;
        src.n_elements_= 0;
    }
    return *this;
}

Vector<bool>::const_reference Vector<bool>::operator[](const std::size_t idx) const
{
    check_bounds(idx);
    return Vector<bool>::const_reference(this, idx);
}


Vector<bool>::reference Vector<bool>::operator[](const std::size_t idx)
{
    check_bounds(idx);    
    return Vector<bool>::reference(this, idx);
}


Vector<bool>::~Vector()
{
    delete[] data_;
    size_ = 0;
    capacity_ = 0;
}

void Vector<bool>::reset()
{
    for(std::size_t i = 0; i < n_elements_; ++i)
        data_[i] = storage_type{};
}

void Vector<bool>::push_back(const bool& src)
{
    // ** Check size
    if (size_ < capacity_) //No need to allocate more memory
    {
        size_++;
        (*this)[size_-1] = src;
    }
    else
    {
        // ** Reallocate data
        capacity_ = computeCapacity(capacity_);
        n_elements_ = computeStorage(capacity_);
        storage_type* newData = new storage_type[n_elements_];

        // ** Move data
        for (std::size_t i = 0; i < n_elements_; ++i)
        {
            newData[i] = data_[i];
        }

        // ** Add new element
        size_++;
        (*this)[size_-1] = src;

        // ** Delete old data
        delete [] data_;

        // ** Reassign data
        data_ = newData;
    }
}

void Vector<bool>::clear()
{
    size_ = 0;
}


std::size_t Vector<bool>::size() const
{
    return size_;
}

std::size_t Vector<bool>::capacity() const
{
    return capacity_;
}

Vector<bool>::iterator Vector<bool>::begin()
{
    Vector<bool>::reference r(this,0);
    return Vector<bool>::iterator(r);
}

Vector<bool>::const_iterator Vector<bool>::begin() const
{
    Vector<bool>::const_reference r(this,0);
    return Vector<bool>::const_iterator(r);
}

Vector<bool>::iterator Vector<bool>::end()
{
    Vector<bool>::reference r(this,size_);
    return Vector<bool>::iterator(r);
}

Vector<bool>::const_iterator Vector<bool>::end() const
{
    Vector<bool>::const_reference r(this,size_);
    return Vector<bool>::const_iterator(r);
}

Vector<bool>::iterator Vector<bool>::find(const bool& src)
{
    for (auto it = begin(); it < end(); ++it)
    {
        if (*it == src)
            return it;
    }
    return end();
}

Vector<bool>::const_iterator Vector<bool>::find(const bool& src) const
{
    for (auto it = begin(); it < end(); ++it)
    {
        if (*it == src)
            return it;
    }
    return end();
}

void Vector<bool>::print() const
{
    for(std::size_t i = 0; i < size_; ++i)
    {
        std::cout << (*this)[i]<<" ";
    }
    std::cout << std::endl;
}

std::size_t Vector<bool>::computeCapacity(const std::size_t size) const
{
    return size != 0? size*2 : INITIAL_SIZE;
}

std::size_t Vector<bool>::computeStorage(const std::size_t capacity) const
{
    return capacity/sizeof(storage_type) + 1;
}

void Vector<bool>::check_bounds(const std::size_t idx) const
{
    if(idx < 0 || idx >= size_ )
    {
        throw std::out_of_range("Index out of bounds!");
    }
}

// ** Required for sort
void swap(Vector<bool>::reference& r1, Vector<bool>::reference& r2)
{
    bool tmp = r2;
    r2 = r1;
    r1 = tmp;
}
#endif // VECTOR_BOOL_H
