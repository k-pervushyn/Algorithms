//
// Created by kyrylo on 02/01/25.
//

#ifndef LIST_H
#define LIST_H

#include <stdlib.h>

typedef struct str_list list;

list *create_list();
void destroy_list(list*);

int list_front(const list*);
int list_back(const list*);
void list_push_front(list*, const int);
void list_push_back(list*, const int);
int list_pop_front(list*);
int list_pop_back(list*);

int list_empty(const list*);
size_t list_size(const list*);
list *list_reverse(const list*);

#endif //LIST_H
