#include <iostream>
#include <queue>

using namespace std;

int numberOfNodes, numberOfEdges; 
int* visited;
void BFS(int** adjacencyList, int node){
    queue<int> q;
    q.push(node);
    visited[node] = 1;
    while (!q.empty()){
        int curNode = q.front();
        q.pop();
        cout << curNode << " ";
        for (int i = 1; i <= numberOfNodes; i++){
            if (adjacencyList[curNode][i] == 1 && !visited[i]){
                q.push(i);
                visited[i] = 1;
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
        if (!visited[i]) BFS(adjacencyList, i);
    }

    // Deallocate mem
    for (int i = 1; i <= numberOfNodes; i++){
        delete[] adjacencyList[i];
    }
    delete[] adjacencyList;
    adjacencyList = nullptr;
    return 0;
}