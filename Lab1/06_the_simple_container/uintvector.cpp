#include "kth_cprog_simple_container.hpp"

UIntVector::UIntVector()
{
    size_ = 0;
    data_ = nullptr;
}

UIntVector::UIntVector(const std::size_t size)
{
    // ** Allocate space
    data_ = new unsigned int[size];
    size_ = size;

    // ** Initialize elements to zero
    for(std::size_t i = 0; i < size_; i++)
    {
        data_[i] = 0;
    }
}

UIntVector::UIntVector(const UIntVector& src)
{
    // ** Allocate space
    data_ = new unsigned int[src.size()];
    size_ = src.size();

    // ** Copy elements
    for(std::size_t i = 0; i < size_; i++)
    {
        data_[i] = src.data_[i];
    }
}

UIntVector::UIntVector(const std::initializer_list<unsigned int>& src)
{
    // ** Allocate space
    data_ = new unsigned int[src.size()];
    size_ = src.size();

    // ** Copy elements
    std::size_t i = 0;
    for(auto it = src.begin(); it != src.end(); it++, i++)
    {
        data_[i] = *it;
    }
}

UIntVector::UIntVector(UIntVector&& src)
{
    // ** Move the data
    data_ = src.data_;
    size_ = src.size_;

    // ** Remove old references
    src.size_ = 0;
    src.data_ = nullptr;
}

UIntVector& UIntVector::operator= (const UIntVector& src)
{
    if(&src != this) // Check self-assignment
    {
        // ** Rellocate space if needed
        if (src.size() > size_)
        {
            delete [] data_;
            data_ = new unsigned int[src.size()];
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

UIntVector& UIntVector::operator= (UIntVector&& src)
{
    if(&src != this) // Self-assignment check
    {
        // ** Release own resources
        delete [] data_;

        // ** Get src resources
        data_ = src.data_;
        size_ = src.size_;

        // ** Anulate src resources
        src.data_ = nullptr;
        src.size_ = 0;
    }
    return *this;
}

UIntVector::~UIntVector()
{
    delete [] data_;
}

std::size_t UIntVector::size() const
{
    return size_;
}

const unsigned int& UIntVector::operator [](const std::size_t idx) const
{
    check_inside(idx);
    return data_[idx];
}

unsigned int& UIntVector::operator [](const std::size_t idx)
{
    check_inside(idx);
    return data_[idx];
}

void UIntVector::reset()
{
    for(std::size_t i = 0; i < size_; i++)    
        data_[i] = (unsigned) int{};    
}

void UIntVector::check_inside(const std::size_t idx) const
{
    if(idx < 0 || idx >= size_ )
        throw std::out_of_range("Index out of bounds!");    
}
