/**
 * @file lab1_5.cpp
 * @brief Mảng số nguyên
 * @note Nhập số lượng phần tử và sắp xếp tăng dần
 *
 * @author VuQuan
 * @date 17-07-2026
 *
 * @status done
 */

#include <iostream>

using namespace std;

class MANGSONGUYEN {
  private:
    int n;
    int *arr;

  public:
    void nhap() {
        cout << "Nhap so luong phan tu: ";
        cin >> n;
        arr = new int[n];
        for (int i = 0; i < n; i++) {
            cout << "Nhap phan tu thu " << i + 1 << ": ";
            cin >> arr[i];
        }
    }

    void xuat() const {
        for (int i = 0; i < n; i++) {
            cout << arr[i] << " ";
        }
        cout << endl;
    }

    void sort() {
        for (int i = 0; i < n - 1; i++) {
            for (int j = i + 1; j < n; j++) {
                if (arr[i] > arr[j]) {
                    int temp = arr[i];
                    arr[i] = arr[j];
                    arr[j] = temp;
                }
            }
        }
    }

    ~MANGSONGUYEN() {
        delete[] arr;
    }
};

int main() {
    MANGSONGUYEN m;
    m.nhap();

    cout << "=== Mang so nguyen ===" << endl;
    m.xuat();

    m.sort();

    cout << "=== Mang so nguyen sau khi sap xep tang dan ===" << endl;
    m.xuat();

    return 0;
}
