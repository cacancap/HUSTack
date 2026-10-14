#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
#include <numeric>
using namespace std;

int best_max_load = INT_MAX;

class Courses{
private:
       
    
public:
    int max_load = INT_MAX;
    int numberOfCourses, numberOfTeachers;
    vector<int> course_order;   // Sorted order of course list by 3 criterias.
    vector<int> teacher_count;  // Track number of teachers prefering each course.
    vector<int> conflict_count; // Track number of confliction in each course.
    vector<vector<bool>> conflictingTable;  // Track every pair of courses that are conflict to each other.
    vector<int> assigned;   // Track & map a course to a teacher.
    vector<int> assigned_count; // Count the number of courses assigned to a teacher.
    vector<int> load;       // Track the number of credits assigned to a teacher.
    vector<vector<bool>> isPreference;  // Track whether a course is prefered by a teacher or not.
    vector<int> credits;    // Track credits of each subject.
    vector<int> LB;         // Lowerbound: minimum credit that a teacher can solve.
    vector<vector<int>> can_be_teached;
    Courses(int numberOfCourses, int numberOfTeachers){
        conflictingTable = vector<vector<bool>> (numberOfCourses + 1, vector<bool>(numberOfCourses + 1, false));
        assigned = vector<int> (numberOfCourses + 1, 0);
        assigned_count = vector<int> (numberOfTeachers + 1, 0);
        credits = vector<int> (numberOfCourses + 1, 0);
        LB = vector<int> (numberOfTeachers + 1, 0);
        teacher_count = vector<int> (numberOfCourses + 1, 0);
        conflict_count = vector<int> (numberOfCourses + 1, 0);
        isPreference = vector<vector<bool>> (numberOfCourses + 1, vector<bool> (numberOfTeachers + 1, false));
        can_be_teached = vector<vector<int>> (numberOfCourses + 1, vector<int>());
        this->numberOfCourses = numberOfCourses; this->numberOfTeachers = numberOfTeachers;
        
    }
    void add_preference(int courseNumber, int teacherNumber){
        if (courseNumber > numberOfCourses || teacherNumber > numberOfTeachers){
            cout << "invalid add command!" << endl;
            return;
        }
        isPreference[courseNumber][teacherNumber] = true;
        teacher_count[courseNumber]++;
        can_be_teached[courseNumber].push_back(teacherNumber);
    }

    void add_credits(){
        for (int i = 1; i <= numberOfCourses; i++){
            cin >> credits[i];
        }
    }
    void add_LB(){
        for (int i = 1; i <= numberOfTeachers; i++){
            cin >> LB[i];
        }
    }
    void set_conflict(int course1, int course2){
        conflictingTable[course1][course2] = conflictingTable[course2][course1] = true;
        conflict_count[course1] ++;
        conflict_count[course2] ++;
    }
    void assign(int courseNumber, int teacherNumber){
        assigned[courseNumber] = teacherNumber;
    }
    void undo_assign(int courseNumber){
        assigned[courseNumber] = 0;
    }
    void printPreferences(){
        for (int i = 1; i <= numberOfCourses; i++){
            for (int j = 1; j <= numberOfTeachers; j++){
                cout << isPreference[i][j] << " ";
            }
            cout << endl;
        }
    }
    void printConflict(){
        for (int i = 1; i <= numberOfCourses; i++){
            for (int j = 1; j <= numberOfCourses; j++){
                cout << conflictingTable[i][j] << " ";
            }
            cout << endl;
        }
    }
    void print_teacher_count(){
        for (int i = 1; i <= numberOfCourses; i++){
            cout << "subject: " << i << ", count: " << teacher_count[i] << endl;
        }
    }
};


vector<int> sortCourses(int n,  const vector<int>& teacher_count,
                                const vector<int>& conflict_count,
                                const vector<int>& credits){
    vector<int> course_order(n);
    iota(course_order.begin(), course_order.end(), 1);
          /*
        Compare by criterias:
        1. teacher_count ascending
        2. credit descending
        3. conflict_count descending
        */
    sort(course_order.begin(), course_order.end(), [&](int a, int b){
        if (teacher_count[a] != teacher_count[b]) 
            return teacher_count[a] < teacher_count[b]; // 1. teacher_count tăng dần
        if (credits[a] != credits[b]) 
            return credits[a] > credits[b];             // 2. credits giảm dần
        return conflict_count[a] > conflict_count[b];   // 3. conflict_count giảm dần
    });                                
    return course_order;
}

bool canTeach(Courses& courses, int teacherNumber, int courseNumber){
    if (courses.assigned[courseNumber] != 0 || 
        !courses.isPreference[courseNumber][teacherNumber]
        ) return false;
    
    return true;
}

void tryAssigning(int step, Courses& courses){
    if (step > courses.numberOfCourses){
        best_max_load = (courses.max_load < best_max_load) ? courses.max_load : best_max_load;
        return;
    }

    int targetCourse = courses.course_order[step];
    vector<int> candidateTeacher = courses.can_be_teached[targetCourse];


    sort(candidateTeacher.begin(), candidateTeacher.end(), [&](int a, int b){
        int remain_lb1 = max(0, courses.LB[a] - courses.assigned_count[a]);
        int remain_lb2 = max(0, courses.LB[b] - courses.assigned_count[b]);
        if (courses.load[a] != courses.load[b]){
            return courses.load[a] < courses.load[b];
        }
        return remain_lb1 > remain_lb2;
    });

    for (int t : candidateTeacher){
        if (canTeach(courses, t, targetCourse)){
            
        }
    }
    
}

void input(){
    int m, n;
    cin >> m >> n;
    Courses courses(n, m);  // Initialize

    // For m teachers: input the preference list for each one of them.
    for (int i = 1; i <= m; i++){
        int k; cin >> k;
        for (int j = 1; j <= k; j++){
            int preferenceSubject; cin >> preferenceSubject;
            courses.add_preference(preferenceSubject, i);
        }
    }

    courses.add_credits();
    courses.add_LB();
    int numberOfContraints;
    cin >> numberOfContraints;

    for (int i = 0; i < numberOfContraints; i++){
        int subject1, subject2;
        cin >> subject1 >> subject2;
        courses.set_conflict(subject1, subject2);
    }

    courses.course_order = sortCourses(n, courses.teacher_count, courses.conflict_count, courses.credits);
    tryAssigning(0, courses);
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    input();

    return 0;
}

