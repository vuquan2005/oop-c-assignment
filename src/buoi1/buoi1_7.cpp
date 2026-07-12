/**
 * @file Lớp CanBo
 * @brief Cài đặt chương trình hướng đối tượng thực hiện các yêu cầu:
- Thiết kế, cài đặt lớp CanBo bao gồm các thuộc tính: Mã cán bộ, họ và tên, ngày
sinh, số ngày làm việc trong tháng và các phương thức:
  + Phương thức nhap() để nhập thông tin của cán bộ.
  + Phương thức tinhLuong(): Trả về lương của cán bộ theo công thức Lương = Số
ngày làm việc trong tháng * 250.000.
  + Phương thức xuat(): hiển thị thông tin của cán bộ ra màn hình.
- Xây dựng chương trình chính nhập thông tin cho 1 cán bộ. Xuất thông tin của
cán bộ đó ra màn hình và cho biết Lương của cán bộ đó là bao nhiêu.
 */

#include <iostream>

using namespace std;

class CanBo {
  private:
    string maCanBo;
    string hoTen;
    string ngaySinh;
    int soNgayLamViec;

  public:
    void nhap() {
        cout << "Nhap ma can bo > ";
        cin.ignore();
        getline(cin, maCanBo);
        cout << "Nhap ho ten > ";
        getline(cin, hoTen);
        cout << "Nhap ngay sinh > ";
        getline(cin, ngaySinh);
        cout << "Nhap so ngay lam viec trong thang > ";
        cin >> soNgayLamViec;
    }
    float tinhLuong() const {
        return soNgayLamViec * 250000;
    }
    void xuat() const {
        cout << "=== Thong tin can bo ===" << endl;
        cout << "Ma can bo: " << maCanBo << endl;
        cout << "Ho ten: " << hoTen << endl;
        cout << "Ngay sinh: " << ngaySinh << endl;
        cout << "So ngay lam viec trong thang: " << soNgayLamViec << endl;
        cout << "Luong: " << tinhLuong() << endl;
    }
};

int main() {
    CanBo cb;
    cb.nhap();
    cb.xuat();

    return 0;
}
