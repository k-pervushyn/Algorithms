//
// Created by kyrylo on 02/01/25.
//

#ifndef VECTOR_H
#define VECTOR_H

#include <stdlib.h>

typedef struct vector vector;

vector *create_vector();
vector *create_vector(const size_t capacity);
void destroy_vector(vector *v);

int get(const vector*, const size_t);
void set(vector*, const size_t, const int);

int front(const vector*);
int back(const vector*);
void push_back(vector*, const int);
int pop_back(vector*);

size_t size(const vector*);
size_t capacity(const vector*);

void insert(vector*, const size_t, const int);
void erase(vector*, const size_t);

void shrink_to_fit(vector*);

#endif //VECTOR_H
