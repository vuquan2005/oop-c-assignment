/**
 * @file online3_1.cpp
 * @brief Mảng 1 chiều
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

class ARR {
  private:
    float *value;
    int n;

  public:
    ~ARR() {
        delete[] value;
    }

    friend istream &operator>>(istream &in, ARR &arr) {
        cout << "Nhap n: ";
        in >> arr.n;
        arr.value = new float[arr.n];

        for (int i = 0; i < arr.n; i++) {
            cout << "Nhap arr " << i << ": ";
            in >> arr.value[i];
        }
        return in;
    }

    friend ostream &operator<<(ostream &out, const ARR &arr) {
        for (int i = 0; i < arr.n; i++) {
            out << arr.value[i] << " ";
        }
        return out;
    }

    void operator++() {
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                if (value[i] > value[j]) {
                    float temp = value[i];
                    value[i] = value[j];
                    value[j] = temp;
                }
            }
        }
    }

    void operator--() {
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                if (value[i] < value[j]) {
                    float temp = value[i];
                    value[i] = value[j];
                    value[j] = temp;
                }
            }
        }
    }
};

int main() {

    ARR arr;
    cin >> arr;
    cout << arr << endl;

    ++arr;
    cout << arr << endl;
    --arr;
    cout << arr << endl;

    fstream f("MANG.txt", ios::out);

    f << arr << endl;

    ++arr;
    f << arr << endl;
    --arr;
    f << arr << endl;

    return 0;
}
