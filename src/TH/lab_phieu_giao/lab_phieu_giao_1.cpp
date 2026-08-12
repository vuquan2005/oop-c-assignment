/**
 * @file lab_phieu_giao_1.cpp
 * @brief [Mô tả ngắn gọn]
 * @note [Ghi chú]
 *
 * @author VuQuan
 * @date 12-08-2026
 *
 * @status todo
 */

#include <iomanip>
#include <iostream>

using namespace std;

class Hang {
  private:
    char ma[10], ten[20];
    int slg, gia;

    friend class Phieu;

  public:
    void nhap() {
        cin.ignore();
        cin.getline(ma, 10);

        cin.getline(ten, 20);
        cin >> slg;
        cin >> gia;
    }

    void xuat() const {
        cout << setw(15) << ma << setw(25) << ten << setw(10) << slg << setw(10)
             << gia << setw(20) << gia * slg << endl;
    }
};

class Phieu {
  private:
    char ma[10], date[10], ncc[10], tncc[20], dc[30], sdt[15];
    int n;
    Hang *h;

  public:
    void nhap() {

        cin.ignore();
        cin.getline(ma, 10);

        cin.getline(date, 10);

        cin.getline(ncc, 10);

        cin.getline(tncc, 20);

        cin.getline(dc, 30);

        cin.getline(sdt, 15);

        do {
            cin >> n;
        } while (n < 1 || n > 10000);

        h = new Hang[n];

        for (int i = 0; i < n; i++) {
            h[i].nhap();
        }
    }

    void xuat() {
        cout << setw(30) << "ma phieu: " << setw(15) << ma << setw(20)
             << setw(30) << date << endl
             << setw(15) << "ncc: " << setw(15) << "ten ncc: " << setw(30)
             << tncc << setw(30) << "dia chi: " << setw(40) << dc << setw(5)
             << "sdt: " << setw(20) << sdt << endl;

        cout << setw(15) << "ma" << setw(25) << "ten" << setw(10) << "slg"
             << setw(10) << "gia" << setw(20) << "tien" << endl;

        int sum = 0;

        for (int i = 0; i < n; i++) {
            h[i].xuat();
            sum += h[i].gia * h[i].slg;
        }

        cout << setw(40) << setw(15) << sum;
    }
};

int main() {

    return 0;
}
