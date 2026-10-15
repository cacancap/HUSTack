#include <iostream>
#include <math.h>
using namespace std;


int hash_string(const string& str, int m){
    long long result = 0;
    for (char c : str){
        result = (result * 256 + (unsigned char)c) % m;
    }
    return (int)result;
}

int main(){
    int n, m; cin >> n >> m;
    cin.ignore();
    for (int i = 0; i < n; i++){
        string str; getline(cin, str);
        cout << hash_string(str, m) << endl;
    }
    return 0;
}