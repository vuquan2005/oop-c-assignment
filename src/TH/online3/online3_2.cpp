/**
 * @file online3_2.cpp
 * @brief Tam giac
 * @note
 *
 * @author VuQuan
 * @date 28-07-2026
 *
 * @status todo
 */

#include <fstream>
#include <iostream>

using namespace std;

class TG {
  private:
    int a, b, c;

  public:
    int operator~() {
        return a + b + c;
    }

    friend istream &operator>>(istream &in, TG &tg) {
        in >> tg.a >> tg.b >> tg.c;
        return in;
    }

    friend ostream &operator<<(ostream &out, TG &tg) {
        out << "a: " << tg.a << " b: " << tg.b << " c: " << tg.c
            << " chu vi: " << ~tg << endl;
        return out;
    }
};

int main() {
    TG a, b;

    cin >> a >> b;

    cout << a << b;

    ofstream f("INOUT.txt", ios::out);

    f << a << b;

    return 0;
}
