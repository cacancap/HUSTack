#include <iostream>
#include <string>
#include <sstream>
#include <map>
using namespace std;

map<char, char> dictionary;

string translate(string token){
    string result = "";
    for (char c : token){
        if (dictionary.count(c) == 0){
            result.push_back(c);
        } else {
            result.push_back(dictionary[c]);
        }
    }
    return result;
}

int main(){
    dictionary['V'] = 'a';
    dictionary['W'] = 'b';
    dictionary['X'] = 'c';
    dictionary['Y'] = 'd';
    dictionary['Z'] = 'e';
    dictionary['R'] = 'f';
    dictionary['A'] = 'g';
    dictionary['C'] = 'h';
    dictionary['L'] = 'i';
    // dictionary[''] = 'j';
    // dictionary[''] = 'k';
    dictionary['S'] = 'l';
    dictionary['E'] = 'm';
    dictionary['B'] = 'n';
    dictionary['D'] = 'o';
    // dictionary[''] = 'p';
    dictionary['F'] = 'q';
    dictionary['H'] = 'r';
    dictionary['I'] = 's';
    dictionary['J'] = 't';
    dictionary['K'] = 'u';
    dictionary['N'] = 'v';
    // dictionary[''] = 'w';
    dictionary['Q'] = 'x';
    dictionary['T'] = 'y';
    // dictionary[''] = 'z';

    string line;
    string paragraph;
    while (getline(cin, line)){
        if (line == "#") break;
        stringstream ss(line);
        string token;
        while (ss >> token){
            paragraph += translate(token) + " ";
        }
    }

    cout << paragraph << endl;

    return 0;
}