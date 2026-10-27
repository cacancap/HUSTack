#include <iostream>
#include <vector>
#include <stack>
using namespace std;

const pair<int, int> error = make_pair(-1, -1);
// Move function: returns destination with a specific trajectory, returns pair(-1, -1) if the movement is invalid
// Following Trigonometric circle
pair<int, int> nextPosition(int direction, int r, int c, int N){
    if (direction == 1){
        if (r - 1 >= 0 && c + 2 < N){
            return make_pair(r - 1, c + 2);
        } else {
            return error;
        }
    } else if (direction == 2){
        if (r - 2 >= 0 && c + 1 < N){
            return make_pair(r - 2, c + 1);
        } else {
            return error;
        }
    } else if (direction == 3){
        if (r - 2 >= 0 && c - 1 >= 0){
            return make_pair(r - 2, c - 1);
        } else return error;
    } else if (direction == 4){
        if (r - 1 >= 0 && c - 2 >= 0){
            return make_pair(r - 1, c - 2);
        } else return error;
    } else if (direction == 5){
        if (r + 1 < N && c - 2 >= 0){
            return make_pair(r + 1, c - 2);
        } else return error;
    } else if (direction == 6){
        if (r + 2 < N && c - 1 >= 0){
            return make_pair(r + 2, c - 1);
        } else return error;
    } else if (direction == 7){
        if (r + 2 < N && c + 1 < N){
            return make_pair(r + 2, c + 1);
        } else return error;
    } else if (direction == 8){
        if (r + 1 < N && c + 2 < N){
            return make_pair(r + 1, c + 2);
        } else return error;
    } 
    return error;
}

int maxSum = -1e9;

// Backtracking for knight's tour with branch and bound
void travel(vector<vector<int>>& matrix, vector<vector<bool>>& visited, int r, int c, int curSum, int remainingPositive){
    curSum += matrix[r][c];
    if (matrix[r][c] > 0) remainingPositive -= matrix[r][c];
    if (curSum > maxSum){
        maxSum = curSum;
    }

    // Nhánh cận: nếu tổng hiện tại + tất cả số dương còn lại trên bàn cờ <= maxSum thì cắt tỉa
    if (curSum + remainingPositive <= maxSum) return;

    visited[r][c] = true;
    for (int i = 1; i <= 8; i++){
        pair<int, int> newDest = nextPosition(i, r, c, matrix.size());
        if (newDest.first != -1 && !visited[newDest.first][newDest.second]){
            travel(matrix, visited, newDest.first, newDest.second, curSum, remainingPositive);
        }
    }
    // Hoàn tác (backtrack)
    visited[r][c] = false;
}

int main(){
    int N, r, c;
    if (!(cin >> N >> r >> c)) return 0;
    r--; c--; // Chỉ số dòng và cột trong đề bài là 1-based
    vector<vector<int>> matrix(N, vector<int> (N, 0));
    vector<vector<bool>> visited(N, vector<bool> (N, false));
    int totalPositive = 0;
    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){
            cin >> matrix[i][j];
            if (matrix[i][j] > 0) totalPositive += matrix[i][j];
        }
    }

    travel(matrix, visited, r, c, 0, totalPositive);

    cout << maxSum << endl;

    return 0;
}