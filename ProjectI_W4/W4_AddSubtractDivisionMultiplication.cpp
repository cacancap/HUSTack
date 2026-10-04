#include <iostream>
using namespace std;

void input(){
    int a, b;
    cin >> a >> b;
    cout << a + b << " " << a - b << " " << a * b << " " << a / b;
}

int main(){
    input();
    return 0;
}