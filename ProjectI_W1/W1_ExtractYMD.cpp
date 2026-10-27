#include <iostream>
#include <string>
#include <sstream>
using namespace std;

int main(){
    string line;
    getline(cin, line);

    stringstream ss(line);
    string token;
    int year, month, date;

    getline(ss, token, '-');
    year = stoi(token);
    if (year < 0 || token.length() != 4) {
        cout << "INCORRECT" << endl;
        return 0;
    }
    getline(ss, token, '-');
    month = stoi(token);

    if (month < 0 || month > 12 || token.length() != 2){
        cout << "INCORRECT" << endl;
        return 0;
    }

    getline(ss, token, '-');
    date = stoi(token);

    if (date < 1 || date > 31 || token.length() != 2){
        cout << "INCORRECT" << endl;
        return 0;
    }

    cout << year << " " << month << " " << date << endl;

    return 0;
}