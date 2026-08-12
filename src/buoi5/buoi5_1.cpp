/**
 * @file buoi5_1.cpp
 * @brief Số phức
 * @note [Ghi chú]
 *
 * @author VuQuan
 * @date 12-08-2026
 *
 * @status todo
 */

#include <iostream>

using namespace std;

class SoPhuc {

  private:
    float a, b;

  public:
    friend std::istream &operator>>(std::istream &in, SoPhuc &x) {
        cout << "Nhap phan thuc: ";
        in >> x.a; // dùng luồng in thay vì cin
        cout << "Nhap phan ao: ";
        in >> x.b;

        return in;
    }
    friend std::ostream &operator<<(std::ostream &out, const SoPhuc &x) {
        out << x.a << " + " << x.b << "i"; // out not cout
        return out;
    }

    SoPhuc operator+(SoPhuc x) {
        SoPhuc temp;
        temp.a = a + x.a;
        temp.b = b + x.b;
        return temp;
    }

    bool operator==(SoPhuc x) {
        if (a == x.a && b == x.b)
            return true;
        else
            return false;
    }
};

int main() {

    SoPhuc A;
    SoPhuc B;

    cin >> A >> B;

    cout << "Tổng: " << (A + B) << endl;

    cout << (A == B ? "Bằng" : "Không bằng") << endl;

    return 0;
}
