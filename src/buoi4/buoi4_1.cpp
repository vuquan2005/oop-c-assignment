/**
 * @file buoi4_1.cpp
 * @brief Sách giáo khoa
 * @note
 *
 * @author VuQuan
 * @date 27-07-2026
 *
 * @status todo
 */

#include <cstring>
#include <iomanip>
#include <iostream>

using namespace std;

class BookID {
  protected:
    char tenSach[30];
    char maSach[10];

  public:
    void nhap() {
        cout << "Nhap ten sach: ";
        cin.ignore();
        cin.getline(tenSach, 30);
        cout << "Nhap ma sach: ";
        cin.getline(maSach, 10);
    }
    void xuat() const {
        cout << "Ma sach : " << maSach << endl;
        cout << "Ten sach: " << tenSach << endl;
    }
};

class TacGia {
  private:
    char tenTacGia[30];
    char diaChi[50];
    friend class SachGK;
    friend void search_kimdong(SachGK *sach, int n);
};

class NXB {
  private:
    char tenNXB[30];
    char diaChi[50];
    friend class SachGK;
    friend void search_kimdong(SachGK *sach, int n);
};

class SachGK : bookID {
  private:
    TacGia tacGia;
    NXB nxb;

  public:
    void nhap() {
        cout << "Nhap ten tac gia: ";
        cin.getline(tacGia.tenTacGia, 30);
        cout << "Nhap dia chi tac gia: ";
        cin.getline(tacGia.diaChi, 50);
        cout << "Nhap ten NXB: ";
        cin.getline(nxb.tenNXB, 30);
        cout << "Nhap dia chi NXB: ";
        cin.getline(nxb.diaChi, 50);
    }
    void xuat() const {
        bookID.xuat();
        cout << "Ten tac gia: " << tacGia.tenTacGia << endl;
        cout << "Dia chi tac gia: " << tacGia.diaChi << endl;
        cout << "Ten NXB: " << nxb.tenNXB << endl;
        cout << "Dia chi NXB: " << nxb.diaChi << endl;
    }
    friend void search_kimdong(SachGK *sach, int n) {
        for (int i = 0; i < n; i++) {
            if (strcmp(sach[i].tacGia.tenTacGia, "Kim Dong"))
        }
    }
};

int main() {
    SachGK sach[100];
    int n;
    do {
        cout << "Nhap so luong sach: ";
        cin >> n;
        cin.ignore();
    } while (n <= 0 || n > 100);

    for (int i = 0; i < n; i++) {
        cout << "Nhap thong tin sach thu " << i + 1 << ":" << endl;
        sach[i].nhap();
    }

    cout << "=== Danh sach sach ===" << endl;
    for (int i = 0; i < n; i++) {
        cout << "Sach thu " << i + 1 << ":" << endl;
        sach[i].xuat();
    }

    return 0;
}
