#include <iostream>
#include <stack>
#include <sstream>
using namespace std;

int main(){
    ios_base::sync_with_stdio(false); 
    cin.tie(nullptr);
    stack<int> stk;
    string line;
    while(getline(cin, line)){
        if (line == "#") break;
        stringstream ss(line);
        string command;
        int val;
        ss >> command;
        
        if (command == "PUSH"){
            ss >> val;
            stk.push(val);
        } else if (command == "POP"){
            if (stk.empty()) { 
                cout << "NULL" << endl;
            } else {
                cout << stk.top() << endl;
                stk.pop();
            }
        }
    }

    return 0;
}