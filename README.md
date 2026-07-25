# 📚 BÀI TẬP LẬP TRÌNH HƯỚNG ĐỐI TƯỢNG (OOP C++)

Repository lưu trữ toàn bộ mã nguồn bài tập, bài thực hành của môn học **Lập trình hướng đối tượng (OOP C++)**.

Tiến độ [`TODO.md`](./TODO.md)

---

## 🛠️ Cài đặt môi trường

Để biên dịch và chạy code C++, máy tính của bạn cần có trình biên dịch `g++` và công cụ `make`.

### 1. Sử dụng Makefile hoặc Script cài đặt tự động (Linux/macOS)

Nên sử dụng lệnh `make` để vừa cài đặt môi trường vừa cấu hình Git hooks tự động:

```bash
make setup
```

Hoặc chạy trực tiếp script:

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
│   └── BÀI TẬP BUỔI 2.pdf
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

Repository sử dụng `Makefile` để đơn giản hóa quá trình biên dịch và chạy các file mã nguồn C++.

### 1. Biên dịch và chạy chương trình

Để chạy một bài tập (ví dụ: `src/buoi1/buoi1_1.cpp`), sử dụng lệnh:

```bash
make run FILE=src/buoi1/buoi1_1.cpp
```

Hoặc sử dụng script tìm kiếm nhanh:

```bash
./scripts/run.sh buoi1_1
```

Script `run.sh` sẽ tự động tìm kiếm file có tên khớp trong thư mục `src/` và biên dịch bằng `make`.

### 2. Chỉ biên dịch (Không chạy)

Nếu bạn chỉ muốn kiểm tra lỗi cú pháp và biên dịch file:

```bash
make build FILE=src/buoi1/buoi1_1.cpp
```

File thực thi sau khi biên dịch sẽ nằm trong thư mục `build/`.

### 3. Kiểm thử tự động (Integration Testing)

Repository hỗ trợ kiểm thử tự động Stdin/Stdout cho tất cả bài tập:

- **Chạy toàn bộ bài test:**
  ```bash
  make test
  ```
- **Test một file cụ thể:**
  ```bash
  make test FILE=src/buoi1/buoi1_1.cpp
  ```
- **Chỉ kiểm tra biên dịch toàn bộ mã nguồn (Compile check):**
  ```bash
  make test-compile
  ```

Các file test được lưu tại thư mục `tests/<tên_thư_mục>/<tên_bài>/` dưới dạng cặp file `.in` (đầu vào) và `.out` (kết quả mong đợi).

### 4. Dọn dẹp thư mục build

Để xóa toàn bộ các file thực thi đã biên dịch và các file tạm khác:

```bash
make clean
```

---

## 📂 Quản lý bài tập và Tiến độ làm bài

### 1. Tạo thư mục bài tập mới

Bạn có thể tự động tạo thư mục và các file stub bài tập mới bằng lệnh:

```bash
make new
```

_(Lệnh này gọi trực tiếp script `./scripts/new_exercise.sh` không có tham số và chạy ở chế độ tương tác)_

Hoặc nếu muốn truyền tham số nhanh từ command line:

```bash
make new FOLDER=buoi6 NUM=5 AUTHOR="Tên_Của_Bạn"
```

### 2. Đồng bộ tiến độ làm bài

Khi bạn cập nhật tag `@status done` hoặc `@status done` trong phần comment ở đầu mỗi file bài tập, bạn có thể đồng bộ trạng thái này vào file `TODO.md` ở gốc repo và các file `README.md` trong từng thư mục con bằng lệnh:

```bash
make sync
```

_(Lệnh này gọi trực tiếp `./scripts/sync_todo.py` không có tham số để quét và cập nhật toàn bộ trạng thái bài tập)_

---

## ⚓ Git Hooks & Tự động hóa

Repository này được tích hợp sẵn Git hooks để tự động hóa các tác vụ trước khi commit:

- Hook **pre-commit** (`.githooks/pre-commit`) được cấu hình để tự động chạy `./scripts/sync_todo.py` mỗi khi bạn thực hiện commit.
- Nếu việc đồng bộ thành công, trạng thái bài tập trong `TODO.md` và `src/*/README.md` sẽ được cập nhật tự động và thêm vào commit hiện tại.
- Để kích hoạt Git hooks này, hãy chạy lệnh thiết lập môi trường:
  ```bash
  make setup
  ```
