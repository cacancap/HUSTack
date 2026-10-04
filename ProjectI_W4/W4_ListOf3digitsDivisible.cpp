#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

int scale(int n){
    float quotient = 100 / (float)n;
    int result = ceil(quotient);
    return result;
}

int main()
{
    int n; cin >> n;
    int count = 0;
    int multiplier = scale(n);
    
    while (n * multiplier <= 999){
        if (multiplier == 0) continue;
        cout << n * multiplier << " ";
        multiplier ++;
    }
    
    
    return 0;
}