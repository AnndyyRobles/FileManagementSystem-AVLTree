#include "Tree.h"
#include <iostream>

TreeNode::TreeNode(std::string nombreArchivo, std::string contenidoArchivo) :
    nombreArchivo(nombreArchivo), contenidoArchivo(contenidoArchivo),
    izquierdo(nullptr), derecho(nullptr), altura(1) {}  // Asegurarse de inicializar la altura

BinarySearchTree::BinarySearchTree() : root(nullptr) {}

void BinarySearchTree::insert(const std::string& fileName, const std::string& fileContent) {
    root = insert(root, fileName, fileContent);
}

TreeNode* BinarySearchTree::insert(TreeNode* node, const std::string& fileName, const std::string& fileContent) {
    if (!node) {
        return new TreeNode(fileName, fileContent);
    }
    if (fileName < node->nombreArchivo) {
        node->izquierdo = insert(node->izquierdo, fileName, fileContent);
    }
    else if (fileName > node->nombreArchivo) {
        node->derecho = insert(node->derecho, fileName, fileContent);
    }
    return node;
}

TreeNode* BinarySearchTree::search(TreeNode* node, const std::string& fileName) {
    if (node == nullptr) return nullptr;
    if (node->nombreArchivo == fileName) return node;
    if (fileName < node->nombreArchivo)
        return search(node->izquierdo, fileName);
    else
        return search(node->derecho, fileName);
}

void BinarySearchTree::inOrder(TreeNode* node) {
    if (node) {
        inOrder(node->izquierdo);
        std::cout << node->nombreArchivo << " ";
        inOrder(node->derecho);
    }
}

void BinarySearchTree::preOrder(TreeNode* node) {
    if (node) {
        std::cout << node->nombreArchivo << " ";
        preOrder(node->izquierdo);
        preOrder(node->derecho);
    }
}

void BinarySearchTree::postOrder(TreeNode* node) {
    if (node) {
        postOrder(node->izquierdo);
        postOrder(node->derecho);
        std::cout << node->nombreArchivo << " ";
    }
}

TreeNode* BinarySearchTree::deleteNode(TreeNode* root, const std::string& fileName) {
    if (!root) return nullptr;
    if (fileName < root->nombreArchivo)
        root->izquierdo = deleteNode(root->izquierdo, fileName);
    else if (fileName > root->nombreArchivo)
        root->derecho = deleteNode(root->derecho, fileName);
    else {
        if (!root->izquierdo) {
            TreeNode* temp = root->derecho;
            delete root;
            return temp;
        }
        else if (!root->derecho) {
            TreeNode* temp = root->izquierdo;
            delete root;
            return temp;
        }
        TreeNode* temp = minValueNode(root->derecho);
        root->nombreArchivo = temp->nombreArchivo;
        root->derecho = deleteNode(root->derecho, temp->nombreArchivo);
    }
    return root;
}

TreeNode* BinarySearchTree::minValueNode(TreeNode* node) {
    TreeNode* current = node;
    while (current && current->izquierdo != nullptr) {
        current = current->izquierdo;
    }
    return current;
}
