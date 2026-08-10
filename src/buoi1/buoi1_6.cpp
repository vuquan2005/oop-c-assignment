/**
 * @file buoi1_6.cpp
 * @brief Học sinh
 * @note
 *
 * @author VuQuan
 * @date 12-07-2026
 *
 * @status done
 */

#include <iostream>

using namespace std;

class HocSinh {
  private:
    char hoTen[20];
    int ngaySinh;
    int thangSinh;
    int namSinh;
    char gioiTinh[10];
    float diemTB;
    char xepLoaiDaoDuc[15];

  public:
    void nhap() {
        cout << "Nhap ho ten hoc sinh > ";
        cin.ignore();
        cin.getline(hoTen, 20);
        cout << "Nhap ngay sinh > ";
        cin >> ngaySinh;
        cout << "Nhap thang sinh > ";
        cin >> thangSinh;
        cout << "Nhap nam sinh > ";
        cin >> namSinh;
        cout << "Nhap gioi tinh > ";
        cin.ignore();
        cin.getline(gioiTinh, 10);
        cout << "Nhap diem trung binh > ";
        cin >> diemTB;
        cout << "Nhap xep loai dao duc > ";
        cin.ignore();
        cin.getline(xepLoaiDaoDuc, 15);
    }
    void xuat() const {
        cout << "=== Thong tin hoc sinh ===" << endl;
        cout << "Ho ten: " << hoTen << endl;
        cout << "Ngay sinh: " << ngaySinh << "/" << thangSinh << "/" << namSinh
             << endl;
        cout << "Gioi tinh: " << gioiTinh << endl;
        cout << "Diem trung binh: " << diemTB << endl;
        cout << "Xep loai dao duc: " << xepLoaiDaoDuc << endl;
    }
};

int main() {
    HocSinh hs;
    hs.nhap();
    hs.xuat();

    return 0;
}
