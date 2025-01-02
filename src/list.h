//
// Created by kyrylo on 02/01/25.
//

#ifndef LIST_H
#define LIST_H

#include <stdlib.h>

typedef struct list list;

list *create_list();
void destroy_list(list*);

int front(const list*);
int back(const list*);
void push_front(list*, const int);
void push_back(list*, const int);
int pop_front(list*);
int pop_back(list*);

int empty(const list*);
size_t size(const list*);
list *reverse(const list*);

#endif //LIST_H
