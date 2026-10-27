#include <iostream>
#include <vector>
using namespace std;
const int quotient = 1e9 + 7;


int combination(vector<vector<int>>& memoization, int n, int k){
    if (k == n || k == 0) return 1;
    if (k > n) return 0;
    if (memoization[n][k] != -1) return memoization[n][k];

    memoization[n][k] = (combination(memoization, n - 1, k - 1) + combination(memoization, n - 1, k)) % quotient;
    return memoization[n][k]; 
}

int main(){
    int k, n; cin >> k >> n;
    vector<vector<int>> memoization(n + 1, vector<int>(k + 1, -1));
    
    cout << combination(memoization, n, k) << endl;

    return 0;
}