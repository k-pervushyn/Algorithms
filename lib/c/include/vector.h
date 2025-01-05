//
// Created by kyrylo on 02/01/25.
//

#ifndef VECTOR_H
#define VECTOR_H

#include <stdlib.h>

typedef struct str_vector vector;

vector *create_vector();
void destroy_vector(vector*);

int vector_get(const vector*, const size_t);
void vector_set(vector*, const size_t, const int);

int vector_front(const vector*);
int vector_back(const vector*);
void vector_push_back(vector*, const int);
int vector_pop_back(vector*);

size_t vector_size(const vector*);
size_t vector_capacity(const vector*);

void vector_insert(vector*, const size_t, const int);
void vector_erase(vector*, const size_t);

void vector_shrink_to_fit(vector*);

#endif //VECTOR_H
