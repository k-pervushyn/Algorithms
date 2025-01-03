//
// Created by kyrylo on 02/01/25.
//

#include "forward_list.h"

typedef struct str_node {
    int _data;
    struct str_node *_next;
} node;

struct str_forward_list {
    node *_head;
    size_t _size;
};

forward_list *create_forward_list()
{
    forward_list *_list = (forward_list *)malloc(sizeof(forward_list));
    _list->_head = NULL;
    _list->_size = 0;
    return _list;
}

void destroy_forward_list(forward_list *_list)
{
    while (_list->_head) {
        node *tmp = _list->_head;
        _list->_head = _list->_head->_next;
        free(tmp);
    }
    free(_list);
}

int forward_list_front(const forward_list *_list)
{
    if (!_list->_head)
        return -1; // error: empty list
    return _list->_head->_data;
}

void forward_list_push_front(forward_list *_list, const int _data)
{
    node *new_node = (node *)malloc(sizeof(node));
    new_node->_next = _list->_head;
    new_node->_data = _data;
    _list->_head = new_node;
    _list->_size++;
}

int forward_list_pop_front(forward_list *_list)
{
    if (!_list->_head)
        return -1; // error: empty list
    node *tmp = _list->_head;
    _list->_head = _list->_head->_next;
    const int result = tmp->_data;
    free(tmp);
    _list->_size--;
    return result;
}

int forward_list_empty(const forward_list *_list) { return _list->_size == 0; }
size_t forward_list_size(const forward_list *_list) { return _list->_size; }

forward_list *forward_list_reverse(const forward_list *_list)
{
    forward_list *_reversed = create_forward_list();
    const node *tmp = _list->_head;
    while (tmp) {
        forward_list_push_front(_reversed, tmp->_data);
        tmp = tmp->_next;
    }
    return _reversed;
}
