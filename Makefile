# Makefile - Lightweight Facade / Wrapper for Python CLI Automation
PYTHON = python3
CLI = scripts/cli.py

GREEN = \033[0;32m
YELLOW = \033[1;33m
NC = \033[0m # No Color

# Fallback for uppercase/lowercase arguments in make new
FOLDER_VAL = $(if $(FOLDER),$(FOLDER),$(folder))
NUM_VAL = $(if $(NUM),$(NUM),$(num))
AUTHOR_VAL = $(if $(AUTHOR),$(AUTHOR),$(author))

.PHONY: help setup new run build build-all test test-compile clean sync

help:
	@echo -e "$(GREEN)=== C++ OOP Homework Makefile ===$(NC)"
	@echo "Các lệnh hỗ trợ:"
	@echo "  make setup                          - Khởi tạo môi trường lập trình & thiết lập Git hooks"
	@echo "  make new                            - Khởi tạo thư mục và file bài tập C++ mới"
	@echo "  make run FILE=path/to/file.cpp      - Biên dịch và chạy tương tác file C++"
	@echo "  make build FILE=path/to/file.cpp    - Chỉ biên dịch file C++ vào thư mục build"
	@echo "  make build-all                      - Kiểm tra biên dịch tất cả file C++ trong src/"
	@echo "  make test [FILE=...] [DIR=...]      - Chạy Integration Test Stdin/Stdout"
	@echo "  make sync                           - Đồng bộ trạng thái bài tập sang TODO.md và README.md"
	@echo "  make clean                          - Xóa thư mục build và các file tạm"
	@echo ""
	@echo "Ví dụ:"
	@echo "  make run FILE=src/buoi1/buoi1_1.cpp"
	@echo "  make test FILE=src/buoi1/buoi1_1.cpp"
	@echo "  make build-all"

setup:
	@$(PYTHON) $(CLI) setup

new:
	@$(PYTHON) $(CLI) new $(if $(FOLDER_VAL),--folder "$(FOLDER_VAL)") $(if $(NUM_VAL),--num "$(NUM_VAL)") $(if $(AUTHOR_VAL),--author "$(AUTHOR_VAL)")

run:
	@$(PYTHON) $(CLI) run --file "$(FILE)"

build:
	@$(PYTHON) $(CLI) build --file "$(FILE)"

build-all:
	@$(PYTHON) $(CLI) build-all

test:
	@$(PYTHON) $(CLI) test --file "$(FILE)" --dir "$(DIR)"

test-compile:
	@$(PYTHON) $(CLI) build-all

clean:
	@$(PYTHON) $(CLI) clean

sync:
	@$(PYTHON) $(CLI) sync
