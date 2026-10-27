#include <iostream>
#include <string>
#include <sstream>
#include <map>
using namespace std;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    map<string, bool> dictionary;
    string key;
    while (getline(cin, key)){
        if (key == "*") break;
        dictionary.insert({key, true});
    }

    string line;
    while (getline(cin, line)){
        if (line == "***") break;
        string command;
        stringstream ss(line);
        ss >> command;
        ss >> key;
        if (command == "find"){
            if (dictionary.find(key) != dictionary.end()) cout << "1" << endl;
            else cout << "0" << endl;
        } else if (command == "insert"){
            if (dictionary.find(key) == dictionary.end()){
                cout << "1" << endl;
                dictionary.insert({key, true});
            } else cout << "0" << endl;
        }
    }

    return 0;
}