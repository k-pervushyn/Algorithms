//
// Created by kyrylo on 06/01/25.
//

#ifndef FORWARD_LIST_H
#define FORWARD_LIST_H

#include "Option.h"

template <typename T>
class ForwardList {
    struct node {
        T _data;
        node *_next;

        node(const T &data) : _data(data), _next(nullptr) { }
    };

    node *_head;
    size_t _size;

public:
    ForwardList();
    ForwardList(const ForwardList<T> &);
    ForwardList<T> &operator=(const ForwardList<T> &);

    ~ForwardList();

    void clear();

    Option<T> front() const;
    void push_front(const T&);
    Option<T> pop_front();

    bool empty() const { return _size == 0; }
    size_t size() const { return _size; }
    ForwardList<T> reverse() const;
};

template <typename T>
ForwardList<T>::ForwardList() : _head(nullptr), _size(0) { }

template <typename T>
ForwardList<T>::ForwardList(const ForwardList<T> &that) : _head(nullptr), _size(0)
{
    const node *current = that._head;
    node *last = nullptr;
    while (current) {
        if (last != nullptr) {
            last->_next = new node(current->_data);
            last = last->_next;
        } else {
            last = new node(current->_data);
            _head = last;
        }
        current = current->_next;
        _size++;
    }
}

template <typename T>
ForwardList<T> &ForwardList<T>::operator=(const ForwardList<T> &that)
{
    if (this == &that)
        return *this;
    clear();
    const node *current = that._head;
    node *last = nullptr;
    while (current) {
        if (last != nullptr) {
            last->_next = new node(current->_data);
            last = last->_next;
        } else {
            last = new node(current->_data);
            _head = last;
        }
        current = current->_next;
        _size++;
    }
    return *this;
}

template <typename T>
ForwardList<T>::~ForwardList()
{
    clear();
}

template<typename T>
void ForwardList<T>::clear()
{
    while (_head) {
        const node *tmp = _head;
        _head = _head->_next;
        delete tmp;
    }
    _size = 0;
}

template<typename T>
Option<T> ForwardList<T>::front() const
{
    if (empty())
        return Nothing();
    return Some(_head->_data);
}

template<typename T>
void ForwardList<T>::push_front(const T &value)
{
    node *new_node = new node(value);
    new_node->_next = _head;
    _head = new_node;
    _size++;
}

template<typename T>
Option<T> ForwardList<T>::pop_front()
{
    if (empty())
        return Nothing();
    node *tmp = _head;
    _head = _head->_next;
    Option<T> result = Some(tmp->_data);
    delete tmp;
    _size--;
    return result;
}

template<typename T>
ForwardList<T> ForwardList<T>::reverse() const
{
    ForwardList<T> reversed;
    const node *tmp = _head;
    while (tmp) {
        reversed.push_front(tmp->_data);
        tmp = tmp->_next;
    }
    return reversed;
}

#endif //FORWARD_LIST_H
