/**
 * @file lab2_2.cpp
 * @brief Hàng
 * @note
 * Cài đặt lớp theo sơ đồ quan hệ 1-1:
 *  - NSX: Mansx, Tennsx, Dcnsx. void NHAP(), void XUAT().
 *  - HANG: Mahang, Tenhang, NSX x. void NHAP(), void XUAT().
 *  Cài đặt hàm main nhập vào một mặt hàng a. In thông tin của mặt hàng a ra màn hình.
 *
 * @author VuQuan
 * @date 21-07-2026
 *
 * @status done
 */

#include <iostream>

using namespace std;

class NSX {
  private:
    char maNSX[10];
    char tenNSX[30];
    char diaChi[50];

  public:
    void nhap() {
        cout << "Nhap ma nha san xuat: ";
        cin.ignore();
        cin.getline(maNSX, 10);
        cout << "Nhap ten nha san xuat: ";
        cin.getline(tenNSX, 30);
        cout << "Nhap dia chi: ";
        cin.getline(diaChi, 50);
    }

    void xuat() const {
        cout << "Ma nha san xuat: " << maNSX << endl;
        cout << "Ten nha san xuat: " << tenNSX << endl;
        cout << "Dia chi: " << diaChi << endl;
    }
};

int main() {

    NSX nsx;
    nsx.nhap();
    nsx.xuat();

    return 0;
}
