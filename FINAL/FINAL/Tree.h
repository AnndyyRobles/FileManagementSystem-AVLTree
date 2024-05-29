#ifndef TREE_H
#define TREE_H

#include <string>

struct TreeNode {
    std::string nombreArchivo;
    std::string contenidoArchivo;
    TreeNode* izquierdo;
    TreeNode* derecho;
    int altura;  // Se usa para AVL, se inicializa en el constructor

    TreeNode(std::string nombreArchivo, std::string contenidoArchivo);
};

class BinarySearchTree {
public:
    TreeNode* root;
    BinarySearchTree();

    void insert(const std::string& fileName, const std::string& fileContent);
    TreeNode* search(TreeNode* node, const std::string& fileName);
    void inOrder(TreeNode* node);
    void preOrder(TreeNode* node);
    void postOrder(TreeNode* node);
    TreeNode* deleteNode(TreeNode* root, const std::string& fileName);
    TreeNode* minValueNode(TreeNode* node);

private:
    TreeNode* insert(TreeNode* node, const std::string& fileName, const std::string& fileContent); // Inserción recursiva
};

class AVLTree {
public:
    TreeNode* root;
    AVLTree();

    TreeNode* insert(TreeNode* node, const std::string& fileName, const std::string& fileContent);
    TreeNode* deleteNode(TreeNode* node, const std::string& fileName);
    int getBalance(TreeNode* N);
    TreeNode* leftRotate(TreeNode* x);
    TreeNode* rightRotate(TreeNode* y);
    void inOrder(TreeNode* node);
    void preOrder(TreeNode* node);
    void postOrder(TreeNode* node);
    TreeNode* search(TreeNode* root, const std::string& fileName);
    int max(int a, int b);
};

#endif // TREE_H
