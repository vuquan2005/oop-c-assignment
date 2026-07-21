/**
 * @file buoi3_4.cpp
 * @brief Thông tin học sinh
 * @note [Ghi chú]
 *
 * @author VuQuan
 * @date 21-07-2026
 *
 * @status done
 */

#include <cstring>
#include <iostream>

using namespace std;

class HocSinh {
  private:
    char hoTen[30];
    int tuoi;
    char queQuan[50];
    float diemToan;
    float diemLy;
    float diemHoa;

  public:
    HocSinh() : tuoi(0), diemToan(0), diemLy(0), diemHoa(0) {
        hoTen[0] = '\0';
        queQuan[0] = '\0';
    }

    HocSinh(const char *ten, int t, const char *que, float toan, float ly,
            float hoa)
        : tuoi(t), diemToan(toan), diemLy(ly), diemHoa(hoa) {
        strncpy(hoTen, ten, sizeof(hoTen) - 1);
        hoTen[sizeof(hoTen) - 1] = '\0';
        strncpy(queQuan, que, sizeof(queQuan) - 1);
        queQuan[sizeof(queQuan) - 1] = '\0';
    }

    void xuat() const {
        cout << "Ho ten: " << hoTen << endl;
        cout << "Tuoi: " << tuoi << endl;
        cout << "Que quan: " << queQuan << endl;
        cout << "Diem Toan: " << diemToan << endl;
        cout << "Diem Ly: " << diemLy << endl;
        cout << "Diem Hoa: " << diemHoa << endl;
    }
};

int main() {

    HocSinh hs1("Nguyen Van A", 16, "Ha Noi", 8.5, 7.0, 9.0);
    cout << "Thong tin hoc sinh 1:" << endl;
    hs1.xuat();

    HocSinh hs2;
    cout << "Thong tin hoc sinh 2:" << endl;
    hs2.xuat();

    return 0;
}
