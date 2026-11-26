#include <iostream>
#include <vector>
#include <climits>
#include "../profiler.h"
using namespace std;

int min_cost = INT_MAX;

// Baseline: naive TSP
void NaiveTSP(vector<vector<int>>& cost_matrix, vector<int>& visited, int curHop, int curCost, int count){
    // Finished all cities => check to update records.
    if (count == 0){
        min_cost = min(min_cost, curCost + cost_matrix[curHop][0]);
        return;
    }

    // Traverse
    for (int nextHop = 1; nextHop < cost_matrix.size(); nextHop++){
        if (!visited[nextHop]){
            int hopCost = cost_matrix[curHop][nextHop];
            visited[nextHop] = true;
            NaiveTSP(cost_matrix, visited, nextHop, curCost + hopCost, count - 1);
            visited[nextHop] = false;
        }
    }
}

// MinEdge-Branching
void BranchingV1TSP(vector<vector<int>>& cost_matrix, vector<int>& visited, int curHop, int curCost, int count, int min_edge){
    // Finished all cities => check to update records.
    if (count == 0){
        min_cost = min(min_cost, curCost + cost_matrix[curHop][0]);
        return;
    } 

    // Traverse
    for (int nextHop = 1; nextHop < cost_matrix.size(); nextHop++){
        if (!visited[nextHop]){
            int hopCost = cost_matrix[curHop][nextHop];
            if (curCost + hopCost + count * min_edge >= min_cost) continue;
            visited[nextHop] = true;
            BranchingV1TSP(cost_matrix, visited, nextHop, curCost + hopCost, count - 1, min_edge);
            visited[nextHop] = false;
        }
    }
}

// Branching V2: using min out
void BranchingV2TSP(vector<vector<int>>& cost_matrix, vector<int>& visited, int curHop, int curCost, int count, int rem_out, vector<int>& min_out){
    // Check the finish status
    if (count == 0){
        min_cost = min(min_cost, curCost + cost_matrix[curHop][0]);
        return;
    }

    // Traverse
    for (int nextHop = 1; nextHop < cost_matrix.size(); nextHop++){
        if (!visited[nextHop]){
            int hopCost = cost_matrix[curHop][nextHop];
            if (curCost + hopCost + rem_out >= min_cost) continue;
            visited[nextHop] = true;
            BranchingV2TSP(cost_matrix, visited, nextHop, curCost + hopCost, count - 1, rem_out - min_out[curHop], min_out);
            visited[nextHop] = false;
        }
    }
}

int main(){
    int n; cin >> n;
    int min_edge = INT_MAX;
    vector<vector<int>> cost_matrix(n, vector<int> (n));
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            cin >> cost_matrix[i][j];
            if (cost_matrix[i][j] != 0) min_edge = min(min_edge, cost_matrix[i][j]);
        }
    }

    // {
    //     PROFILE_SCOPE("Branch and Bound - V2 TSP");
    //     min_cost = INT_MAX;
    //     vector<int> visited(n, false);
    //     visited[0] = true;
    //     vector<int> min_out(n);
    //     for (int i = 0; i < n; i++){
    //         int min_outi = INT_MAX;
    //         for (int j = 0; j < n; j++){
    //             if (i != j){
    //                 min_outi = min(min_outi, cost_matrix[i][j]);
    //             }
    //         }
    //         min_out[i] = min_outi;
    //     }

    //     int rem_out = 0;
    //     for (int i = 1; i < n; i++) rem_out += min_out[i];

    //     BranchingV2TSP(cost_matrix, visited, 0, 0, n - 1, rem_out, min_out);
    //     cout << "V2 TSP: " << min_cost << endl;
    // }

    {
        PROFILE_SCOPE("Branch and Bound - V1 TSP");
        min_cost = INT_MAX;
        vector<int> visited(n, false);
        visited[0] = true;
        BranchingV1TSP(cost_matrix, visited, 0, 0, n - 1, min_edge);
        cout << "V1 TSP: " << min_cost << endl;
    }

    // {
    //     PROFILE_SCOPE("Naive TSP");
    //     min_cost = INT_MAX;
    //     vector<int> visited(n, false);
    //     visited[0] = true;
    //     NaiveTSP(cost_matrix, visited, 0, 0, n - 1);
    //     cout << "Naive TSP: " << min_cost << endl;
    //     // Result: 70000ms in average.
    // }

    return 0;
}