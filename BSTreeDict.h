#ifndef BSTREEDICT_H
#define BSTREEDICT_H

#include <ostream>
#include <stdexcept>
#include "Dict.h"
#include "BSTree.h"
#include "TableEntry.h"

template <typename V>
class BSTreeDict : public Dict<V> {
private:
    BSTree<TableEntry<V>> tree;   // ABB con entradas clave->valor

public:
    BSTreeDict() {}

    // INSERT — debe lanzar std::runtime_error si la clave ya existe
    void insert(const std::string &key, const V &value) override {
        TableEntry<V> entry(key, value);

        if (tree.search(entry)) {
            throw std::runtime_error("Clave duplicada");
        }

        tree.insert(entry);
    }

    // CONTAINS
    bool contains(const std::string &key) const override {
        return tree.search(TableEntry<V>(key, V()));
    }

    // ERASE
    bool erase(const std::string &key) override {
        if (!contains(key)) return false;
        tree.remove(TableEntry<V>(key, V()));
        return true;
    }

    // AT (mutable)
    V &at(const std::string &key) override {
        return tree.at(TableEntry<V>(key, V())).getValue();
    }

    // AT (const)
    const V &at(const std::string &key) const override {
        return tree.at(TableEntry<V>(key, V())).getValue();
    }

    // SIZE
    int size() const override {
        return tree.size();
    }

    // EMPTY
    bool empty() const override {
        return tree.size() == 0;
    }

    // EXTRA: entries() — lo pide testBSTreeDict.cpp
    int entries() {
        return size();
    }

    // EXTRA: search() — lo pide testBSTreeDict.cpp
    V search(const std::string &key) {
        return at(key);
    }

    // EXTRA: remove() — lo pide testBSTreeDict.cpp
    V remove(const std::string &key) {
        V val = at(key);
        erase(key);
        return val;
    }

    // operator[]
    V operator[](const std::string &key) {
        return at(key);
    }

    // operator<<
    friend std::ostream& operator<<(std::ostream &out, const BSTreeDict<V> &bs) {
        out << bs.tree;
        return out;
    }
};

#endif

