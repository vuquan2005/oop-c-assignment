/**
 * @file buoi2_2.cpp
 * @brief Phiếu mua hàng
 * @note
 *
 * @author VuQuan
 * @date 12-07-2026
 *
 * @status done
 */

#include <iomanip>
#include <iostream>

using namespace std;

class HangHoa {
  private:
    int maHang;
    char tenHang[50];
    long tienTra;

    friend class PhieuMuaHang;
    // Theo sơ đồ lớp, lớp này không có phương thức
};

class PhieuMuaHang {
  private:
    int maPhieu;
    char tenKhachHang[30];
    int n;
    HangHoa *hangHoa;

  public:
    void nhap() {
        cout << "Nhap ma phieu > ";
        cin >> maPhieu;
        cout << "Nhap ten khach hang > ";
        cin.ignore();
        cin.getline(tenKhachHang, 30);
        cout << "Nhap so luong hang hoa > ";
        cin >> n;
        hangHoa = new HangHoa[n];
        for (int i = 0; i < n; i++) {
            cout << "Nhap thong tin hang hoa thu " << i + 1 << ":" << endl;
            cout << "Nhap ma hang > ";
            cin >> hangHoa[i].maHang;
            cout << "Nhap ten hang > ";
            cin.ignore();
            cin.getline(hangHoa[i].tenHang, 50);
            cout << "Nhap tien tra > ";
            cin >> hangHoa[i].tienTra;
        }
    }
    void xuat() const {
        cout << "=== Thong tin phieu mua hang ===" << endl;
        cout << "Ma phieu: " << maPhieu << endl;
        cout << "Ten khach hang: " << tenKhachHang << endl;
        cout << "Danh sach hang hoa:" << endl << endl;
        cout << setw(10) << "Ma hang" << setw(20) << "Ten hang" << setw(15)
             << "Tien tra" << endl;
        for (int i = 0; i < n; i++) {
            cout << setw(10) << hangHoa[i].maHang << setw(20)
                 << hangHoa[i].tenHang << setw(15) << hangHoa[i].tienTra
                 << endl;
        }
    }
    int slHangGialonHon(long gia) const {
        int count = 0;
        for (int i = 0; i < n; i++) {
            if (hangHoa[i].tienTra > gia) {
                count++;
            }
        }
        return count;
    }
};

int main() {
    PhieuMuaHang phieu;
    phieu.nhap();
    cout << endl;
    phieu.xuat();

    int count = phieu.slHangGialonHon(250);
    if (count > 0)
        cout << "So hang co tien tra lon hon 250: " << count << endl;
    else
        cout << "Khong co hang hoa thoa man dieu kien!" << endl;

    return 0;
}
