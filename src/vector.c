//
// Created by kyrylo on 02/01/25.
//

#include "vector.h"

#define INITIAL_CAPACITY 2

struct vector {
    int *_allocator;
    size_t _size;
    size_t _capacity;
};

vector *create_vector(const size_t capacity)
{
    vector *_vector = malloc(sizeof(vector));
    _vector->_allocator = malloc(capacity * sizeof(int));
    _vector->_capacity = capacity;
    _vector->_size = 0;
    return _vector;
}

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

int get(const vector *_vector, const size_t _position)
{
    if (_position < _vector->_size)
        return _vector->_allocator[_position];
    return -1;
}

void set(vector *_vector, const size_t _position, const int _value)
{
    if (_position < _vector->_size)
        _vector->_allocator[_position] = _value;
    // error: no element on this position
}

int front(const vector *_vector)
{
    if (_vector->_size > 0)
        return _vector->_allocator[0];
    return -1; // error: empty list
}

int back(const vector *_vector)
{
    if (_vector->_size > 0)
        return _vector->_allocator[_vector->_size - 1];
    return -1; // error: empty list
}

void grow(vector *_vector)
{
    int *_new_allocator = malloc(2 * _vector->_capacity * sizeof(int));
    for (int i = 0; i < _vector->_size; i++)
        _new_allocator[i] = _vector->_allocator[i];
    free(_vector->_allocator);
    _vector->_allocator = _new_allocator;
    _vector->_capacity = 2 * _vector->_capacity;
}

void shrink(vector *_vector)
{
    int *_new_allocator = malloc(_vector->_capacity * sizeof(int) / 2);
    for (int i = 0; i < _vector->_capacity / 2; i++)
        _new_allocator[i] = _vector->_allocator[i];
    free(_vector->_allocator);
    _vector->_allocator = _new_allocator;
    _vector->_capacity = _vector->_capacity / 2;
}

void push_back(vector *_vector, const int _value)
{
    if (_vector->_size >= _vector->_capacity)
        shrink(_vector);
    _vector->_allocator[_vector->_size++] = _value;
}

int pop_back(vector *_vector)
{

}

size_t size(const vector *_vector) { return _vector->_size; }
size_t capacity(const vector*);

void insert(vector*, size_t, int);
void erase(vector*, size_t);

void shrink_to_fit(vector *_vector)
{
    int *_new_allocator = malloc(_vector->_size);
    for (int i = 0; i < _vector->_size; i++)
        _new_allocator[i] = _vector->_allocator[i];
    free(_vector->_allocator);
    _vector->_allocator = _new_allocator;
    _vector->_capacity = _vector->_size;
}
