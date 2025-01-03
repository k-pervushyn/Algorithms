//
// Created by kyrylo on 02/01/25.
//

#ifndef STACK_H
#define STACK_H

#include "deque.h"

typedef struct str_stack stack;

stack *create_stack();
void destroy_stack(stack*);

int stack_empty(const stack*);
size_t stack_size(const stack*);

void stack_swap(stack*, stack*);

int stack_top(const stack*);

void stack_push(stack*, int);
void stack_pop(stack*);

#endif //STACK_H
