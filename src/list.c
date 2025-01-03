//
// Created by kyrylo on 02/01/25.
//

#include "list.h"

typedef struct str_node {
    int _data;
    struct str_node *_next;
    struct str_node *_prev;
} node;

struct str_list {
    node *_head;
    node *_tail;
    size_t _size;
};

list *create_list()
{
    list *_list = malloc(sizeof(list));
    _list->_head = NULL;
    _list->_tail = NULL;
    _list->_size = 0;
    return _list;
}

void destroy_list(list *_list)
{
    if (_list) {
        while (_list->_head) {
            node *tmp = _list->_head;
            _list->_head = _list->_head->_next;
            free(tmp);
        }
        free(_list);
        _list = NULL;
    }
}

int list_front(const list *_list)
{
    if (_list->_head)
        return _list->_head->_data;
    return -1;
}

int list_back(const list *_list)
{
    if (_list->_tail)
        return _list->_tail->_data;
    return -1;
}

void list_push_front(list *_list, const int _data)
{
    if (!_list->_head) {
        _list->_head = malloc(sizeof(node));
        _list->_tail = _list->_head;
        _list->_head->_next = NULL;
        _list->_head->_prev = NULL;
    } else {
        node *new_node = malloc(sizeof(node));
        new_node->_next = _list->_head;
        new_node->_prev = NULL;
        _list->_head->_prev = new_node;
        _list->_head = new_node;
    }
    _list->_head->_data = _data;
    _list->_size++;
}

void list_push_back(list *_list, const int _data)
{
     if (!_list->_tail) {
        _list->_tail = malloc(sizeof(node));
        _list->_head = _list->_tail;
        _list->_tail->_next = NULL;
        _list->_tail->_prev = NULL;
    } else {
        node *new_node = malloc(sizeof(node));
        new_node->_prev = _list->_tail;
        new_node->_next = NULL;
        _list->_tail->_next = new_node;
        _list->_tail = new_node;
    }
    _list->_tail->_data = _data;
    _list->_size++;
}

int list_pop_front(list *_list)
{
    if (!_list->_head)
        return -1;
    node *tmp = _list->_head;
    _list->_head = _list->_head->_next;
    if (!_list->_head)
        _list->_tail = NULL;
    else
        _list->_head->_prev = NULL;
    const int value = tmp->_data;
    free(tmp);
    _list->_size--;
    return value;
}

int list_pop_back(list *_list)
{
     if (!_list->_tail)
        return -1;
    node *tmp = _list->_tail;
    _list->_tail = _list->_tail->_prev;
    if (!_list->_tail)
        _list->_head = NULL;
    else
        _list->_tail->_next = NULL;
    const int value = tmp->_data;
    free(tmp);
    _list->_size--;
    return value;
}

int list_empty(const list *_list) { return _list->_head ? 0 : 1; }
size_t list_size(const list *_list) { return _list->_size; }

list *list_reverse(const list *_list)
{
    list *_reversed = create_list();
    const node *tmp = _list->_head;
    while (tmp) {
        list_push_front(_reversed, tmp->_data);
        tmp = tmp->_next;
    }
    return _reversed;
}
