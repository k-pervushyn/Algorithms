//
// Created by kyrylo on 02/01/25.
//

#include "stack.h"

struct str_stack {
    deque *_deque;
};

stack *create_stack()
{
    stack *_stack = malloc(sizeof(stack));
    _stack->_deque = create_deque();
    return _stack;
}

void destroy_stack(stack *_stack)
{
    destroy_deque(_stack->_deque);
    free(_stack);
}

int stack_empty(const stack *_stack) { return deque_empty(_stack->_deque); }
size_t stack_size(const stack *_stack) { return deque_size(_stack->_deque); }

void stack_swap(stack *_fst, stack *_snd)
{
    deque *tmp = _fst->_deque;
    _fst->_deque = _snd->_deque;
    _snd->_deque = tmp;
}

int stack_top(const stack *_stack) { return deque_back(_stack->_deque); }
void stack_push(stack *_stack, const int _data) { return deque_push_back(_stack->_deque, _data); }
void stack_pop(stack *_stack) { deque_pop_back(_stack->_deque); }
