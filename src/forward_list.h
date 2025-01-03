//
// Created by kyrylo on 03/01/25.
//

#ifndef FORWARD_LIST_H
#define FORWARD_LIST_H

#include <stdlib.h>

typedef struct str_forward_list forward_list;

forward_list *create_forward_list();
void destroy_forward_list(forward_list*);

int forward_list_front(const forward_list*);
void forward_list_push_front(forward_list*, int);
int forward_list_pop_front(forward_list*);

int forward_list_empty(const forward_list*);
size_t forward_list_size(const forward_list*);
forward_list *forward_list_reverse(const forward_list*);

#endif //FORWARD_LIST_H
