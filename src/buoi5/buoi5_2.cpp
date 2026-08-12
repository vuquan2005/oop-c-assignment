/**
 * @file buoi5_2.cpp
 * @brief [Mô tả ngắn gọn]
 * @note [Ghi chú]
 *
 * @author VuQuan
 * @date 12-08-2026
 *
 * @status todo
 */

#include <iostream>

using namespace std;

class Diem {
  private:
    int x, y, z;

  public:
    Diem() : x(0), y(0), z(0) {}
    Diem(int x, int y, int z) : x(x), y(y), z(z) {}

    Diem operator+(const Diem &p) const {
        return Diem(x + p.x, y + p.y, z + p.z);
    }

    Diem operator-(const Diem &p) const {
        return Diem(x - p.x, y - p.y, z - p.z);
    }

    friend std::istream &operator>>(std::istream &in, Diem &p) {
        in >> p.x >> p.y >> p.z;

        return in;
    }
    friend std::ostream &operator<<(std::ostream &out, const Diem &p) {
        out << "(" << p.x << "," << p.y << "," << p.z << ")";
        return out;
    }
};

int main() {

    Diem a(1, 2, 3);
    Diem b;

    cin >> b;

    Diem t = a + b;
    Diem h = a - b;
    cout << "Tong: " << t << endl << "Hieu: " << h << endl;

    return 0;
}
