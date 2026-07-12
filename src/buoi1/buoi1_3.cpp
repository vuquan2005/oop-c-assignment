/**
 * @file buoi1_3.cpp
 * @brief Giải phương trình bậc nhất một ẩn
 * @note
 *
 * @author VuQuan
 * @date 12-07-2026
 *
 * @status todo
 */

#include <iostream>

using namespace std;

class PTBacNhat {
  private:
    float a;
    float b;

  public:
    void nhap() {
        cout << "Nhap he so a > ";
        cin >> a;
        cout << "Nhap he so b > ";
        cin >> b;
    }
    void xuat() const {
        cout << "Phuong trinh: " << a << "x + " << b << " = 0" << endl;
    }
    float giaiPT() {
        if (a == 0) {
            if (b == 0) {
                cout << "Phuong trinh co vo so nghiem." << endl;
            } else {
                cout << "Phuong trinh vo nghiem." << endl;
            }
            return 0;
        } else {
            return -b / a;
        }
    }
};

int main() {
    PTBacNhat pt;
    pt.nhap();
    pt.xuat();
    cout << "Nghiem cua phuong trinh la: " << pt.giaiPT() << endl;

    return 0;
}
