//
// Created by kyrylo on 02/01/25.
//

#ifndef QUEUE_H
#define QUEUE_H

#include "deque.h"

typedef struct str_queue queue;

queue *create_queue();
void destroy_queue(queue*);

int queue_empty(const queue*);
size_t queue_size(const queue*);

void queue_swap(queue*, queue*);

int queue_front(const queue*);
int queue_back(const queue*);

void queue_push(queue*, int);
void queue_pop(queue*);

#endif //QUEUE_H
