//
// Created by Mali Abramovitch on 12/05/2023.
//

#ifndef INC_015_BINARYSEARCHTREE_H
#define INC_015_BINARYSEARCHTREE_H

#include <memory>
#include <iostream>

template<class T>
class BinarySearchTree {
    struct BSTNode {
        std::shared_ptr<T> data;
        std::shared_ptr<BSTNode> left;
        std::shared_ptr<BSTNode> right;
        std::weak_ptr<BSTNode> parent;

        BSTNode(const T &element, std::shared_ptr<BinarySearchTree<T>::BSTNode> p) {
            data = std::make_shared<T>(element);
            left = nullptr;
            right = nullptr;
            parent = p;
        }

        ~BSTNode() {
            data.reset();
            left.reset();
            right.reset();
            parent.reset();
        }

        std::shared_ptr<BinarySearchTree<T>::BSTNode> addNode(const T &element, std::shared_ptr<BinarySearchTree<T>::BSTNode> p);

        std::shared_ptr<BinarySearchTree<T>::BSTNode> getSuccessive(const T &element);

        std::shared_ptr<BinarySearchTree<T>::BSTNode> find(const T &element);
    };

    std::shared_ptr<BinarySearchTree<T>::BSTNode> root;

    void printHelper(std::shared_ptr<BinarySearchTree<T>::BSTNode> n);


public:
    BinarySearchTree() : root(nullptr) {}

    BinarySearchTree(const BinarySearchTree<T> &other) = delete;

    BinarySearchTree(BinarySearchTree<T> &&other) = delete;

    ~BinarySearchTree();

    BinarySearchTree &operator=(const BinarySearchTree<T> &other) = delete;

    BinarySearchTree &operator=(BinarySearchTree<T> &&other) = delete;

    std::shared_ptr<BinarySearchTree<T>::BSTNode> find(const T &element);

    void insert(const T &element);

    void remove(const T &element);

    void Delete();

    std::shared_ptr<BinarySearchTree<T>::BSTNode> getHead();

    void printBST(); //inOrder
};

template<class T>
std::shared_ptr<typename BinarySearchTree<T>::BSTNode>
BinarySearchTree<T>::BSTNode::addNode(const T &element, std::shared_ptr<BinarySearchTree<T>::BSTNode> p) {
    if (data && element < *data) {
        if (!left) {
            left = std::make_shared<BinarySearchTree<T>::BSTNode>(element, p);
        } else {
            left->addNode(element, left);
        }
        return left;
    } else {
        if (!right) {
            right = std::make_shared<BinarySearchTree<T>::BSTNode>(element, p);
        } else {
            right->addNode(element, right);
        }
        return right;
    }
}

template<class T>
std::shared_ptr<typename BinarySearchTree<T>::BSTNode> BinarySearchTree<T>::BSTNode::getSuccessive(const T &element) {
    auto x = find(element); //the node to find it's successor
    if (x) {
        if (x->right) {
            if (!x->right->left) return x->right;
            else {
                x = x->right;
                while (x->left) x = x->left;
                return x;
            }
        } else {
            while (x->parent.lock()->left) {
                x = x->parent.lock();
            }
            return x->parent.lock();
        }
    }

}


template<class T>
std::shared_ptr<typename BinarySearchTree<T>::BSTNode> BinarySearchTree<T>::BSTNode::find(const T &element) {
    if (data) {
        if (*data == element) return std::make_shared<BinarySearchTree<T>::BSTNode>(*this);
        if (data) {
            if (left) {
                if (*left->data == element) return left;
                if (*data > element) {
                    return left->find(element);
                }
            }
            if (right) {
                if (*right->data == element) return right;
                if (*data < element) {
                    return right->find(element);
                }
            }
            return nullptr;


        }
    }
    return nullptr;
}

template<class T>
BinarySearchTree<T>::~BinarySearchTree() {
    root.reset();
}

template<class T>
typename std::shared_ptr<typename BinarySearchTree<T>::BSTNode> BinarySearchTree<T>::find(const T &element) {
    if (root) {
        auto ret = root->find(element);
        if (!ret) std::cout << element << " is not at home right now :(" << std::endl;
        return ret;
    }
    std::cout << element << "not at home right now :(" << element;
    return nullptr;
}

template<class T>
void BinarySearchTree<T>::insert(const T &element) {
    if (!root) {
        root = std::make_shared<BinarySearchTree<T>::BSTNode>(element, nullptr);
        return;
    }
    auto f = root->find(element);
    if (!f) {
        if (element < *root->data) {
            root->left = root->addNode(element, root);
        } else if (element > *root->data) {
            root->right = root->addNode(element, root);
        }
    }
}

template<class T>
void BinarySearchTree<T>::remove(const T &element) {
    if (root && root->data) {
        typedef std::shared_ptr<BinarySearchTree<T>::BSTNode> SmShPtBSTNode;
        SmShPtBSTNode remove = root->find(element);
        if (remove) { ///the node remove is exists
            if (!remove->left && !remove->right) { ///remove is leaf
                if (!remove->parent.expired())
                    remove->parent.lock()->left->data == remove->data ? remove->parent.lock()->left.reset()
                                                                      : remove->parent.lock()->right.reset();
                if (remove->data == root->data) {
                    root.reset();
                }
            } else if ((remove->left && !remove->right) || (remove->right && !remove->left)) { ///remove has one son
                if (remove->left) { ///remove has left son.
                    if (!remove->parent.expired())
                        remove->parent.lock()->left->data == remove->data
                        ? remove->parent.lock()->left->left = remove->right
                        : remove->parent.lock()->right = remove->left;
                    remove->left->parent = remove->parent;
                    if (remove->data == root->data) {
                        root = remove->left;
                    }
                } else {///remove has right son
                    if (!remove->parent.expired())
                        remove->parent.lock()->left->data == remove->data ? remove->parent.lock()->left = remove->right
                                                                          : remove->parent.lock()->right = remove->right;
                    remove->right->parent = remove->parent;
                    if (remove->data == root->data) {
                        root = remove->right;
                    }
                }
            } else { /// remove has 2 sons
                SmShPtBSTNode successor = remove->getSuccessive(element);
                if (successor->data == remove->right->data) { ///successor is right son
                    if (!remove->parent.expired())
                        remove->parent.lock()->left == remove ? remove->parent.lock()->left = successor
                                                              : remove->parent.lock()->right = successor;
                    successor->parent = remove->parent;
                    successor->left = remove->left;
                    remove->left->parent = successor;
                } else { ///successor is the minimum in the rooted tree.
                    remove->right->parent = successor;
                    remove->left->parent = successor;
                    if (!remove->parent.expired()) {
                        remove->parent.lock()->left == remove ? remove->parent.lock()->left = successor
                                                              : remove->parent.lock()->right = successor;
                    }
                    successor->parent.lock()->left.reset();
                    successor->parent = remove->parent;
                    successor->left = remove->left;
                    successor->right = remove->right;
                }
                if (remove->data == root->data) {
                    root = successor;
                }
            }
        }
    }
}


template<class T>
void BinarySearchTree<T>::Delete() {
    root.reset();
}

template<class T>
std::shared_ptr<typename BinarySearchTree<T>::BSTNode> BinarySearchTree<T>::getHead() {
    return root;
}

template<class T>
void BinarySearchTree<T>::printHelper(std::shared_ptr<BinarySearchTree<T>::BSTNode> n) {
    if (n->left) {
        printHelper(n->left);
    }
    if (n->data) {
        std::cout << *(n->data) << '\t';
    }
    if (n->right) {
        printHelper(n->right);
    }
}

template<class T>
void BinarySearchTree<T>::printBST() {
    if (root) {
        printHelper(root);
    }
    std::cout << std::endl;
}


#endif //INC_015_BINARYSEARCHTREE_H
