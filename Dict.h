#ifndef DICT_H
#define DICT_H

#include <string>

template <typename V>
class Dict {
public:
    virtual ~Dict() {}

    virtual void insert(const std::string &key, const V &value) = 0;
    virtual bool contains(const std::string &key) const = 0;
    virtual bool erase(const std::string &key) = 0;

    virtual V &at(const std::string &key) = 0;
    virtual const V &at(const std::string &key) const = 0;

    virtual int size() const = 0;
    virtual bool empty() const = 0;
};

#endif // DICT_H

