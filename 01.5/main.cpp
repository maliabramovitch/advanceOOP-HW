#include <iostream>
#include <memory>
#include "Vector.h"
#include "BinarySearchTree.h"

using namespace std;

template<class T>
class Comp {
public:
    bool operator()(const T &a, const T &b) const { return a < b; }
};

bool VECTOR = false;


int main() {
    if (VECTOR) {
        Vector<string> v;
        try {
            v.pushBack("Mali Abramovitch was here!");
            v.pushBack("ABBA");
            v.pushBack("Agneta");
            v.pushBack("Bjorn");
            v.pushBack("Benny");
            v.pushBack("Anni");
            cout << v << endl;
            v.sort(Comp<string>());
            cout << v << endl;
            v.resize(v.size() - 1);
            cout << v << endl;
            v.clear();
            cout << v.size() << endl;
            cout << v[6] << endl;
            return 0;
        }
        catch (Vector<string>::IndexOutOfrRange &e) {
            cerr << e.what();
            return -1;
        }
    } else { // BST
        BinarySearchTree<int> bst;
        bst.insert(4);
        bst.insert(2);
        bst.insert(4);
        bst.printBST();
        bst.insert(1);
        bst.insert(3);
        bst.insert(6);;
        bst.insert(5);
        bst.insert(7);
        bst.insert(8);
        bst.printBST();
        //bst.Delete();
        //bst.printBST();
        bst.find(11);
        bst.remove(1);
        bst.printBST();
        bst.remove(7);
        bst.printBST();
        bst.remove(6);
        bst.printBST();
        bst.remove(4);
        bst.printBST();
        bst.remove(2);
        bst.printBST();
        bst.remove(5);
        bst.printBST();
        bst.remove(8);
        bst.printBST();
        bst.remove(3);
        bst.printBST();
        bst.insert(10);
        bst.printBST();
    }
}