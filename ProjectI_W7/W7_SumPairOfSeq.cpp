#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int sumPairOfSeq_TwoPointers(vector<int>& arr, int M){
    int left = 0, right = arr.size() - 1;
    sort(arr.begin(), arr.end(), [&](int a, int b){
        return a < b;
    });
    int count = 0;
    while (left < right){
        if (arr[left] + arr[right] == M){
            count++;
            left++; right--;
        } else if (arr[left] + arr[right] > M){
            right --;
        } else {
            left++;
        }
    }
    return count;
}

int main(){
    int n, M; cin >> n >> M;
    vector<int> arr(n);
    for (int i = 0; i < n; i++){
        cin >> arr[i];
    }
    cout << sumPairOfSeq_TwoPointers(arr, M) << endl;

    return 0;
}