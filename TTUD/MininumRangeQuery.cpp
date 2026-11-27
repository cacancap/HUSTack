#include <iostream>
#include <climits>
using namespace std;

int MAXN = 1000005;
int *tree = nullptr;
int *arr = nullptr; 

void build(int node, int l, int r){
	if (l == r){
		tree[node] = arr[l];
		return;
	}
	
	int mid = (l + r) / 2;
	int leftChild = node * 2, rightChild = node * 2 + 1;
	build(leftChild, l, mid);
	build(rightChild, mid + 1, r);
	tree[node] = min(tree[leftChild], tree[rightChild]);
}

void update(int node, int l, int r, int pos, int newVal){
	if (l == r){
		tree[node] = newVal;
		return;
	}
	
	int mid = (l + r) / 2;
	int leftChild = node * 2, rightChild = node * 2 + 1;
	
	if (pos <= mid){
		update(leftChild, l, mid, pos, newVal);
	} else {
		update(rightChild, mid + 1, r, pos, newVal);
	}
	
	tree[node] = min(tree[leftChild], tree[rightChild]);
}

int query(int node, int l, int r, int ql, int qr){
	if (r < ql || qr < l) return INT_MAX;
	
	if (ql <= l && r <= qr) return tree[node];
	
	int mid = (l + r) / 2;
	return min(
		query(node * 2, l, mid, ql, qr),
		query(node * 2 + 1, mid + 1, r, ql, qr)
	);
}

int main(){
	int n;
	cin >> n;
	tree = new int[4 * n];
	arr = new int[n];
	
	for (int i = 0; i < n; i++){
		cin >> arr[i];
	}
	
	build(1, 0, n - 1);
	
	int m; cin >> m;
	long long sum = 0;
	for (int i = 0; i < m; i++){
		int ql, qr;
		cin >> ql >> qr;
		sum += query(1, 0, n - 1, ql, qr);
	}
	cout << sum << endl;
	
	return 0;
}
