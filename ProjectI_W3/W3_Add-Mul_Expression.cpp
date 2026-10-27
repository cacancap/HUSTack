#include <iostream>
#include <stack>
#include <vector>

#define reject() do {cout << "NOT_CORRECT\n"; return {};} while (0)

using namespace std;

const long long MOD = 1000000007;

enum class TokenType{
    ADD,
    MUL,
    NUM,
    OPEN,
    CLOSE,
    UNKNOWN,
    NONE
};

// Take an input as character/string and return the token type
TokenType getTokenType(string str) {
    if (str[0] == '+') {
        return TokenType::ADD;
    } else if (str[0] == '*') {
        return TokenType::MUL;
    } else if (str[0] >= '0' && str[0] <= '9') {
        return TokenType::NUM;
    } else if (str[0] == '('){
        return TokenType::OPEN;
    } else if (str[0] == ')'){
        return TokenType::CLOSE;
    } else {
        return TokenType::UNKNOWN;
    }
}

bool checkPrevCurType(TokenType prevType, TokenType curType){
    if (prevType == TokenType::NONE){   // PrevType == NONE once the expression starts
        if (curType == TokenType::NUM || curType == TokenType::OPEN){
            return true;
        }
        return false;
    } else if (prevType == TokenType::NUM){
        if (curType == TokenType::ADD || curType == TokenType::MUL || curType == TokenType::CLOSE){
            return true;
        }
        return false; 
    } else if (prevType == TokenType::MUL || prevType == TokenType::ADD){
        if (curType == TokenType::NUM || curType == TokenType::OPEN){
            return true;
        }
        return false;
    } else if (prevType == TokenType::OPEN){
        if (curType == TokenType::NUM || curType == TokenType::OPEN){
            return true;
        }
        return false;
    } else if (prevType == TokenType::CLOSE){
        if (curType == TokenType::ADD || curType == TokenType::MUL || curType == TokenType::CLOSE){
            return true;
        }
        return false;
    } else {
        return false;
    }
}

// Return a list of tokens: each token can only be operand or operator.
vector<string> tokenize(string& expression){
    vector<string> tokenList;
    string curNumber = "";
    int countParentheses = 0;
    TokenType prevType = TokenType::NONE;

    for (int i = 0; i < expression.length(); i++){
        char c = expression[i];

        // 1. Bỏ qua khoảng trắng
        if (c == ' '){
            if (!curNumber.empty()){
                if (!checkPrevCurType(prevType, TokenType::NUM)) reject();
                tokenList.push_back(curNumber);
                curNumber.clear();
                prevType = TokenType::NUM;
            }
            continue;
        }

        // 2. Chữ số
        if (c >= '0' && c <= '9'){
            curNumber += c;
        } else {
            // Chốt số trước khi nhận toán tử / ngoặc
            if (!curNumber.empty()) {
                if (!checkPrevCurType(prevType, TokenType::NUM)) reject();
                tokenList.push_back(curNumber);
                curNumber.clear();
                prevType = TokenType::NUM;
            }

            string newEx(1, c);
            TokenType curType = getTokenType(newEx);
            if (curType == TokenType::UNKNOWN) reject();

            if (curType == TokenType::OPEN) countParentheses++;
            else if (curType == TokenType::CLOSE){
                countParentheses--;
                if (countParentheses < 0) reject();
            }

            if (!checkPrevCurType(prevType, curType)) reject();

            tokenList.push_back(newEx);
            prevType = curType;
        }
    }

    // 3. Chốt số cuối cùng nếu biểu thức kết thúc bằng số
    if (!curNumber.empty()){
        if (!checkPrevCurType(prevType, TokenType::NUM)) reject();
        tokenList.push_back(curNumber);
        prevType = TokenType::NUM;
    }

    // 4. Kiểm tra điều kiện kết thúc biểu thức hợp lệ
    if (tokenList.empty()) reject();
    if (countParentheses != 0) reject();
    if (prevType != TokenType::NUM && prevType != TokenType::CLOSE) reject();

    return tokenList;
}

// Độ ưu tiên của toán tử
int precedence(char op) {
    if (op == '*') return 2;
    if (op == '+') return 1;
    return 0; // '('
}

void applyOp(stack<long long>& values, stack<char>& ops) {
    long long b = values.top(); values.pop();
    long long a = values.top(); values.pop();
    char op = ops.top(); ops.pop();
    if (op == '+') values.push((a + b) % MOD);
    else if (op == '*') values.push((a * b) % MOD);
}

// Tính giá trị biểu thức đã được tokenize
long long evaluate(const vector<string>& tokenList) {
    stack<long long> values;
    stack<char> ops;

    for (const string& token : tokenList) {
        if (token[0] >= '0' && token[0] <= '9') {
            long long val = 0;
            for (char c : token) {
                val = (val * 10 + (c - '0')) % MOD;
            }
            values.push(val);
        } else if (token == "(") {
            ops.push('(');
        } else if (token == ")") {
            while (!ops.empty() && ops.top() != '(') {
                applyOp(values, ops);
            }
            ops.pop(); // Bỏ '('
        } else { // '+' hoặc '*'
            while (!ops.empty() && precedence(ops.top()) >= precedence(token[0])) {
                applyOp(values, ops);
            }
            ops.push(token[0]);
        }
    }

    while (!ops.empty()) {
        applyOp(values, ops);
    }

    return values.top();
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string expression;
    if (getline(cin, expression)){
        vector<string> tokenList = tokenize(expression);
        if (!tokenList.empty()) {
            cout << evaluate(tokenList) << "\n";
        }
    }
    return 0;
}