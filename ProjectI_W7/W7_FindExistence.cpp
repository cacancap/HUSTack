#include <iostream>
#include <set>

using namespace std;

int main(){
    int n; cin >> n;
    set<int> container;
    for (int i = 0; i < n; i++){
        int newVal; cin >> newVal;
        if (container.find(newVal) != container.end()){
            cout << "1" << endl;
        } else {
            container.insert(newVal);
            cout << "0" << endl;
        }
    }

    return 0;
}