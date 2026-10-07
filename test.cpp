#include <iostream>
#include <unordered_map>
using namespace std;

int main(){
    unordered_map<int, bool> test;
    test.insert({1, true});
    cout << (test.find(1) != test.end()) << endl;
    return 0;
}