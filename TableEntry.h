#ifndef TABLE_ENTRY_H
#define TABLE_ENTRY_H

#include <string>
#include <iostream>

template <typename V>
class TableEntry {
private:
    std::string key;
    V value;

public:
    TableEntry() {}

    TableEntry(const std::string &k, const V &v)
        : key(k), value(v) {}

    const std::string &getKey() const {
        return key;
    }

    const V &getValue() const {
        return value;
    }

    V &getValue() {
        return value;
    }

    void setValue(const V &v) {
        value = v;
    }

    bool operator==(const TableEntry<V> &other) const {
        return key == other.key;
    }

    bool operator!=(const TableEntry<V> &other) const {
        return !(*this == other);
    }

    // NECESARIO PARA EL ABB
    bool operator<(const TableEntry<V> &other) const {
        return key < other.key;
    }

    bool operator>(const TableEntry<V> &other) const {
        return key > other.key;
    }
};

// operador <<
template <typename V>
std::ostream& operator<<(std::ostream& os, const TableEntry<V>& entry) {
    os << "(" << entry.getKey() << ", " << entry.getValue() << ")";
    return os;
}

#endif // TABLE_ENTRY_H

