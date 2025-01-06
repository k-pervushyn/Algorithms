//
// Created by kyrylo on 02/01/25.
//

#include "deque.h"

#define INITIAL_CAPACITY 2

struct str_deque {
    int *_allocator;
    size_t _size;
    size_t _capacity;
    size_t _first;
    size_t _last;
};

deque *create_deque()
{
    deque *_deque = malloc(sizeof(deque));
    _deque->_allocator = malloc(INITIAL_CAPACITY * sizeof(int));
    _deque->_capacity = INITIAL_CAPACITY;
    _deque->_size = 0;
    _deque->_first = 0;
    _deque->_last = 0;
    return _deque;
}

void destroy_deque(deque *_deque)
{
    free(_deque->_allocator);
    free(_deque);
}

int deque_front(const deque *_deque)
{
    if (deque_empty(_deque))
        return -1; // error: empty deque
    return _deque->_allocator[_deque->_first];
}

int deque_back(const deque *_deque)
{
    if (deque_empty(_deque))
        return -1; // error: empty deque
    return _deque->_allocator[_deque->_last];
}

size_t deque_next_index(const deque *_deque, size_t _index)
{
    _index = _index % _deque->_capacity;
    return _index == _deque->_capacity - 1 ? 0 : _index + 1;
}

size_t deque_prev_index(const deque *_deque, size_t _index)
{
    _index = _index % _deque->_capacity;
    return _index == 0 ? _deque->_capacity - 1 : _index - 1;
}

int deque_needs_grow(const deque *_deque)
{
    if (_deque->_size == _deque->_capacity) {
#ifdef M_DEBUG
        assert(deque_next_index(_deque, _deque->_last) == _deque->_first);
        assert(deque_prev_index(_deque, _deque->_first) == _deque->_last);
#endif
        return 1;
    }
#ifdef M_DEBUG
    assert(deque_next_index(_deque, _deque->_last) != _deque->_first);
    assert(deque_prev_index(_deque, _deque->_first) != _deque->_last);
#endif
    return 0;
}

int deque_needs_shrink(const deque *_deque)
{
    return _deque->_size <= _deque->_capacity / 4 && _deque->_capacity / 4 >= INITIAL_CAPACITY;
}

void deque_grow(deque *_deque)
{
    int *_new_allocator = malloc(2 * _deque->_capacity * sizeof(int));
    size_t position = _deque->_first;
    for (size_t i = 0; i < _deque->_size; i++) {
        _new_allocator[i] = _deque->_allocator[position];
        position = deque_next_index(_deque, position);
    }
    free(_deque->_allocator);
    _deque->_first = 0;
    _deque->_last = _deque->_size > 0 ? _deque->_size - 1 : 0;
    _deque->_allocator = _new_allocator;
    _deque->_capacity = 2 * _deque->_capacity;
}

void deque_shrink(deque *_deque)
{
    int *_new_allocator = malloc(_deque->_capacity * sizeof(int) / 2);
    size_t position = _deque->_first;
    for (size_t i = 0; i < _deque->_size; i++) {
        _new_allocator[i] = _deque->_allocator[position];
        position = deque_next_index(_deque, position);
    }
    free(_deque->_allocator);
    _deque->_first = 0;
    _deque->_last = _deque->_size > 0 ? _deque->_size - 1 : 0;
    _deque->_allocator = _new_allocator;
    _deque->_capacity = _deque->_capacity / 2;
}

void deque_push_front(deque *_deque, const int _value)
{
    if (deque_needs_grow(_deque))
        deque_grow(_deque);
    if (!deque_empty(_deque))
        _deque->_first = deque_prev_index(_deque, _deque->_first);
    _deque->_allocator[_deque->_first] = _value;
    _deque->_size++;
}

void deque_push_back(deque *_deque, const int _value)
{
    if (deque_needs_grow(_deque))
        deque_grow(_deque);
    if (!deque_empty(_deque))
        _deque->_last = deque_next_index(_deque, _deque->_last);
    _deque->_allocator[_deque->_last] = _value;
    _deque->_size++;
}

int deque_pop_front(deque *_deque)
{
    if (deque_empty(_deque))
        return -1; // error: empty deque
    const int result = _deque->_allocator[_deque->_first];
    _deque->_first = deque_next_index(_deque, _deque->_first);
    _deque->_size--;
    if (_deque->_size == 0)
        _deque->_first = _deque->_last = 0;
    if (deque_needs_shrink(_deque))
        deque_shrink(_deque);
    return result;
}

int deque_pop_back(deque *_deque)
{
    if (deque_empty(_deque))
        return -1; // error: empty deque
    const int result = _deque->_allocator[_deque->_last];
    _deque->_last = deque_prev_index(_deque, _deque->_last);
    _deque->_size--;
    if (_deque->_size == 0)
        _deque->_first = _deque->_last = 0;
    if (deque_needs_shrink(_deque))
        deque_shrink(_deque);
    return result;
}

size_t deque_size(const deque *_deque) { return _deque->_size; }
size_t deque_capacity(const deque *_deque) { return _deque->_capacity; }

int deque_empty(const deque *_deque)
{
#ifdef M_DEBUG
    if (_deque->_size == 0) {
        assert(_deque->_first == 0);
        assert(_deque->_last == 0);
    }
#endif
    return _deque->_size == 0;
}

void deque_shrink_to_fit(deque *_deque)
{
    if (_deque->_size <= INITIAL_CAPACITY)
        return;
    int *_new_allocator = malloc(_deque->_size*sizeof(int));
    size_t position = _deque->_first;
    for (size_t i = 0; i < _deque->_size; i++) {
        _new_allocator[i] = _deque->_allocator[position];
        position = deque_next_index(_deque, position);
    }
   free(_deque->_allocator);
    _deque->_first = 0;
    _deque->_last = _deque->_size - 1;
    _deque->_allocator = _new_allocator;
    _deque->_capacity = _deque->_size;
}
