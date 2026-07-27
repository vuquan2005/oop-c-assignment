/**
 * @file lab2_1.cpp
 * @brief Nhân sự
 * @note
 * Cài đặt các lớp theo sơ đồ:
 *  - DATE: D(ngày), M(tháng), Y(năm). void NHAP(), void XUAT().
 *  - NHANSU: Manhansu, Hoten, DATE NS. void NHAP(), void XUAT().
 *  Cài đặt hàm main nhập vào một nhân sự x, in thông tin của nhân sự ra màn hình.
 *
 * @author VuQuan
 * @date 21-07-2026
 *
 * @status done
 */

#include <iostream>

using namespace std;

class Date {
  private:
    int day;
    int month;
    int year;

  public:
    void nhap() {
        cout << "Nhap ngay: ";
        cin >> day;
        cout << "Nhap thang: ";
        cin >> month;
        cout << "Nhap nam: ";
        cin >> year;
    }
    void xuat() const {
        cout << day << "/" << month << "/" << year;
    }
};

class NhanSU {
  private:
    char maNS[10];
    char hoTen[30];
    Date ngaySinh;

  public:
    void nhap() {
        cout << "Nhap ma nhan su: ";
        cin >> maNS;
        cout << "Nhap ho ten: ";
        cin >> hoTen;
        ngaySinh.nhap();
    }
    void xuat() {
        cout << "Ma nhan su: " << maNS << endl;
        cout << "Ho ten: " << hoTen << endl;
        cout << "Ngay sinh: ";
        ngaySinh.xuat();
        cout << endl;
    }
};

int main() {

    NhanSU ns;
    ns.nhap();
    ns.xuat();

    return 0;
}
