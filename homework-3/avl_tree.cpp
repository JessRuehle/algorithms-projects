// Include necessary headers
#include "avl_tree.h"

//// Implementation of AVL tree insertion
//template <typename T>
//void AvlTree<T>::insert(T data) {
//    // Perform ordinary BST insertion
//    BST<T>::insert(data);
//    Node<T>* current = BST<T>::root;
//    while (current) {
//        if (unbalanced(current)) {
//            Node<T>* parent = current->parent;
//            Node<T>* new_root = trinode_restructure(current, current->left, current->right);
//            if (parent == nullptr) {
//                BST<T>::root = new_root;
//                new_root->parent = nullptr;
//            } else if (parent->left == current) {
//                parent->left = new_root;
//                new_root->parent = parent;
//            } else {
//                parent->right = new_root;
//                new_root->parent = parent;
//            }
//            break;
//        }
//        updateHeight(current);
//        current = current->parent;
//    }
//}
//
//// Implementation of trinode successor
//template <typename T>
//Node<T>* AvlTree<T>::trinode_successor(Node<T>* x, T data) {
//    // Find the node with the given data in the tree
//    Node<T>* current = BST<T>::root;
//    while (current && current->data != data) {
//        if (data < current->data) {
//            current = current->left;
//        } else {
//            current = current->right;
//        }
//    }
//
//    // If the node is not found or has no right child, return null
//    if (!current || !current->right) {
//        return nullptr;
//    }
//
//    // Find the smallest node in the right subtree
//    Node<T>* successor = current->right;
//    while (successor->left) {
//        successor = successor->left;
//    }
//
//    return successor;
//}
//
//// Implementation of trinode restructuring
//template <typename T>
//Node<T>* AvlTree<T>::trinode_restructure(Node<T>* x, Node<T>* y, Node<T>* z) {
//    Node<T>* a, *b, *c;
//    Node<T>* T1, *T2, *T3;
//
//    if (z->data > y->data && y->data > x->data) {
//        a = x;
//        b = y;
//        c = z;
//        T1 = x->left;
//        T2 = y->left;
//        T3 = z->right;
//    } else if (z->data < y->data && y->data < x->data) {
//        a = z;
//        b = y;
//        c = x;
//        T1 = z->left;
//        T2 = y->left;
//        T3 = x->right;
//    } else if (z->data > x->data && x->data > y->data) {
//        a = y;
//        b = x;
//        c = z;
//        T1 = y->left;
//        T2 = x->left;
//        T3 = z->right;
//    } else { // (z->data < x->data && x->data < y->data)
//        a = z;
//        b = x;
//        c = y;
//        T1 = z->left;
//        T2 = x->left;
//        T3 = y->right;
//    }
//
//    // Rearrange the nodes and subtrees to perform trinode restructuring
//    Node<T>* parent = x->parent;
//    if (parent) {
//        if (parent->left == x) {
//            parent->left = b;
//        } else {
//            parent->right = b;
//        }
//    } else {
//        BST<T>::root = b;
//    }
//
//    b->parent = parent;
//    b->left = a;
//    b->right = c;
//
//    a->parent = b;
//    a->right = T2;
//
//    c->parent = b;
//    c->left = T3;
//
//    if (T2) {
//        T2->parent = a;
//    }
//
//    if (T3) {
//        T3->parent = c;
//    }
//
//    // Update heights of affected nodes
//    updateHeight(a);
//    updateHeight(c);
//    updateHeight(b);
//
//    // Return the new root after restructuring
//    return b;
//}
//
//template <typename T>
//int AvlTree<T>::height(Node<T>* node) {
//    if (node == nullptr) {
//        return -1;
//    } else {
//        int leftHeight = (node->left != nullptr) ? node->left->height : 0;
//        int rightHeight = (node->right != nullptr) ? node->right->height : 0;
//
//        return 1 + std::max(leftHeight, rightHeight);
//    }
//}
//
//template <typename T>
//void AvlTree<T>::updateHeight(Node<T>* node) {
//    while(node){
//        if (unbalanced(node)) {
//            node->height = 1 + std::max(height(node->left), height(node->right));
//            break;
//        }
//        updateHeight(node);
//        node = node->parent;
//    }
//}
//
//// Implementation of checking if a node is unbalanced
//template <typename T>
//bool AvlTree<T>::unbalanced(Node<T>* node) {
//    // Calculate the balance factor
//    int balanceFactor = this->height(node->left) - this->height(node->right);
//
//    // Check if the node is unbalanced
//    return (balanceFactor > 1 || balanceFactor < -1);
//}
//
//template class AvlTree<int>;



template <typename T>
void AvlTree<T>::insert(T data) {

    // use inherited insert function
    BST<T>::insert(data);

    // search for newly inserting node and backtrack, comparing heights and
    // restructuring where needed
    checkTree(BST<T>::root, data);

}

template <typename T>
void AvlTree<T>::find(T data) {

    Node<T>* current = BST<T>::root;

    // if the node is found, return to its parent
    if (current->data == data) {
        lastInsertedNode = current;
        return;

    } else if (data < current->data) {
        checkTree(current->left, data); // check left child
        checkBalance(current); // check balance on way back from finding node

    } else if (data > current->data) {
        checkTree(current->right, data); // check right child
        checkBalance(current); // check balance on way back from finding node
    }
}

template <typename T>
void AvlTree<T>::checkTree(Node<T>* current, T data) {

    // if the node is found, return to its parent
    if (current->data == data) {
        lastInsertedNode = current;
        return;

    } else if (data < current->data) {
        checkTree(current->left, data); // check left child
        checkBalance(current); // check balance on way back from finding node

    } else if (data > current->data) {
        checkTree(current->right, data); // check right child
        checkBalance(current); // check balance on way back from finding node
    }
}

template <typename T>
void AvlTree<T>::checkBalance(Node<T>* x) {

    // if the node is balanced, do nothing. if not, proceed
    if (!unbalanced(x)) {
        return;
    }

    // nodes to be restructured
    Node<T>* y = nullptr;
    Node<T>* z = nullptr;

    // determine which nodes need restructure by comparing heights
    if (height(x->left) > height(x->right)) y = x->left;
    else y = x->right;
    if (height(y->left) > height(y->right)) z = x->left;
    else z = y->right;

    // call on function to perform restructure
    trinode_restructure(x, y, z);
}

template <typename T>
bool AvlTree<T>::unbalanced(Node<T>* node) {

    // if the node doesn't exist, return false
    if (node == nullptr) {
        return false;
    }

    // otherwise, calculate imbalance
    int balance_factor = height(node->left) - height(node->right);
    return (std::abs(balance_factor) > 1) || unbalanced(node->left)
                                             || unbalanced(node->right);
}

// Helper function to update height attribute while walking back to the root
template <typename T>
int AvlTree<T>::updateHeight(Node<T>* node) {
    if (node == nullptr) {
        return -1;  // Base case: Height of an empty tree is -1
    } else {
        int leftHeight = updateHeight(node->left);
        int rightHeight = updateHeight(node->right);
        node->height = 1 + std::max(leftHeight, rightHeight);
        return node->height;
    }
}


template <typename T>
Node<T>* AvlTree<T>::trinode_restructure(Node<T>* x, Node<T>* y, Node<T>* z) {

    // determine the configuration of the trinode and perform restructuring
    if (z->left == y && y->left == x) {
        // Left-Left case
        return trinode_LL(x, y, z);
    } else if (z->left == y && y->right == x) {
        // Left-Right case
        return trinode_LR(x, y, z);
    } else if (z->right == y && y->left == x) {
        // Right-Left case
        return trinode_RL(x, y, z);
    } else {
        // Right-Right case
        return trinode_RR(x, y, z);
    }
}



template <typename T>
Node<T>* AvlTree<T>::trinode_LL(Node<T>* x, Node<T>* y, Node<T>* z) {
    // Perform the trinode restructuring for the Left-Left case
    // Update parent-child relationships
    y->parent = z->parent;
    if (z->parent) {
        if (z->parent->left == z) {
            z->parent->left = y;
        } else {
            z->parent->right = y;
        }
    } else {
        // Update the root if necessary
        BST<T>::root = y;
    }

    z->parent = y;
    z->left = y->right;
    if (y->right) {
        y->right->parent = z;
    }

    y->right = z;

    // Update heights
    z->height = 1 + std::max(height(z->left), height(z->right));
    y->height = 1 + std::max(height(y->left), height(y->right));

    return y;  // Return the new root (y)
}


template <typename T>
Node<T>* AvlTree<T>::trinode_LR(Node<T>* x, Node<T>* y, Node<T>* z) {
    // Perform the trinode restructuring for the Left-Right case
    // Update parent-child relationships
    z->parent = y->parent;
    if (y->parent) {
        if (y->parent->left == y) {
            y->parent->left = z;
        } else {
            y->parent->right = z;
        }
    } else {
        // Update the root if necessary
        BST<T>::root = z;
    }

    y->parent = z;
    y->right = z->left;
    if (z->left) {
        z->left->parent = y;
    }

    x->parent = z;
    x->left = z->right;
    if (z->right) {
        z->right->parent = x;
    }

    z->left = y;
    z->right = x;

    // Update heights
    y->height = 1 + std::max(height(y->left), height(y->right));
    x->height = 1 + std::max(height(x->left), height(x->right));
    z->height = 1 + std::max(height(y), height(x));

    return z;  // Return the new root (z)
}


template <typename T>
Node<T>* AvlTree<T>::trinode_RR(Node<T>* x, Node<T>* y, Node<T>* z) {
    // Perform the trinode restructuring for the Right-Right case
    // Update parent-child relationships
    y->parent = x->parent;
    if (x->parent) {
        if (x->parent->left == x) {
            x->parent->left = y;
        } else {
            x->parent->right = y;
        }
    } else {
        // Update the root if necessary
        BST<T>::root = y;
    }

    x->parent = y;
    x->right = y->left;
    if (y->left) {
        y->left->parent = x;
    }

    y->left = x;

    // Update heights
    x->height = 1 + std::max(height(x->left), height(x->right));
    y->height = 1 + std::max(height(x), height(y->right));

    return y;  // Return the new root (y)
}


template <typename T>
Node<T>* AvlTree<T>::trinode_RL(Node<T>* x, Node<T>* y, Node<T>* z) {
    // Perform the trinode restructuring for the Right-Left case
    // Update parent-child relationships
    z->parent = y->parent;
    if (y->parent) {
        if (y->parent->left == y) {
            y->parent->left = z;
        } else {
            y->parent->right = z;
        }
    } else {
        // Update the root if necessary
        BST<T>::root = z;
    }

    x->parent = z;
    x->right = z->left;
    if (z->left) {
        z->left->parent = x;
    }

    y->parent = z;
    y->left = z->right;
    if (z->right) {
        z->right->parent = y;
    }

    z->left = x;
    z->right = y;

    // Update heights
    x->height = 1 + std::max(height(x->left), height(x->right));
    y->height = 1 + std::max(height(y->left), height(y->right));
    z->height = 1 + std::max(height(x), height(y));

    return z;  // Return the new root (z)
}
