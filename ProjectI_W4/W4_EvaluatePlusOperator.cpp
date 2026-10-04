#include <iostream>
#include <string>
#include <sstream>
using namespace std;

long long evaluate(string line){
    if (!line.empty() && line.back() == '+'){
        return -1;
    }

    long long result = 0;
    int count = 0;
    stringstream ss(line);
    string token;
    while (getline(ss, token, '+')){
        if (token.empty()) {
            return -1; // có dấu ++ hoặc bắt đầu bằng +
        }
        result += stoi(token);
    }
    return result;
}

int main(){
    string line;
    getline(cin, line);
    int result = evaluate(line);
    if (result == -1){
        cout << "NOTCORRECT" << endl;
    } else {
        cout << result << endl;
    }

    return 0;
}