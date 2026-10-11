#include <iostream>
#include <stack>
using namespace std;

bool isOpenParenthesis(char c){
    if (c == '(' || c == '[' || c == '{') return true;
    return false;
}

bool isCloseParenthesis(char c){
    if (c == ')' || c == ']' || c == '}') return true;
    return false;
}

bool isMatchingParenthesis(char a, char b){
    if ((a == '(' && b == ')') || (a == '{' && b == '}') || (a == '[' && b == ']')) return true;
    return false;
}

bool solve(){
    string str;
    getline(cin, str);
    stack<char> stk;

    for (int i = 0; i < str.length(); i++){
        if (isOpenParenthesis(str[i])){
            stk.push(str[i]);
        } else if (isCloseParenthesis(str[i])){
            if (stk.empty()) return false;
            if (isMatchingParenthesis(stk.top(), str[i])){
                stk.pop();
            } else {
                return false;
            }
        }
    }

    if (stk.empty()) return true;
    return false;
}

int main(){
    cout << solve() << endl;

    return 0;
}
