#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <vector>
#include <string>
#include <list>
#include <iostream>
#include <stdexcept>
#include "Dict.h"
#include "TableEntry.h"

template <typename V>
class HashTable : public Dict<V> {
private:
    int bucketCount;
    int numElements;
    std::vector<std::list<TableEntry<V>>> table;

    // 🔥 FUNCIÓN HASH EXACTA DEL PROFESOR (suma ASCII)
    int hash(const std::string &key) const {
        int sum = 0;
        for (char c : key)
            sum += c;
        return sum % bucketCount;
    }

    template <typename U>
    friend std::ostream& operator<<(std::ostream&, const HashTable<U>&);

public:
    HashTable(int buckets = 3)
        : bucketCount(buckets), numElements(0), table(buckets) {}

    virtual ~HashTable() {}

    int capacity() const {
        return bucketCount;
    }

    int entries() const {
        return numElements;
    }

    // search: devuelve valor o lanza error
    V search(const std::string &key) const {
        int idx = hash(key);
        for (const auto &entry : table[idx]) {
            if (entry.getKey() == key)
                return entry.getValue();
        }
        throw std::runtime_error("Key '" + key + "' not found!");
    }

    // operator[]
    V &operator[](const std::string &key) {
        int idx = hash(key);
        for (auto &entry : table[idx]) {
            if (entry.getKey() == key)
                return entry.getValue();
        }
        throw std::runtime_error("Key '" + key + "' not found!");
    }

    // remove: devuelve valor borrado o lanza error
    V remove(const std::string &key) {
        int idx = hash(key);
        auto &bucket = table[idx];

        for (auto it = bucket.begin(); it != bucket.end(); ++it) {
            if (it->getKey() == key) {
                V val = it->getValue();
                bucket.erase(it);
                numElements--;
                return val;
            }
        }
        throw std::runtime_error("Key '" + key + "' not found!");
    }

    // insert: lanza error si ya existe
    void insert(const std::string &key, const V &value) override {
        int idx = hash(key);
        auto &bucket = table[idx];

        for (auto &entry : bucket) {
            if (entry.getKey() == key)
                throw std::runtime_error("Key '" + key + "' already exists!");
        }

        bucket.emplace_back(key, value);
        numElements++;
    }

    bool contains(const std::string &key) const override {
        int idx = hash(key);
        for (const auto &entry : table[idx]) {
            if (entry.getKey() == key)
                return true;
        }
        return false;
    }

    bool erase(const std::string &key) override {
        int idx = hash(key);
        auto &bucket = table[idx];

        for (auto it = bucket.begin(); it != bucket.end(); ++it) {
            if (it->getKey() == key) {
                bucket.erase(it);
                numElements--;
                return true;
            }
        }
        return false;
    }

    V &at(const std::string &key) override {
        return (*this)[key];
    }

    const V &at(const std::string &key) const override {
        int idx = hash(key);
        for (const auto &entry : table[idx]) {
            if (entry.getKey() == key)
                return entry.getValue();
        }
        throw std::runtime_error("Key '" + key + "' not found!");
    }

    int size() const override {
        return numElements;
    }

    bool empty() const override {
        return numElements == 0;
    }
};

// -------------------------
// operator<< EXACTO COMO EL PROFESOR LO QUIERE
// -------------------------
template <typename V>
std::ostream &operator<<(std::ostream &os, const HashTable<V> &ht) {
    os << "HashTable [entries: " << ht.entries()
       << ", capacity: " << ht.capacity() << "]\n";
    os << "==============\n\n";

    for (int i = 0; i < ht.capacity(); i++) {
        os << "== Cubeta " << i << " ==\n\n";
        os << "List => [";

        if (!ht.table[i].empty()) {
            os << "\n";
            for (const auto &entry : ht.table[i]) {
                os << "  ('" << entry.getKey()
                   << "' => " << entry.getValue() << ")\n";
            }
        }

        os << "]\n\n";
    }

    os << "==============\n";
    return os;
}

#endif

