//
// Created by kyrylo on 06/01/25.
//

#ifndef OPTION_H
#define OPTION_H

struct Nothing {
    Nothing() = default;
    Nothing (const Nothing&) = delete;
    Nothing& operator=(const Nothing&) = delete;
};

template <class T>
class Option {
    bool _has;
    T *_value;

public:
    Option(const Nothing &nothing) : _has(false), _value(nullptr) { }
    Option(const T &value) : _has(true), _value(nullptr) { _value = new T(value); }

    Option(const Option<T> &that);
    Option<T> &operator=(const Option<T> &that);

    ~Option() { if (_has) delete _value; }

    inline bool has() const { return _has; }
    inline const T &get() const { return *_value; }
};

template<class T>
Option<T>::Option(const Option<T> &that): _has(that._has), _value(nullptr)
{
    if (that._has)
        _value = new T(*that._value);
}

template<class T>
Option<T> & Option<T>::operator=(const Option<T> &that)
{
    if (this == &that)
        return *this;
    if (_has)
        delete _value;
    _has = that._has;
    if (_has)
        _value = new T(*that._value);
    return *this;
}

template <class T>
Option<T> Some(const T &value) { return Option<T>(value); }

#endif //OPTION_H
