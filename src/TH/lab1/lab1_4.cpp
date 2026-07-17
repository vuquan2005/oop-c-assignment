/**
 * @file lab1_4.cpp
 * @brief Sách
 * @note Nhập số lượng sách và xuất định dạng
 *
 * @author VuQuan
 * @date 17-07-2026
 *
 * @status done
 */

#include <iomanip>
#include <iostream>

using namespace std;

class SACH {
  private:
    char maSach[15];
    char tenSach[20];
    char nxb[20];
    int soTrang;
    int giaTien;

  public:
    void nhap() {
        cout << "Nhap ma sach: ";
        cin >> maSach;
        cout << "Nhap ten sach: ";
        cin.ignore();
        cin.getline(tenSach, 20);
        cout << "Nhap nha xuat ban: ";
        cin.getline(nxb, 20);
        cout << "Nhap so trang: ";
        cin >> soTrang;
        cout << "Nhap gia tien: ";
        cin >> giaTien;
    }
    void xuat() const {
        cout << setw(15) << left << maSach << setw(20) << left << tenSach
             << setw(20) << left << nxb << setw(15) << right << soTrang
             << setw(15) << right << giaTien << endl;
    }
};

int main() {

    int n = 0;
    do {
        cout << "Nhap so luong sach (1-100): ";
        cin >> n;
    } while (n < 1 || n > 100);

    SACH *sachs = new SACH[n];
    for (int i = 0; i < n; i++) {
        cout << "Nhap thong tin sach thu " << i + 1 << ":" << endl;
        sachs[i].nhap();
    }

    cout << "=== Danh sach sach ===" << endl;
    cout << setw(15) << left << "Ma sach" << setw(20) << left << "Ten sach"
         << setw(20) << left << "Nha xuat ban" << setw(15) << right
         << "So trang" << setw(15) << right << "Gia tien" << endl;
    for (int i = 0; i < n; i++) {
        sachs[i].xuat();
    }

    delete[] sachs;

    return 0;
}
