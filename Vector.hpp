#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <cstddef>
#include <iterator>
#include <initializer_list>
#include <limits>
#include <vector>
#include <iostream>


// TO DO: add r-value reference support
// DO DO: re-write iterator classes in DRY way


template <typename T, typename A = std::allocator<T>>
class Vector {
//////////////////////////////////////////////////////////////////////////////////////////////
/// Simple template vector class similar to std::vector
/////////////////////////////////////////////////////////////////////////////////////////////

public:

    typedef A allocator_type;
    typedef typename A::size_type size_type;
    typedef typename A::reference reference;
    typedef typename A::pointer pointer;
    typedef typename A::const_reference const_reference;
    typedef typename A::difference_type difference_type;

    class iterator
    {
    public:

        // This typedef's can be also replaced by public inheritance from std::iterator<std::random_iterator_tag, T>
        // More info:
        //      1: 'C++ Standard Library, second edition' chapter 9.6 (page 516 in Polish edition)
        //      2: std::iterator class implementation (<iterator> in STL library)
        typedef typename A::difference_type difference_type;
        typedef typename A::value_type value_type;
        typedef typename A::reference reference;
        typedef typename A::pointer pointer;
        typedef std::random_access_iterator_tag iterator_category;

        friend class Vector<T, A>;

        iterator() noexcept;
        iterator(const iterator& rhs) noexcept;
        ~iterator() noexcept;

        const iterator& operator =(const iterator& rhs) noexcept;

        bool operator ==(const iterator& rhs) const;
        bool operator !=(const iterator& rhs) const;
        bool operator <(const iterator& rhs) const;
        bool operator <=(const iterator& rhs) const;
        bool operator >(const iterator& rhs) const;
        bool operator >=(const iterator& rhs) const;

        const iterator& operator ++();
        iterator operator ++(int rhs);
        const iterator& operator --();
        iterator operator --(int rhs);
        iterator operator +(size_type rhs) const;
        const iterator& operator +=(size_type rhs);
        iterator operator -(size_type rhs) const;
        const iterator& operator -=(size_type rhs);
        //diffrence_type operator -(const iterator& rhs) const; // TO DO: to implement if it is necesary

        // iterator state dosen't change, only pointed data can change, so these functions are marked as 'const'
        reference operator *() const;
        pointer operator ->() const;
        reference operator [](size_type index) const;

    protected:
        pointer container_;
        pointer actual_element_;
        pointer first_element_;
        pointer last_element_;
    };

    class const_iterator
    {
    public:

        // This typedef's can be also replaced by public inheritance from std::iterator<std::random_iterator_tag, const T>
        // More info:
        //      1: 'C++ Standard Library, second edition' chapter 9.6 (page 516 in Polish edition)
        //      2: std::iterator class implementation (<iterator> in STL library)
        typedef typename A::difference_type difference_type;
        typedef typename A::value_type value_type;
        typedef typename A::reference reference;
        typedef typename A::const_reference const_reference;
        typedef typename A::pointer pointer;
        typedef typename A::const_pointer const_pointer;
        typedef std::random_access_iterator_tag iterator_category;

        friend class Vector<T, A>;

        const_iterator() noexcept;
        const_iterator(const const_iterator& rhs) noexcept;
        ~const_iterator() noexcept;

        const const_iterator& operator =(const const_iterator& rhs) noexcept;
        const const_iterator& operator =(const iterator& rhs) noexcept;

        bool operator ==(const const_iterator& rhs) const;
        bool operator !=(const const_iterator& rhs) const;
        bool operator <(const const_iterator& rhs) const;
        bool operator <=(const const_iterator& rhs) const;
        bool operator >(const const_iterator& rhs) const;
        bool operator >=(const const_iterator& rhs) const;

        const_iterator& operator ++();
        const_iterator operator ++(int rhs);
        const_iterator& operator --();
        const_iterator operator --(int rhs);
        const_iterator operator +(size_type rhs) const;
        const_iterator& operator +=(size_type rhs);
        const_iterator operator -(size_type rhs) const;
        const_iterator& operator -=(size_type rhs);
        difference_type operator -(const const_iterator& rhs) const;

        const_reference operator *() const;
        const_pointer operator ->() const;
        const_reference operator [](size_type index) const;

    protected:
        const_pointer container_;
        const_pointer actual_element_;
        const_pointer first_element_;
        const_pointer last_element_;
    };

    typedef std::reverse_iterator<iterator> reverse_iterator;
    typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

    Vector() noexcept; // No dynamic memory allocation here
    Vector(size_type size) noexcept; // No dynamic memory allocation here
    Vector(size_type size, const T& init_value); // Memory allocation for at least [sizeof(T) * size]
    Vector(const Vector<T, A>& rhs);
    Vector(Vector<T, A>&& rhs);

    ~Vector() noexcept;

    const Vector<T, A>& operator =(const Vector<T, A>& rhs);
    const Vector<T, A>& operator =(Vector<T, A>&& rhs);

    bool operator ==(const Vector<T, A>& rhs) const noexcept;
    bool operator !=(const Vector<T, A>& rhs) const noexcept;
    bool operator <(const Vector<T, A>& rhs) const noexcept;
    bool operator <=(const Vector<T, A>& rhs) const noexcept;
    bool operator >(const Vector<T, A>& rhs) const noexcept;
    bool operator >=(const Vector<T, A>& rhs) const noexcept;

    bool empty() const noexcept;
    size_type size() const noexcept;
    size_type max_size() const noexcept;
    size_type capacity() const noexcept;

    iterator begin() const noexcept;
    iterator end() const noexcept;
    const_iterator cbegin() const noexcept;
    const_iterator cend() const noexcept;
    reverse_iterator rbegin() const noexcept;
    reverse_iterator rend() const noexcept;
    const_reverse_iterator crbegin() const noexcept;
    const_reverse_iterator crend() const noexcept;

    reference front() const noexcept;
    reference back() const noexcept;
    const_reference cfront() const noexcept;
    const_reference cback() const noexcept;

    void clear() noexcept; // Is it correct to mark this function as 'noexcept' ?
    void erease(iterator pos); // repace this with iterators
    void reserve(size_type count);
    void resize(size_type count);
    void insert(iterator pos, const T& value) noexcept; // TO DO: modify this with 'noexcept(is_noexcept(T))', or something like this
    void emplace_back(std::initializer_list<T> init_list) noexcept;
    void push_back(const T& value);
    void pop_back(const T& value) noexcept;
    void swap(const T& value);


private:
    allocator_type allocator_;
    size_type size_;
    size_type capacity_;
    pointer data_array_;
};


/////////////////////////////////////////////////////////////////////////////////////////////
/// iterator implementation
////////////////////////////////////////////////////////////////////////////////////////////

template <typename T, typename A>
Vector<T, A>::iterator::iterator() noexcept
{
    container_ = nullptr;
    actual_element_ = nullptr;
    first_element_ = nullptr;
    last_element_ = nullptr;
}

template <typename T, typename A>
Vector<T, A>::iterator::iterator(const iterator &rhs) noexcept
{
    container_ = rhs.container_;
    actual_element_ = rhs.actual_element_;
    first_element_ = rhs.first_element_;
    last_element_ = rhs.last_element_;
}

template <typename T, typename A>
Vector<T, A>::iterator::~iterator() noexcept
{

}

template <typename T, typename A>
const typename Vector<T, A>::iterator& Vector<T, A>::iterator::operator =(const typename Vector<T, A>::iterator& rhs) noexcept
{
    container_ = rhs.container_;
    actual_element_ = rhs.actual_element_;
    first_element_ = rhs.first_element_;
    last_element_ = rhs.last_element_;
    return rhs;
}

template <typename T, typename A>
bool Vector<T, A>::iterator::operator ==(const typename Vector<T, A>::iterator& rhs) const // TO DO: if there is noexcept operator ==() in T type, then this method is also noexcept
{
   if (actual_element_ == rhs.actual_element_)
       return true;
   else
       return false;
}

template <typename T, typename A>
bool Vector<T, A>::iterator::operator !=(const typename Vector<T, A>::iterator& rhs) const // TO DO: if there is noexcept operator !=() in T type, then this method is also noexcept
{
   return !(*this == rhs);
}

template <typename T, typename A>
bool Vector<T, A>::iterator::operator <(const typename Vector<T, A>::iterator& rhs) const // TO DO: if there is noexcept operator <() in T type, then this method is also noexcept
{
   if (actual_element_ < rhs.actual_element_)
       return true;
   else
       return false;
}

template <typename T, typename A>
bool Vector<T, A>::iterator::operator <=(const typename Vector<T, A>::iterator& rhs) const // TO DO: if there is noexcept operator <=() in T type, then this method is also noexcept
{
    return (*this < rhs) || (*this == rhs);
}

template <typename T, typename A>
bool Vector<T, A>::iterator::operator >(const typename Vector<T, A>::iterator& rhs) const // TO DO: if there is noexcept operator >() in T type, then this method is also noexcept
{
    return !(*this <= rhs);
}

template <typename T, typename A>
bool Vector<T, A>::iterator::operator >=(const typename Vector<T, A>::iterator& rhs) const // TO DO: if there is noexcept operator >=() in T type, then this method is also noexcept
{
    return !(*this < rhs);
}

template <typename T, typename A>
const typename Vector<T, A>::iterator& Vector<T, A>::iterator::operator ++()
{
    ++actual_element_;
    return *this;
}

template <typename T, typename A>
typename Vector<T, A>::iterator Vector<T, A>::iterator::operator ++(int rhs)
{
    actual_element_++;
    return *this;
}

template <typename T, typename A>
const typename Vector<T, A>::iterator& Vector<T, A>::iterator::operator --()
{
    --actual_element_;
    return *this;
}

template <typename T, typename A>
typename Vector<T, A>::iterator Vector<T, A>::iterator::operator --(int rhs)
{
    --actual_element_;
    return *this;
}

template <typename T, typename A>
typename Vector<T, A>::iterator Vector<T, A>::iterator::operator +(typename Vector<T, A>::size_type rhs) const
{
    typename Vector<T, A>::iterator x(*this);
    x.actual_element_ += rhs;
    return x;
}

template <typename T, typename A>
const typename Vector<T, A>::iterator& Vector<T, A>::iterator::operator +=(typename Vector<T, A>::size_type rhs)
{
    actual_element_ += rhs;
    return *this;
}

template <typename T, typename A>
typename Vector<T, A>::iterator Vector<T, A>::iterator::operator -(typename Vector<T, A>::size_type rhs) const
{
    typename Vector<T, A>::iterator x(*this);
    x.actual_element_ -= rhs;
    return x;
}

template <typename T, typename A>
const typename Vector<T, A>::iterator& Vector<T, A>::iterator::operator -=(typename Vector<T, A>::size_type rhs)
{
    actual_element_ -= rhs;
    return *this;
}

template <typename T, typename A>
typename Vector<T, A>::reference Vector<T, A>::iterator::operator *() const
{
    return *actual_element_;
}

template <typename T, typename A>
typename Vector<T, A>::pointer Vector<T, A>::iterator::operator ->() const
{
    return actual_element_;
}

template <typename T, typename A>
typename Vector<T, A>::reference Vector<T, A>::iterator::operator [](typename Vector<T, A>::size_type index) const
{
    return *actual_element_;
}


/////////////////////////////////////////////////////////////////////////////////////////////
/// const iterator implementation
////////////////////////////////////////////////////////////////////////////////////////////

template <typename T, typename A>
Vector<T, A>::const_iterator::const_iterator() noexcept
{
    container_ = nullptr;
    actual_element_ = nullptr;
    first_element_ = nullptr;
    last_element_ = nullptr;
}

template <typename T, typename A>
Vector<T, A>::const_iterator::~const_iterator() noexcept
{

}

template <typename T, typename A>
bool Vector<T, A>::const_iterator::operator ==(const Vector<T, A>::const_iterator& rhs) const
{
    if (actual_element_ == rhs.actual_element_)
        return true;
    else
        return false;
}


/////////////////////////////////////////////////////////////////////////////////////////////
/// Vector implementation
////////////////////////////////////////////////////////////////////////////////////////////

template <typename T, typename A>
Vector<T, A>::Vector(size_type size) noexcept :
    allocator_(A())
{
    size_ = size;
    capacity_ = 0;
    data_array_ = nullptr;
}

template <typename T, typename A>
Vector<T, A>::Vector(size_type size, const T &init_value) :
    allocator_(A())
{
    capacity_ = size_ = size;
    data_array_ = allocator_.allocate(capacity_);

    for (size_type i=0; i < size; ++i)
        allocator_.construct(&data_array_[i], init_value);
}

template <typename T, typename A>
Vector<T, A>::Vector(const Vector<T, A>& rhs) :
    allocator_(A())
{
    if (allocator_.get_allocator != rhs.allocator_.get_allocator())
        throw "INTERNAL ERROR: user provided allocators not supported yet"; // TO DO: implement this funcionality. More info: 'C++ Standard Library, second edition' page 1086 (Polish edition)

    capacity_ = rhs.capacity_;
    size_ = rhs.size_;
    data_array_ = allocator_.allocate(capacity_);

    for (size_type i=0; i < size_; ++i)
        allocator_.construct(&data_array_[i], rhs.data_array_[i]);
}


template <typename T, typename A>
Vector<T, A>::Vector(Vector<T, A>&& rhs) :
    allocator_(rhs.allocator_)
{
    size_ = rhs.size_;
    capacity_ = rhs.capacity_;
    data_array_ = rhs.data_array_;

    rhs.size_ = 0;
    rhs.capacity_ = 0;
    rhs.data_array_ = nullptr;
}

template <typename T, typename A>
Vector<T, A>::~Vector() noexcept
{
    if (data_array_) {
        allocator_.deallocate(data_array_, capacity_);
    }
}

template <typename T, typename A>
const Vector<T, A>& Vector<T, A>::operator =(const Vector<T, A>& rhs)
{
    if (allocator_.get_allocator != rhs.allocator_.get_allocator())
        throw "INTERNAL ERROR: user provided allocators not supported yet"; // TO DO: implement this funcionality. More info: 'C++ Standard Library, second edition' page 1086 (Polish edition)

    capacity_ = rhs.capacity_;
    size_ = rhs.size_;
    data_array_ = allocator_.allocate(capacity_);

    for (size_type i=0; i < size_; ++i)
        allocator_.construct(&data_array_[i], rhs.data_array_[i]);
}

template <typename T, typename A>
const Vector<T, A>& Vector<T, A>::operator =(Vector<T, A>&& rhs)
{
    if (allocator_.get_allocator != rhs.allocator_.get_allocator())
        throw "INTERNAL ERROR: user provided allocators not supported yet"; // TO DO: implement this funcionality. More info: 'C++ Standard Library, second edition' page 1086 (Polish edition)

    size_ = rhs.size_;
    capacity_ = rhs.capacity_;
    data_array_ = rhs.data_array_;

    rhs.size_ = 0;
    rhs.capacity_ = 0;
    rhs.data_array_ = nullptr;
}

template <typename T, typename A>
bool Vector<T, A>::operator ==(const Vector<T, A>& rhs) const noexcept
{
    if (data_array_ == rhs.data_array_ && size_ == rhs.size_) {
        for (size_type i=0; i < size_; ++i) {
            if (data_array_[i] == rhs.data_array_[i])
                continue;
            else
                return false;
        }
        return true;
    } else
        return false;
}

template <typename T, typename A>
bool Vector<T, A>::operator !=(const Vector<T, A>& rhs) const noexcept
{
    return !(*this == rhs);
}

template <typename T, typename A>
bool Vector<T, A>::operator <(const Vector<T, A>& rhs) const noexcept
{
    if (data_array_ == rhs.data_array_ && size_ == rhs.size_) {
        for (size_type i=0; i < size_; ++i) {
            if (data_array_[i] < rhs.data_array_[i])
                continue;
            else
                return false;
        }
        return true;
    } else
        return false;
}

template <typename T, typename A>
bool Vector<T, A>::operator <=(const Vector<T, A>& rhs) const noexcept
{
    if (data_array_ == rhs.data_array_ && size_ == rhs.size_) {
        for (size_type i=0; i < size_; ++i) {
            if (data_array_[i] <= rhs.data_array_[i])
                continue;
            else
                return false;
        }
        return true;
    } else
        return false;
}

template <typename T, typename A>
bool Vector<T, A>::operator >(const Vector<T, A>& rhs) const noexcept
{
    if (data_array_ == rhs.data_array_ && size_ == rhs.size_) {
        for (size_type i=0; i < size_; ++i) {
            if (data_array_[i] > rhs.data_array_[i])
                continue;
            else
                return false;
        }
        return true;
    } else
        return false;
}

template <typename T, typename A>
bool Vector<T, A>::operator >=(const Vector<T, A>& rhs) const noexcept
{
    if (data_array_ == rhs.data_array_ && size_ == rhs.size_) {
        for (size_type i=0; i < size_; ++i) {
            if (data_array_[i] >= rhs.data_array_[i])
                continue;
            else
                return false;
        }
        return true;
    } else
        return false;
}

template <typename T, typename A>
bool Vector<T, A>::empty() const noexcept
{
    if (size_ == 0)
        return true;
    else
        return false;
}

template <typename T, typename A>
typename Vector<T, A>::size_type Vector<T, A>::size() const noexcept
{
    return size_;
}

template <typename T, typename A>
typename Vector<T, A>::size_type Vector<T, A>::max_size() const noexcept
{
    return std::numeric_limits<size_type>::max();
}

template <typename T, typename A>
typename Vector<T, A>::size_type Vector<T, A>::capacity() const noexcept
{
    return capacity_;
}

template <typename T, typename A>
typename Vector<T, A>::iterator Vector<T, A>::begin() const noexcept
{
    iterator x;
    x.container_ = data_array_;
    x.actual_element_ = data_array_;
    x.first_element_ = data_array_;
    x.last_element_ = data_array_ + size_;

    return x;
}

template <typename T, typename A>
typename Vector<T, A>::iterator Vector<T, A>::end() const noexcept
{
    iterator x;
    x.container_ = data_array_;
    x.actual_element_ = data_array_ + size_;
    x.first_element_ = data_array_;
    x.last_element_ = data_array_ + size_;

    return x;
}

//template <typename T, typename A>
//typename Vector<T, A>::const_iterator Vector<T, A>::cbegin() const noexcept
//{
//    const_iterator x;
//    x.container_ = data_array_;
//    x.actual_element_ = data_array_;
//    x.first_element_ = data_array_;
//    x.last_element_ = data_array_ + size_;

//    return x;

//}

//template <typename T, typename A>
//typename Vector<T, A>::const_iterator Vector<T, A>::cend() const noexcept
//{
//    const_iterator x;
//    x.container_ = data_array_;
//    x.actual_element_ = data_array_ + size_;
//    x.first_element_ = data_array_;
//    x.last_element_ = data_array_ + size_;

//    return x;

//}

//template <typename T, typename A>
//typename Vector<T, A>::reverse_iterator Vector<T, A>::rbegin() const noexcept
//{
//    reverse_iterator x;
//    x.container_ = data_array_;
//    x.actual_element_ = data_array_ + size_;
//    x.first_element_ = data_array_ + size_;
//    x.last_element_ = data_array_;

//    return x;

//}

//template <typename T, typename A>
//typename Vector<T, A>::reverse_iterator Vector<T, A>::rend() const noexcept
//{
//    reverse_iterator x;
//    x.container_ = data_array_;
//    x.actual_element_ = data_array_;
//    x.first_element_ = data_array_ + size_;
//    x.last_element_ = data_array_;

//    return x;

//}

//template <typename T, typename A>
//typename Vector<T, A>::const_reverse_iterator Vector<T, A>::crbegin() const noexcept
//{
//    const_reverse_iterator x;
//    x.container_ = data_array_;
//    x.actual_element_ = data_array_ + size_;
//    x.first_element_ = data_array_ + size_;
//    x.last_element_ = data_array_;

//    return x;

//}

//template <typename T, typename A>
//typename Vector<T, A>::const_reverse_iterator Vector<T, A>::crend() const noexcept
//{
//    const_reverse_iterator x;
//    x.container_ = data_array_;
//    x.actual_element_ = data_array_;
//    x.first_element_ = data_array_ + size_;
//    x.last_element_ = data_array_;

//    return x;

//}

template <typename T, typename A>
typename Vector<T, A>::reference Vector<T, A>::front() const noexcept
{
    return data_array_[0]; // first array element
}

template <typename T, typename A>
typename Vector<T, A>::reference Vector<T, A>::back() const noexcept
{
    return data_array_[size_ - 1]; // last array element
}

//template <typename T, typename A>
//typename Vector<T, A>::const_reference Vector<T, A>::cfront() const noexcept
//{
//    return data_array_[0];
//}

//template <typename T, typename A>
//typename Vector<T, A>::const_reference Vector<T, A>::cback() const noexcept
//{
//    return data_array_[size_ - 1];
//}

template <typename T, typename A>
void Vector<T, A>::clear() noexcept
{
    allocator_.dealocate(data_array_, capacity_);
    data_array_ = nullptr;
    capacity_ = 0;
    size_ = 0;
}

//template <typename T, typename A>
//void Vector<T, A>::erease(typename Vector<T,A>::iterator pos)
//{

//}

template <typename T, typename A>
void Vector<T, A>::reserve(size_type count)
{
    if (capacity_ > size_) // No memory operations needed
        return;

    std::cout << "Memory realocation" << std::endl; // DEBUG MODE

    pointer old_data_array = data_array_;
    size_type old_capacity = capacity_;
    capacity_ = count;
    data_array_ = allocator_.allocate(capacity_);

    for (size_type i=0; i < size_; ++i)
        allocator_.construct(&data_array_[i], old_data_array[i]);

    allocator_.deallocate(old_data_array, old_capacity);
}

//template <typename T, typename A>
//void Vector<T, A>::resize(size_type count)
//{

//}

template <typename T, typename A>
void Vector<T,A>::push_back(const T& value)
{
    if (capacity_ > size_) {
    allocator_.construct(end().actual_element_, value);
    ++size_;
    } else {
        reserve(2 * capacity_); // TO DO: search for some better algorithm
        allocator_.construct(end().actual_element_, value);
        ++size_;
    }
}

#endif // VECTOR_HPP
