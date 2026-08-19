/**
 * @file lab_phieu_giao_2.cpp
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

class LopHoc;
int count_khoa(LopHoc a, int n);
void sort_lh(LopHoc a);

class Nguoi {
  protected:
    char ht[20], ns[15], que[30];

  public:
    void nhap() {
        cout << "ho ten: ";
        cin.getline(ht, 20);
        cout << "ngay sinh: ";
        cin.getline(ns, 15);
        cout << "que quan: ";
        cin.getline(que, 30);
    }
    void xuat() {
        cout << setw(25) << ht << setw(20) << ns << setw(35) << que;
    }
};

class SinhVien : public Nguoi {
  private:
    char msv[10], nganh[20];
    int kh;

    friend int count_khoa(LopHoc a, int n);
    friend void sort_lh(LopHoc a);

  public:
    void nhap() {
        Nguoi::nhap();
        cout << "msv: ";
        cin.getline(msv, 10);
        cout << "nganh: ";
        cin.getline(nganh, 10);
        cout << "khoa hoc: ";
        cin >> kh;
        cin.ignore();
    }
    void xuat() {
        Nguoi::xuat();
        cout << setw(15) << msv << setw(25) << nganh << setw(10) << kh << endl;
    }
};

class LopHoc {
  private:
    char ma[10], ten[20], ngay[15], gv[20];
    int n;
    SinhVien *x;

    friend int count_khoa(LopHoc a, int n);
    friend void sort_lh(LopHoc a);

  public:
    ~LopHoc() {
        if (x != nullptr) {
            delete[] x;
        }
    }

    void nhap() {
        cout << "Nhap thong tin lop hoc: " << endl;
        cout << "ma: ";
        cin.getline(ma, 10);
        cout << "ten: ";
        cin.getline(ten, 20);
        cout << "ngay mo: ";
        cin.getline(ngay, 15);
        cout << "giao vien: ";
        cin.getline(gv, 20);
        do {

            cout << "so hoc sinh: ";
            cin >> n;
            cin.ignore();
        } while (n <= 0);
        x = new SinhVien[n];

        for (int i = 0; i < n; i++) {
            cout << "sinh vien " << i << " :" << endl;
            x[i].nhap();
        }
    }

    void xuat() {
        cout << "Ma lop hoc: " << ma << endl
             << "ten lop hoc: " << ten << endl
             << "ngay mo: " << ngay << endl
             << "giao vien: " << gv << endl;

        cout << setw(25) << "ho ten" << setw(15) << "ngay sinh" << setw(35)
             << "que quan" << setw(15) << "msv" << setw(25) << "nganh"
             << setw(10) << "khoa hoc" << endl;
        for (int i = 0; i < n; i++) {
            x[i].xuat();
        }
    }
};

int count_khoa(LopHoc a, int n) {
    int count = 0;
    for (int i = 0; i < a.n; i++) {
        if (a.x[i].kh == n)
            count++;
    }
    return count;
}

void sort_lh(LopHoc a) {
    for (int i = 0; i < a.n; i++) {
        for (int j = i; j < a.n; j++) {
            if (a.x[i].kh > a.x[j].kh) {
                SinhVien x = a.x[i];
                a.x[i] = a.x[j];
                a.x[j] = x;
            }
        }
    }
}

int main() {

    LopHoc a;
    a.nhap();
    cout << "===========" << endl;
    a.xuat();

    int k11 = count_khoa(a, 11);

    if (k11 > 0) {
        cout << "Co " << k11 << " sinh vien khoa 11" << endl;
    } else
        cout << "Khong co sinh vien khoa 11" << endl;

    cout << "======";
    sort_lh(a);
    a.xuat();

    return 0;
}
