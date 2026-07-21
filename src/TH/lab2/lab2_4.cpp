/**
 * @file lab2_4.cpp
 * @brief Phòng máy
 * @note [Ghi chú]
 *
 * @author VuQuan
 * @date 21-07-2026
 *
 * @status done
 */

#include <iomanip>
#include <iostream>

using namespace std;

class May {
  private:
    char maMay[10];
    char tenMay[30];
    char tinhTrang[20];

  public:
    void nhap() {
        cout << "Nhap ma may: ";
        cin.ignore();
        cin.getline(maMay, 10);
        cout << "Nhap ten may: ";
        cin.ignore();
        cin.getline(tenMay, 30);
        cout << "Nhap tinh trang: ";
        cin.ignore();
        cin.getline(tinhTrang, 20);
    }

    void xuat() const {
        cout << setw(15) << maMay << setw(30) << tenMay << setw(20) << tinhTrang
             << endl;
    }
};

class QuanLy {
  private:
    char maQL[10];
    char hoTen[30];

  public:
    void nhap() {
        cout << "Nhap ma quan ly: ";
        cin.ignore();
        cin.getline(maQL, 10);
        cout << "Nhap ho ten quan ly: ";
        cin.ignore();
        cin.getline(hoTen, 30);
    }

    void xuat() const {
        cout << "Ma quan ly: " << maQL << endl;
        cout << "Ho ten quan ly: " << hoTen << endl;
    }
};

class PhongMay {
  private:
    char maPhong[10];
    char tenPhong[30];
    float dienTich;
    May *may;
    int soLuongMay;
    QuanLy quanLy;

  public:
    void nhap() {
        cout << "Nhap ma phong: ";
        cin.ignore();
        cin.getline(maPhong, 10);
        cout << "Nhap ten phong: ";
        cin.ignore();
        cin.getline(tenPhong, 30);
        cout << "Nhap dien tich: ";
        cin >> dienTich;
        cout << "Nhap thong tin quan ly:" << endl;
        quanLy.nhap();

        cout << "Nhap so luong may: ";
        do {
            cin >> soLuongMay;
            if (soLuongMay < 1 || soLuongMay > 100) {
                cout << "So luong may phai tu 1 den 100. Vui long nhap lai: ";
            }
        } while (soLuongMay < 1 || soLuongMay > 100);

        may = new May[soLuongMay];

        for (int i = 0; i < soLuongMay; i++) {
            cout << "Nhap thong tin may thu " << i + 1 << ":" << endl;
            may[i].nhap();
        }
    }

    void xuat() const {
        cout << setw(15) << maPhong << setw(30) << tenPhong << setw(10)
             << soLuongMay << endl;
        for (int i = 0; i < soLuongMay; i++) {
            may[i].xuat();
        }
        quanLy.xuat();
    }
};

int main() {
    PhongMay phongMay;
    phongMay.nhap();
    phongMay.xuat();

    return 0;
}
