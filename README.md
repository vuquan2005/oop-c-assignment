# 📚 BÀI TẬP LẬP TRÌNH HƯỚNG ĐỐI TƯỢNG (OOP C++)

Repository lưu trữ toàn bộ mã nguồn bài tập lớn, bài thực hành và phiếu giao bài tập của môn học **Lập trình hướng đối tượng (OOP C++)**.

---

## 🛠️ Cài đặt môi trường

Để biên dịch và chạy code C++, máy tính của bạn cần có trình biên dịch `g++` và công cụ `make`.

### 1. Sử dụng script cài đặt tự động (Linux/macOS)

Chạy script để tự động cài đặt các công cụ cần thiết:

```bash
./scripts/setup_env.sh
```

### 2. Cài đặt thủ công

- **Fedora**:
  ```bash
  sudo dnf install -y gcc-c++ make gdb
  ```
- **Ubuntu / Debian**:
  ```bash
  sudo apt update
  sudo apt install -y build-essential make gdb
  ```
- **macOS** (Cài đặt qua Homebrew hoặc Command Line Tools):
  ```bash
  xcode-select --install
  ```
- **Windows**:
  - Tải và cài đặt [MSYS2](https://www.msys2.org/) (Shell giống bash trên windows).
  - Cài đặt gói `mingw-w64-x86_64-toolchain` và `make`.
  - Thêm đường dẫn `C:\msys64\mingw64\bin` vào biến môi trường `PATH`.

---

## 📂 Cấu trúc thư mục (Folder Tree)

```text
oop-c-assignment/
├── docs/                     # Tài liệu môn học, đề bài PDF/TXT
│   ├── BÀI THỰC HÀNH LTHĐT HKH.pdf
│   ├── BÀI TẬP BUỔI 1.pdf
│   └── BÀI TẬP BUỔI 1.pdf
├── src/                      # Mã nguồn bài làm
│   ├── buoi1/                # Bài tập Buổi 1 (7 bài)
│   ├── lab1/ ... / lab5/     # Bài thực hành số 1 đến 5
│   ├── online1/ ... / 3      # Bài thực hành Online 1 đến 3
│   └── phieu_giao_bt/        # Phiếu giao bài tập & Bài thu hoạch
├── scripts/                  # Bộ script hỗ trợ tự động hóa
│   ├── run.sh                # Script tìm và chạy nhanh bài tập
│   ├── setup_env.sh          # Script cài đặt môi trường C++
│   └── new_exercise.sh       # Script tạo nhanh thư mục/file bài tập mới
├── build/                    # Thư mục chứa file thực thi (được gitignore)
├── Makefile                  # Trình quản lý biên dịch tập trung
└── README.md                 # Hướng dẫn sử dụng
```

---

## 🚀 Cách chạy và biên dịch chương trình

### 1. Sử dụng script run nhanh (`scripts/run.sh`)

Script sẽ tự động tìm kiếm đường dẫn chính xác và biên dịch/chạy thử:

```bash
# Chạy bằng đường dẫn tương đối hoặc chỉ cần tên file
./scripts/run.sh src/buoi1/bai1.cpp
./scripts/run.sh buoi1/bai1.cpp
./scripts/run.sh bai1.cpp
./scripts/run.sh bai1     # Tìm kiếm mờ (hiển thị danh sách nếu trùng)
```

### 2. Sử dụng Makefile

- **Biên dịch và chạy ngay lập tức**: `make run FILE=src/buoi1/bai1.cpp`
- **Chỉ biên dịch (không chạy)**: `make build FILE=src/buoi1/bai1.cpp`
- **Dọn dẹp thư mục build & file rác**: `make clean`

### 3. Sử dụng VS Code

- **Chạy thử (Run)**: Chọn lệnh `Tasks: Run Test Task` từ Command Palette.
- **Debug bài tập**: Mở file `.cpp` muốn debug, nhấn **`F5`** để biên dịch debug và chạy `gdb` trực quan.

---

## ➕ Tự động khởi tạo bài tập mới (`scripts/new_exercise.sh`)

Script này giúp bạn tạo nhanh một thư mục học tập mới cùng các file code `.cpp` mẫu được đánh chỉ số tự động.

### Cách sử dụng:

1. **Chạy tương tác**:
   ```bash
   ./scripts/new_exercise.sh
   ```
   Hệ thống sẽ hỏi bạn tên thư mục (ví dụ: `buoi6`) và số lượng bài tập (ví dụ: `5`).
2. **Chạy nhanh bằng tham số**:
   ```bash
   ./scripts/new_exercise.sh <tên_thư_mục> <số_lượng_bài>
   # Ví dụ: Tạo thư mục buoi6 chứa buoi6_1.cpp đến buoi6_5.cpp
   ./scripts/new_exercise.sh buoi6 5
   ```
