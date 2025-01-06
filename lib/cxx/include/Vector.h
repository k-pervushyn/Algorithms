//
// Created by kyrylo on 04/01/25.
//

#ifndef VECTOR_H
#define VECTOR_H

template <typename T>
class Vector {
    static constexpr size_t INIT_CAPACITY = 2;
    static constexpr size_t GROW_MULTIPLIER = 2;
    static constexpr size_t SHRINK_FRACTION = 2;
    static constexpr size_t SHRINK_NEED_FRACTION = 2;

    T *_allocator;
    size_t _size;
    size_t _capacity;

public:
    Vector() : _allocator(nullptr), _size(0), _capacity(INIT_CAPACITY)
            { _allocator = new T[INIT_CAPACITY]; }
    Vector(const Vector<T>&);
    Vector<T> &operator=(const Vector<T>&);

    ~Vector() { delete[] _allocator; }

    void clear();

    /* These two methods cause undefined behaviour if position falls out of range. */
    T &operator[](const size_t position) { return _allocator[position]; }
    const T &operator[](const size_t position) const { return _allocator[position]; }

    Option<T> front() const;
    Option<T> back() const;

private:
    bool needs_grow() const;
    bool needs_shrink() const;
    void grow();
    void shrink();

public:
    void push_back(const T&);
    Option<T> pop_back();

    size_t size() const { return _size; }
    size_t capacity() const { return _capacity; }

    /* These methods do nothing if position falls out of range. */
    void insert(const size_t, const T&);
    void erase(const size_t);
};

template<typename T>
Vector<T>::Vector(const Vector<T> &that) : _allocator(nullptr), _size(that._size), _capacity(that._capacity)
{
    _allocator = new T[_capacity];
    for (size_t i = 0; i < _size; i++)
        _allocator[i] = that._allocator[i];
}

template<typename T>
Vector<T> &Vector<T>::operator=(const Vector<T> &that)
{
    if (this == &that)
        return *this;
    delete[] _allocator;
    _size = that._size;
    _capacity = that._capacity;
    _allocator = new T[_capacity];
    for (size_t i = 0; i < _size; i++)
        _allocator[i] = that._allocator[i];
    return *this;
}

template<typename T>
void Vector<T>::clear()
{
    delete[] _allocator;
    _size = 0;
    _capacity = INIT_CAPACITY;
    _allocator = new T[_capacity];
}

template<typename T>
Option<T> Vector<T>::front() const
{
    if (_size == 0)
        return Nothing();
    return Some(_allocator[0]);
}

template<typename T>
Option<T> Vector<T>::back() const
{
    if (_size == 0)
        return Nothing();
    return Some(_allocator[_size - 1]);
}

template<typename T>
bool Vector<T>::needs_grow() const { return _size == _capacity; }

template<typename T>
bool Vector<T>::needs_shrink() const
{
    return _size <= _capacity / SHRINK_NEED_FRACTION && _capacity / SHRINK_NEED_FRACTION >= INIT_CAPACITY;
}

template<typename T>
void Vector<T>::grow()
{
    T *new_allocator = new T[_capacity * GROW_MULTIPLIER];
    for (size_t i = 0; i < _size; i++)
        new_allocator[i] = _allocator[i];
    delete[] _allocator;
    _allocator = new_allocator;
    _capacity *= GROW_MULTIPLIER;
}

template<typename T>
void Vector<T>::shrink()
{
    T *new_allocator = new T[_capacity / SHRINK_FRACTION];
    for (size_t i = 0; i < _size; i++)
        new_allocator[i] = _allocator[i];
    delete[] _allocator;
    _allocator = new_allocator;
    _capacity /= SHRINK_FRACTION;
}

template<typename T>
void Vector<T>::push_back(const T &value)
{
    if (needs_grow())
        grow();
    _allocator[_size++] = value;
}

template<typename T>
Option<T> Vector<T>::pop_back()
{
    if (_size == 0)
        return Nothing();
    Option<T> result = Some(_allocator[--_size]);
    if (needs_shrink())
        shrink();
    return result;
}

template<typename T>
void Vector<T>::insert(const size_t position, const T &value)
{
    if (position > _size)
        return; // error: position out of range
    if (needs_grow())
        grow();
    for (size_t i = _size; i > position; i--)
        _allocator[i] = _allocator[i - 1];
    _allocator[position] = value;
    _size++;
}

template<typename T>
void Vector<T>::erase(const size_t position)
{
    if (position >= _size)
        return; // error: position out of range
    for (size_t i = position; i < _size - 1; i++)
        _allocator[i] = _allocator[i + 1];
    _size--;
    if (needs_shrink())
        shrink();
}

#endif //VECTOR_H
