#include <iostream>
#include <queue>
#include <sstream>
using namespace std;

int main(){
    queue<int> q;
    string line;
    while(getline(cin, line)){
        if (line == "#") break;
        stringstream ss(line);
        string command;
        int val;
        ss >> command;
        
        if (command == "PUSH"){
            ss >> val;
            q.push(val);
        } else if (command == "POP"){
            if (q.empty()) { 
                cout << "NULL" << endl;
            } else {
                cout << q.front() << endl;
                q.pop();
            }
        }
    }

    return 0;
}