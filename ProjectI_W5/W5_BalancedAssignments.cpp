#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <climits>
using namespace std;

int best_max_load = INT_MAX;

class Courses{
public:
    vector<int> credits;    // Count the credits of each course.
    vector<vector<bool>> conflictingTable;  // Track the confliction in every pair of courses.
    vector<int> conflict_count; // Count the number of conflictions in specific course.
    vector<int> assigned_to;    // Track the teacher that a course is assigned to.
    vector<vector<bool>> is_preference;  // Mark the subject as prefered by a specific teacher.
    vector<int> preference_count;   // Count of teachers who prefer a subject.
    vector<int> sorted_course_order;
    int numberOfTeachers, numberOfCourses;

    Courses(int numberOfTeachers, int numberOfCourses){
        this->numberOfTeachers = numberOfTeachers; 
        this->numberOfCourses = numberOfCourses;
        credits = vector<int> (numberOfCourses + 1, 0);
        conflictingTable = vector<vector<bool>> (numberOfCourses + 1, vector<bool> (numberOfCourses + 1, false));
        conflict_count = vector<int> (numberOfCourses + 1, 0);
        assigned_to = vector<int> (numberOfCourses + 1, 0);
        is_preference = vector<vector<bool>> (numberOfCourses + 1, vector<bool> (numberOfTeachers + 1, false));
        preference_count = vector<int> (numberOfCourses + 1, 0);
    }
};

class Teachers{
public:
    int cur_max_load = 0;
    vector<int> LB; // Lower bound: minimum number of courses that a teacher can hold.
    vector<vector<int>> teached;    // adjacent list: track the teached courses in each teacher.
    vector<int> load;   // Track the number of credits in each teacher.

    Teachers(int numberOfTeachers, int numberOfCourses){
        LB = vector<int> (numberOfTeachers + 1, 0);
        teached = vector<vector<int>> (numberOfTeachers + 1, vector<int> ());
        load = vector<int> (numberOfTeachers + 1, 0);
    }
};

bool can_teach(Courses& courses, Teachers& teachers, int courseNumber, int teacherNumber){
    // Condition 1: the target course must be prefered by the teacher.
    if (!courses.is_preference[courseNumber][teacherNumber]) return false;
    // Condition 2: all the teached courses must not be conflicted to the target course.
    for (int c : teachers.teached[teacherNumber]){
        if (courses.conflictingTable[courseNumber][c]){
            return false;
        }
    }
    return true;
}

void add_preference(Courses& courses, int courseNumber, int teacherNumber){
    courses.is_preference[courseNumber][teacherNumber] = true;
    courses.preference_count[courseNumber]++;
}
void add_conflict(Courses& courses, int course1, int course2){
    courses.conflictingTable[course1][course2] = true;
    courses.conflictingTable[course2][course1] = true;
    courses.conflict_count[course1]++;
    courses.conflict_count[course2]++;
}
void test_print(Courses& courses, Teachers& teachers){
    for (int i = 1; i <= courses.numberOfCourses; i++){
        cout << "course " << i << ":" << courses.preference_count[i] << endl;
    }
    cout << "================SORTED_COURSE_ORDER=================" << endl;
    for (int c : courses.sorted_course_order){
        cout << c << " ";
    }
    cout << endl;
}

vector<int> sortCourses(int numberOfCourses, vector<int>& preference_count, vector<int>& conflict_count, vector<int>& credits){
    vector<int> sorted_course_order(numberOfCourses);
    iota(sorted_course_order.begin(), sorted_course_order.end(), 1);
    sort(sorted_course_order.begin(), sorted_course_order.end(), [&](int a, int b){
    /*
    Compare by criterias:
    1. teacher_count ascending
    2. credit descending
    3. conflict_count descending
    */
        if (preference_count[a] != preference_count[b]) return preference_count[a] < preference_count[b];
        
        if (credits[a] != credits[b]) return credits[a] > credits[b];
        return conflict_count[a] > conflict_count[b];
    });
    return sorted_course_order;
}

void Try(int step, Courses& courses, Teachers& teachers){
    if (step == courses.numberOfCourses){
        for (int t = 1; t <= courses.numberOfTeachers; t++){
            if (teachers.teached[t].size() < teachers.LB[t]){
                return;
            }
        }
        best_max_load = (teachers.cur_max_load < best_max_load) ? teachers.cur_max_load : best_max_load;
        return;
    }

    int targetCourse = courses.sorted_course_order[step];
    for (int t = 1; t <= courses.numberOfTeachers; t++){
        if (can_teach(courses, teachers, targetCourse, t)){
            int prev_max_load = teachers.cur_max_load;
            // Assign 
            teachers.teached[t].push_back(targetCourse);
            teachers.load[t] += courses.credits[targetCourse];
            if (teachers.load[t] > teachers.cur_max_load) teachers.cur_max_load = teachers.load[t];
            courses.assigned_to[targetCourse] = t;
            Try(step + 1, courses, teachers);
            // Backtrack
            teachers.teached[t].pop_back();
            teachers.load[t] -= courses.credits[targetCourse];
            courses.assigned_to[targetCourse] = 0;
            teachers.cur_max_load = prev_max_load;
        }
    }
}

void input(){
    int m, n; cin >> m >> n;
    Courses courses(m, n);
    Teachers teachers(m, n);
    for (int t = 1; t <= m; t++){
        int numberOfPreferences; cin >> numberOfPreferences;
        for (int i = 0; i < numberOfPreferences; i++){
            int prefered_course; cin >> prefered_course;
            add_preference(courses, prefered_course, t);
        }
    }

    for (int c = 1; c <= n; c++){
        cin >> courses.credits[c];
    }

    for (int t = 1; t <= m; t++){
        cin >> teachers.LB[t];
    }

    int numberOfConflictions; cin >> numberOfConflictions;
    for (int i = 0; i < numberOfConflictions; i++){
        int course1, course2; cin >> course1 >> course2;
        add_conflict(courses, course1, course2);
    }

    courses.sorted_course_order = sortCourses(n, courses.preference_count, courses.conflict_count, courses.credits);

    Try(0, courses, teachers);

    cout << best_max_load << endl;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    input();
    return 0;
}