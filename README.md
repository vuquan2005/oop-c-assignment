# 📚 BÀI TẬP LẬP TRÌNH HƯỚNG ĐỐI TƯỢNG (OOP C++)

Repository lưu trữ toàn bộ mã nguồn bài tập lớn, bài thực hành và phiếu giao bài tập của môn học **Lập trình hướng đối tượng (OOP C++)**. Hệ thống được thiết lập sẵn cấu trúc thư mục, các công cụ biên dịch tự động (Makefile) và cấu hình chạy/debug cho VS Code để hỗ trợ quá trình làm bài và nộp bài nhanh chóng nhất.

Tiến độ bài tập [✅TODO.md](./TODO.md)

---

## 🛠️ Cài đặt môi trường

Để biên dịch và chạy code C++, máy tính của bạn cần có trình biên dịch `g++` và công cụ `make`.

### 1. Sử dụng script cài đặt tự động (Linux/macOS)
Bạn có thể chạy script được chuẩn bị sẵn để tự động phát hiện hệ điều hành và cài đặt các công cụ cần thiết:
```bash
./scripts/setup_env.sh
```

### 2. Cài đặt thủ công
* **Fedora**:
  ```bash
  sudo dnf install -y gcc-c++ make gdb
  ```
* **Ubuntu / Debian**:
  ```bash
  sudo apt update
  sudo apt install -y build-essential make gdb
  ```
* **macOS** (Cài đặt qua Homebrew hoặc Command Line Tools):
  ```bash
  xcode-select --install
  ```
* **Windows**:
  - Tải và cài đặt [MSYS2](https://www.msys2.org/) (Shell giống bash trên windows).
  - Cài đặt gói `mingw-w64-x86_64-toolchain` và `make`.
  - Thêm đường dẫn `C:\msys64\mingw64\bin` vào biến môi trường `PATH`.

---

## 📂 Cấu trúc thư mục (Folder Tree)

Dưới đây là sơ đồ thư mục của dự án, các file bài tập đã được tạo sẵn mẫu (template) đi kèm với mô tả đề bài chi tiết bằng tiếng Việt trong chú thích ở đầu mỗi file.

```text
oop-c-assignment/
├── docs/                     # Tài liệu môn học, đề bài PDF/TXT
│   ├── BÀI THỰC HÀNH LTHĐT HKH.pdf
│   ├── BÀI TẬP BUỔI 1.pdf
│   └── lab_outline.txt       # Nội dung text được trích xuất từ PDF thực hành
├── src/                      # Mã nguồn bài làm của sinh viên
│   ├── buoi1/                # Bài tập Buổi 1
│   ├── .../
│   └── folder_bai_tap/
├── scripts/                  # Chứa các mã/tool tự động hỗ trợ
│   ├── run.sh                # Script tìm và chạy nhanh bài tập
│   └── setup_env.sh          # Script cài đặt môi trường
├── build/                    # Thư mục chứa các file nhị phân sau khi dịch (được gitignore)
├── Makefile                  # Trình quản lý biên dịch tập trung
└── README.md                 # Tài liệu hướng dẫn sử dụng repo
```

---

## 🚀 Cách chạy và biên dịch chương trình

### Cách 1: Sử dụng script run nhanh (`scripts/run.sh`)
Đây là cách tiện lợi nhất vì bạn chỉ cần truyền tên file, script sẽ tự động tìm kiếm đường dẫn chính xác và biên dịch/chạy thử.

```bash
# Chạy trực tiếp qua đường dẫn
./scripts/run.sh src/buoi1/bai1.cpp

# Chạy nhanh chỉ bằng tên thư mục và tên file
./scripts/run.sh buoi1/bai1.cpp

# Chạy nhanh bằng tên file (tự động tìm kiếm)
./scripts/run.sh bai1.cpp

# Tìm kiếm mờ (Nếu tìm thấy nhiều file khớp, hệ thống sẽ cho bạn lựa chọn)
./scripts/run.sh bai1
```

### Cách 2: Sử dụng Makefile
Makefile trung tâm hỗ trợ biên dịch và chạy bằng cách chỉ định tham số `FILE`:

* **Biên dịch và chạy ngay lập tức**:
  ```bash
  make run FILE=src/buoi1/bai1.cpp
  ```
* **Chỉ biên dịch (không chạy)**:
  ```bash
  make build FILE=src/buoi1/bai1.cpp
  ```
* **Dọn dẹp thư mục build & file rác sinh ra trong quá trình chạy**:
  ```bash
  make clean
  ```

### Cách 3: Sử dụng VS Code (Được cấu hình sẵn)
Nếu bạn mở repo này bằng VS Code, các tác vụ sau đã được thiết lập sẵn trong thư mục `.vscode`:
1. **Biên dịch và chạy thử (Run)**: Chọn lệnh `Tasks: Run Test Task` và chọn chương trình tương ứng.
2. **Debug bài tập**: Mở file `.cpp` bạn muốn debug, nhấn **`F5`**. VS Code sẽ tự động biên dịch file đó sang thư mục `build/` dưới dạng debug và khởi chạy công cụ gdb để bạn đặt breakpoint gỡ lỗi trực tiếp trên giao diện trực quan.
