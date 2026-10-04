#include <iostream>
#include <vector>
using namespace std;

vector<int> curString;
vector<bool> *visited = nullptr;
void permutation(vector<bool>& visited, int n, int pos){
    if (pos == n){
        for (int i = 0; i < curString.size(); i++){
            cout << curString[i] << " ";
        }
        cout << endl;
        return;
    }

    for (int i = 1; i <= n; i++){
        if (!visited[i]){
            visited[i] = true;
            curString.push_back(i);
            permutation(visited, n, pos + 1);
            visited[i] = false;
            curString.pop_back();
        }
    }
}

int main(){
    int n; cin >> n;
    vector<bool> visited(n + 1, 0);
    permutation(visited, n, 0);
    return 0;
}