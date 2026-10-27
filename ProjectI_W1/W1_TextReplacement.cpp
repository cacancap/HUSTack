#include <iostream>
#include <string>
#include <sstream>
using namespace std;


int main(){
    string P1, P2, T;
    getline(cin, P1);
    getline(cin, P2);
    getline(cin, T);
    size_t pos = 0;

    while (pos != string::npos){
        T.replace(pos, P1.length(), P2);
        pos = T.find(P1, pos + 1);
    }

    cout << T << endl;
    return 0;
}