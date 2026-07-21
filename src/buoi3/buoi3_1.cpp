/**
 * @file buoi3_1.cpp
 * @brief Doanh nghiệp
 * @note
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
};

class DiaChi {
  private:
    char dienThoai[12];
    char phuong[30];
    char quan[30];
    char thanhPho[30];
    friend class DoanhNghiep;
};

class DoanhNghiep {
  private:
    int maDN;
    char tenDN[60];
    Date ngayThanhLap;
    DiaChi diaChi;
    char giamDoc[30];
    long doanhThu;

  public:
    void nhap() {
        cout << "Nhap ma doanh nghiep: ";
        cin >> maDN;

        cout << "Nhap ten doanh nghiep: ";
        cin.ignore();
        cin.getline(tenDN, 60);

        cout << "Nhap ngay thanh lap: " << endl;
        ngayThanhLap.nhap();

        cout << "Nhap dia chi: " << endl;

        cout << "Nhap dien thoai: ";
        cin.ignore();
        cin.getline(diaChi.dienThoai, 12);

        cout << "Nhap phuong: ";
        cin.ignore();
        cin.getline(diaChi.phuong, 30);

        cout << "Nhap quan: ";
        cin.ignore();
        cin.getline(diaChi.quan, 30);

        cout << "Nhap thanh pho: ";
        cin.ignore();
        cin.getline(diaChi.thanhPho, 30);

        cout << "Nhap giam doc: ";
        cin.ignore();
        cin.getline(giamDoc, 30);

        cout << "Nhap doanh thu: ";
        cin >> doanhThu;
    }

    void xuat() const {
        cout << setw(15) << maDN << setw(30) << tenDN << setw(15);
        ngayThanhLap.xuat();
        cout << setw(15) << diaChi.dienThoai << setw(30) << diaChi.phuong
             << setw(30) << diaChi.quan << setw(30) << diaChi.thanhPho
             << setw(30) << giamDoc << setw(15) << doanhThu << endl;
    }

    int getMaDN() const {
        return maDN;
    }

    const char *getThanhPho() const {
        return diaChi.thanhPho;
    }

    long getDoanhThu() const {
        return doanhThu;
    }
};

int main() {

    DoanhNghiep dn[20];
    int n;

    do {
        cout << "Nhap so luong doanh nghiep: ";
        cin >> n;
    } while (n <= 0 || n > 20);

    for (int i = 0; i < n; i++) {
        cout << "Nhap thong tin doanh nghiep thu " << i + 1 << ":" << endl;
        dn[i].nhap();
    }

    cout << "Danh sach doanh nghiep:" << endl;
    cout << setw(15) << "Ma DN" << setw(30) << "Ten DN" << setw(15) << "Ngay TL"
         << setw(15) << "Dien thoai" << setw(30) << "Phuong" << setw(30)
         << "Quan" << setw(30) << "Thanh pho" << setw(30) << "Giam doc"
         << setw(15) << "Doanh thu" << endl;
    for (int i = 0; i < n; i++) {
        dn[i].xuat();
    }

    cout << "Danh sach doanh nghiep o thanh pho Ha Noi:" << endl;
    for (int i = 0; i < n; i++) {
        if (strcmp(dn[i].getThanhPho(), "Ha Noi") == 0) {
            dn[i].xuat();
        }
    }

    cout << "Tong thu nhap cua doanh nghiep thanh lap nam 2015: ";
    long tongDoanhThu = 0;
    for (int i = 0; i < n; i++) {
        if (dn[i].getDoanhThu() == 2015) {
            tongDoanhThu += dn[i].getDoanhThu();
        }
    }
    cout << tongDoanhThu << endl;

    cout << "Sua thong tin theo ma doanh nghiep: ";
    int maDN;
    cin >> maDN;
    bool found = false;
    for (int i = 0; i < n; i++) {
        if (dn[i].getMaDN() == maDN) {
            cout << "Nhap thong tin moi cho doanh nghiep: " << endl;
            dn[i].nhap();
            found = true;
            break;
        }
    }
    if (!found) {
        cout << "Khong tim thay doanh nghiep voi ma " << maDN << endl;
    }

    return 0;
}
