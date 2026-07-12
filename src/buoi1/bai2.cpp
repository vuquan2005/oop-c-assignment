/**
 * @file Tính chu vi, diện tích hình tròn
 * @brief Viết chương trình hướng đối tượng giải quyết bài toán tính chu vi,
 * diện tích hình tròn.
 */

#include <cmath>
#include <iostream>

using namespace std;

class HinhTron {
  private:
    float banKinh;

  public:
    void nhap() {
        cout << "Nhap ban kinh hinh tron > ";
        cin >> banKinh;
    }
    void xuat() {
        cout << "Ban kinh hinh tron: " << banKinh << endl;
    }
    float tinhDienTich() const {
        return M_PI * banKinh * banKinh;
    }
    float tinhChuvi() const {
        return M_PI * 2 * banKinh;
    }
};

int main() {
    HinhTron ht;
    ht.nhap();
    ht.xuat();

    cout << "Chu vi hinh tron la: " << ht.tinhChuvi() << endl;
    cout << "Dien tich hinh tron la: " << ht.tinhDienTich() << endl;

    return 0;
}
