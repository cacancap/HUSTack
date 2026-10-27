#include <iostream>
#include <string>
#include <sstream>

using namespace std;

int main(){
    string line;
    getline(cin, line);
    stringstream ss(line);
    string token;
    int hour, min, second;
    getline(ss, token, ':');
    
    hour = stoi(token);
    if (token.length() != 2 || hour < 0 || hour > 23 || !getline(ss, token, ':')){
        cout << "INCORRECT" << endl;
        return 0;
    }

    min = stoi(token);
    if (token.length() != 2 || min < 0 || min > 59 || !getline(ss, token, ':')){
        cout << "INCORRECT" << endl;
        return 0;
    }

    second = stoi(token);
    if (token.length() != 2 || second < 0 || second > 59){
        cout << "INCORRECT" << endl;
        return 0;
    }

    cout << hour * 3600 + min * 60 + second << endl;

    return 0;
}