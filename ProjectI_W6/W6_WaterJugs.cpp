#include <iostream>
#include <queue>
#include <algorithm>
#include <cstring>
using namespace std;

/* Movement when pouring water:
    - Move 1: Fill the A only.
    - Move 2: Fill the B only.
    - Move 3: Pour the A to B untill B is full or A is empty.
    - Move 4: Same but reverse to 3th. 
    - Move 5: Clear the A only.
    - Move 6: Clear the B only.
*/

bool visited[905][905];


struct PourTurn{
    int litres_a;
    int litres_b;
    int turn_number = 0;
    PourTurn(int a, int b, int turn): litres_a(a), litres_b(b), turn_number(turn) {}
};

inline pair<int, int> move(int a, int b, int x, int y, int direction){
    switch(direction){
        case 1: return make_pair(a, y);
        case 2: return make_pair(x, b);
        case 3: return (x + y > b) ? make_pair(x + y - b, b) : make_pair(0, x + y);
        case 4: return (x + y > a) ? make_pair(a, x + y - a) : make_pair(x + y, 0);
        case 5: return make_pair(0, y);
        case 6: return make_pair(x, 0);
        default: return make_pair(-1, -1);
    }
}

void pourSearching(int a, int b, int c){
    if ((c > a && c > b) || (c % __gcd(a, b) != 0)){
        cout << "-1" << endl;
        return;
    }
    
    queue<PourTurn> q;
    q.push(PourTurn(0, 0, 0));
    visited[0][0] = true;
    while (!q.empty()){
        PourTurn curState = q.front();
        q.pop();
        if (curState.litres_a == c || curState.litres_b == c){  // Check finish state
            cout << curState.turn_number << endl;
            return;
        }
        
        for (int direction = 1; direction <= 6; direction++){
            pair<int, int> nextMove = move(a, b, curState.litres_a, curState.litres_b, direction);
            if (!visited[nextMove.first][nextMove.second]){
                q.push({nextMove.first, nextMove.second, curState.turn_number + 1});
                visited[nextMove.first][nextMove.second] = true;
            }
        }    
            
    }
}

int main(){
    memset(visited, false, sizeof(visited));
    int a, b, c; cin >> a >> b >> c;
    pourSearching(a, b, c);
    return 0;
}