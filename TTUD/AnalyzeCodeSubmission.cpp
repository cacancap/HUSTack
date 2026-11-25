#include <iostream>
#include <sstream>
#include <unordered_map>
#include <vector>
#include <algorithm>
using namespace std;

struct TimePoint{
    int hour;
    int minute;
    int second;
    TimePoint(int h = 0, int m = 0, int s = 0): hour(h), minute(m), second(s){}

    bool operator<(const TimePoint& other) const{
        if (hour != other.hour) return hour < other.hour;
        if (minute != other.minute) return minute < other.minute;
        return second < other.second;
    }

    bool operator<=(const TimePoint& other) const{
        if (hour != other.hour) return hour <= other.hour;
        if (minute != other.minute) return minute <= other.minute;
        return second <= other.second;
    }
};

struct UserData{
    string userId;
    int total_point;
    int total_err;
    unordered_map<string, int> problemSolved;
    UserData(string UID): userId(UID), total_point(0), total_err(0) {}
};

int global_total_err = 0;
unordered_map<string, UserData*> userDictionary; 
vector<UserData*> userList;
vector<TimePoint> submissionRecords;

TimePoint getTimePoint(string timePoint){
    int h = (timePoint[0] - '0') * 10 + timePoint[1] - '0';
    int m = (timePoint[3] - '0') * 10 + timePoint[4] - '0';
    int s = (timePoint[6] - '0') * 10 + timePoint[7] - '0'; 
    return TimePoint(h, m, s);
}

void processSubmission(string userId, string problemId, TimePoint timePoint, string status, int point){
    UserData* targetUser = nullptr;
    if (userDictionary.find(userId) == userDictionary.end()){
        targetUser = new UserData(userId);
        userDictionary.insert({userId, targetUser});
        userList.push_back(targetUser);        
    } else {
        targetUser = userDictionary[userId];
    }
    if (status == "ERR") {
        targetUser->total_err += 1;
        global_total_err += 1;
    }

    // Hanlde point of new problem
    if (targetUser->problemSolved.find(problemId) == targetUser->problemSolved.end()){
        targetUser->problemSolved.insert({problemId, point});
    } else {
        if (targetUser->problemSolved[problemId] < point){
            targetUser->problemSolved[problemId] = point;
        }
    }
    
    submissionRecords.push_back(timePoint);
}

int number_submission_period(TimePoint startTp, TimePoint endTp){
    auto lb = lower_bound(submissionRecords.begin(), submissionRecords.end(), startTp);
    auto ub = upper_bound(submissionRecords.begin(), submissionRecords.end(), endTp);
    if (ub <= lb) return 0;
    return ub - lb;
}

int total_point_of_user(string userId){
    UserData* targetUser = (userDictionary.find(userId) != userDictionary.end()) ? userDictionary[userId] : nullptr;
    if (targetUser == nullptr) return 0;
    int result = 0;
    for (const auto& [key, value] : targetUser->problemSolved){
        result += value;
    }
    return result;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    userDictionary.reserve(100005);
    userList.reserve(100005);
    submissionRecords.reserve(100005);
    string line;
    while (getline(cin, line)){
        if (line == "#") break;
        string userId, problemId, timePoint, status; 
        int point;
        stringstream ss(line);
        ss >> userId >> problemId >> timePoint >> status >> point;
        processSubmission(userId, problemId, getTimePoint(timePoint), status, point);
    }

    sort(submissionRecords.begin(), submissionRecords.end(), [&](TimePoint tp1, TimePoint tp2){
        if (tp1.hour != tp2.hour) return tp1.hour < tp2.hour;
        if (tp1.minute != tp2.minute) return tp1.minute < tp2.minute;
        return tp1.second < tp2.second;
    });

    string query;
    while (getline(cin, query)){
        if (query == "#") break;
        stringstream ss(query);
        string command;
        ss >> command;
        if (command == "?total_number_submissions"){
            cout << submissionRecords.size() << endl;
        }
        else if (command == "?number_error_submision"){
            cout << global_total_err << endl;
        }
        else if (command == "?number_error_submision_of_user"){
            string userId; ss >> userId;
            cout << userDictionary[userId]->total_err << endl;
        }
        else if (command == "?total_point_of_user"){
            string userId; ss >> userId;
            cout << total_point_of_user(userId) << endl;
        }
        else if (command == "?number_submission_period"){
            string tp1, tp2; ss >> tp1 >> tp2;
            cout << number_submission_period(getTimePoint(tp1), getTimePoint(tp2)) << endl;
        } else {
            cout << "ERROR!" << endl;
            break;
        }
    }

    // cout << "==============TEST=============" << endl;
    // for (UserData* userData : userList){
    //     cout << userData->userId << ": " << "ERR: " << userData->total_err << "| POINT: " << userData->total_point << endl;
    // }
    // cout << "submissions: " << endl;
    // for (TimePoint tp : submissionRecords){
    //     cout << tp.hour << ":" << tp.minute << ":" << tp.second << endl;
    // }

    // cout << "numebr between: " << endl;
    // cout << number_submission_period(getTimePoint("10:00:00"), getTimePoint("11:30:45"));
    
    return 0;
}