#include <iostream>
#include <string>
#include <sstream>
using namespace std;

const int MAXN = 100005;
int arr[MAXN];
long long tree[4 * MAXN];
int n;

// ---------- 1. BUILD ----------
// node: chỉ số nút hiện tại trong mảng tree[]
// l, r: đoạn mà nút này phụ trách
void build(int node, int l, int r){
    if (l == r){
        tree[node] = arr[l];
        return;
    }

    int mid = (l + r) / 2;
    int leftChild = 2 * node;
    int rightChild = 2 * node + 1;

    build(leftChild, l, mid);
    build(rightChild, mid + 1, r);

    tree[node] = tree[leftChild] + tree[rightChild];
}

// ---------- 2. UPDATE ----------
// gán a[pos] = val, cập nhật lại các nút bị ảnh hưởng
void update(int node, int l, int r, int pos, int val){
    if (l == r){
        tree[node] == val;
        return;
    }

    int mid = (l + r) / 2;
    int leftChild = node * 2;
    int rightChild = node * 2 + 1;

    if (pos <= mid){
        update(leftChild, l, mid, pos, val);
    } else {
        update(rightChild, mid + 1, r, pos, val);
    }

    tree[node] = tree[leftChild] + tree[rightChild];
}

long long query(int node, int l, int r, int ql, int qr){
    // Outside
    if (qr < l || r < ql) return 0;

    // Embrace
    if (ql <= l && r <= qr){
        return tree[node];
    }

    // Intersect
    int mid = (l + r) / 2;
    long long leftSum = query(2 * node, l, mid, ql, qr);
    long long rightSum = query(2 * node + 1, mid + 1, r, ql, qr);
    return leftSum + rightSum;
}

void solve(){
    cin >> n;
    for (int i = 1; i <= n; i++){
        cin >> arr[i];
    }

    build(1, 1, n);

    char dummy; cin >> dummy;

    cin.ignore();
    string line;
    while (getline(cin, line)){
        stringstream ss(line);
        string token;
        ss >> token;
        if (token == "find-max"){
            
        }
    }
}

int main(){
    solve();

    return 0;
}