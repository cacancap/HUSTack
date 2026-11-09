#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
using namespace std;

struct AccountInformation{
    string account_id;
    int total_transferred;
    AccountInformation(string id): account_id(id), total_transferred(0) {}
};

int number_transactions = 0, total_money_transactions = 0;
unordered_set<string> visited;


unordered_map<string, AccountInformation*> account_dictionary;
vector<AccountInformation*> accountList;
unordered_map<string, unordered_set<string>> adj;

void process_transcaction(string source_id, string dest_id, int money){
    AccountInformation* source_account = nullptr, *dest_account = nullptr;
    if (account_dictionary.find(source_id) != account_dictionary.end()){
        source_account = account_dictionary[source_id];
    } else {
        source_account = new AccountInformation(source_id);
        account_dictionary.insert({source_id, source_account});
        accountList.push_back(source_account);
    }
    if (account_dictionary.find(dest_id) != account_dictionary.end()){
        dest_account = account_dictionary[dest_id];
    } else {
        dest_account = new AccountInformation(dest_id);
        account_dictionary.insert({dest_id, dest_account});
        accountList.push_back(dest_account);
    }
    source_account->total_transferred += money;
    total_money_transactions += money;
    number_transactions += 1;

    if (source_id != dest_id){
        if (adj.find(source_id) == adj.end()){
            adj.insert({source_id, {}});
        }
        adj[source_id].insert(dest_id);
    }
}

void inspect_cycle(int k, string start_acc, string cur_acc, bool& find){
    if (k == 1 ){
        if (adj[cur_acc].find(start_acc) != adj[cur_acc].end()) find = true;
        return;
    }

    // This node was visited
    if (visited.find(cur_acc) != visited.end()){
        return;
    }
    visited.insert(cur_acc);

    for (string next_acc : adj[cur_acc]){
        if (visited.find(next_acc) == visited.end()){
            inspect_cycle(k - 1, start_acc, next_acc, find);
        }
    }
    visited.erase(cur_acc);
}

void print_accounts(){
    cout << "=======================ACCOUNT INFORMATION==========================" << endl;
    for (AccountInformation* acc_info : accountList){
        cout << acc_info->account_id << " transferred " << acc_info->total_transferred << " in total!" << endl;
    }
}

void print_adj(){
    cout << "adjacency list: " << endl;
    for (const auto& [key, value] : adj){
        cout << "src: " << key << " -> ";
        for (const auto& dest : value){
            cout << dest << " | ";
        } 
        cout << endl;
    }
}

int main(){
    string line;
    // Block 1: transaction information
    while (getline(cin, line)){
        if (line == "#") break;
        stringstream ss(line);
        string src_id, dst_id, TimePoint, atm;
        int money;
        ss >> src_id >> dst_id >> money >> TimePoint >> atm;
        process_transcaction(src_id, dst_id, money);
    }

    sort(accountList.begin(), accountList.end(), [&](AccountInformation* account1, AccountInformation* account2){
        return account1->account_id < account2->account_id;
    });

    string query;
    while (getline(cin, query)){
        if (query == "#") break;
        stringstream ss(query);
        string command;
        ss >> command;
        if (command == "?number_transactions"){
            cout << number_transactions << endl;
        } else if (command == "?total_money_transaction"){
            cout << total_money_transactions << endl;
        } else if (command == "?list_sorted_accounts"){
            for (AccountInformation* acc_info : accountList){
                cout << acc_info->account_id << " ";
            }
            cout << endl;
        } else if (command == "?total_money_transaction_from"){
            string AccountID; ss >> AccountID;
            if (account_dictionary.find(AccountID) == account_dictionary.end()){
                cout << "0" << endl;
            } else {
                cout << account_dictionary[AccountID]->total_transferred << endl;
            }
        } else if (command == "?inspect_cycle"){
            string AccountID; int k;
            ss >> AccountID >> k;
            bool find = false;
            inspect_cycle(k, AccountID, AccountID, find);
            if (find == false) cout << "0" << endl;
            else cout << "1" << endl;
        }
    }

    // print_accounts();
    // bool find = false;
    // inspect_cycle(3, "T000010010", "T000010010", find);
    // if (find == true){
    //     cout << "1" << endl;
    // }
    return 0;
}