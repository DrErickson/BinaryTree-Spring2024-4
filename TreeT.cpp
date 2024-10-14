
#include "TreeT.h"

template<class T>
TreeT<T>::TreeT() {
    numNodes = 0;
    root = nullptr;
}

template<class T>
TreeT<T>::~TreeT() {
    DestroyTree(root);
}

template<class T>
void TreeT<T>::DestroyTree(TreeT::Node *node) {
    if (node == nullptr) {
        return;
    }

    DestroyTree(node->left);
    DestroyTree(node->right);
    delete node;
}

// myAwesomeTree = anotherAwesomeTree;
// tree = tree;
template<class T>
TreeT<T> &TreeT<T>::operator=(const TreeT &otherTree) {

    if (this != &otherTree) {
        CopyHelper(root, otherTree);
    }
    
    return *this;
}


template<class T>
void TreeT<T>::CopyHelper(TreeT::Node *&thisTree, TreeT::Node *otherTree) {

    if (otherTree == nullptr) {
        thisTree = nullptr;
        return;
    }
    
    thisTree = new Node;
    thisTree->value = otherTree->value;
    CopyHelper(thisTree->left, otherTree->left);
    CopyHelper(thisTree->right, otherTree->right);
}


template<class T>
void TreeT<T>::Add(T value) {

    Node* newNode = new Node;
    newNode->value = value;
    
    if (root == nullptr) {
        root = newNode;
        numNodes++;
        return;
    }
    
    Node *curr = root;
    
    while (curr != nullptr) {
        if (value < curr->value) {
            if (curr->left != nullptr) {
                curr = curr->left;
            }
            else {
                curr->left = newNode;
                numNodes++;
                return;
            }
        } 
        else if (value > curr->value) {
            if (curr->right != nullptr) {
                curr = curr->right;
            }
            else {
                curr->right = newNode;
                numNodes++;
                return;
            }
        }
        else { // Equal case
            delete newNode;
            return;
        }
    }
}

template<class T>  // Remove is a wrapper function
void TreeT<T>::Remove(T value) {
    // Remove value from root subtree
    RemoveHelper(root, value);
}

template<class T>
void TreeT<T>::RemoveHelper(TreeT::Node *&subtree, T value) {
    
    if (value < subtree->value) {
        // Since value is less, we know value is in the left
        // subtree.  Remove value from left subtree
        RemoveHelper(subtree->left, value);
    }
    else if (value > subtree->value) {
        // Since value is greater, we know value is in the right
        // subtree.  Remove value from right subtree
        RemoveHelper(subtree->right, value);
    }
    else {  // Found the node to remove!
        DeleteNode(subtree);
    }
    
}

template<class T>
void TreeT<T>::DeleteNode(TreeT::Node *&subtree) {

    if (subtree->left == nullptr && subtree->right == nullptr) { // leaf node
        delete subtree;
        subtree = nullptr;
    }
    else if (subtree->left == nullptr) {  // one child on right
        Node *tmp = subtree;
        subtree = subtree->right;
        delete tmp;
    }
    else if (subtree->right == nullptr) { // one child on left
        Node *tmp = subtree;
        subtree = subtree->left;
        delete tmp;
    }
    else {
        T predVal;
        GetPredecessor(subtree->left, predVal);
        subtree->value = predVal;
        RemoveHelper(subtree->left, predVal);
    }
}

template<class T>
void TreeT<T>::GetPredecessor(TreeT::Node *curr, T &value) {
    // Move to the rightmost node
    while (curr->right != nullptr) {
        curr = curr->right;
    }
    value = curr->value;
}

template<class T>
bool TreeT<T>::Contains(T value) {

    Node *curr = root;

    while (curr != nullptr) {
        if (value < curr->value) {
            curr = curr->left;
        }
        else if (value > curr->value) {
            curr = curr->right;
        }
        else { // Equal case
            return true;
        }
    }
    return false;
}

template<class T>
int TreeT<T>::Size() {
    return numNodes;
}

template<class T>
void TreeT<T>::ResetIterator(Order traverseOrder) {
    if (traverseOrder == IN_ORDER) {
        PlaceInOrder(root);
    }
    else if (traverseOrder == POST_ORDER) {
        PlacePostOrder(root);
    }
    else {
        PlacePreOrder(root);
    }
}

template<class T>
T TreeT<T>::GetNextItem() {
    T item = iterQue.front();
    iterQue.pop();
    return item;
}

template<class T>
void TreeT<T>::PlacePreOrder(TreeT::Node *node) {
    if (node == nullptr) {
        return;
    }
    
    
}

template<class T>
void TreeT<T>::PlacePostOrder(TreeT::Node *node) {

}

template<class T>
void TreeT<T>::PlaceInOrder(TreeT::Node *node) {
    if (node == nullptr) {
        return;
    }

    PlaceInOrder(node->left);
    iterQue.push(node->value);
    PlaceInOrder(node->right);
}

