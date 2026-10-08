#include <iostream>
#include <string>
#include <sstream>
#include <unordered_map>
using namespace std;

class FamilyTree{
private:
    struct FTreeNode{
        string name;
        FTreeNode *parent;
        FTreeNode *firstChild;
        FTreeNode *nextSibling;
        FTreeNode(string str): name(str), parent(nullptr), firstChild(nullptr), nextSibling(nullptr) {}
    };
    
    unordered_map<string, FTreeNode*> dictionary;
public:
    void insertNewChild(FTreeNode* parentNode, FTreeNode* newChild){
        if (parentNode == nullptr || newChild == nullptr) return;
        newChild->parent = parentNode;
        if (parentNode->firstChild == nullptr){
            parentNode->firstChild = newChild;
        } else {
            FTreeNode* cur = parentNode->firstChild;
            while (cur->nextSibling != nullptr){
                cur = cur->nextSibling;
            }
            cur->nextSibling = newChild;
        }
    }

    void create_relationship(string childName, string parentName){
        FTreeNode* childNode = nullptr;
        FTreeNode* parentNode = nullptr;
        if (dictionary.find(childName) != dictionary.end()){
            childNode = dictionary[childName];
        } else {
            childNode = new FTreeNode(childName);
            dictionary.insert({childName, childNode});
        }

        if (dictionary.find(parentName) != dictionary.end()){
            parentNode = dictionary[parentName];
        } else {
            parentNode = new FTreeNode(parentName);
            dictionary.insert({parentName, parentNode});
        }

        insertNewChild(parentNode, childNode);
    }

    void printFamily(){
        cout << "Family list: " << endl;
        for (const auto& pair : dictionary){
            cout << "name: " << pair.first << ", pointer: " << pair.second << endl;
        }
    }

    // Return number of descendants of a given name: DFS
    int descendants(string parentName){
        int result = 0;
        FTreeNode* parentNode = (dictionary.find(parentName) != dictionary.end()) ? dictionary[parentName] : nullptr;
        if (parentNode == nullptr || parentNode->firstChild == nullptr) return 0;

        FTreeNode* curChild = parentNode->firstChild;
        while (curChild != nullptr){
            result += 1 + descendants(curChild->name);
            curChild = curChild->nextSibling;
        }

        return result;
    }

    // Return the number of generation of given name => DFS
    int generation(string parentName){
        int maxDepth = 0;
        FTreeNode* parentNode = (dictionary.find(parentName) != dictionary.end()) ? dictionary[parentName] : nullptr;
        if (parentNode == nullptr || parentNode->firstChild == nullptr) return 0;

        FTreeNode* curChild = parentNode->firstChild;
        if (curChild == nullptr) return 1;
        while (curChild != nullptr){
            int curDepth = generation(curChild->name);
            maxDepth = (curDepth > maxDepth) ? curDepth : maxDepth;

            curChild = curChild->nextSibling;
        }

        return maxDepth + 1;
    }
};

int main(){
    FamilyTree family;
    string line;
    while (getline(cin, line)){
        if (line == "***") break;
        stringstream ss(line);
        string childName, parentName;
        ss >> childName, ss >> parentName;
        family.create_relationship(childName, parentName);
    }

    while (getline(cin, line)){
        if (line == "***") break;
        stringstream ss(line);
        string command, name;
        ss >> command; ss >> name;
        
        if (command == "descendants"){
            cout << family.descendants(name) << endl;
        } else if (command == "generation"){
            cout << family.generation(name) << endl;
        }
    }

    // family.printFamily();
    // cout << "descendants Newman: " << family.descendants("Newman") << endl;
    // cout << "descendants Mark: " << family.descendants("Mark") << endl;
    // cout << "descendants David: " << family.descendants("David") << endl;
    // cout << "generation Mark: " << family.generation("Mark") << endl;
    return 0;
}