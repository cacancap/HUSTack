#include <iostream>

using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    int odd = 0, even = 0;
    for (int i = 0; i < n; i++){
        int a;
        cin >> a;
        if (a % 2 == 0) even +=1;
        else odd += 1;
    }

    cout << odd << " " << even << endl;
    return 0;
}