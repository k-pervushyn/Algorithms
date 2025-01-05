//
// Created by kyrylo on 02/01/25.
//

#include "vector.h"

#define INITIAL_CAPACITY 2

struct str_vector {
    int *_allocator;
    size_t _size;
    size_t _capacity;
};

vector *create_vector()
{
    vector *_vector = malloc(sizeof(vector));
    _vector->_allocator = malloc(INITIAL_CAPACITY * sizeof(int));
    _vector->_capacity = INITIAL_CAPACITY;
    _vector->_size = 0;
    return _vector;
}

void destroy_vector(vector *_vector)
{
    free(_vector->_allocator);
    free(_vector);
}

int vector_get(const vector *_vector, const size_t _position)
{
    if (_position >= _vector->_size)
        return -1; // error: position out of range
    return _vector->_allocator[_position];
}

void vector_set(vector *_vector, const size_t _position, const int _value)
{
    if (_position >= _vector->_size)
        return; // error: position out of range
    _vector->_allocator[_position] = _value;
}

int vector_front(const vector *_vector)
{
    if (_vector->_size == 0)
        return -1; // error: empty list
    return _vector->_allocator[0];
}

int vector_back(const vector *_vector)
{
    if (_vector->_size == 0)
        return -1; // error: empty list
    return _vector->_allocator[_vector->_size - 1];
}

int vector_needs_grow(const vector *_vector) { return _vector->_size == _vector->_capacity; }
int vector_needs_shrink(const vector *_vector)
{
    return _vector->_size <= _vector->_capacity / 4 && _vector->_capacity / 4 >= INITIAL_CAPACITY;
}

void vector_grow(vector *_vector)
{
    int *_new_allocator = malloc(2 * _vector->_capacity * sizeof(int));
    for (size_t i = 0; i < _vector->_size; i++)
        _new_allocator[i] = _vector->_allocator[i];
    free(_vector->_allocator);
    _vector->_allocator = _new_allocator;
    _vector->_capacity = 2 * _vector->_capacity;
}

void vector_shrink(vector *_vector)
{
    int *_new_allocator = malloc(_vector->_capacity * sizeof(int) / 2);
    for (size_t i = 0; i < _vector->_capacity / 2; i++)
        _new_allocator[i] = _vector->_allocator[i];
    free(_vector->_allocator);
    _vector->_allocator = _new_allocator;
    _vector->_capacity = _vector->_capacity / 2;
}

void vector_push_back(vector *_vector, const int _value)
{
    if (vector_needs_grow(_vector))
        vector_grow(_vector);
    _vector->_allocator[_vector->_size++] = _value;
}

int vector_pop_back(vector *_vector)
{
    const int result = _vector->_allocator[--_vector->_size];
    if (vector_needs_shrink(_vector))
        vector_shrink(_vector);
    return result;
}

size_t vector_size(const vector *_vector) { return _vector->_size; }
size_t vector_capacity(const vector *_vector) { return _vector->_capacity; }

void vector_insert(vector *_vector, const size_t position, const int value)
{
    if (position > _vector->_size)
        return; // error: position out of range
    if (vector_needs_grow(_vector))
        vector_grow(_vector);
    for (size_t i = _vector->_size; i > position; i--)
        _vector->_allocator[i] = _vector->_allocator[i - 1];
    _vector->_allocator[position] = value;
    _vector->_size++;
}

void vector_erase(vector *_vector, const size_t position)
{
    if (position >= _vector->_size)
        return; // error: position out of range
    for (size_t i = position; i < _vector->_size - 1; i++)
        _vector->_allocator[i] = _vector->_allocator[i + 1];
    _vector->_size--;
    if (vector_needs_shrink(_vector))
        vector_shrink(_vector);
}

void vector_shrink_to_fit(vector *_vector)
{
    if (_vector->_size <= INITIAL_CAPACITY)
        return;
    int *_new_allocator = malloc(_vector->_size*sizeof(int));
    for (size_t i = 0; i < _vector->_size; i++)
        _new_allocator[i] = _vector->_allocator[i];
    free(_vector->_allocator);
    _vector->_allocator = _new_allocator;
    _vector->_capacity = _vector->_size;
}
