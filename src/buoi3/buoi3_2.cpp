/**
 * @file buoi3_2.cpp
 * @brief Xe Hơi
 * @note [Ghi chú]
 *
 * @author VuQuan
 * @date 21-07-2026
 *
 * @status done
 */

#include <cstring>
#include <iomanip>
#include <iostream>

using namespace std;

class Date {
  private:
    int day;
    int month;
    int year;

  public:
    void nhap() {
        cout << "Nhap ngay: ";
        cin >> day;
        cout << "Nhap thang: ";
        cin >> month;
        cout << "Nhap nam: ";
        cin >> year;
    }
    void xuat() const {
        cout << day << "/" << month << "/" << year;
    }
    int getDay() const {
        return day;
    }
    int getMonth() const {
        return month;
    }
    int getYear() const {
        return year;
    }
};

class XeHoi {
  private:
    char nhanHieu[30];
    char hangSX[30];
    char kieuDang[30];
    char mauSac[30];
    Date namSX;
    char xuatXu[30];
    long giaBan;

  public:
    void nhap() {
        cout << "Nhap nhan hieu: ";
        cin.ignore();
        cin.getline(nhanHieu, 30);

        cout << "Nhap hang san xuat: ";
        cin.ignore();
        cin.getline(hangSX, 30);

        cout << "Nhap kieu dang: ";
        cin.ignore();
        cin.getline(kieuDang, 30);

        cout << "Nhap mau sac: ";
        cin.ignore();
        cin.getline(mauSac, 30);

        cout << "Nhap nam san xuat: " << endl;
        namSX.nhap();

        cout << "Nhap xuat xu: ";
        cin.ignore();
        cin.getline(xuatXu, 30);

        cout << "Nhap gia ban: ";
        cin >> giaBan;
    }

    void xuat() const {
        cout << setw(30) << nhanHieu << setw(30) << hangSX << setw(15)
             << kieuDang << setw(30) << mauSac << setw(15);
        namSX.xuat();
        cout << setw(30) << xuatXu << setw(15) << giaBan << endl;
    }

    const char *getHangSX() const {
        return hangSX;
    }

    long getGiaBan() const {
        return giaBan;
    }

    const Date &getNamSX() const {
        return namSX;
    }
};

int main() {

    XeHoi *xeHoi;
    int n;

    do {
        cout << "Nhap so luong xe hoi: ";
        cin >> n;
    } while (n <= 0 || n > 200);

    xeHoi = new XeHoi[n];

    for (int i = 0; i < n; i++) {
        cout << "Nhap thong tin xe hoi thu " << i + 1 << ":" << endl;
        xeHoi[i].nhap();
    }

    cout << "Danh sach xe hoi:" << endl;
    for (int i = 0; i < n; i++) {
        xeHoi[i].xuat();
    }

    cout << "Danh sach xe hoi hang Toyota:" << endl;
    for (int i = 0; i < n; i++) {
        if (strcmp(xeHoi[i].getHangSX(), "Toyota") == 0) {
            xeHoi[i].xuat();
        }
    }

    cout << "Xe san xuat 5/2025: ";
    int count = 0;
    for (int i = 0; i < n; i++) {
        if (xeHoi[i].getNamSX().getMonth() == 5 &&
            xeHoi[i].getNamSX().getYear() == 2025) {
            xeHoi[i].xuat();
            count++;
        }
    }
    cout << "So luong xe san xuat 5/2025: " << count << endl;

    cout << "Xap xep danh sach xe hoi theo gia ban tang dan:" << endl;
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (xeHoi[i].getGiaBan() > xeHoi[j].getGiaBan()) {
                swap(xeHoi[i], xeHoi[j]);
            }
        }
    }

    for (int i = 0; i < n; i++) {
        xeHoi[i].xuat();
    }

    delete[] xeHoi;
    return 0;
}
