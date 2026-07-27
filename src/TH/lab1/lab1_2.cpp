/**
 * @file lab1_2.cpp
 * @brief Hình chữ nhật
 * @note
 * Cài đặt lớp Hình chữ nhật bao gồm hai thuộc tính Dài, Rộng và các phương thức:
 *  - NHAP: nhập chiều dài và chiều rộng.
 *  - VE: vẽ hình chữ nhật lên màn hình bằng cách sử dụng ký tự * với chiều dài, chiều rộng vốn có của nó.
 *  - DIENTICH: trả về diện tích hình chữ nhật.
 *  - CHUVI: trả về chu vi hình chữ nhật.
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
