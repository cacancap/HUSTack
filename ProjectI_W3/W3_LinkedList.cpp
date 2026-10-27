#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <stack>
#include <unordered_map>
using namespace std;

class LinkedList{
private:
    struct Node{
        int value;
        Node* next;
        Node(int val): value(val), next(nullptr) {}
    };
    Node* head;
    Node* tail;
    unordered_map<int, bool> dictionary;

public:
    LinkedList() : head(nullptr), tail(nullptr) {}
    LinkedList(const vector<int>& origin_arr) : head(nullptr){
        for (int i = 0; i < origin_arr.size(); i++){
            addToLast(origin_arr[i]);
        }
    }

    ~LinkedList(){
        Node* curr = head;
        while (curr != nullptr){
            Node* nextNode = curr->next;
            delete curr;
            curr = nextNode;
        }
    }

    void printList(){
        Node* curr = head;
        while (curr != nullptr){
            cout << curr->value << " ";
            curr = curr->next;
        }
        cout << endl;
    }

    void addToLast(int value){
        if (dictionary.find(value) != dictionary.end()){
            return;
        }
        if (head == nullptr){
            head = new Node(value);
            tail = head;
        } else {
            Node* newNode = new Node(value);
            tail->next = newNode;
            tail = newNode;
        }

        dictionary.insert({value, true});
    }

    void addToFirst(int value){
        if (dictionary.find(value) != dictionary.end()){
            return;
        }

        if (head == nullptr){
            head = new Node(value);
            tail = head;
        } else {
            Node* newNode = new Node(value);
            newNode->next = head;
            head = newNode;
        }

        dictionary.insert({value, true});
    }

    void addAfter(int newVal, int refVal){
        if (dictionary.find(newVal) != dictionary.end() || dictionary.find(refVal) == dictionary.end()){
            return;
        }
        Node* curr = head;
        while (curr != nullptr){
            if (curr->value == refVal){
                Node* newNode = new Node(newVal);
                newNode->next = curr->next;
                curr->next = newNode;
                dictionary.insert({newVal, true});
                return;
            }
            curr = curr->next;
        }
    }

    void addBefore(int newVal, int refVal){
        if (dictionary.find(newVal) != dictionary.end() || dictionary.find(refVal) == dictionary.end()){
            return;
        }
        Node* curr = head;
        Node* prev = nullptr;
        while (curr != nullptr){
            if (curr->value == refVal){
                Node* newNode = new Node(newVal);
                newNode->next = curr;
                if (curr == head){
                    head = newNode;
                    dictionary.insert({newVal, true});
                    return;
                }

                prev->next = newNode;
                dictionary.insert({newVal, true});
                return;
            }

            prev = curr;
            curr = curr->next;
        }
    }
    
    // Remove all node having value == refVal
    void remove(int refVal){
        Node* prev = nullptr;
        Node* curr = head;

        while (curr != nullptr){
            if (curr->value == refVal){
                Node* temp = curr; // Đánh dấu node cần xóa
                if (curr == head){
                    head = curr->next;
                    if (head == nullptr) tail = nullptr;
                    curr = head;  
                } else {
                    prev->next = curr->next;
                    if (curr == tail) tail = prev;
                    curr = curr->next; 
                }
                delete temp;     
                dictionary.erase(refVal); 
            } else {
                prev = curr;
                curr = curr->next;
            }
        }
    }

    // Reverse the entire linked list
    void reverse(){
        stack<Node*> container;
        
        for (Node* temp = head; temp != nullptr; temp = temp->next){
            container.push(temp);
        }

        if (container.empty()) return;
        tail = head;    // Update tail, head
        head = container.top();
        Node* curr = head;
        container.pop();
        while (!container.empty()){
            Node* nextNode = container.top();
            curr->next = nextNode;
            curr = nextNode;
            container.pop();
        }
        curr->next = nullptr;
    }
};



int main(){
    int n; cin >> n;
    vector<int> origin_arr;
    for (int i = 0; i < n; i++){
        int x;
        cin >> x; origin_arr.push_back(x);
    }

    LinkedList Llist(origin_arr);
    string line;
    while (getline(cin, line)){
        if (line == "#") break;
        stringstream ss(line);
        string token;
        ss >> token;
        int val;

        if (token == "addlast"){
            ss >> val;
            Llist.addToLast(val);
        } else if (token == "addfirst"){
            ss >> val;
            Llist.addToFirst(val);
        } else if (token == "addafter"){
            int refVal;
            ss >> val;
            ss >> refVal;
            Llist.addAfter(val, refVal);
        } else if (token == "addbefore"){
            int refVal; 
            ss >> refVal;
            ss >> val;
            Llist.addBefore(refVal, val);
        } else if (token == "remove"){
            ss >> val;
            Llist.remove(val);
        } else if (token == "reverse"){
            Llist.reverse();
        }
    }
    Llist.printList();
    return 0;
}