/**
 * @file buoi1_1.cpp
 * @brief Tính diện tích hình thang
 * @note
 *
 * @author VuQuan
 * @date 12-07-2026
 *
 * @status done
 */

#include <iostream>

using namespace std;

class HinhThang {
  private:
    float dayLon;
    float dayNho;
    float chieuCao;

  public:
    void nhap() {
        cout << "Nhap day lon > ";
        cin >> dayLon;
        cout << "Nhap day nho > ";
        cin >> dayNho;
        cout << "Nhap chieu cao > ";
        cin >> chieuCao;
    }
    void xuat() const {
        cout << "Day lon: " << dayLon << endl;
        cout << "Day nho: " << dayNho << endl;
        cout << "Chieu cao: " << chieuCao << endl;
    }
    float tinhDienTich() const {
        return (dayLon + dayNho) * chieuCao / 2;
    }
};

int main() {
    HinhThang ht;
    ht.nhap();
    ht.xuat();
    cout << "Dien tich hinh thang: " << ht.tinhDienTich() << endl;

    return 0;
}
