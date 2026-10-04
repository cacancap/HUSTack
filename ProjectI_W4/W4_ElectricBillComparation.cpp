#include <iostream>
#include <iomanip>

using namespace std;

// Hàm tính tiền điện theo Biểu giá 6 bậc (hiện hành)
double tinhGia6Bac(int n) {
    double tien = 0;
    
    // Bậc 6: Từ 401 kWh trở lên
    if (n > 400) {
        tien += (n - 400) * 3.015;
        n = 400;
    }
    // Bậc 5: 301 - 400 kWh (tối đa 100 kWh)
    if (n > 300) {
        tien += (n - 300) * 2.919;
        n = 300;
    }
    // Bậc 4: 201 - 300 kWh (tối đa 100 kWh)
    if (n > 200) {
        tien += (n - 200) * 2.612;
        n = 200;
    }
    // Bậc 3: 101 - 200 kWh (tối đa 100 kWh)
    if (n > 100) {
        tien += (n - 100) * 2.074;
        n = 100;
    }
    // Bậc 2: 51 - 100 kWh (tối đa 50 kWh)
    if (n > 50) {
        tien += (n - 50) * 1.786;
        n = 50;
    }
    // Bậc 1: 0 - 50 kWh (tối đa 50 kWh)
    tien += n * 1.728;
    
    // Đổi từ nghìn đồng sang đồng
    return tien * 1000;
}

// Hàm tính tiền điện theo Biểu giá 5 bậc (đề xuất)
double tinhGia5Bac(int n) {
    double tien = 0;
    
    // Bậc 5: Từ 701 kWh trở lên
    if (n > 700) {
        tien += (n - 700) * 3.457;
        n = 700;
    }
    // Bậc 4: 401 - 700 kWh (tối đa 300 kWh)
    if (n > 400) {
        tien += (n - 400) * 3.111;
        n = 400;
    }
    // Bậc 3: 201 - 400 kWh (tối đa 200 kWh)
    if (n > 200) {
        tien += (n - 200) * 2.612;
        n = 200;
    }
    // Bậc 2: 101 - 200 kWh (tối đa 100 kWh)
    if (n > 100) {
        tien += (n - 100) * 2.074;
        n = 100;
    }
    // Bậc 1: 0 - 100 kWh (tối đa 100 kWh)
    tien += n * 1.728;
    
    // Đổi từ nghìn đồng sang đồng
    return tien * 1000;
}

int main() {
    // Tối ưu hóa nhập xuất dữ liệu trong C++
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int kwh;
    if (cin >> kwh) {
        // Tính tổng tiền điện đã bao gồm 10% VAT
        double tienCu = tinhGia6Bac(kwh) * 1.1;
        double tienMoi = tinhGia5Bac(kwh) * 1.1;
        
        // Độ chênh lệch giữa giá mới và giá cũ
        double chenhLech = tienMoi - tienCu;
        
        // In ra kết quả chính xác 2 chữ số thập phân
        cout << fixed << setprecision(2) << chenhLech << "\n";
    }

    return 0;
}