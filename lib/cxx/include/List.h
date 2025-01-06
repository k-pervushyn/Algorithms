//
// Created by kyrylo on 04/01/25.
//

#ifndef LIST_H
#define LIST_H

#include "Option.h"

template <typename T>
class List {
    struct node {
        T _data;
        node *_next;
        node *_prev;
        node(const T &data) : _data(data), _next(nullptr), _prev(nullptr) { }
    };

    node *_head;
    node *_tail;
    size_t _size;

public:
    List();
    List(const List<T>&);
    List<T>& operator=(const List<T>&);

    ~List();

    void clear();

    Option<T> front() const;
    Option<T> back() const;

    void push_front(const T&);
    void push_back(const T&);

    Option<T> pop_front();
    Option<T> pop_back();

    bool empty() const { return _size == 0; }
    size_t size() const { return _size; }
    List<T> reverse() const;
};

template <typename T>
List<T>::List() : _head(nullptr), _tail(nullptr), _size(0) { }

template <typename T>
List<T>::List(const List<T> &other) : _head(nullptr), _tail(nullptr), _size(0)
{
    const node *current = other._head;
    while (current) {
        push_back(current->_data);
        current = current->_next;
    }
}

template <typename T>
List<T> &List<T>::operator=(const List<T> &other)
{
    if (this == &other)
        return *this;
    clear();
    const node *current = other._head;
    while (current) {
        push_back(current->_data);
        current = current->_next;
    }
    return *this;
}

template <typename T>
List<T>::~List()
{
    clear();
}

template <typename T>
void List<T>::clear()
{
    while (_head) {
        const node *tmp = _head;
        _head = _head->_next;
        delete tmp;
    }
    _size = 0;
    _tail = nullptr;
}

template <typename T>
Option<T> List<T>::front() const
{
    if (empty())
        return Nothing();
    return Some(_head->_data);
}

template <typename T>
Option<T> List<T>::back() const
{
    if (empty())
        return Nothing();
    return Some(_tail->_data);
}

template <typename T>
void List<T>::push_front(const T &value)
{
    if (!_head) {
        _head = new node(value);
        _tail = _head;
    } else {
        node *new_node = new node(value);
        new_node->_next = _head;
        _head->_prev = new_node;
        _head = new_node;
    }
    _size++;
}

template <typename T>
void List<T>::push_back(const T &value)
{
    if (!_tail) {
        _tail = new node(value);
        _head = _tail;
    } else {
        node *new_node = new node(value);
        new_node->_prev = _tail;
        _tail->_next = new_node;
        _tail = new_node;
    }
    _size++;
}

template <typename T>
Option<T> List<T>::pop_front()
{
    if (!_head)
        return Nothing();
    node *_tmp = _head;
    _head = _head->_next;
    if (!_head)
        _tail = nullptr;
    else
        _head->_prev = nullptr;
    Option<T> result = Some(_tmp->_data);
    delete _tmp;
    _size--;
    return result;
}

template <typename T>
Option<T> List<T>::pop_back()
{
    if (!_tail)
        return Nothing();
    node *_tmp = _tail;
    _tail = _tail->_prev;
    if (!_tail)
        _head = nullptr;
    else
        _tail->_next = nullptr;
    Option<T> result = Some(_tmp->_data);
    delete _tmp;
    _size--;
    return result;
}

template <typename T>
List<T> List<T>::reverse() const
{
    List<T> result;
    const node *tmp = _head;
    while (tmp) {
        result.push_front(tmp->_data);
        tmp = tmp->_next;
    }
    return result;
}

#endif //LIST_H
