#include <iostream>
#include <vector>
using namespace std;

int k_subsequence_even(vector<int>& arr, int k){
    if (k <= 0 || k > arr.size() / 2) return 0;
    int count = 0;
    int curWeight = 0;
    
    int left = 0, right = k - 1;

    for (int i = left; i <= right; i++) curWeight += arr[i];
    
    while (left < right && right < arr.size()){
        if (curWeight % 2 == 0) count += 1;
        curWeight -= arr[left]; 
        left ++; right ++;
        if (right == arr.size()) break;
        curWeight += arr[right];
    }

    return count;
}

int main(){
    int n, k;
    cin >> n >> k;
    vector<int> arr(n);
    for (int i = 0; i < n; i++) cin >> arr[i];
    cout << k_subsequence_even(arr, k) << endl;
    return 0;
}