/**
 * @file buoi1_4.cpp
 * @brief Giải phương trình bậc 2
 * @note
 *
 * @author VuQuan
 * @date 12-07-2026
 *
 * @status todo
 */

#include <cmath>
#include <iostream>

using namespace std;

class PTBacHai {
  private:
    float a;
    float b;
    float c;

  public:
    void nhap() {
        cout << "Nhap he so a > ";
        cin >> a;
        cout << "Nhap he so b > ";
        cin >> b;
        cout << "Nhap he so c > ";
        cin >> c;
    }
    void xuat() const {
        cout << "Phuong trinh: " << a << "x^2 + " << b << "x + " << c << " = 0"
             << endl;
    }
    void giaiPT() {
        if (a == 0) {
            if (b == 0) {
                if (c == 0) {
                    cout << "Phuong trinh co vo so nghiem." << endl;
                } else {
                    cout << "Phuong trinh vo nghiem." << endl;
                }
            } else {
                cout << "Phuong trinh co mot nghiem: x = " << -c / b << endl;
            }
        } else {
            float delta = b * b - 4 * a * c;
            if (delta < 0) {
                cout << "Phuong trinh vo nghiem." << endl;
            } else if (delta == 0) {
                cout << "Phuong trinh co mot nghiem kep: x = " << -b / (2 * a)
                     << endl;
            } else {
                cout << "Phuong trinh co hai nghiem phan biet: x1 = "
                     << (-b + sqrt(delta)) / (2 * a)
                     << ", x2 = " << (-b - sqrt(delta)) / (2 * a) << endl;
            }
        }
    }
};

int main() {
    PTBacHai pt;
    pt.nhap();
    pt.xuat();
    pt.giaiPT();

    return 0;
}
