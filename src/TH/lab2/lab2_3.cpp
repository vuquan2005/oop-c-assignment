/**
 * @file lab2_3.cpp
 * @brief Phiếu-Hàng
 * @note
 * Cài đặt lớp theo sơ đồ quan hệ 1-n:
 *  - HANG: Mahang, Tenhang, Dongia. void NHAP(), void XUAT().
 *  - PHIEU: Maphieu, HANG x[], int n. void NHAP(), void XUAT().
 *  Trong đó n là số mặt hàng trong phiếu. Viết hàm main nhập vào một phiếu gồm n mặt hàng. In ra thông tin của phiếu.
 *
 * @author VuQuan
 * @date 21-07-2026
 *
 * @status done
 */

#include <iomanip>
#include <iostream>

using namespace std;

class Hang {
  private:
    char maHang[10];
    char tenHang[30];
    float donGia;

  public:
    void nhap() {
        cout << "Nhap ma hang: ";
        cin.ignore();
        cin.getline(maHang, 10);
        cout << "Nhap ten hang: ";
        cin.getline(tenHang, 30);
        cout << "Nhap don gia: ";
        cin >> donGia;
    }

    void xuat() const {
        cout << setw(15) << maHang << setw(30) << tenHang << setw(10) << donGia
             << endl;
    }
};

class Phieu {
  private:
    char maPhieu[10];
    Hang hang[100];
    int soLuongHang;

  public:
    void nhap() {
        cout << "Nhap ma phieu: ";
        cin.ignore();
        cin.getline(maPhieu, 10);
        cout << "Nhap so luong hang: ";
        do {
            cin >> soLuongHang;
            if (soLuongHang < 1 || soLuongHang > 100) {
                cout << "So luong hang phai tu 1 den 100. Vui long nhap lai: ";
            }
        } while (soLuongHang < 1 || soLuongHang > 100);

        for (int i = 0; i < soLuongHang; i++) {
            cout << "Nhap thong tin hang thu " << i + 1 << ":" << endl;
            hang[i].nhap();
        }
    }

    void xuat() const {
        cout << "Ma phieu: " << maPhieu << endl;
        cout << setw(15) << "Ma hang" << setw(30) << "Ten hang" << setw(10)
             << "Don gia" << endl;
        for (int i = 0; i < soLuongHang; i++) {
            hang[i].xuat();
        }
    }
};

int main() {
    Phieu phieu;
    phieu.nhap();
    phieu.xuat();
    return 0;
}
