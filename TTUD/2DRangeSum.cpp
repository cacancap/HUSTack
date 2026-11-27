#include <iostream>
#include <vector>
using namespace std;

void build(vector<vector<int>>& tabulation, vector<vector<int>>& matrix){
    tabulation[0][0] = matrix[0][0];
    // Fill value to the first column
    for (int i = 1; i < matrix.size(); i++){
        tabulation[i][0] = tabulation[i - 1][0] + matrix[i][0];
    }
    // Fill value to the first row
    for (int i = 1; i < matrix[0].size(); i++){
        tabulation[0][i] = tabulation[0][i - 1] + matrix[0][i];
    }
    for (int i = 1; i < matrix.size(); i++){
        for (int j = 1; j < matrix[0].size(); j++){
            tabulation[i][j] = matrix[i][j] + tabulation[i - 1][j] + tabulation[i][j - 1] - tabulation[i - 1][j - 1];
        }
    }
}

int query(vector<vector<int>>& tabulation, int x1, int y1, int x2, int y2){
    int XSide = (x1 - 1 >= 0) ? tabulation[x1 - 1][y2] : 0;
    int YSide = (y1 - 1 >= 0) ? tabulation[x2][y1 - 1] : 0;
    int CrossSide = (x1 - 1 >= 0 && y1 - 1 >= 0) ? tabulation[x1 - 1][y1 - 1] : 0;
    return tabulation[x2][y2] - XSide - YSide + CrossSide; 
}

int main(){
    // input
    int n, m, q; cin >> n >> m >> q;
    vector<vector<int>> matrix(n, vector<int> (m, 0));
    vector<vector<int>> tabulation(n, vector<int> (m, 0));
    for (int i = 0; i < n; i++){
        for (int j = 0; j < m; j++){
            cin >> matrix[i][j];
        }
    }
    build(tabulation, matrix);
    cout << "Build result: " << endl;
    for (int i = 0; i < tabulation.size(); i++){
        for (int j = 0; j < tabulation[0].size(); j++){
            cout << tabulation[i][j] << " ";
        }
        cout << endl;
    }
    for (int i = 0; i < q; i++){
        int x1, x2, y1, y2; cin >> x1 >> y1 >> x2 >> y2;
        cout << query(tabulation, x1 - 1, y1 - 1, x2 - 1, y2 - 1) << endl;
    }
    

    return 0;
}