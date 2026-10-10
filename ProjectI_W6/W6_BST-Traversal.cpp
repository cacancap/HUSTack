#include <iostream>
#include <string>
#include <sstream>

using namespace std;

// ── BSTree class 
class BSTree {
private:
    struct TreeNode{
        int value;
        TreeNode* leftChild = nullptr;
        TreeNode* rightChild = nullptr;
    };

    TreeNode* root;
    void preOrderTraversal(TreeNode* node){
        if (node == nullptr) return;
        cout << node->value << " ";
        preOrderTraversal(node->leftChild);
        preOrderTraversal(node->rightChild);
    }

    void destroy(TreeNode* node){
        if (node == nullptr) return;
        destroy(node->leftChild);
        destroy(node->rightChild);
        delete node;
    }

public:
    // Constructor: Initialize empty tree
    BSTree() : root(nullptr) {}

    // Destructor
    ~BSTree() {
        destroy(root);
    }

    void insert(int val){
        TreeNode* newNode = new TreeNode({val, nullptr, nullptr});
        if (root == nullptr){
            root = newNode;
            return;
        }
        TreeNode* curr = root;
        while (true){
            if (val == curr->value){
                return;
            }
            else if (val < curr->value){
                if (curr->leftChild == nullptr){ curr->leftChild = newNode; return; }
                curr = curr->leftChild;
            } else {
                if (curr->rightChild == nullptr){ curr->rightChild = newNode; return; }
                curr = curr->rightChild;
            }
        }
    }

    void preOrderTraversal(){
        preOrderTraversal(root);
    }
};

int main(){
    BSTree tree;
    string line;
    while (getline(cin, line)){
        if (line == "#") break;
        stringstream ss(line);
        string token;
        ss >> token; ss >> token;
        tree.insert(stoi(token));
    }
    tree.preOrderTraversal();
    return 0;
}