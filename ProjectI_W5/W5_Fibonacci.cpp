#include <iostream>
using namespace std;

void fibonacci(int n){
    int *tabulation = new int[2];
    tabulation[0] = 0; tabulation[1] = 1;
    for (int i = 0; i < (n / 3); i++){
        tabulation[2] = tabulation[0] + tabulation[1];
        tabulation[0] = tabulation[1] + tabulation[2];
        tabulation[1] = tabulation[2] + tabulation[0];
    }

    int idx = ((n % 3) - 1 < 0) ? 2 : (n % 3 - 1);

    cout << tabulation[idx] << endl;
}

int main(){
    int n; cin >> n;

    fibonacci(n);

    return 0;
}