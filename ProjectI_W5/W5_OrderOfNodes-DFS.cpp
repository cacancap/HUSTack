#include <iostream>
#include <stack>
using namespace std;

int numberOfNodes, numberOfEdges; 
int* visited;
void DFS(int** adjacencyList, int node){
    stack<int> s;
    s.push(node);
    while (!s.empty()){
        int curNode = s.top();
        s.pop();
        if (!visited[curNode]) {cout << curNode << " "; visited[curNode] = 1;}
        for (int i = numberOfNodes; i >= 1; i--){
            if (adjacencyList[curNode][i] == 1 && !visited[i]){
                s.push(i);
            }
        }
    }
}

int main(){
    
    cin >> numberOfNodes >> numberOfEdges;
    
    // Allocate memmory
    int** adjacencyList = new int*[numberOfNodes + 1];
    visited = new int[numberOfNodes + 1]();
    for (int i = 1; i <= numberOfNodes; i++){
        adjacencyList[i] = new int[numberOfNodes + 1]();
    }
    // Input
    for (int i = 0; i < numberOfEdges; i++){
        int node1, node2; cin >> node1 >> node2;
        adjacencyList[node1][node2] = 1;
        adjacencyList[node2][node1] = 1;
    }
    
    for (int i = 1; i <= numberOfNodes; i++){
        if (!visited[i]) DFS(adjacencyList, i);
    }

    // Deallocate mem
    for (int i = 1; i <= numberOfNodes; i++){
        delete[] adjacencyList[i];
    }
    delete[] adjacencyList;
    adjacencyList = nullptr;
    return 0;
}