#include <iostream>
#include <vector>
#include <unordered_set>
using namespace std;

struct Graph{
    int numberOfNodes;
    vector<vector<bool>> adjacencyTable;
    unordered_set<int> visited;
    bool has_hamilton_cycle = false;
    Graph(int number_of_nodes): numberOfNodes(number_of_nodes), 
    adjacencyTable(vector<vector<bool>> (number_of_nodes + 1, vector<bool> (number_of_nodes + 1, 0))) {}
};


void hamilton_traversal(Graph& targetGraph, int node){
    // Check the finish status
    if (targetGraph.visited.size() == targetGraph.numberOfNodes){
        if (targetGraph.adjacencyTable[node][1]) targetGraph.has_hamilton_cycle = true;
        return;
    }

    for (int i = 1; i <= targetGraph.numberOfNodes; i++){
        if (targetGraph.adjacencyTable[node][i] && targetGraph.visited.find(i) == targetGraph.visited.end()){
            targetGraph.visited.insert(i);
            hamilton_traversal(targetGraph, i);
            targetGraph.visited.erase(i);
        }
    }
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T; cin >> T;
    for (int i = 0; i < T; i++){
        int number_of_nodes, number_of_edges; cin >> number_of_nodes >> number_of_edges;
        Graph newGraph = Graph(number_of_nodes);
        for (int j = 0; j < number_of_edges; j++){
            int node1, node2; cin >> node1 >> node2;
            newGraph.adjacencyTable[node1][node2] = true;
            newGraph.adjacencyTable[node2][node1] = true;
        }
        newGraph.visited.insert(1);
        hamilton_traversal(newGraph, 1);
        cout << (newGraph.has_hamilton_cycle == 1) << endl;
    }

    return 0;
}