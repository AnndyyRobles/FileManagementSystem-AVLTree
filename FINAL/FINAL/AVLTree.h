#ifndef AVL_TREE_H
#define AVL_TREE_H
#include "archivo.h"
#include <algorithm>
#include <iostream>
#include <string>
using namespace std;

template<typename T>
class AVLByTree {
private:
    struct Node {
        string key;
        T* data;
        Node *left, *right;
        int height;

        Node(string key, T* data) : key(key), data(data), left(nullptr), right(nullptr), height(1) {}
    };

    Node* root;

    Node* insert(Node* node, const string& key, T* data) {
        if (!node) return new Node(key, data);
        if (key < node->key)
            node->left = insert(node->left, key, data);
        else if (key > node->key)
            node->right = insert(node->right, key, data);
        else
            return node;

        return balance(node);
    }

    Node* remove(Node* node, const string& key) {
        if (!node) return node;

        if (key < node->key)
            node->left = remove(node->left, key);
        else if (key > node->key)
            node->right = remove(node->right, key);
        else {
            if (!node->left || !node->right) {
                Node* temp = node->left ? node->left : node->right;
                if (!temp) {
                    temp = node;
                    node = nullptr;
                } else
                    *node = *temp;
                delete temp;
            } else {
                Node* temp = minValueNode(node->right);
                node->key = temp->key;
                node->data = temp->data;
                node->right = remove(node->right, temp->key);
            }
        }

        if (!node) return node;
        return balance(node);
    }

    Node* minValueNode(Node* node) {
        Node* current = node;
        while (current && current->left != nullptr)
            current = current->left;
        return current;
    }

    Node* rotateLeft(Node* x) {
        Node* y = x->right;
        Node* T2 = y->left;
        y->left = x;
        x->right = T2;
        x->height = max(height(x->left), height(x->right)) + 1;
        y->height = max(height(y->left), height(y->right)) + 1;
        return y;
    }

    Node* rotateRight(Node* y) {
        Node* x = y->left;
        Node* T2 = x->right;
        x->right = y;
        y->left = T2;
        y->height = max(height(y->left), height(y->right)) + 1;
        x->height = max(height(x->left), height(x->right)) + 1;
        return x;
    }

    int height(Node* n) {
        if (!n) return 0;
        return n->height;
    }

    int getBalance(Node* n) {
        if (!n) return 0;
        return height(n->left) - height(n->right);
    }

    Node* balance(Node* n) {
        n->height = max(height(n->left), height(n->right)) + 1;
        int balance = getBalance(n);

        if (balance > 1 && getBalance(n->left) >= 0)
            return rotateRight(n);
        if (balance < -1 && getBalance(n->right) <= 0)
            return rotateLeft(n);
        if (balance > 1 && getBalance(n->left) < 0) {
            n->left = rotateLeft(n->left);
            return rotateRight(n);
        }
        if (balance < -1 && getBalance(n->right) > 0) {
            n->right = rotateRight(n->right);
            return rotateLeft(n);
        }
        return n;
    }

public:
    AVLByTree() : root(nullptr) {}

    void insert(const string& key, T* data) {
        root = insert(root, key, data);
    }

    void remove(const string& key) {
        root = remove(root, key);
    }

    void displayInOrder() {
        inOrder(root);
    }

    T* search(const string& key) {
        Node* res = search(root, key);
        return res ? res->data : nullptr;
    }

private:
    Node* search(Node* node, const string& key) {
        if (node == nullptr || node->key == key)
            return node;
        if (key < node->key)
            return search(node->left, key);
        return search(node->right, key);
    }

    void inOrder(Node* node) {
        if (node) {
            inOrder(node->left);
            cout << "Key: " << node->key << ", Data: " << node->data->getNombre() << endl;
            inOrder(node->right);
        }
    }
};

#endif // AVL_TREE_H
