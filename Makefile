# Makefile - Lightweight Facade / Wrapper for Python CLI Automation
PYTHON = python3
CLI = scripts/cli.py

GREEN = \033[0;32m
YELLOW = \033[1;33m
NC = \033[0m # No Color

# Fallback for uppercase/lowercase arguments in make new / test
FOLDER_VAL = $(if $(FOLDER),$(FOLDER),$(folder))
NUM_VAL = $(if $(NUM),$(NUM),$(num))
AUTHOR_VAL = $(if $(AUTHOR),$(AUTHOR),$(author))
IN_VAL = $(if $(IN),$(IN),$(in))
OUT_VAL = $(if $(OUT),$(OUT),$(out))

.PHONY: help setup new run build build-all test add-test test-compile clean sync

help:
	@echo -e "$(GREEN)=== C++ OOP Homework Makefile ===$(NC)"
	@echo "Các lệnh hỗ trợ:"
	@echo "  make setup                          - Khởi tạo môi trường lập trình & thiết lập Git hooks"
	@echo "  make new                            - Khởi tạo thư mục và file bài tập C++ mới"
	@echo "  make run FILE=... [IN=\"...\"]         - Biên dịch và chạy file C++ (tương tác hoặc với IN)"
	@echo "  make build FILE=path/to/file.cpp    - Chỉ biên dịch file C++ vào thư mục build"
	@echo "  make build-all                      - Kiểm tra biên dịch tất cả file C++ trong src/"
	@echo "  make test FILE=... [IN=\"...\"]        - Chạy test case tự động hoặc test nhanh với IN"
	@echo "  make add-test FILE=... IN=\"...\"     - Lưu test case (.in) mới cho bài tập"
	@echo "  make sync                           - Đồng bộ trạng thái bài tập sang TODO.md và README.md"
	@echo "  make clean                          - Xóa thư mục build và các file tạm"
	@echo ""
	@echo "Ví dụ:"
	@echo "  make test FILE=buoi1_1 IN=\"10 5 4\""
	@echo "  make test FILE=buoi1_1"
	@echo "  make add-test FILE=buoi1_1 IN=\"12 6 5\""
	@echo "  make run FILE=src/buoi1/buoi1_1.cpp"

setup:
	@$(PYTHON) $(CLI) setup

new:
	@$(PYTHON) $(CLI) new $(if $(FOLDER_VAL),--folder "$(FOLDER_VAL)") $(if $(NUM_VAL),--num "$(NUM_VAL)") $(if $(AUTHOR_VAL),--author "$(AUTHOR_VAL)")

run:
	@$(PYTHON) $(CLI) run --file "$(FILE)" $(if $(IN_VAL),--in "$(IN_VAL)")

build:
	@$(PYTHON) $(CLI) build --file "$(FILE)"

build-all:
	@$(PYTHON) $(CLI) build-all

test:
	@$(PYTHON) $(CLI) test --file "$(FILE)" --dir "$(DIR)" $(if $(IN_VAL),--in "$(IN_VAL)")

add-test:
	@$(PYTHON) $(CLI) add-test --file "$(FILE)" --in "$(IN_VAL)" $(if $(OUT_VAL),--out "$(OUT_VAL)")

test-compile:
	@$(PYTHON) $(CLI) build-all

clean:
	@$(PYTHON) $(CLI) clean

sync:
	@$(PYTHON) $(CLI) sync

