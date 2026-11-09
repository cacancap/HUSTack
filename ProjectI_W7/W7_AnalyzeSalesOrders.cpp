#include <iostream>
#include <vector>
#include <sstream>  
#include <unordered_map>
#include <algorithm>
using namespace std;

class ECompany{
public:
    int total_revenue = 0;
    struct Shop{
        string ShopID;
        int shop_revenue;
        unordered_map<string, int> consume_of_customer; 
        Shop(string id): ShopID(id), shop_revenue(0) {}
    };
    
    struct Purchase{
        int second;
        int price;
        Purchase(int s, int p): second(s), price(p) {}
    };

    vector<Shop*> shopList;
    vector<Purchase*> purchaseList;
    unordered_map<string, Shop*> shop_dictionary;
    int* prefix_sum = nullptr;

    ECompany(){
        this->shop_dictionary.reserve(100000);
        shopList.reserve(100000);
    }
    ~ECompany(){
        for (Shop* shop : shopList){
            delete shop;
        }
        for (Purchase* p : purchaseList){
            delete p;
        }
        delete[] prefix_sum;
    }

    void add_purchase(string CustomerID, int price, string ShopID, int second){
        Shop* targetShop;
        if (shop_dictionary.find(ShopID) != shop_dictionary.end()){
            targetShop = shop_dictionary[ShopID];
        } else {
            targetShop = new Shop(ShopID);
            shopList.push_back(targetShop);
            shop_dictionary.insert({ShopID, targetShop});
        }

        this->total_revenue += price;
        targetShop->shop_revenue += price;

        if (targetShop->consume_of_customer.find(CustomerID) != targetShop->consume_of_customer.end()){
            targetShop->consume_of_customer[CustomerID] += price;
        } else {
            targetShop->consume_of_customer.insert({CustomerID, price});
        }

        purchaseList.push_back(new Purchase(second, price));
    }

    void sort_purchases_by_second(){
        if (purchaseList.empty()) return;
        sort(purchaseList.begin(), purchaseList.end(), [&](Purchase* pc1, Purchase* pc2){
            return pc1->second < pc2->second;
        });
        prefix_sum = new int[purchaseList.size()];
        prefix_sum[0] = purchaseList[0]->price;
        for (int i = 1; i < purchaseList.size(); i++){
            prefix_sum[i] = purchaseList[i]->price + prefix_sum[i - 1];
        }
    }

    int query_by_shop(string ShopID){
        if (shop_dictionary.find(ShopID) == shop_dictionary.end()){
            return 0;
        }
        return shop_dictionary[ShopID]->shop_revenue;
    }

    int query_by_customer_shop(string CustomerID, string ShopID){
        if (shop_dictionary.find(ShopID) == shop_dictionary.end()) return 0;
        Shop* targetShop = shop_dictionary[ShopID];
        if (targetShop->consume_of_customer.find(CustomerID) == targetShop->consume_of_customer.end()) return 0;
        return targetShop->consume_of_customer[CustomerID];
    }

    int query_by_time_range(int src_second, int dst_second){
        if (purchaseList.empty()) return 0;
        auto it_first = lower_bound(purchaseList.begin(), purchaseList.end(), src_second, [](const Purchase* p, int val){
            return p->second < val;            
        });
        int lb = (it_first - purchaseList.begin()) - 1;

        auto it_last = upper_bound(purchaseList.begin(), purchaseList.end(), dst_second, [](int val, const Purchase* p){
            return val < p->second;
        });
        int ub = it_last - purchaseList.begin();
        
        int start_idx = lb + 1, end_idx = ub - 1;
        if (start_idx > end_idx){
            return 0;
        }

        int total = prefix_sum[end_idx] - (lb >= 0 ? prefix_sum[lb] : 0);
        return total;
    }

    void print_company(){
        cout << "==================ECOMMERCE COMPANY====================" << endl;
        cout << "total revenue: " << this->total_revenue << endl;
        cout << "shop List: " << endl;
        for (int i = 0; i < shopList.size(); i++){
            cout << shopList[i]->ShopID << ": ";
            for (const auto& [key, value]: shopList[i]->consume_of_customer){
                cout << key << "->" << value << " | ";
            }
            cout << endl;
        }
        cout << "purchase list: " << endl;
        for (Purchase* pc : purchaseList){
            cout << pc->second << "->" << pc->price << " | "; 
        }
        cout << endl;
    }
};

int time_point_to_int(string TimePoint){
    int hour = (TimePoint[1] - '0') + (TimePoint[0] - '0') * 10;
    int minute = (TimePoint[4] - '0') + (TimePoint[3] - '0') * 10;
    int second = (TimePoint[7] - '0') + (TimePoint[6] - '0') * 10;
    return hour * 3600 + minute * 60 + second;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    string line;
    ECompany company;
    while (getline(cin, line)){
        if (line == "#") break;
        stringstream ss(line);
        string CustomerID, ProductID, ShopID, TimePoint;
        int price;
        ss >> CustomerID >> ProductID >> price >> ShopID >> TimePoint;
        company.add_purchase(CustomerID, price, ShopID, time_point_to_int(TimePoint));
    }

    company.sort_purchases_by_second();
    
    string query;
    while (getline(cin, query)){
        if (query == "#") break;
        string command;
        stringstream ss(query);
        ss >> command;
        if (command == "?total_number_orders"){
            cout << company.purchaseList.size() << endl;
        } else if (command == "?total_revenue"){
            cout << company.total_revenue << endl;
        } else if (command == "?revenue_of_shop"){
            string ShopID; ss >> ShopID;
            cout << company.query_by_shop(ShopID) << endl;
        } else if (command == "?total_consume_of_customer_shop"){
            string ShopID, CustomerID; ss >> CustomerID >> ShopID;
            cout << company.query_by_customer_shop(CustomerID, ShopID) << endl;
        } else if (command == "?total_revenue_in_period"){
            string tp1, tp2; ss >> tp1 >> tp2;
            cout << company.query_by_time_range(time_point_to_int(tp1), time_point_to_int(tp2)) << endl;
        } else {
            cout << "ERROR!" << endl; return 1;
        }
    }
    // company.print_company();
    // cout << "test query: " << company.query_by_time_range(time_point_to_int("10:00:00"), time_point_to_int("18:40:45")) << endl;
    return 0;
}