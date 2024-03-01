#include <ostream>

/*
 * Binary Search Tree. Deletions are not supported.
 *
 * Author: Drue Coles
 */
 
template <typename T> 
struct Node {
    Node(T data) {this->data = data;}
    T data;
    int height = 0;
    Node* parent = 0;
    Node* left = 0;
    Node* right = 0;
};

template <typename T>
class BST {

    // Outputs keys of the tree in sorted order.
    template <typename S>
    friend std::ostream& operator<<(std::ostream&, const BST<S>&);

    // Outputs keys of the tree via recursive inorder traversal. Called 
    // from stream insertion operator.
    template <typename S> 
    friend void print(std::ostream&, Node<S>*);

public:
    BST() {root = nullptr;}
    ~BST<T>() {remove(root);} 
    virtual void insert(T data); 
    int height() {return height(root);}     
     
protected:
    Node<T>* root;

    void remove(Node<T>*); // Recursively deallocates tree.
    int height(Node<T>*); // Returns height of node (-1 if NULL)

private:
    Node<T>* traverseAdd(Node<T>* node, T data);
    Node<T>* traverseRemove(Node<T>* current, Node<T>* target);

};