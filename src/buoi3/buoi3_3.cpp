/**
 * @file buoi3_3.cpp
 * @brief Phiếu nhập văn phòng phẩm
 * @note [Ghi chú]
 *
 * @author VuQuan
 * @date 21-07-2026
 *
 * @status done
 */

#include <cstring>
#include <iomanip>
#include <iostream>

using namespace std;

class SanPham {
  private:
    char maSP[10];
    char tenSP[30];
    int soLuong;
    float donGia;

  public:
    void nhap() {
        cout << "Nhap ma san pham: ";
        cin.ignore();
        cin.getline(maSP, 10);

        cout << "Nhap ten san pham: ";
        cin.getline(tenSP, 30);

        cout << "Nhap so luong: ";
        cin >> soLuong;

        cout << "Nhap don gia: ";
        cin >> donGia;
    }

    void xuat() const {
        cout << setw(15) << maSP << setw(30) << tenSP << setw(15) << soLuong
             << setw(15) << donGia << setw(15) << soLuong * donGia << endl;
    }

    int getSoLuong() const {
        return soLuong;
    }

    float getDonGia() const {
        return donGia;
    }
};

class Phieu {
  private:
    char maPhieu[10];
    char ngayLap[15];
    char maNhaCungCap[10];
    char tenNhaCungCap[30];
    char diaChi[50];
    char dienThoai[15];
    SanPham *dsSanPham;
    int soLuongSanPham;

  public:
    void nhap() {
        cout << "Nhap ma phieu: ";
        cin.ignore();
        cin.getline(maPhieu, 10);

        cout << "Nhap ngay lap: ";
        cin.getline(ngayLap, 15);

        cout << "Nhap ma nha cung cap: ";
        cin.getline(maNhaCungCap, 10);

        cout << "Nhap ten nha cung cap: ";
        cin.getline(tenNhaCungCap, 30);

        cout << "Nhap dia chi: ";
        cin.getline(diaChi, 50);

        cout << "Nhap dien thoai: ";
        cin.getline(dienThoai, 15);

        do {
            cout << "Nhap so luong san pham: ";
            cin >> soLuongSanPham;
        } while (soLuongSanPham <= 0 || soLuongSanPham > 100);

        dsSanPham = new SanPham[soLuongSanPham];

        for (int i = 0; i < soLuongSanPham; i++) {
            cout << "Nhap thong tin san pham thu " << i + 1 << ":" << endl;
            dsSanPham[i].nhap();
        }
    }

    void xuat() const {
        cout << setw(15) << "Ma phieu:" << setw(15) << maPhieu << setw(15)
             << "Ngay lap:" << setw(15) << ngayLap << setw(15)
             << "Ma nha cung cap:" << setw(15) << maNhaCungCap << setw(30)
             << "Ten nha cung cap:" << setw(30) << tenNhaCungCap << setw(50)
             << "Dia chi:" << setw(10) << setw(40) << diaChi << setw(15)
             << "Dien thoai:" << setw(15) << dienThoai << endl;

        cout << setw(15) << "Ma SP" << setw(30) << "Ten SP" << setw(15)
             << "So luong" << setw(15) << "Don gia" << setw(15) << "Thanh tien"
             << endl;

        for (int i = 0; i < soLuongSanPham; i++) {
            dsSanPham[i].xuat();
        }

        cout << setw(30) << "Tong tien: ";
        float tongTien = 0;
        for (int i = 0; i < soLuongSanPham; i++) {
            tongTien += dsSanPham[i].getSoLuong() * dsSanPham[i].getDonGia();
        }
        cout << tongTien << endl;
    }

    SanPham &getSanPham(int index) {
        return dsSanPham[index];
    }

    int getSoLuongSanPham() const {
        return soLuongSanPham;
    }

    void sortSP() {
        for (int i = 0; i < soLuongSanPham - 1; i++) {
            for (int j = i + 1; j < soLuongSanPham; j++) {
                if (dsSanPham[i].getSoLuong() < dsSanPham[j].getSoLuong()) {
                    swap(dsSanPham[i], dsSanPham[j]);
                }
            }
        }
    }

    void suaTenNhaCungCap(const char *tenMoi) {
        strncpy(tenNhaCungCap, tenMoi, sizeof(tenNhaCungCap) - 1);
        tenNhaCungCap[sizeof(tenNhaCungCap) - 1] = '\0';
    }
};

int main() {
    Phieu phieu;
    cout << "Nhap thong tin phieu:" << endl;
    phieu.nhap();
    cout << "Thong tin phieu:" << endl;
    phieu.xuat();

    cout << "So san pham co so luong nho hon 80: ";
    int count = 0;
    for (int i = 0; i < phieu.getSoLuongSanPham(); i++) {
        if (phieu.getSanPham(i).getSoLuong() < 80) {
            // phieu.getSanPham(i).xuat();
            count++;
        }
    }
    if (count == 0) {
        cout << "\nKhong co san pham nao co so luong nho hon 80." << endl;
    } else {
        cout << count << endl;
    }
    cout << "Tong so san pham: " << count << endl;

    phieu.sortSP();
    cout << "Danh sach san pham sau khi sap xep theo so luong giam dan:"
         << endl;
    phieu.xuat();

    phieu.suaTenNhaCungCap("Cong ty TNHH Thanh Do");
    cout << "Thong tin phieu sau khi sua ten nha cung cap:" << endl;
    phieu.xuat();

    return 0;
}
