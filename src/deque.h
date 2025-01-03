//
// Created by kyrylo on 03/01/25.
//

#ifndef DEQUE_H
#define DEQUE_H

#define M_DEBUG

#ifdef M_DEBUG
#include <assert.h>
#endif
#include <stdlib.h>

typedef struct str_deque deque;

deque *create_deque();
void destroy_deque(deque*);

int deque_front(const deque*);
int deque_back(const deque*);

void deque_push_front(deque*, const int);
void deque_push_back(deque*, const int);
int deque_pop_front(deque*);
int deque_pop_back(deque*);

size_t deque_size(const deque*);
size_t deque_capacity(const deque*);
int deque_empty(const deque*);

void deque_shrink_to_fit(deque*);

#endif //DEQUE_H
