#include <iostream>
#include <algorithm>
#include <cmath>
#include <iomanip>
using namespace std;

const double epsilon = 1e-6;

void solveEquation(double a, double b, double c){
    double delta = b * b - 4 * a * c;
    if (delta < 0){
        cout << "NO SOLUTION" << endl;
        return;
    } else if (abs(delta) < epsilon){
        cout << fixed << setprecision(2) << -b / (2 * a) << endl;
        return;
    } else {
        double x1 = (-b - sqrt(delta)) / (2 * a);
        double x2 = (-b + sqrt(delta)) / (2 * a);
        cout << fixed << setprecision(2) << x1 << " " << x2 << endl;
    }
}

int main(){
    double a, b, c;
    cin >> a >> b >> c;

    solveEquation(a, b, c);
    return 0;
}