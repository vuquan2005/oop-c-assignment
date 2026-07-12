/**
 * @file buoi1_5.cpp
 * @brief Tính chu vi, diện tích tam giác
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

class TamGiac {
  private:
    float canhA;
    float canhB;
    float canhC;

  public:
    void nhap() {
        cout << "Nhap canh A > ";
        cin >> canhA;
        cout << "Nhap canh B > ";
        cin >> canhB;
        cout << "Nhap canh C > ";
        cin >> canhC;
    }
    void xuat() const {
        cout << "Canh A: " << canhA << endl;
        cout << "Canh B: " << canhB << endl;
        cout << "Canh C: " << canhC << endl;
    }
    float tinhChuVi() const {
        return canhA + canhB + canhC;
    }
    float tinhDienTich() const {
        float p = tinhChuVi() / 2;
        return sqrt(p * (p - canhA) * (p - canhB) * (p - canhC));
    }
};

int main() {
    TamGiac tg;
    tg.nhap();
    tg.xuat();
    cout << "Chu vi tam giac: " << tg.tinhChuVi() << endl;
    cout << "Dien tich tam giac: " << tg.tinhDienTich() << endl;

    return 0;
}
