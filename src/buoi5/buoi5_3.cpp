/**
 * @file buoi5_3.cpp
 * @brief [Mô tả ngắn gọn]
 * @note [Ghi chú]
 *
 * @author VuQuan
 * @date 12-08-2026
 *
 * @status todo
 */

#include <iostream>
#include <string.h>

using namespace std;

class MayIn {
  private:
    char ten[20];
    char mau[20];
    long gia;

  public:
    MayIn() : gia(0) {
        strcpy(ten, "");
        strcpy(mau, "");
    }
    MayIn(char t[], char m[], long gia) : gia(gia) {
        strcpy(ten, t);
        strcpy(mau, m);
    }

    friend istream &operator>>(istream &in, MayIn &m) {
        cout << "ten: ";
        in.ignore();
        in.getline(m.ten, 20);
        cout << "mau: ";
        in.getline(m.mau, 20);
        cout << "gia: ";
        in >> m.gia;
        in.ignore();
        return in;
    }

    friend ostream &operator<<(ostream &out, const MayIn &m) {
        out << "ten: " << m.ten << endl
            << "mau: " << m.mau << endl
            << "gia: " << m.gia << endl;
        return out;
    }

    bool operator++() {
        if (strcmp(mau, "trắng") == 0 && gia > 95)
            return true;
        return false;
    }

    bool operator==(const MayIn &m) {
        if (strcmp(ten, m.ten) == 0 && gia == m.gia)
            return true;
        return false;
    }
};

int main() {
    MayIn A;
    cin >> A;
    MayIn B("hehe", "trang", 1000);

    if (++A || ++B) {
        cout << "May in co mau trang va gia > 95 la:" << endl;
        if (++A)
            cout << A;
        if (++B)
            cout << B;
    }

    if (A == B)
        cout << "Hai may cung ten va gia thanh" << endl;
    else
        cout << "Hai may khong cung ten hoac gia thanh" << endl;

    return 0;
}
