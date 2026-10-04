#include <iostream>
#include <vector>
using namespace std;

void solve(vector<int> &curString, size_t pos, int n, bool filled){
    if (pos == n){
        for (int i = 0; i < n; i++){
            cout << curString[i];
        }
        cout << endl;
        return;
    }

    curString[pos] = 0;
    solve(curString, pos + 1, n, false);
    if (!filled){
        curString[pos] = 1;
        solve(curString, pos + 1, n, true);
    }

}

int main(){
    int n; cin >> n;
    vector<int> curString(n);
    solve(curString, 0, n, false);

    return 0;
}