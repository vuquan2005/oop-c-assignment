/**
 * @file online1_1.cpp
 * @brief Phiếu nhập hàng
 * @note
 * Viết chương trình cho phép nhập, xuất thông tin của phiếu PHIẾU NHẬP HÀNG
 * gồm:
 *  - Mã phiếu, Ngày lập, Mã NCC, Tên NCC, Địa chỉ.
 *  - Danh sách hàng hóa (Mã hàng, Tên hàng, Đơn giá, Số lượng). Thành tiền =
 * Đơn giá * Số lượng.
 *  - In ra mẫu phiếu căn lề đẹp mắt, hiển thị tổng tiền của toàn phiếu.
 *
 * @author VuQuan
 * @date 28-07-2026
 *
 * @status todo
 */

#include <iomanip>
#include <iostream>

using namespace std;

class Phieu;

class Hang {
  private:
    char ten[20];
    int dg, sl;

    friend class Phieu;

  public:
    void nhap() {
        cout << "Nhap ten hang: ";
        cin.ignore();
        cin.getline(ten, 20);
        cout << "Nhap don gia: ";
        cin >> dg;
        cout << "Nhap so luong: ";
        cin >> sl;
    }
    void xuat() {
        cout << setw(25) << ten << setw(15) << dg << setw(15) << sl << setw(15)
             << dg * sl << endl;
    }
};

class Phieu {
  private:
    char maPhieu[10];
    char ngayLap[10];
    char NCC[10];
    char tenNCC[20];
    char dc[30];
    Hang *hang;
    int n;

  public:
    void nhap() {
        cout << "Nhap ma phieu: ";
        cin.ignore();
        cin.getline(maPhieu, 10);
        cout << "Nhap ngay lap: ";
        cin.ignore();
        cin.getline(ngayLap, 10);
        cout << "Nhap ma ncc: ";
        cin.ignore();
        cin.getline(NCC, 10);
        cout << "Nhap ten ncc: ";
        cin.ignore();
        cin.getline(tenNCC, 20);
        cout << "Nhap dia chi: ";
        cin.ignore();
        cin.getline(dc, 30);

        do {
            cout << "nhap so hang: ";
            cin >> n;
            cin.ignore();
        } while (n <= 0 || n >= 100);
        hang = new Hang[n];

        for (int i = 0; i < n; i++)
            hang[i].nhap();
    }
    void xuat() {
        cout << "=== Phieu nhap hang ===" << endl
             << setw(30) << "ma phieu: " << maPhieu << setw(30)
             << "Ngay lap: " << ngayLap << endl
             << setw(30) << "ma ncc: " << NCC << setw(30)
             << "Ten ncc: " << tenNCC << endl
             << "dia chi: " << dc << endl;
        int sum = 0;
        for (int i = 0; i < n; i++) {
            hang[i].xuat();
            sum += hang[i].dg * hang[i].sl;
        }
        cout << setw(30) << "thanh tien: " << sum << endl;
    }
};

int main() {

    // freopen("tests/online1_1/1.in", "r", stdin);

    Phieu a;

    a.nhap();
    a.xuat();

    return 0;
}
