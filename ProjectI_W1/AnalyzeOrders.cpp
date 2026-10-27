#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
using namespace std;

struct TimePoint{
    int hour;
    int min;
    int sec;
};

struct Order{
    string OrderID;
    TimePoint timepoint;
};

struct Query{
    string type; // Three types: "number", "number_at_time", "number_in_period"
    TimePoint timepoint1, timepoint2;
};

// Converting a raw time (string) to a timepoint (struct)
TimePoint getTimePoint(string &rawTimeString){
    istringstream tokenStream(rawTimeString);
    string token;
    int hour, min, sec;
    getline(tokenStream, token, ':');
    hour = stoi(token);
    getline(tokenStream, token, ':');
    min = stoi(token);
    getline(tokenStream, token, ':');
    sec = stoi(token);
    return {hour, min, sec};
}

void input(vector<Order*>& orderList, vector<Query*>& queryList){
    cout << "Start inputing: " << endl;
    string line;
    while (getline(cin, line)){
        if (line == "#") break;

        Order *newOrder = new Order({});
        stringstream ss(line);
        string ID;
        ss >> ID;
        string rawTimePoint;
        ss >> rawTimePoint;
        newOrder->OrderID = ID;
        newOrder->timepoint = getTimePoint(rawTimePoint);
        orderList.push_back(newOrder);
    }

    while (getline(cin, line)){
        if (line == "###") break;

        Query *newQuery = new Query({});
        istringstream ss(line);
        string query;
        string rawTimePoint1;
        
        ss >> query;
        if (query == "?number_orders"){
            newQuery->type = "number";
            queryList.push_back(newQuery);
            continue;
        } else if (query == "?number_orders_in_period"){
            newQuery->type = "number_in_period";
        } else if (query == "?number_orders_at_time"){
            newQuery->type = "number_at_time";
        } else {
            cout << "Error01!" << endl;
            return;
        }

        ss >> rawTimePoint1;
        newQuery->timepoint1 = getTimePoint(rawTimePoint1);        
        
        string rawTimePoint2;
        if (ss >> rawTimePoint2){
            newQuery->timepoint2 = getTimePoint(rawTimePoint2);
        }

        queryList.push_back(newQuery);
    }
}

bool isExactTime(TimePoint* tp1, TimePoint* tp2){
    return (tp1->hour == tp2->hour) && (tp1->min == tp2->min) && (tp1->sec == tp2->sec);
}

bool isSoonerThan(TimePoint* tp1, TimePoint* tp2){
    if (tp1->hour != tp2->hour){
        return tp1->hour < tp2->hour;
    } 
    if (tp1->min != tp2->min){
        return tp1->min < tp2->min;
    }
    return tp1->sec < tp2->sec;
}

int compareTimePoint(const TimePoint& a, const TimePoint& b){
    if (a.hour != b.hour) return a.hour - b.hour;
    if (a.min != b.min) return a.min - b.min;
    return a.sec - b.sec;
}

int searchOrderAtTime(const vector<Order*>& orderList, const TimePoint& target){
    int left = 0, right = (int)orderList.size() - 1;

    while (left <= right){
        int mid = left + (right - left) / 2;

        int cmp = compareTimePoint(orderList[mid]->timepoint, target);

        if (cmp == 0){
            // Tìm cả dãy giá trị bằng nhau ở trái và phải
            int l = mid;
            int r = mid;

            while (l > 0 && compareTimePoint(orderList[l - 1]->timepoint, target) == 0){
                l--;
            }
            while (r + 1 < (int)orderList.size() &&
                   compareTimePoint(orderList[r + 1]->timepoint, target) == 0){
                r++;
            }

            return r - l + 1;
        }
        else if (cmp < 0){
            left = mid + 1;
        }
        else {
            right = mid - 1;
        }
    }

    return 0;
}

int lowerBoundTime(const vector<Order*>& orderList, const TimePoint& target){
    int left = 0, right = (int)orderList.size();

    while (left < right){
        int mid = left + (right - left) / 2;
        if (compareTimePoint(orderList[mid]->timepoint, target) < 0){
            left = mid + 1;
        } else {
            right = mid;
        }
    }
    return left;
}

int upperBoundTime(const vector<Order*>& orderList, const TimePoint& target){
    int left = 0, right = (int)orderList.size();

    while (left < right){
        int mid = left + (right - left) / 2;
        if (compareTimePoint(orderList[mid]->timepoint, target) <= 0){
            left = mid + 1;
        } else {
            right = mid;
        }
    }
    return left;
}

int searchOrderInPeriod(vector<Order*>& orderList, TimePoint* timepoint1, TimePoint* timepoint2){
    if (compareTimePoint(*timepoint1, *timepoint2) > 0){
        swap(*timepoint1, *timepoint2); // hoặc trả về 0
    }

    int left = lowerBoundTime(orderList, *timepoint1);
    int right = upperBoundTime(orderList, *timepoint2);

    return max(0, right - left);
}
void solveInput(vector<Order*>& orderList, vector<Query*>& queryList){
    for (Query* query : queryList){
        if (query->type == "number"){
            cout << orderList.size() << endl;
        } else if (query->type == "number_at_time"){
            cout << searchOrderAtTime(orderList, query->timepoint1) << endl;
        } else if (query->type == "number_in_period"){
            cout << searchOrderInPeriod(orderList, &(query->timepoint1), &(query->timepoint2));
        } else {
            cout << "Error02!" << endl;
            return;
        }
    }
}

int main(){
    vector<Order*> orderList;
    vector<Query*> queryList;
    input(orderList, queryList);

    // Sort the orderList
    sort(orderList.begin(), orderList.end(), [](Order* a, Order* b){
        if (a->timepoint.hour != b->timepoint.hour){
            return a->timepoint.hour < b->timepoint.hour;
        } 
        if (a->timepoint.min != b->timepoint.min){
            return a->timepoint.min < b->timepoint.min;
        } 
        return a->timepoint.sec < b->timepoint.sec;
    });

    solveInput(orderList, queryList);
    return 0;
}