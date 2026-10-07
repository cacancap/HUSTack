#include <iostream>
#include <vector>
#include <stack>
using namespace std;

vector<vector<int>> table(9, vector<int>(9, 0));
vector<vector<bool>> rowTracker(10, vector<bool> (10, false));
vector<vector<bool>> colTracker(10, vector<bool> (10, false));
vector<vector<bool>> squareTracker(10, vector<bool> (10, false));
stack<pair<int, int>> remainingCells;

int getSquarePosition(int r, int c){
    if (r >= 0 && r <= 2){
        if (c >= 0 && c <= 2) return 0;
        if (c >= 3 && c <= 5) return 1;
        if (c >= 6 && c <= 8) return 2;
    } else if (r >= 3 && r <= 5){
        if (c >= 0 && c <= 2) return 3;
        if (c >= 3 && c <= 5) return 4;
        if (c >= 6 && c <= 8) return 5;
    } else if (r >= 6 && r <= 8){
        if (c >= 0 && c <= 2) return 6;
        if (c >= 3 && c <= 5) return 7;
        if (c >= 6 && c <= 8) return 8;
    }
    return -1;
}

// Try filling one cell: checking the conditions
bool fillCell(int r, int c, int val){
    int squarePosition = getSquarePosition(r, c);
    if (squarePosition == -1) return false;
    if (rowTracker[r][val] == 0 && colTracker[c][val] == 0 && squareTracker[squarePosition][val] == 0){
        rowTracker[r][val] = 1;
        colTracker[c][val] = 1;
        squareTracker[squarePosition][val] = 1;
        table[r][c] = val;
        return true;
    }
    return false;
}

void resetCell(int r, int c){
    int val = table[r][c];
    int squarePosition = getSquarePosition(r, c);
    rowTracker[r][val] = 0;
    colTracker[c][val] = 0;
    squareTracker[squarePosition][val] = 0;       
    table[r][c] = 0;
}

void solveSudoku(int& totalSolutions, int& totalRemainingCells, int r, int c){
    if (totalRemainingCells == 0 || remainingCells.empty()){
        totalSolutions += 1;
        return;
    }

    for (int i = 1; i <= 9; i++){
        if (fillCell(r, c, i)){
            pair<int, int> nextDest = remainingCells.top();
            remainingCells.pop();
            totalRemainingCells -= 1;
            // cout << "filled: " << "<" << r << "," << c << ">" << endl;
            solveSudoku(totalSolutions, totalRemainingCells, nextDest.first, nextDest.second);
            resetCell(r, c);
            totalRemainingCells += 1;
            remainingCells.push(nextDest);
            
        }
    }
}


int main(){
    
    int totalRemainingCells = 81;
    for (int i = 0; i < 9; i++){
        for (int j = 0; j < 9; j++){
            cin >> table[i][j];
            if (table[i][j] != 0){
                int squarePos = getSquarePosition(i, j);
                rowTracker[i][table[i][j]] = true;
                colTracker[j][table[i][j]] = true;
                squareTracker[squarePos][table[i][j]] = true;
                totalRemainingCells--;
            } else {
                remainingCells.push(make_pair(i, j));
            }
        }
    }

    int totalSolutions = 0;
    pair<int, int> top = remainingCells.top();
    remainingCells.pop();
    solveSudoku(totalSolutions, totalRemainingCells, top.first, top.second);
    cout << totalSolutions << endl;
    return 0;
}
