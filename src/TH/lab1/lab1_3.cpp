/**
 * @file lab1_3.cpp
 * @brief Hàng hóa
 * @note
 * Cài đặt lớp Hàng Hóa với các thuộc tính: Mã hàng, Tên hàng, Đơn giá, Số lượng và các phương thức:
 *  - NHAP: nhập thông tin của mặt hàng.
 *  - XUAT: xuất thông tin của mặt hàng lên màn hình (dữ liệu xuất trên 1 dòng) kèm theo Thành tiền.
 *  Viết hàm main nhập vào một danh sách gồm n mặt hàng. In danh sách các mặt hàng vừa nhập ra màn hình.
 *
 * @author VuQuan
 * @date 17-07-2026
 *
 * @status done
 */

#include <iomanip>
#include <iostream>

using namespace std;

class HANG {
  private:
    char maHang[15];
    char tenHang[20];
    int donGia;
    int soLuong;

  public:
    void nhap() {
        cout << "Nhap ma hang: ";
        cin >> maHang;
        cout << "Nhap ten hang: ";
        cin.ignore();
        cin.getline(tenHang, 20);
        cout << "Nhap don gia: ";
        cin >> donGia;
        cout << "Nhap so luong: ";
        cin >> soLuong;
    }
    void xuat() const {
        cout << setw(15) << left << maHang << setw(20) << left << tenHang
             << setw(15) << right << donGia << setw(15) << right << soLuong
             << setw(15) << right << (donGia * soLuong) << endl;
    }
};

int main() {
    int n = 0;

    do {
        cout << "Nhap so luong hang (1-150): ";
        cin >> n;
    } while (n < 1 || n > 150);

    HANG *hangs = new HANG[n];
    for (int i = 0; i < n; i++) {
        cout << "Nhap thong tin hang thu " << i + 1 << ":" << endl;
        hangs[i].nhap();
    }

    cout << "=== Danh sach hang ===" << endl;
    cout << setw(15) << left << "Ma hang" << setw(20) << left << "Ten hang"
         << setw(15) << right << "Don gia" << setw(15) << right << "So luong"
         << setw(15) << right << "Thanh tien" << endl;
    for (int i = 0; i < n; i++) {
        hangs[i].xuat();
    }
    delete[] hangs;
    return 0;
}
