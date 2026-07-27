/**
 * @file lab1_6.cpp
 * @brief Mảng số thực
 * @note
 * Sinh viên tự thiết kế lớp, các thuộc tính, các phương thức cần thiết để cho phép trong chương trình chính, nhập vào một mảng gồm n số thực, tìm và in ra phần tử lớn nhất và phần tử nhỏ nhất của mảng. In mảng ra màn hình.
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
