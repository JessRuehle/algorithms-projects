#include "bst.h"

template <typename T>
void BST<T>::insert(T data) {
    this->root = traverseAdd(this->root, data);
}

template <typename T>
Node<T>* BST<T>::traverseAdd(Node<T>* node, T data) {

    // check if the root is null, and if so add a new node there and set it's parent to
    // our current node
    if (node == nullptr) {
        auto* temp = new Node<T>(data);
        temp->parent = node;
        return temp;
    }

    // if the data we are inserting is less than of the node we are currently at,
    // traverse left. otherwise, traverseAdd right
    if (data < node->data) {
        node->left = traverseAdd(node->left, data);
    } else if (data > node->data) {
        node->right = traverseAdd(node->right, data);
    }

    // retrieve the height of the children nodes, determine which one is bigger, and
    // set the height of the current node to the greater height + 1
    node->height = 1 + std::max(height(node->left), height(node->right));

    return node;

}

template <typename T>
int BST<T>::height(Node<T>* node) {

    if (node == nullptr) {
        return -1; // if the node is null, return -1.
    } else {
        return node->height; // otherwise, return its height
    }
}

template <typename S>
std::ostream& operator<<(std::ostream& os, const BST<S>& tree) {
    print(os, tree.root);
    return os;
}

template <typename S>
void print(std::ostream& os, Node<S>* node) {
    if (node) {
        print(os, node->left);
        os << node->data << ' ';
        print(os, node->right);
    }
}


template <typename T>
void BST<T>::remove(Node<T>* node) {
    root = traverseRemove(root, node);
}

template <typename T>
Node<T>* BST<T>::traverseRemove(Node<T>* current, Node<T>* target) {

    // check if the root is null, and if so add a new node there
    if (current == nullptr) {
        return current;  // Data not found, no changes needed
    }

    if (target->data < current->data) {

        // if the target node is less than the current one, traverse left
        current->left = removeRecursive(current->left, target);
    } else if (target->data > current->data) {

        // if the target node is greater than the current one, traverse right
        current->right = removeRecursive(current->right, target);
    } else {
        // Node with data found, handle removal case
        if (current->left == nullptr) {
            Node<T>* temp = current->right;
            delete current;
            return temp;
        } else if (current->right == nullptr) {
            Node<T>* temp = current->left;
            delete current;
            return temp;
        } else {
            // Node has two children, find the in-order successor (min node of the right subtree)
            Node<T>* temp = findMin(current->right);
            current->data = temp->data;
            current->right = removeRecursive(current->right, temp);
        }
    }

    return current;
}