/**
 * @file lab1_2.cpp
 * @brief Hình chữ nhật
 * @note
 *
 * @author VuQuan
 * @date 17-07-2026
 *
 * @status done
 */

#include <iostream>

using namespace std;

class HCN {
  private:
    float chieuDai;
    float chieuRong;

  public:
    void nhap() {
        cout << "Nhap chieu dai: ";
        cin >> chieuDai;
        cout << "Nhap chieu rong: ";
        cin >> chieuRong;
    }

    void ve() const {
        cout << "Hinh chu nhat: " << endl;
        for (int i = 0; i < chieuDai; i++) {
            for (int j = 0; j < chieuRong; j++) {
                cout << "* ";
            }
            cout << endl;
        }
    }

    float tinhDienTich() const {
        return chieuDai * chieuRong;
    }

    float tinhChuVi() const {
        return 2 * (chieuDai + chieuRong);
    }
};

int main() {
    HCN hcn;
    hcn.nhap();
    hcn.ve();
    cout << "Dien tich: " << hcn.tinhDienTich() << endl;
    cout << "Chu vi: " << hcn.tinhChuVi() << endl;

    return 0;
}
