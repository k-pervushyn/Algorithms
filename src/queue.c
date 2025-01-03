//
// Created by kyrylo on 02/01/25.
//

#include "queue.h"

struct str_queue {
    deque *_deque;
};

queue *create_queue()
{
    queue *_queue = malloc(sizeof(queue));
    _queue->_deque = create_deque();
    return _queue;
}

void destroy_queue(queue *_queue)
{
    destroy_deque(_queue->_deque);
    free(_queue);
}

int queue_empty(const queue *_queue) { return deque_empty(_queue->_deque); }
size_t queue_size(const queue *_queue) { return deque_size(_queue->_deque); }

void queue_swap(queue *_fst, queue *_snd)
{
    deque *tmp = _fst->_deque;
    _fst->_deque = _snd->_deque;
    _snd->_deque = tmp;
}

int queue_front(const queue *_queue) { return deque_front(_queue->_deque); }
int queue_back(const queue *_queue) { return deque_back(_queue->_deque); }

void queue_push(queue *_queue, const int _data) { deque_push_back(_queue->_deque, _data); }
void queue_pop(queue *_queue) { deque_pop_front(_queue->_deque); }
