#include <iostream>
#include <vector>
using namespace std;

void input(){
    int n;      // Number of days that client deposited
    cin >> n;
    
}

int query(vector<int>& prefix, int start, int end){
    return prefix[end] - prefix[start - 1];
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;

    // initiate records (to save daily deposits) and LUT (look-up table) for quick queries.
    vector<int> records(n + 1);
    vector<int> prefix(n + 1, 0);
    for (int i = 1; i <= n; i++){
        cin >> records[i];
        prefix[i] = prefix[i - 1] + records[i];
    }

    int m;
    cin >> m;
    for (int i = 0; i < m; i++){
        int i1, j1, i2, j2;
        cin >> i1 >> j1 >> i2 >> j2;
        int sum1 = query(prefix, i1, j1), sum2 = query(prefix, i2, j2);
        if (sum1 < sum2) cout << "1" << endl;
        else cout << "0" << endl;
    }

    // cout << query(LUT, records, 1, 3) << endl;
    // cout << query(LUT, records, 1, 3) << endl;

    return 0;
}