#include <iostream>
#include <string>
#include <sstream>

using namespace std;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    string P, T;
    getline(cin, P); getline(cin, T);

    int count = 0;
    size_t pos = T.find(P);
    while (pos != string::npos){
        count++;
        pos = T.find(P, pos + 1);
    }

    cout << count << endl;
    return 0;
}