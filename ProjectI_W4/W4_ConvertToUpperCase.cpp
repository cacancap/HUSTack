#include <iostream>
#include <string>
using namespace std;

string convertToUpperCase(string raw){
    string result = "";
    for (char c : raw){
        if (c >= 97 && c <= 122){
            result.push_back((char)(c - 32));
        } else {
            result.push_back(c);
        }
    }
    return result;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    string line;
    while (getline(cin, line)){
        cout << convertToUpperCase(line) << endl;
    }

    return 0;
}