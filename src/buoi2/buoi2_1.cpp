/**
 * @file buoi2_1.cpp
 * @brief Ô tô
 * @note
 *
 * @author VuQuan
 * @date 12-07-2026
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
        cout << "Nhap ngay > ";
        cin >> day;
        cout << "Nhap thang > ";
        cin >> month;
        cout << "Nhap nam > ";
        cin >> year;
    }
    void xuat() const {
        cout << day << "/" << month << "/" << year << endl;
    }
};

class XeHoi {
  private:
    char hangSX[20];
    Date namSX;
    int giaBan;
    int soLuong;

  public:
    void nhap() {
        cout << "Nhap hang san xuat > ";
        cin.ignore();
        cin.getline(hangSX, 20);
        cout << "Nhap nam san xuat:" << endl;
        namSX.nhap();
        cout << "Nhap gia ban > ";
        cin >> giaBan;
        cout << "Nhap so luong > ";
        cin >> soLuong;
    }
    void xuat() const {
        cout << "=== Thong tin xe hoi ===" << endl;
        cout << "Hang san xuat: " << hangSX << endl;
        cout << "Nam san xuat: ";
        namSX.xuat();
        cout << "Gia ban: " << giaBan << endl;
        cout << "So luong: " << soLuong << endl;
    }
};

int main() {
    XeHoi xe;
    xe.nhap();
    cout << endl;
    xe.xuat();

    return 0;
}
