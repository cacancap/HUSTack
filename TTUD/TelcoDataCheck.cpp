#include <iostream>
#include <unordered_map>
#include <string>
#include <sstream>
using namespace std;

struct PhoneNumberData{
	int duration_seconds;
	int count;
};

bool isValidPhoneNumber(string phoneNumber){
	if (phoneNumber.length() != 10) return false;
	for (int i = 0; i < 10; i++){
		if (phoneNumber[i] < '0' || phoneNumber[i] > '9') return false;
	}
	return true;
}

int callDuration(string sourceTime, string destTime){
	int h1, m1, s1, h2, m2, s2;
	
	h1 = stoi(sourceTime.substr(0, 2));
	m1 = stoi(sourceTime.substr(3, 2));
	s1 = stoi(sourceTime.substr(6, 2));
	
	h2 = stoi(destTime.substr(0, 2));
	m2 = stoi(destTime.substr(3, 2));
	s2 = stoi(destTime.substr(6, 2));
	return (h2 - h1) * 3600 + (m2 - m1) * 60 + (s2 - s1);
}

void solve(){
	string line;
	unordered_map<string, PhoneNumberData> tabulation;
	bool status = true;
	int number_total_calls = 0;
	// Input block 1: data
	while (getline(cin, line)){
		if (line == "#") break;
		
		stringstream ss(line);
		string token;
		ss >> token;
		if (token != "call"){
			cout << "error01!" << endl; return;
		}	
		
		string sourcePhone, destPhone;
		ss >> sourcePhone; ss >> destPhone;
		
		if (!isValidPhoneNumber(sourcePhone) || !isValidPhoneNumber(destPhone)){
			status = false; break;
		}
		
		if (tabulation.find(sourcePhone) != tabulation.end()){
			tabulation.insert({
				sourcePhone, PhoneNumberData{0, 0}
			});
		}
		
		if (tabulation.find(destPhone) != tabulation.end()){
			tabulation.insert({
				destPhone, PhoneNumberData{0, 0}
			});
		}
		
		string date;
		ss >> date;
		
		string sourceTime, destTime;
		ss >> sourceTime; ss >> destTime;
		
		int duration = callDuration(sourceTime, destTime);
		tabulation[sourcePhone].count += 1; 
		tabulation[sourcePhone].duration_seconds += duration;
		number_total_calls += 1;
	}
	
	string query;
	while (getline(cin, query)){
		if (query == "#") break;
		stringstream ss(query);
		string command;
		ss >> command; command = command.substr(1, command.length() - 1);
		if (command == "check_phone_number"){
			cout << status << endl;
		} else if (command == "number_calls_from"){
			string phoneNumber;
			ss >> phoneNumber;
			cout << tabulation[phoneNumber].count << endl;
		} else if (command == "number_total_calls"){
			cout << number_total_calls << endl;
		} else if (command == "count_time_calls_from"){
			string phoneNumber;
			ss >> phoneNumber;
			cout << tabulation[phoneNumber].duration_seconds << endl;
		} else {
			cout << "Error03!, invalid command: " << command << endl;
			return;
		}
	}
}

int main(){
    solve();
	
	
    return 0;
}
