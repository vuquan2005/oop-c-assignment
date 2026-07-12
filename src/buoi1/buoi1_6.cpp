/**
 * @file Học sinh
 * @brief Viết chương trình hướng đối tượng giải quyết bài toán, nhập và hiển
 * thị thông tin của một học sinh gồm: Họ tên, ngày, tháng, năm sinh, giới tính,
 * điểm trung bình, xếp loại đạo đức.
 */

#include <iostream>

using namespace std;

class HocSinh {
  private:
    string hoTen;
    int ngaySinh;
    int thangSinh;
    int namSinh;
    string gioiTinh;
    float diemTB;
    string xepLoaiDaoDuc;

  public:
    void nhap() {
        cout << "Nhap ho ten hoc sinh > ";
        cin.ignore();
        getline(cin, hoTen);
        cout << "Nhap ngay sinh > ";
        cin >> ngaySinh;
        cout << "Nhap thang sinh > ";
        cin >> thangSinh;
        cout << "Nhap nam sinh > ";
        cin >> namSinh;
        cout << "Nhap gioi tinh > ";
        cin.ignore();
        getline(cin, gioiTinh);
        cout << "Nhap diem trung binh > ";
        cin >> diemTB;
        cout << "Nhap xep loai dao duc > ";
        cin.ignore();
        getline(cin, xepLoaiDaoDuc);
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
