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

    typedef A _allocatortype;
    typedef typename A::size_type size_type;
    typedef typename A::reference reference;
    typedef typename A::pointer pointer;
    typedef typename A::const_reference const_reference;
    typedef typename A::difference_type difference_type;
    typedef T* iterator;
    typedef const T* const_iterator;
    typedef std::reverse_iterator<iterator> reverse_iterator;
    typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

    Vector();                              // No dynamic memory allocation here
    Vector(size_type size);                // No dynamic memory allocation here
    Vector(size_type size, const T& init_value);    // Memory allocation for at least [sizeof(T) * size]
    Vector(const Vector<T, A>& rhs);
    Vector(Vector<T, A>&& rhs);

    ~Vector();

    const Vector<T, A>& operator =(const Vector<T, A>& rhs);
    const Vector<T, A>& operator =(Vector<T, A>&& rhs);

    bool operator ==(const Vector<T, A>& rhs) const;
    bool operator !=(const Vector<T, A>& rhs) const;
    bool operator <(const Vector<T, A>& rhs) const;
    bool operator <=(const Vector<T, A>& rhs) const;
    bool operator >(const Vector<T, A>& rhs) const;
    bool operator >=(const Vector<T, A>& rhs) const;

    reference operator [](size_type pos);
    const_reference operator [](size_type pos) const;

    bool empty() const;
    size_type size() const;
    size_type max_size() const;
    size_type capacity() const;

    iterator begin() const;
    iterator end() const;
    const_iterator cbegin() const;
    const_iterator cend() const;
    reverse_iterator rbegin() const;
    reverse_iterator rend() const;
    const_reverse_iterator crbegin() const;
    const_reverse_iterator crend() const;

    reference front() const;
    reference back() const;
    const_reference cfront() const;
    const_reference cback() const;

    void clear(); // Is it correct to mark this function as 'noexcept' ?
    void erease(iterator pos); // repace this with iterators
    void reserve(size_type count);
    void resize(size_type count);
    void insert(iterator pos, const T& value); // TO DO: modify this with 'noexcept(is_noexcept(T))', or something like this
    void emplace_back(std::initializer_list<T> init_list);
    void push_back(const T& value);
    void pop_back(const T& value);
    void swap(const T& value);


private:
    _allocatortype _allocator;
    size_type _size;
    size_type _capacity;
    pointer _data_array;
};                             


/////////////////////////////////////////////////////////////////////////////////////////////
/// Vector implementation
////////////////////////////////////////////////////////////////////////////////////////////

template <typename T, typename A>
Vector<T, A>::Vector() :
_allocator(A())
{
    _size = 0;
    _capacity = 0;
    _data_array = nullptr;
}

template <typename T, typename A>
Vector<T, A>::Vector(size_type size) :
    _allocator(A())
{
    _size = 0;
    _capacity = size;
    _data_array = _allocator.allocate(_capacity);
}

template <typename T, typename A>
Vector<T, A>::Vector(size_type size, const T &init_value) :
    _allocator(A())
{
    _size = size;
    _capacity = size;
    _data_array = _allocator.allocate(_capacity);

    for (size_type i=0; i < size; ++i)
        _allocator.construct(&_data_array[i], init_value);
}

template <typename T, typename A>
Vector<T, A>::Vector(const Vector<T, A>& rhs) :
    _allocator(A())
{
    if (_allocator.get_allocator != rhs._allocator.get_allocator())
        throw "INTERNAL ERROR: user provided allocators not supported yet"; // TO DO: implement this funcionality. More info: 'C++ Standard Library, second edition' page 1086 (Polish edition)

    _capacity = rhs._capacity;
    _size = rhs._size;
    _data_array = _allocator.allocate(_capacity);

    for (size_type i=0; i < _size; ++i)
        _allocator.construct(&_data_array[i], rhs._data_array[i]);
}


template <typename T, typename A>
Vector<T, A>::Vector(Vector<T, A>&& rhs) :
    _allocator(rhs._allocator)
{
    _size = rhs._size;
    _capacity = rhs._capacity;
    _data_array = rhs._data_array;

    rhs._size = 0;
    rhs._capacity = 0;
    rhs._data_array = nullptr;
}

template <typename T, typename A>
Vector<T, A>::~Vector()
{
    if (_data_array) {
        _allocator.deallocate(_data_array, _capacity);
    }
}

template <typename T, typename A>
const Vector<T, A>& Vector<T, A>::operator =(const Vector<T, A>& rhs)
{
    if (_allocator.get_allocator != rhs._allocator.get_allocator())
        throw "INTERNAL ERROR: user provided allocators not supported yet"; // TO DO: implement this funcionality. More info: 'C++ Standard Library, second edition' page 1086 (Polish edition)

    _capacity = rhs._capacity;
    _size = rhs._size;
    _data_array = _allocator.allocate(_capacity);

    for (size_type i=0; i < _size; ++i)
        _allocator.construct(&_data_array[i], rhs._data_array[i]);
}

template <typename T, typename A>
const Vector<T, A>& Vector<T, A>::operator =(Vector<T, A>&& rhs)
{
    if (_allocator.get_allocator != rhs._allocator.get_allocator())
        throw "INTERNAL ERROR: user provided allocators not supported yet"; // TO DO: implement this funcionality. More info: 'C++ Standard Library, second edition' page 1086 (Polish edition)

    _size = rhs._size;
    _capacity = rhs._capacity;
    _data_array = rhs._data_array;

    rhs._size = 0;
    rhs._capacity = 0;
    rhs._data_array = nullptr;
}

template <typename T, typename A>
bool Vector<T, A>::operator ==(const Vector<T, A>& rhs) const
{
    if (_data_array == rhs._data_array && _size == rhs._size) {
        for (size_type i=0; i < _size; ++i) {
            if (_data_array[i] == rhs._data_array[i])
                continue;
            else
                return false;
        }
        return true;
    } else
        return false;
}

template <typename T, typename A>
bool Vector<T, A>::operator !=(const Vector<T, A>& rhs) const
{
    return !(*this == rhs);
}

template <typename T, typename A>
bool Vector<T, A>::operator <(const Vector<T, A>& rhs) const
{
    if (_data_array == rhs._data_array && _size == rhs._size) {
        for (size_type i=0; i < _size; ++i) {
            if (_data_array[i] < rhs._data_array[i])
                continue;
            else
                return false;
        }
        return true;
    } else
        return false;
}

template <typename T, typename A>
bool Vector<T, A>::operator <=(const Vector<T, A>& rhs) const
{
    if (_data_array == rhs._data_array && _size == rhs._size) {
        for (size_type i=0; i < _size; ++i) {
            if (_data_array[i] <= rhs._data_array[i])
                continue;
            else
                return false;
        }
        return true;
    } else
        return false;
}

template <typename T, typename A>
bool Vector<T, A>::operator >(const Vector<T, A>& rhs) const
{
    if (_data_array == rhs._data_array && _size == rhs._size) {
        for (size_type i=0; i < _size; ++i) {
            if (_data_array[i] > rhs._data_array[i])
                continue;
            else
                return false;
        }
        return true;
    } else
        return false;
}

template <typename T, typename A>
bool Vector<T, A>::operator >=(const Vector<T, A>& rhs) const
{
    if (_data_array == rhs._data_array && _size == rhs._size) {
        for (size_type i=0; i < _size; ++i) {
            if (_data_array[i] >= rhs._data_array[i])
                continue;
            else
                return false;
        }
        return true;
    } else
        return false;
}

template <typename T, typename A>
typename Vector<T, A>::reference Vector<T, A>::operator [](size_type pos)
{
    return _data_array[pos];
}

template <typename T, typename A>
bool Vector<T, A>::empty() const
{
    if (_size == 0)
        return true;
    else
        return false;
}

template <typename T, typename A>
typename Vector<T, A>::size_type Vector<T, A>::size() const
{
    return _size;
}

template <typename T, typename A>
typename Vector<T, A>::size_type Vector<T, A>::max_size() const
{
    return std::numeric_limits<size_type>::max();
}

template <typename T, typename A>
typename Vector<T, A>::size_type Vector<T, A>::capacity() const
{
    return _capacity;
}

template <typename T, typename A>
typename Vector<T, A>::iterator Vector<T, A>::begin() const
{
    iterator x = _data_array;
    return x;
}

template <typename T, typename A>
typename Vector<T, A>::iterator Vector<T, A>::end() const
{
    iterator x = _data_array + _size;
    return x;
}

//template <typename T, typename A>
//typename Vector<T, A>::const_iterator Vector<T, A>::cbegin() const
//{
//    const_iterator x;
//    x.container_ = _data_array;
//    x.actual_element_ = _data_array;
//    x.first_element_ = _data_array;
//    x.last_element_ = _data_array + _size;

//    return x;

//}

//template <typename T, typename A>
//typename Vector<T, A>::const_iterator Vector<T, A>::cend() const
//{
//    const_iterator x;
//    x.container_ = _data_array;
//    x.actual_element_ = _data_array + _size;
//    x.first_element_ = _data_array;
//    x.last_element_ = _data_array + _size;

//    return x;

//}

//template <typename T, typename A>
//typename Vector<T, A>::reverse_iterator Vector<T, A>::rbegin() const
//{
//    reverse_iterator x;
//    x.container_ = _data_array;
//    x.actual_element_ = _data_array + _size;
//    x.first_element_ = _data_array + _size;
//    x.last_element_ = _data_array;

//    return x;

//}

//template <typename T, typename A>
//typename Vector<T, A>::reverse_iterator Vector<T, A>::rend() const
//{
//    reverse_iterator x;
//    x.container_ = _data_array;
//    x.actual_element_ = _data_array;
//    x.first_element_ = _data_array + _size;
//    x.last_element_ = _data_array;

//    return x;

//}

//template <typename T, typename A>
//typename Vector<T, A>::const_reverse_iterator Vector<T, A>::crbegin() const
//{
//    const_reverse_iterator x;
//    x.container_ = _data_array;
//    x.actual_element_ = _data_array + _size;
//    x.first_element_ = _data_array + _size;
//    x.last_element_ = _data_array;

//    return x;

//}

//template <typename T, typename A>
//typename Vector<T, A>::const_reverse_iterator Vector<T, A>::crend() const
//{
//    const_reverse_iterator x;
//    x.container_ = _data_array;
//    x.actual_element_ = _data_array;
//    x.first_element_ = _data_array + _size;
//    x.last_element_ = _data_array;

//    return x;

//}

template <typename T, typename A>
typename Vector<T, A>::reference Vector<T, A>::front() const
{
    return _data_array[0]; // first array element
}

template <typename T, typename A>
typename Vector<T, A>::reference Vector<T, A>::back() const
{
    return _data_array[_size - 1]; // last array element
}

//template <typename T, typename A>
//typename Vector<T, A>::const_reference Vector<T, A>::cfront() const
//{
//    return _data_array[0];
//}

//template <typename T, typename A>
//typename Vector<T, A>::const_reference Vector<T, A>::cback() const
//{
//    return _data_array[_size - 1];
//}

template <typename T, typename A>
void Vector<T, A>::clear()
{
    _allocator.dealocate(_data_array, _capacity);
    _data_array = nullptr;
    _capacity = 0;
    _size = 0;
}

//template <typename T, typename A>
//void Vector<T, A>::erease(typename Vector<T,A>::iterator pos)
//{

//}

template <typename T, typename A>
void Vector<T, A>::reserve(size_type count)
{
    if (_capacity > count) // No memory operations needed
        return;

    pointer old_data_array = _data_array;
    size_type old_capacity = _capacity;
    _capacity = count;
    _data_array = _allocator.allocate(_capacity);

    for (size_type i=0; i < _size; ++i)
        _allocator.construct(&_data_array[i], old_data_array[i]);
    _allocator.deallocate(old_data_array, old_capacity);
}

//template <typename T, typename A>
//void Vector<T, A>::resize(size_type count)
//{

//}

template <typename T, typename A>
void Vector<T,A>::push_back(const T& value)
{
    if (!_data_array)
        reserve(1);

    if (_capacity > _size) {
    _allocator.construct(end(), value);
    ++_size;
    } else {
        reserve(2 * _capacity); // TO DO: search for some better algorithm
        _allocator.construct(end(), value);
        ++_size;
    }
}

#endif // VECTOR_HPP
