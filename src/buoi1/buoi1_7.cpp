/**
 * @file buoi1_7.cpp
 * @brief Lớp CanBo
 * @note
 *
 * @author VuQuan
 * @date 12-07-2026
 *
 * @status done
 */

#include <iostream>

using namespace std;

class CanBo {
  private:
    char maCanBo[10];
    char hoTen[20];
    char ngaySinh[10];
    int soNgayLamViec;

  public:
    void nhap() {
        cout << "Nhap ma can bo > ";
        cin.ignore();
        cin.getline(maCanBo, 10);
        cout << "Nhap ho ten > ";
        cin.getline(hoTen, 20);
        cout << "Nhap ngay sinh > ";
        cin.getline(ngaySinh, 10);
        cout << "Nhap so ngay lam viec trong thang > ";
        cin >> soNgayLamViec;
    }
    float tinhLuong() const {
        return soNgayLamViec * 250000;
    }
    void xuat() const {
        cout << "=== Thong tin can bo ===" << endl;
        cout << "Ma can bo: " << maCanBo << endl;
        cout << "Ho ten: " << hoTen << endl;
        cout << "Ngay sinh: " << ngaySinh << endl;
        cout << "So ngay lam viec trong thang: " << soNgayLamViec << endl;
        cout << "Luong: " << tinhLuong() << endl;
    }
};

int main() {
    CanBo cb;
    cb.nhap();
    cb.xuat();

    return 0;
}
