#include <iostream>
#include <vector>
#include <sstream>
#include <unordered_map>
#include <map>
#include <algorithm>
#include <queue>
#include <climits>
using namespace std;

const string orphan_code = "0000000";

struct Date{
    int year;
    int month;
    int day;
    Date(int y, int m, int d):  day(d), month(m), year(y) {}
};

struct Citizen{
    string code;
    string father_code;
    string mother_code;
    Date date_of_birth;
    bool has_relation;
    bool is_alive;
    Citizen(string c, string f, string m, Date d, bool alive): code(c), father_code(f), mother_code(m), date_of_birth(d), has_relation(false), is_alive(alive) {}
};

struct Edge{
    int dest;
    int capacity;
    int flow;
    int rev;
    Edge(int d, int c, int f, int r): dest(d), capacity(c), flow(f), rev(r) {}
};

vector<Citizen*> citizenList;
unordered_map<string, Citizen*> citizenDictionary;
unordered_map<string, int> born_map;
unordered_map<string, int> memo_ancestor;
vector<int> level;
vector<int> ptr;
vector<int> colour;
vector<vector<Edge>> adj;

Date getDate(string date){
    int year = stoi(date.substr(0, 4));
    int month = stoi(date.substr(5, 2));
    int day = stoi(date.substr(8, 2));
    return Date(year, month, day);
}

string dateToString(const Date& d){
    string y = to_string(d.year);
    string m = (d.month < 10 ? "0" : "") + to_string(d.month);
    string day = (d.day < 10 ? "0" : "") + to_string(d.day);
    
    return y + "-" + m + "-" + day;
}

int query_most_alive_ancestor(string cur_code, int depth){
    if (citizenDictionary.find(cur_code) == citizenDictionary.end()) return -1;
    if (memo_ancestor.count(cur_code)) return memo_ancestor[cur_code] + depth;
    Citizen* curCitizen = citizenDictionary[cur_code];

    int max_depth = (curCitizen->is_alive) ? depth : -1;
    if (curCitizen->father_code != orphan_code){
        max_depth = max(max_depth, query_most_alive_ancestor(curCitizen->father_code, depth + 1));
    }
    if (curCitizen->mother_code != orphan_code){
        max_depth = max(max_depth, query_most_alive_ancestor(curCitizen->mother_code, depth + 1));
    }
    return max_depth;
}

void update_born_map(Citizen* newCitizen){
    string born_date = dateToString(newCitizen->date_of_birth);
    born_map[born_date] += 1;
}

// Add new citizen to dictionary if not exists
void add_citizen(Citizen* newCitizen){
    if (citizenDictionary.find(newCitizen->code) != citizenDictionary.end()){
        return;
    }
    citizenDictionary.insert({newCitizen->code, newCitizen});
    citizenList.push_back(newCitizen);
    update_born_map(newCitizen);
    // If has mother => update relation
    if (citizenDictionary.find(newCitizen->mother_code) != citizenDictionary.end()){
        Citizen* mother = citizenDictionary[newCitizen->mother_code];
        mother->has_relation = true;
        newCitizen->has_relation = true;
    } 
    // Also update father.
    if (citizenDictionary.find(newCitizen->father_code) != citizenDictionary.end()){
        Citizen* father = citizenDictionary[newCitizen->father_code];
        father->has_relation = true;
        newCitizen->has_relation = true;
    }
}

// Sort citizenList by born order
void sort_citizen_list(){
    sort(citizenList.begin(), citizenList.end(), [&](Citizen* citizen1, Citizen* citizen2){
        if (citizen1->date_of_birth.year != citizen2->date_of_birth.year){
            return citizen1->date_of_birth.year < citizen2->date_of_birth.year;
        }
        if (citizen1->date_of_birth.month != citizen2->date_of_birth.month){
            return citizen1->date_of_birth.month < citizen2->date_of_birth.month;
        }
        return citizen1->date_of_birth.day < citizen2->date_of_birth.day;
    });
}

void add_edge(int parent_idx, int child_idx){
    int forward_idx = adj[parent_idx].size();
    int backward_idx = adj[child_idx].size();
    // Add forward and backward idx
    adj[parent_idx].push_back({child_idx, 1, 0, backward_idx});
    adj[child_idx].push_back({parent_idx, 0, 0, forward_idx});
}

void BFS_colour(){
    for (int i = 1; i <= citizenList.size(); i++){
        if (colour[i] != -1) continue;  // Node was coloured in a family tree.
        colour[i] = 0;
        queue<int> q;
        q.push(i);
        while (!q.empty()){
            int curNode = q.front();
            q.pop();

            for (const Edge& edge : adj[curNode]){
                if (colour[edge.dest] == -1){
                    colour[edge.dest] = 1 - colour[curNode];
                    q.push(edge.dest);
                }
            }
        }
    }
}

// Build a citizen lookup map: from integer idx to real citizen data.
void build_graph(){
    int max_node = citizenList.size();
    vector<pair<int, int>> relations;

    colour = vector<int> (max_node + 3, -1);
    adj = vector<vector<Edge>> (max_node + 3);

    for (int i = 0; i < citizenList.size(); i++){
        Citizen* curCitizen = citizenList[i];
        string father_code = curCitizen->father_code, mother_code = curCitizen->mother_code;
        if (father_code != orphan_code && citizenDictionary.count(father_code)){
            int u = stoi(father_code), v = stoi(curCitizen->code);
            relations.push_back({u, v});
            // 2-way connection for BFS_colour
            int f1 = adj[u].size(), f2 = adj[v].size();
            adj[u].push_back({v, 1, 0, f2});
            adj[v].push_back({u, 1, 0, f1});
        }
        if (mother_code != orphan_code && citizenDictionary.count(mother_code)){
            int u = stoi(mother_code), v = stoi(curCitizen->code);
            relations.push_back({u, v});
            int f1 = adj[u].size(), f2 = adj[v].size();
            adj[u].push_back({v, 1, 0, f2});
            adj[v].push_back({u, 1, 0, f1});
        }
    }

    // Colouring
    BFS_colour();

    // Rebuild adj for Dinic network
    adj.assign(max_node + 3, vector<Edge>());
    int source = max_node + 1, dest = max_node + 2;

    for (int i = 1; i <= max_node; i++){
        if (colour[i] == 0){
            add_edge(source, i);
        } else if (colour[i] == 1){
            add_edge(i, dest);
        }
    }

    for (const auto& rel : relations){
        int u = rel.first, v = rel.second;
        if (colour[u] == 0) add_edge(u, v);
        else add_edge(v, u);
    }
}

void BFS_dinic(int source, int dest){
    vector<bool> visited(adj.size(), false);   
    queue<int> q;
    q.push(source);
    visited[source] = true;
    while (!q.empty()){
        int curHop = q.front();
        q.pop();
        if (curHop == dest){
            break;   
        }
        
        for (const Edge& edge : adj[curHop]){
            if (!visited[edge.dest] && edge.capacity - edge.flow > 0){
                visited[edge.dest] = true;
                level[edge.dest] = level[curHop] + 1;
                q.push(edge.dest);
            }
        }
    }
}

long long DFS_dinic(int u, int dest, long long pushed){
    if (pushed == 0) return 0;
    if (dest == u) return pushed;

    for (int& cid = ptr[u]; cid < adj[u].size(); cid++){
        Edge& edge = adj[u][cid];
        int rem = edge.capacity - edge.flow;
        if (level[edge.dest] != level[u] + 1 || rem <= 0) continue;
        long long tr = DFS_dinic(edge.dest, dest, min(pushed, (long long)(rem)));
        if (tr > 0){
            edge.flow += tr;
            adj[edge.dest][edge.rev].flow -= tr;
            return tr;
        }
    }
    return 0;
}

int Dinic_max_relation(){
    int max_flow = 0;
    level = vector<int> (adj.size());
    ptr = vector<int> (adj.size());
    int source = citizenList.size() + 1, dest = citizenList.size() + 2;
    while (true){
        fill(level.begin(), level.end(), -1); level[source] = 0;
        BFS_dinic(source, dest);
        if (level[dest] == -1) break;
        fill(ptr.begin(), ptr.end(), 0);
        while (long long pushed = DFS_dinic(source, dest, INT_MAX)){
            max_flow += pushed;
        }
    }
    return max_flow;
}

bool compareDate(const Date& date1, const Date& date2){
    if (date1.year != date2.year) return date1.year < date2.year;
    if (date1.month != date2.month) return date1.month < date2.month;
    return date1.day < date2.day;
}

int query_number_born_between(Date startDate, Date endDate){
    auto lb = lower_bound(citizenList.begin(), citizenList.end(), startDate,
        [](Citizen* ctz, const Date& target){
            return compareDate(ctz->date_of_birth, target);
        }
    );

    auto ub = upper_bound(citizenList.begin(), citizenList.end(), endDate,
        [](const Date& target, Citizen* ctz){
            return compareDate(target, ctz->date_of_birth);
        }
    );

    return ub - lb;
}

void printCitizenList(){
    for (Citizen* ctz : citizenList){
        cout << ctz->code << ", has_relation: " << ctz->has_relation  << endl;
    }
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    string line;
    while (getline(cin, line)){
        if (line == "*") break;
        stringstream ss(line);
        string code, date_of_birth, father_code, mother_code, region_code;
        string is_alive;
        ss >> code >> date_of_birth >> father_code >> mother_code >> is_alive >> region_code;
        bool isAlive = (is_alive == "Y") ? true : false;
        Citizen* newCitizen = new Citizen(code, father_code, mother_code, getDate(date_of_birth), isAlive);
        add_citizen(newCitizen);
    }

    sort_citizen_list();
    build_graph();

    // Precalculate Dinic once since the graph is static
    int max_unrelated = citizenList.size() - Dinic_max_relation();

    string query;
    while (getline(cin, query)){
        if (query == "***") break;
        string command; 
        stringstream ss(query);
        ss >> command;
        if (command == "NUMBER_PEOPLE"){
            cout << citizenList.size() << "\n";
        } else if (command == "NUMBER_PEOPLE_BORN_AT"){
            string born_date; ss >> born_date;
            cout << born_map[born_date] << "\n";
        } else if (command == "MAX_UNRELATED_PEOPLE"){
            cout << max_unrelated << "\n";
        } else if (command == "MOST_ALIVE_ANCESTOR"){
            string sourceCitizen; ss >> sourceCitizen;
            int ans = query_most_alive_ancestor(sourceCitizen, 0);
            cout << (ans >= 0 ? ans : 0) << "\n";
        } else if (command == "NUMBER_PEOPLE_BORN_BETWEEN"){
            string start_date, end_date; ss >> start_date >> end_date;
            Date startDate = getDate(start_date), endDate = getDate(end_date);
            cout << query_number_born_between(startDate, endDate) << "\n";
        } else {
            cout << "ERROR!" << "\n";
            break;
        }
    }

    for (Citizen* ctz : citizenList){
        delete ctz;
    }

    return 0;
}
