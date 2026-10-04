#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>

using namespace std;

int m, n;
vector<vector<int>> teachersOfCourse;
vector<vector<bool>> canTeach;
vector<int> credits;
vector<int> LB;
vector<unsigned int> conflictMask;

// Trạng thái tìm kiếm
vector<unsigned int> assignedMask;
vector<int> teacherLoad;
vector<int> teacherCourseCount;

vector<int> courseOrder;
vector<int> remCredit;
vector<vector<int>> remCanTeach;

int bestMaxLoad = 1e9;

void backtrack(int step, int currentTotalLoad) {
    if (step == n) {
        for (int t = 0; t < m; ++t) {
            if (teacherCourseCount[t] < LB[t]) return;
        }

        int currentMaxLoad = 0;
        for (int t = 0; t < m; ++t) {
            currentMaxLoad = max(currentMaxLoad, teacherLoad[t]);
        }
        bestMaxLoad = min(bestMaxLoad, currentMaxLoad);
        return;
    }

    // Tỉa nhánh: cận tải trọng trung bình
    int minPossibleMax = (currentTotalLoad + remCredit[step] + m - 1) / m;
    if (minPossibleMax >= bestMaxLoad) return;

    // Tỉa nhánh: kiểm tra tính khả thi của LB
    int totalDeficit = 0;
    for (int t = 0; t < m; ++t) {
        if (teacherCourseCount[t] + remCanTeach[t][step] < LB[t]) return;
        if (teacherCourseCount[t] < LB[t]) {
            totalDeficit += (LB[t] - teacherCourseCount[t]);
        }
    }
    if (totalDeficit > n - step) return;

    int c = courseOrder[step];

    // Lọc các giáo viên hợp lệ
    vector<int> candidateTeachers;
    for (int t : teachersOfCourse[c]) {
        if (teacherLoad[t] + credits[c] >= bestMaxLoad) continue;
        if (assignedMask[t] & conflictMask[c]) continue;
        candidateTeachers.push_back(t);
    }

    // Ưu tiên giáo viên có tải trọng nhỏ hơn
    sort(candidateTeachers.begin(), candidateTeachers.end(), [](int a, int b) {
        return teacherLoad[a] < teacherLoad[b];
    });

    for (int t : candidateTeachers) {
        if (teacherLoad[t] + credits[c] >= bestMaxLoad) continue;

        assignedMask[t] |= (1U << c);
        teacherLoad[t] += credits[c];
        teacherCourseCount[t]++;

        backtrack(step + 1, currentTotalLoad + credits[c]);

        assignedMask[t] ^= (1U << c);
        teacherLoad[t] -= credits[c];
        teacherCourseCount[t]--;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    if (!(cin >> m >> n)) return 0;

    teachersOfCourse.assign(n, vector<int>());
    canTeach.assign(m, vector<bool>(n, false));

    for (int t = 0; t < m; ++t) {
        int k;
        cin >> k;
        for (int j = 0; j < k; ++j) {
            int c;
            cin >> c;
            --c;
            canTeach[t][c] = true;
            teachersOfCourse[c].push_back(t);
        }
    }

    credits.resize(n);
    for (int i = 0; i < n; ++i) cin >> credits[i];

    LB.resize(m);
    int sumLB = 0;
    for (int i = 0; i < m; ++i) {
        cin >> LB[i];
        sumLB += LB[i];
    }

    int K;
    cin >> K;
    conflictMask.assign(n, 0);
    for (int k = 0; k < K; ++k) {
        int u, v;
        cin >> u >> v;
        --u; --v;
        conflictMask[u] |= (1U << v);
        conflictMask[v] |= (1U << u);
    }

    // Kiểm tra nhanh điều kiện vô nghiệm
    if (sumLB > n) {
        cout << -1 << "\n";
        return 0;
    }
    for (int c = 0; c < n; ++c) {
        if (teachersOfCourse[c].empty()) {
            cout << -1 << "\n";
            return 0;
        }
    }

    // MRV heuristic: Ưu tiên môn có ít giáo viên dạy được và tín chỉ lớn
    courseOrder.resize(n);
    iota(courseOrder.begin(), courseOrder.end(), 0);
    sort(courseOrder.begin(), courseOrder.end(), [](int a, int b) {
        if (teachersOfCourse[a].size() != teachersOfCourse[b].size()) {
            return teachersOfCourse[a].size() < teachersOfCourse[b].size();
        }
        return credits[a] > credits[b];
    });

    // Tiền xử lý tổng tín chỉ và số môn có thể dạy còn lại để tỉa nhánh
    remCredit.assign(n + 1, 0);
    for (int i = n - 1; i >= 0; --i) {
        remCredit[i] = remCredit[i + 1] + credits[courseOrder[i]];
    }

    remCanTeach.assign(m, vector<int>(n + 1, 0));
    for (int t = 0; t < m; ++t) {
        for (int i = n - 1; i >= 0; --i) {
            remCanTeach[t][i] = remCanTeach[t][i + 1] + (canTeach[t][courseOrder[i]] ? 1 : 0);
        }
        if (remCanTeach[t][0] < LB[t]) {
            cout << -1 << "\n";
            return 0;
        }
    }

    assignedMask.assign(m, 0);
    teacherLoad.assign(m, 0);
    teacherCourseCount.assign(m, 0);

    backtrack(0, 0);

    cout << (bestMaxLoad >= 1e9 ? -1 : bestMaxLoad) << "\n";

    return 0;
}
