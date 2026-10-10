#include <iostream>
#include <sstream>
#include <unordered_map>
using namespace std;

class Tree{
private:
    struct TreeNode{
        int value;
        TreeNode* firstChild;
        TreeNode* nextSibling;
        TreeNode(int val): value(val), firstChild(nullptr), nextSibling(nullptr) {}
    };
    TreeNode *root;
    unordered_map<int, TreeNode*> dictionary;

    void destroy(TreeNode *node){
        if (node == nullptr) return;
        if (node->firstChild == nullptr){
            delete node;
            return;
        }

        TreeNode* curChild = node->firstChild;
        while (curChild != nullptr){
            TreeNode* oldChild = curChild;
            curChild = curChild->nextSibling;
            destroy(oldChild);
        }
    }

    void printPreOrder(TreeNode* node){
        if (node == nullptr) return;

        cout << node->value << " ";

        TreeNode* curChild = node->firstChild;
        while (curChild != nullptr){
            printPreOrder(curChild);
            curChild = curChild->nextSibling;
        }
    }

    void printPostOrder(TreeNode* node){
        if (node == nullptr) return;

        TreeNode* curChild = node->firstChild;
        while (curChild != nullptr){
            printPostOrder(curChild);
            curChild = curChild->nextSibling;
        }

        cout << node->value << " ";
    }

    void printInOrder(TreeNode* node){
        if (node == nullptr) return;

        if (node->firstChild != nullptr){
            printInOrder(node->firstChild);
        }

        cout << node->value << " ";
        if (node->firstChild != nullptr){
            TreeNode* curChild = node->firstChild->nextSibling;

            while (curChild != nullptr){
                printInOrder(curChild);
                curChild = curChild->nextSibling;
            }
        }
    }

public:
    Tree(): root(nullptr){}
    ~Tree(){
        destroy(root);
    }

    Tree(int rootVal){
        root = new TreeNode(rootVal);
        dictionary[rootVal] = root;
    }

    void makeRoot(int rootVal){
        root = new TreeNode(rootVal);
        dictionary[rootVal] = root;
    }

    void insert(int newVal, int rootVal){
        if (dictionary.find(newVal) != dictionary.end() || dictionary.find(rootVal) == dictionary.end()) return;
        
        TreeNode* newNode = new TreeNode(newVal);
        dictionary.insert({newVal, newNode});
        
        TreeNode* targetNode = dictionary[rootVal];
        if (targetNode->firstChild == nullptr) {
            targetNode->firstChild = newNode;
        } else {

            TreeNode* curChild = targetNode->firstChild;
            while (curChild->nextSibling != nullptr){
                curChild = curChild->nextSibling;
            }
            curChild->nextSibling = newNode;
        }
    }

    void preOrder(){
        printPreOrder(root);
        cout << endl;
    }

    void postOrder(){
        printPostOrder(root);
        cout << endl;
    }

    void inOrder(){
        printInOrder(root);
        cout << endl;
    }

};

int main(){
    Tree tree;
    string line;
    while (getline(cin, line)){
        stringstream ss(line);
        if (line == "*") break;
        string command;
        int value1, value2;
        ss >> command;
        if (command == "MakeRoot"){
            ss >> value1;
            tree.makeRoot(value1);
        } else if (command == "Insert"){
            ss >> value1 >> value2;
            tree.insert(value1, value2);
        } else if (command == "PreOrder"){
            tree.preOrder();
        } else if (command == "PostOrder"){
            tree.postOrder();
        } else if (command == "InOrder"){
            tree.inOrder();
        } else {
            cout << "Error01!" << endl;
            break;
        }
    }
    return 0;
}