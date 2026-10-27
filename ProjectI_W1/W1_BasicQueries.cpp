#include <iostream>
#include <string>
#include <sstream>
#include <climits>
using namespace std;

int n;
const int MAXN = 100005;
int arr[MAXN];

struct Node{
    long long sum;
    int max;
    int min;
};

Node* tree = new Node[4 * MAXN];


void build(int node, int l, int r){
    if (l == r){
        tree[node].sum = arr[l];
        tree[node].max = arr[l];
        tree[node].min = arr[l];
        return;
    }

    int mid = (l + r) / 2;
    int leftChild = 2 * node, rightChild = 2 * node + 1;

    build(leftChild, l, mid);
    build(rightChild, mid + 1, r);

    tree[node].sum = tree[leftChild].sum + tree[rightChild].sum;
    tree[node].max = max(tree[leftChild].max, tree[rightChild].max);
    tree[node].min = min(tree[leftChild].min, tree[rightChild].min);
}

void update(int node, int l, int r, int pos, int val){
    if (l == r){
        tree[node].max = val;
        tree[node].sum = val;
        tree[node].min = val;
        return;
    }

    int mid = (l + r) / 2;
    int leftChild = 2 * node, rightChild = 2 * node + 1;
    if (pos <= mid){
        update(leftChild, l, mid, pos, val);
    } else {
        update(rightChild, mid + 1, r, pos, val);
    }

    tree[node].sum = tree[leftChild].sum + tree[rightChild].sum;
    tree[node].max = max(tree[leftChild].max, tree[rightChild].max);
    tree[node].min = min(tree[leftChild].min, tree[rightChild].min);
}

int query_max(int node, int l, int r, int ql, int qr){
    if (ql > r || qr < l) return INT_MIN;
    if (ql <= l && r <= qr) return tree[node].max;

    int mid = (l + r) / 2;
    int leftMax = query_max(node * 2, l, mid, ql, qr);
    int rightMax = query_max(node * 2 + 1, mid + 1, r, ql, qr);
    return max(leftMax, rightMax);
}

int query_min(int node, int l, int r, int ql, int qr){
    if (ql > r || qr < l) return INT_MAX;
    if (ql <= l && r <= qr) return tree[node].min;

    int mid = (l + r) / 2;
    int leftMin = query_min(node * 2, l, mid, ql, qr);
    int rightMin = query_min(node * 2 + 1, mid + 1, r, ql, qr);
    return min(leftMin, rightMin);
}

long long query_sum(int node, int l, int r, int ql, int qr){
    if (ql > r || qr < l){
        return 0;
    }

    if (ql <= l && r <= qr){
        return tree[node].sum;
    }

    int mid = (l + r) / 2;
    long long leftSum = query_sum(node * 2, l, mid, ql, qr);
    long long rightSum = query_sum(node * 2 + 1, mid + 1, r, ql, qr);
    return leftSum + rightSum;
}

void solve(){
    cin >> n;
    for (int i = 1; i <= n; i++){
        cin >> arr[i];
    }

    build(1, 1, n);

    char c; cin >> c; cin.ignore();
    string line;
    while (getline(cin, line)){
        if (line.empty()) continue;

        stringstream ss(line);
        string token;
        ss >> token;

        if (token == "find-max"){
            cout << query_max(1, 1, n, 1, n) << endl;
        } else if (token == "find-min"){
            cout << query_min(1, 1, n, 1, n) << endl;
        } else if (token == "find-max-segment"){
            int ql, qr;
            if (!(ss >> ql >> qr)) {
                cout << "Error01!" << endl;
                return;
            }
            cout << query_max(1, 1, n, ql, qr) << endl;
        } else if (token == "find-min-segment"){
            int ql, qr;
            if (!(ss >> ql >> qr)) {
                cout << "Error01!" << endl;
                return;
            }
            cout << query_min(1, 1, n, ql, qr) << endl;
        } else if (token == "sum"){
            cout << query_sum(1, 1, n, 1, n) << endl;
        } else {
            return;
        }
    }

    string dummy2;
    getline(cin, dummy2);
}

int main(){
    solve();
    delete[] tree;
    return 0;
}