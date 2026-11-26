#include <iostream>
#include <queue>
#include <vector>
#include <climits>
using namespace std;

struct Step{
    int r;
    int c;
    int count;
    Step(int x, int y): r(x), c(y), count(0) {}
    Step(int x, int y, int count): r(x), c(y), count(count) {}
};

bool isFinished(vector<vector<int>>& A, Step curStep){
    if (curStep.r == 0 || curStep.r == A.size() - 1 || curStep.c == 0 || curStep.c == A[0].size() - 1) return true;
    return false;
}

bool canVisit(vector<vector<bool>>& visited, vector<vector<int>>& A, Step nextStep){
    if (nextStep.r < 0 || nextStep.r >= visited.size() || 
        nextStep.c < 0 || nextStep.c >= visited[0].size() || 
        visited[nextStep.r][nextStep.c] || A[nextStep.r][nextStep.c] == 1) return false;
    return true;
}

int BFS(vector<vector<int>>& A, int posX, int posY){
    int min_count = INT_MAX;
    if (A[posX][posY] == 1) return min_count;
    queue<Step> q;
    vector<vector<bool>> visited(A.size(), vector<bool>(A[0].size(), false));
    q.push({posX, posY});
    visited[posX][posY] = true;
    while (!q.empty()){
        Step curStep = q.front();
        q.pop();
        cout << "visited: " << "{" << curStep.r << " , " << curStep.c << "}: " << curStep.count << endl; 
        if (isFinished(A, curStep)){
            min_count = min(min_count, curStep.count + 1);
            cout << "Finshed" << endl; 
        }

        if (canVisit(visited, A, Step(curStep.r + 1, curStep.c, curStep.count + 1))){
            visited[curStep.r + 1][curStep.c] = true;
            q.push(Step(curStep.r + 1, curStep.c, curStep.count + 1));
        }
        if (canVisit(visited, A, Step(curStep.r - 1, curStep.c, curStep.count + 1))){
            visited[curStep.r - 1][curStep.c] = true;
            q.push(Step(curStep.r - 1, curStep.c, curStep.count + 1));
        }
        if (canVisit(visited, A, Step(curStep.r, curStep.c + 1, curStep.count + 1))){
            visited[curStep.r][curStep.c + 1] = true;
            q.push(Step(curStep.r, curStep.c + 1, curStep.count + 1));
        }
        if (canVisit(visited, A, Step(curStep.r, curStep.c - 1, curStep.count + 1))){
            visited[curStep.r][curStep.c - 1] = true;
            q.push(Step(curStep.r, curStep.c - 1, curStep.count + 1));
        }
    }
    return min_count;
}

int main(){
    int n, m, r, c; cin >> n >> m >> r >> c;
    vector<vector<int>> A(n, vector<int>(m, 0));
    for (int i = 0; i < n; i++){
        for (int j = 0; j < m; j++){
            cin >> A[i][j];
        }
    }
    cout << "size: " << A.size() << ", " << A[0].size() << endl;
    cout << "Result: " << BFS(A, r - 1, c - 1) << endl;

    return 0;
}