#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

int cost_mask[5000];
const int INF = 1e9;


// Check if a client subject to a group (with mask number) or not
bool subjectToGroup(int mask, int clientNumber){
    if (mask >> (clientNumber - 1) & 1) return true;
    return false;
}

int ableToDeliver(int mask, vector<int>& demand, int Q){
    int rem_cap = Q;
    bool can_deliver = true;
    int total_client = 0;
    for (int client = 1; client < demand.size(); client++){
        if (subjectToGroup(mask, client)){
            rem_cap -= demand[client];
            total_client += 1;
            if (rem_cap < 0){
                can_deliver = false;
                break;
            }
        }       
    }
    if (!can_deliver) return -1;
    return total_client;
}

// Assign 
void tsp(vector<vector<int>>& cost_matrix, vector<bool>& visited, int mask, int curHop, int count, int curCost, int rem_out, vector<int>& min_out){
    // Check the finish status
    if (count == 0){
        cost_mask[mask] = min(cost_mask[mask], curCost + cost_matrix[curHop][0]);
        return;
    }

    // Traverse
    for (int nextHop = 1; nextHop < cost_matrix.size(); nextHop++){
        if (!visited[nextHop] && subjectToGroup(mask, nextHop)){;
            int hopCost = cost_matrix[curHop][nextHop];
            // Branch and bound: using rem_out
            if (curCost + hopCost + rem_out >= cost_mask[mask]) continue;
            visited[nextHop] = true;
            tsp(cost_matrix, visited, mask, nextHop, count - 1, curCost + hopCost, rem_out - min_out[nextHop], min_out);
            visited[nextHop] = false;
        }
    }
}

void printClientsInMask(int mask, int n){
    cout << "Mask: " << mask << ": ";
    for (int i = 1; i <= n; i++){
        if (subjectToGroup(mask, i)) cout << i << ", ";
    }
    cout << endl;
}

int calculate_rem_out(int mask, int n, vector<int>& min_out){
    int total = 0;
    for (int i = 1; i <= n; i++){
        if (subjectToGroup(mask, i)){
            total += min_out[i];
        }
    }
    return total;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    fill(begin(cost_mask), end(cost_mask), INF);
    int n, K, Q; cin >> n >> K >> Q;
    vector<int> demand(n + 1);
    vector<vector<int>> distance_matrix(n + 1, vector<int>(n + 1, 0));
    vector<bool> visited(n + 1, false);
    vector<int> min_out(n + 1, INT_MAX);
    for (int i = 1; i <= n; i++){
        cin >> demand[i];
    }
    for (int i = 0; i <= n; i++){
        for (int j = 0; j <= n; j++){
            cin >> distance_matrix[i][j];
        }
    }

    // Assigning min_out
    int rem_out = 0;
    for (int i = 0; i <= n; i++){
        for (int j = 0; j <= n; j++){
            if (i != j){
                min_out[i] = min(min_out[i], distance_matrix[i][j]);
            }
        }
    }
    for (int i = 0; i <= n; i++){
        rem_out += min_out[i];
    }
    rem_out -= min_out[0];
    visited[0] = true;

    // Calculate min cost for each mask
    for (int mask = 1; mask < (1 << n); mask++){
        int number_of_clients = ableToDeliver(mask, demand, Q);
        
        if (number_of_clients > 0){
            int rem_out = calculate_rem_out(mask, n, min_out);
            tsp(distance_matrix, visited, mask, 0, number_of_clients, 0, rem_out, min_out);
        }
    }

    

    return 0;
}