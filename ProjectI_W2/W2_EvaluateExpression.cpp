#include <iostream>
#include <vector>
#include <stack>
const int quotient = 1e9 + 7;
using namespace std;

// Tokenize the original expression: each token can be operand or operator only.
vector<string> tokenize(string& expression){
    string curNumber = "";
    vector<string> result;
    for (int i = 0; i < expression.length(); i++){
        if (expression[i] == '+' || expression[i] == '*'){
            if (curNumber != ""){
                result.push_back(curNumber);
                curNumber = "";
            }
            result.push_back(string(1, expression[i]));
        } else if (expression[i] >= '0' && expression[i] <= '9'){
            curNumber += expression[i];
        }
    }

    if (curNumber != "") result.push_back(curNumber);
    return result;
}

bool checkStatus(vector<string>& tokenList){
    int count = 0;
    if (tokenList[0] == "+" || tokenList[0] == "*" || tokenList.back() == "+" || tokenList.back() == "*") return false;
    for (int i = 0; i < tokenList.size(); i++){
        if (tokenList[i] == "*" || tokenList[i] == "+"){
            if (i % 2 == 0) return false;
            count++;
        }
    }

    return (count % 2 == 0);
}

bool isNumber(string token){
    return (token[0] >= '0' && token[0] <= '9'); 
}

long long evaluate(vector<string>& tokenList){
    stack<long long> stk;
    for (int i = 0; i < tokenList.size(); i++){
        string token = tokenList[i];
        if (isNumber(token)){
            stk.push(stoi(token));
        } else if (token == "+"){
            continue;
        } else if (token == "*"){
            long long num = (stoi(tokenList[i + 1]) * stk.top()) % quotient;
            stk.pop();
            stk.push(num);
            i += 1;
        } else {
            cout << "Error01!" << endl; return 0;
        }
    }

    long long sum = 0;
    while (!stk.empty()){
        sum = (sum + stk.top()) % quotient;
        stk.pop();
    }
    return sum;
}

int main(){
    string expression;
    getline(cin, expression);
    vector<string> tokenList = tokenize(expression);

    bool status = checkStatus(tokenList);
    if (!status){
        cout << "NOT CORRECT" << endl;
        return 0;
    }

    cout << evaluate(tokenList) << endl;   


    return 0;
}