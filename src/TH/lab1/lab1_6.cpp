/**
 * @file lab1_6.cpp
 * @brief Mảng số thực
 * @note Nhập số lượng phần tử và tìm giá trị nhỏ nhất, lớn nhất
 *
 * @author VuQuan
 * @date 17-07-2026
 *
 * @status done
 */

#include <iostream>

using namespace std;

class MANGSOTHUC {
  private:
    int n;
    float *arr;

  public:
    void nhap() {
        cout << "Nhap so luong phan tu: ";
        cin >> n;
        arr = new float[n];
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

    float min() const {
        float minVal = arr[0];
        for (int i = 1; i < n; i++) {
            if (arr[i] < minVal) {
                minVal = arr[i];
            }
        }
        return minVal;
    }

    float max() const {
        float maxVal = arr[0];
        for (int i = 1; i < n; i++) {
            if (arr[i] > maxVal) {
                maxVal = arr[i];
            }
        }
        return maxVal;
    }

    ~MANGSOTHUC() {
        delete[] arr;
    }
};

int main() {
    MANGSOTHUC m;
    m.nhap();

    cout << "=== Mang so thuc ===" << endl;
    m.xuat();

    cout << "Gia tri nho nhat: " << m.min() << endl;
    cout << "Gia tri lon nhat: " << m.max() << endl;

    return 0;
}
