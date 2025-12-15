#ifndef BSTREE_H
#define BSTREE_H

#include <ostream>
#include <stdexcept>
#include "BSNode.h"

template <typename T>
class BSTree {
private:
    int nelem;
    BSNode<T>* root;

    // --- BÚSQUEDA INTERNA (NO LANZA EXCEPCIÓN) ---
    BSNode<T>* searchNode(BSNode<T>* n, const T& e) const {
        if (n == nullptr) return nullptr;
        if (e == n->elem) return n;
        if (e < n->elem) return searchNode(n->left, e);
        return searchNode(n->right, e);
    }

    // --- INSERTAR ---
    BSNode<T>* insertNode(BSNode<T>* n, const T& e) {
        if (n == nullptr) {
            nelem++;
            return new BSNode<T>(e);
        }
        if (e < n->elem) n->left = insertNode(n->left, e);
        else if (e > n->elem) n->right = insertNode(n->right, e);
        else {
            // si es igual, reemplazamos el valor
            n->elem = e;
        }
        return n;
    }

    // --- ELIMINAR ---
    BSNode<T>* removeNode(BSNode<T>* n, const T& e) {
        if (n == nullptr) throw std::runtime_error("Elemento no encontrado");

        if (e < n->elem) n->left = removeNode(n->left, e);
        else if (e > n->elem) n->right = removeNode(n->right, e);
        else {
            if (n->left == nullptr) {
                BSNode<T>* tmp = n->right;
                delete n;
                nelem--;
                return tmp;
            }
            if (n->right == nullptr) {
                BSNode<T>* tmp = n->left;
                delete n;
                nelem--;
                return tmp;
            }

            // dos hijos → máximo del subárbol izquierdo
            T m = maxNode(n->left);
            n->elem = m;
            n->left = removeMax(n->left);
        }
        return n;
    }

    T maxNode(BSNode<T>* n) const {
        while (n->right != nullptr) n = n->right;
        return n->elem;
    }

    BSNode<T>* removeMax(BSNode<T>* n) {
        if (n->right == nullptr) {
            BSNode<T>* tmp = n->left;
            delete n;
            nelem--;
            return tmp;
        }
        n->right = removeMax(n->right);
        return n;
    }

    void print_inorder(std::ostream &out, BSNode<T>* n) const {
        if (n != nullptr) {
            print_inorder(out, n->left);
            out << n->elem << " ";
            print_inorder(out, n->right);
        }
    }

    void delete_cascade(BSNode<T>* n) {
        if (n != nullptr) {
            delete_cascade(n->left);
            delete_cascade(n->right);
            delete n;
        }
    }

public:
    BSTree() : nelem(0), root(nullptr) {}

    ~BSTree() {
        delete_cascade(root);
    }

    // --- size ---
    int size() const { return nelem; }

    // --- search: devuelve bool ---
    bool search(const T& e) const {
        return searchNode(root, e) != nullptr;
    }

    // --- at: devuelve referencia ---
    T& at(const T& e) {
        BSNode<T>* n = searchNode(root, e);
        if (!n) throw std::runtime_error("Elemento no encontrado");
        return n->elem;
    }

    const T& at(const T& e) const {
        BSNode<T>* n = searchNode(root, e);
        if (!n) throw std::runtime_error("Elemento no encontrado");
        return n->elem;
    }

    // --- insert ---
    void insert(const T& e) {
        root = insertNode(root, e);
    }

    // --- remove ---
    void remove(const T& e) {
        root = removeNode(root, e);
    }

    // --- operator[] ---
    T operator[](const T& e) const {
        BSNode<T>* n = searchNode(root, e);
        if (!n) throw std::runtime_error("Elemento no encontrado");
        return n->elem;
    }

    // --- imprimir ---
    friend std::ostream& operator<<(std::ostream &out, const BSTree<T> &bst) {
        bst.print_inorder(out, bst.root);
        return out;
    }
};

#endif

