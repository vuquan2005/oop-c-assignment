# Variables
CXX = g++
CXXFLAGS = -Wall -Wextra -pedantic -g -O0 -std=c++17
BUILD_DIR = build

# Colors for nice output
GREEN = \033[0;32m
RED = \033[0;31m
YELLOW = \033[1;33m
NC = \033[0m # No Color

# By default, do nothing or show help
.PHONY: help
help:
	@echo -e "$(GREEN)=== C++ OOP Homework Makefile ===$(NC)"
	@echo "Các lệnh hỗ trợ:"
	@echo "  make run FILE=path/to/file.cpp      - Biên dịch và chạy file C++"
	@echo "  make build FILE=path/to/file.cpp    - Chỉ biên dịch file C++ vào thư mục build"
	@echo "  make clean                          - Xóa thư mục build và các file tạm"
	@echo ""
	@echo "Ví dụ:"
	@echo "  make run FILE=src/buoi1/bai1.cpp"

# Rule to compile and run a file
.PHONY: run
run:
	@if [ -z "$(FILE)" ]; then \
		echo -e "$(RED)Lỗi: Bạn cần chỉ định đường dẫn file bằng FILE=... (Ví dụ: make run FILE=src/buoi1/bai1.cpp)$(NC)"; \
		exit 1; \
	fi
	@if [ ! -f "$(FILE)" ]; then \
		echo -e "$(RED)Lỗi: File '$(FILE)' không tồn tại!$(NC)"; \
		exit 1; \
	fi
	@mkdir -p $(BUILD_DIR)
	@dir_name=$$(dirname "$(FILE)"); \
	base_name=$$(basename "$(FILE)" .cpp); \
	target_dir="$(BUILD_DIR)/$$dir_name"; \
	mkdir -p "$$target_dir"; \
	target_bin="$$target_dir/$$base_name"; \
	echo -e "$(GREEN)Đang biên dịch $(FILE) -> $$target_bin ...$(NC)"; \
	if $(CXX) $(CXXFLAGS) "$(FILE)" -o "$$target_bin"; then \
		echo -e "$(GREEN)Biên dịch thành công!$(NC)"; \
		echo -e "\n=== $(YELLOW)BẮT ĐẦU CHẠY CHƯƠNG TRÌNH$(NC) ==="; \
		./"$$target_bin"; \
		exit_code=$$?; \
		echo -e "=== $(YELLOW)CHƯƠNG TRÌNH KẾT THÚC (Mã thoát: $$exit_code)$(NC) ===\n"; \
	else \
		echo -e "$(RED)Lỗi biên dịch!$(NC)"; \
		exit 1; \
	fi

# Rule to only compile a file
.PHONY: build
build:
	@if [ -z "$(FILE)" ]; then \
		echo -e "$(RED)Lỗi: Bạn cần chỉ định đường dẫn file bằng FILE=...$(NC)"; \
		exit 1; \
	fi
	@if [ ! -f "$(FILE)" ]; then \
		echo -e "$(RED)Lỗi: File '$(FILE)' không tồn tại!$(NC)"; \
		exit 1; \
	fi
	@mkdir -p $(BUILD_DIR)
	@dir_name=$$(dirname "$(FILE)"); \
	base_name=$$(basename "$(FILE)" .cpp); \
	target_dir="$(BUILD_DIR)/$$dir_name"; \
	mkdir -p "$$target_dir"; \
	target_bin="$$target_dir/$$base_name"; \
	echo -e "$(GREEN)Đang biên dịch $(FILE) -> $$target_bin ...$(NC)"; \
	if $(CXX) $(CXXFLAGS) "$(FILE)" -o "$$target_bin"; then \
		echo -e "$(GREEN)Biên dịch thành công!$$target_bin$(NC)"; \
	else \
		echo -e "$(RED)Lỗi biên dịch!$(NC)"; \
		exit 1; \
	fi

# Clean up
.PHONY: clean
clean:
	@rm -rf $(BUILD_DIR)
	@rm -f *.dat *.TXT *.txt *.tmp
	@echo -e "$(GREEN)Đã dọn dẹp thư mục build và các file tạm.$(NC)"
