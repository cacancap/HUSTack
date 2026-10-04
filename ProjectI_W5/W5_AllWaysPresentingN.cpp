#include <iostream>
#include <string>
#include <vector>
using namespace std;

void solve(vector<int>& curString, int curNumber, size_t pos, int remainingSum){
    if (remainingSum == 0){
        for (int i = 0; i < curString.size(); i++){
            cout << curString[i] << " ";
        }
        cout << endl;
        return;
    } else if (curNumber > remainingSum){
    }

    for (int i = curNumber; i <= remainingSum; i++){
        curString.push_back(i);
        solve(curString, i, pos + 1, remainingSum - i);
        curString.pop_back();
    }
}

int main(){
    int n; cin >> n;
    vector<int> curString;
    solve(curString, 1, 0, n);
    return 0;
}