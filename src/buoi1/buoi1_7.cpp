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
    string maCanBo;
    string hoTen;
    string ngaySinh;
    int soNgayLamViec;

  public:
    void nhap() {
        cout << "Nhap ma can bo > ";
        cin.ignore();
        getline(cin, maCanBo);
        cout << "Nhap ho ten > ";
        getline(cin, hoTen);
        cout << "Nhap ngay sinh > ";
        getline(cin, ngaySinh);
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
