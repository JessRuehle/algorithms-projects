/*
 * An AVL tree. Deletions are not supported.
 *
 * Author: Drue Coles
 */

#include "bst.cpp"

template <typename T>
class AvlTree : public BST<T> {

public:
    void insert(T data);

private:

    Node<T>* trinode_restructure(Node<T>*, Node<T>*, Node<T>*);
    Node<T>* trinode_successor(Node<T>*, T);
    bool unbalanced(Node<T>*);
    void checkTree(Node<T>*, T);
    void checkBalance(Node<T>*);
    int updateHeight(Node<T>* node);
    Node<T>* trinode_LL(Node<T>* x, Node<T>* y, Node<T>* z);
    Node<T>* trinode_RL(Node<T>* x, Node<T>* y, Node<T>* z);
    Node<T>* trinode_RR(Node<T>* x, Node<T>* y, Node<T>* z);
    Node<T>* trinode_LR(Node<T>* x, Node<T>* y, Node<T>* z);
    void find(T);
    Node<T>* lastInsertedNode = 0;
    int height(Node<T>*);

};