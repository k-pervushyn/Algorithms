//
// Created by kyrylo on 06/01/25.
//

#ifndef DEQUE_H
#define DEQUE_H

#include "Option.h"

template <typename T>
class Deque {
    static constexpr size_t INIT_CAPACITY = 2;
    static constexpr size_t GROW_MULTIPLIER = 2;
    static constexpr size_t SHRINK_FRACTION = 2;
    static constexpr size_t SHRINK_NEED_FRACTION = 4;

    T *_allocator;
    size_t _size;
    size_t _capacity;
    size_t _first;
    size_t _last;

public:
    Deque() : _allocator(nullptr), _size(0), _capacity(INIT_CAPACITY), _first(0), _last(0)
            { _allocator = new T[INIT_CAPACITY]; }

    Deque(const Deque<T>&);
    Deque<T> &operator=(const Deque<T>&);

    ~Deque() { delete[] _allocator; }

    Option<T> front() const;
    Option<T> back() const;

private:
    size_t next_index(size_t index) const;
    size_t prev_index(size_t index) const;

    bool needs_grow() const;
    bool needs_shrink() const;

    void grow();
    void shrink();

public:
    void push_front(const T&);
    void push_back(const T&);

    Option<T> pop_front();
    Option<T> pop_back();

    size_t size() const { return _size; }
    size_t capacity() const { return _capacity; }
    bool empty() const { return _size == 0; }
};

template <typename T>
Deque<T>::Deque(const Deque<T> &that) : _allocator(nullptr), _size(that._size),
        _capacity(that._capacity), _first(0), _last(0)
{
    _allocator = new T[_capacity];
    _last = _size > 0 ? _size - 1 : 0;
    size_t position = that._first;
    for (size_t i = 0; i < _size; i++) {
        _allocator[i] = that._allocator[position];
        position = that.next_index(position);
    }
}

template <typename T>
Deque<T> &Deque<T>::operator=(const Deque<T> &that)
{
    if (this == &that)
        return *this;
    delete[] _allocator;
    _size = that._size;
    _capacity = that._capacity;
    _first = 0;
    _last = _size > 0 ? _size - 1 : 0;
    _allocator = new T[_capacity];
    size_t position = that._first;
    for (size_t i = 0; i < _size; i++) {
        _allocator[i] = that._allocator[position];
        position = that.next_index(position);
    }
    return *this;
}

template <typename T>
Option<T> Deque<T>::front() const
{
    if (_size == 0)
        return Nothing();
    return Some(_allocator[_first]);
}

template <typename T>
Option<T> Deque<T>::back() const
{
    if (_size == 0)
        return Nothing();
    return Some(_allocator[_last]);
}

template <typename T>
size_t Deque<T>::next_index(size_t index) const
{
    index = index % _capacity;
    return index == _capacity - 1 ? 0 : index + 1;
}

template <typename T>
size_t Deque<T>::prev_index(size_t index) const
{
    index = index % _capacity;
    return index == 0 ? _capacity - 1 : index - 1;
}

template <typename T>
bool Deque<T>::needs_grow() const { return _size == _capacity; }

template <typename T>
bool Deque<T>::needs_shrink() const
{
    return _size <= _capacity / SHRINK_NEED_FRACTION && _capacity / SHRINK_NEED_FRACTION >= INIT_CAPACITY;
}

template <typename T>
void Deque<T>::grow()
{
    T *new_allocator = new T[_capacity * GROW_MULTIPLIER];
    size_t position = _first;
    for (size_t i = 0; i < _size; i++) {
        new_allocator[i] = _allocator[position];
        position = next_index(position);
    }
    delete[] _allocator;
    _first = 0;
    _last = _size > 0 ? _size - 1 : 0;
    _allocator = new_allocator;
    _capacity *= GROW_MULTIPLIER;
}

template <typename T>
void Deque<T>::shrink()
{
    T *new_allocator = new T[_capacity / SHRINK_FRACTION];
    size_t position = _first;
    for (size_t i = 0; i < _size; i++) {
        new_allocator[i] = _allocator[position];
        position = next_index(position);
    }
    delete[] _allocator;
    _first = 0;
    _last = _size > 0 ? _size - 1 : 0;
    _allocator = new_allocator;
    _capacity /= SHRINK_FRACTION;
}

template <typename T>
void Deque<T>::push_front(const T &value)
{
    if (needs_grow())
        grow();
    if (!empty())
        _first = prev_index(_first);
    _allocator[_first] = value;
    _size++;
}

template <typename T>
void Deque<T>::push_back(const T &value)
{
    if (needs_grow())
        grow();
    if (!empty())
        _last = next_index(_last);
    _allocator[_last] = value;
    _size++;
}

template <typename T>
Option<T> Deque<T>::pop_front()
{
    if (empty())
        return Nothing();
    Option<T> result = Some(_allocator[_first]);
    _first = next_index(_first);
    _size--;
    if (_size == 0)
        _first = _last = 0;
    if (needs_shrink())
        shrink();
    return result;
}

template <typename T>
Option<T> Deque<T>::pop_back()
{
    if (empty())
        return Nothing();
    Option<T> result = Some(_allocator[_last]);
    _last = prev_index(_last);
    _size--;
    if (_size == 0)
        _first = _last = 0;
    if (needs_shrink())
        shrink();
    return result;
}

#endif //DEQUE_H
