/**
 * @file buoi2_3.cpp
 * @brief Quản lý Phiếu mua hàng
 * @note
 * Đề bài yêu cầu:
 * - Tạo các lớp: HangHoa, ChiTietDonMua, Date, PhieuMuaHang.
 * - Sử dụng hàm bạn (friend class) để truy cập thuộc tính private.
 * - Thống kê số lượng mặt hàng có số lượng mua lớn nhất.
 *
 * @author VuQuan
 * @date 12-07-2026
 *
 * @status done
 */

#include <iomanip>
#include <iostream>

using namespace std;

#define COT_1 10
#define COT_2 30
#define COT_3 15
#define COT_4 10
#define COT_5 15

class HangHoa {
  private:
    char maHang[10];
    char tenHang[30];
    long donGia;

    friend class ChiTietDonMua;

  public:
    void nhap() {
        cout << "Nhap ma hang > ";
        cin.ignore();
        cin.getline(maHang, 10);
        cout << "Nhap ten hang > ";
        cin.getline(tenHang, 30);
        cout << "Nhap don gia > ";
        cin >> donGia;
    }
    void xuat() const {
        cout << setw(COT_1) << maHang << setw(COT_2) << tenHang << setw(COT_3)
             << donGia;
    }
};

class ChiTietDonMua {
  private:
    HangHoa hangHoa;
    int soLuong;
    friend class PhieuMuaHang;

  public:
    void nhap() {
        cout << "Nhap thong tin hang hoa:" << endl;
        hangHoa.nhap();
        cout << "Nhap so luong > ";
        cin >> soLuong;
    }
    void xuat() const {
        hangHoa.xuat();
        cout << setw(COT_4) << soLuong;
    }
    long thanhTien() const {
        return hangHoa.donGia * soLuong;
    }
};

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

class PhieuMuaHang {
  private:
    char maPhieu[10];
    Date ngayLap;
    char maNhanVien[10];
    char tenNhanVien[30];
    char tenKhachHang[30];
    int n;
    ChiTietDonMua *chiTiet;

  public:
    void nhap() {
        cout << "Nhap ma phieu > ";
        cin.ignore();
        cin.getline(maPhieu, 10);
        cout << "Nhap ngay lap phieu:" << endl;
        ngayLap.nhap();
        cout << "Nhap ma nhan vien > ";
        cin.ignore();
        cin.getline(maNhanVien, 10);
        cout << "Nhap ten nhan vien > ";
        cin.getline(tenNhanVien, 30);
        cout << "Nhap ten khach hang > ";
        cin.getline(tenKhachHang, 30);
        cout << "Nhap so luong chi tiet don mua > ";
        cin >> n;
        chiTiet = new ChiTietDonMua[n];
        for (int i = 0; i < n; i++) {
            cout << "Nhap thong tin chi tiet don mua thu " << i + 1 << ":"
                 << endl;
            chiTiet[i].nhap();
        }
    }
    void xuat() const {
        cout << "=== Thong tin phieu mua hang ===" << endl;
        cout << "Ma phieu: " << maPhieu << endl;
        cout << "Ngay lap: ";
        ngayLap.xuat();
        cout << "Ma nhan vien: " << maNhanVien << endl;
        cout << "Ten nhan vien: " << tenNhanVien << endl;
        cout << "Ten khach hang: " << tenKhachHang << endl;
        cout << "Danh sach chi tiet don mua:" << endl;
        cout << setw(COT_1) << "Ma hang" << setw(COT_2) << "Ten hang"
             << setw(COT_3) << "Don gia" << setw(COT_4) << "So luong"
             << setw(COT_5) << "Thanh tien" << endl;
        for (int i = 0; i < n; i++) {
            chiTiet[i].xuat();
            cout << setw(COT_5) << chiTiet[i].thanhTien() << endl;
        }
    }
    int slHangCoSLMuaLonNhat() const {
        int slMuaMAX = chiTiet[0].soLuong;
        for (int i = 1; i < n; i++) {
            if (chiTiet[i].soLuong > slMuaMAX) {
                slMuaMAX = chiTiet[i].soLuong;
            }
        }
        int count = 0;
        for (int i = 1; i < n; i++) {
            if (chiTiet[i].soLuong == slMuaMAX) {
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

    cout << "So hang co so luong mua lon nhat: " << phieu.slHangCoSLMuaLonNhat()
         << endl;

    return 0;
}
