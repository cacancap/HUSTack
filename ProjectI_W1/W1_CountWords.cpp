#include <iostream>
#include <string>
#include <sstream>

using namespace std;

void solve(){
    string line;
    int result = 0;
    while (getline(cin, line)){
        stringstream ss(line);
        string token;
        while (ss >> token){
            result += 1;
        }
    }
    cout << result << endl;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}