/**
 * @file lab1_1.cpp
 * @brief Sinh viên
 * @note
 * Cài đặt lớp SINHVIEN gồm các thuộc tính: Mã Sinh Viên, Họ và Tên, Tuổi, Điểm và các phương thức:
 *  - NHAP: nhập toàn bộ các thông tin cho sinh viên.
 *  - XUAT: xuất toàn bộ thông tin của sinh viên ra màn hình.
 *  Cài đặt hàm main khai báo hai sinh viên a, b. Sử dụng các phương thức của hai sinh viên để nhập vào thông tin của sinh viên a, b; xuất thông tin của hai sinh viên ra màn hình.
 *
 * @author VuQuan
 * @date 17-07-2026
 *
 * @status done
 */

#include <iostream>

using namespace std;

class SINHVIEN {
  private:
    char mssv[10];
    char hoten[20];
    int tuoi;
    float diem;

  public:
    void nhap() {
        cout << "Nhap MSSV: ";
        cin >> mssv;
        cout << "Nhap ho ten: ";
        cin.ignore();
        cin.getline(hoten, 20);
        cout << "Nhap tuoi: ";
        cin >> tuoi;
        cout << "Nhap diem: ";
        cin >> diem;
    }

    void xuat() const {
        cout << "=== Thong tin sinh vien ===" << endl;
        cout << "MSSV: " << mssv << endl;
        cout << "Ho ten: " << hoten << endl;
        cout << "Tuoi: " << tuoi << endl;
        cout << "Diem: " << diem << endl;
    }
};

int main() {
    SINHVIEN sv;
    sv.nhap();
    sv.xuat();

    return 0;
}
