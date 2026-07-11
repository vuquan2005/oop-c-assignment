#!/bin/bash

# Helper script to run C++ OOP assignment files
# Usage: ./scripts/run.sh <file_path_or_name>
# Examples:
#   ./scripts/run.sh src/buoi1/bai1.cpp
#   ./scripts/run.sh buoi1/bai1.cpp
#   ./scripts/run.sh bai1.cpp
#   ./scripts/run.sh bai1

set -e

RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

TARGET_FILE="$1"

if [ -z "$TARGET_FILE" ]; then
    echo -e "${RED}Lỗi: Vui lòng cung cấp tên file hoặc đường dẫn cần chạy.${NC}"
    echo -e "Ví dụ:"
    echo -e "  ./scripts/run.sh src/buoi1/bai1.cpp"
    echo -e "  ./scripts/run.sh buoi1/bai1.cpp"
    echo -e "  ./scripts/run.sh bai1"
    exit 1
fi

# 1. If it's a direct file path that exists
if [ -f "$TARGET_FILE" ]; then
    # If it doesn't end with .cpp, we might have an issue unless it's a C++ file
    if [[ "$TARGET_FILE" != *.cpp ]]; then
        echo -e "${RED}Lỗi: File '$TARGET_FILE' không phải là file C++ (.cpp).${NC}"
        exit 1
    fi
    make run FILE="$TARGET_FILE"
    exit 0
fi

# 2. If it's in the src directory (e.g. buoi1/bai1.cpp)
if [ -f "src/$TARGET_FILE" ]; then
    make run FILE="src/$TARGET_FILE"
    exit 0
fi

# 3. Add .cpp extension and check
if [ -f "src/$TARGET_FILE.cpp" ]; then
    make run FILE="src/$TARGET_FILE.cpp"
    exit 0
fi

if [ -f "$TARGET_FILE.cpp" ]; then
    make run FILE="$TARGET_FILE.cpp"
    exit 0
fi

# 4. Search for the file in the src/ directory
echo -e "Đang tìm kiếm file '${TARGET_FILE}' trong thư mục src/..."
FOUND_FILES=$(find src -type f -iname "*${TARGET_FILE}*" -name "*.cpp")

COUNT=$(echo "$FOUND_FILES" | grep -c '^' || true)

if [ "$COUNT" -eq 0 ]; then
    echo -e "${RED}Lỗi: Không tìm thấy file nào khớp với '${TARGET_FILE}' trong thư mục src/.${NC}"
    exit 1
elif [ "$COUNT" -eq 1 ]; then
    echo -e "${GREEN}Đã tìm thấy file:${NC} $FOUND_FILES"
    make run FILE="$FOUND_FILES"
else
    echo -e "${YELLOW}Tìm thấy nhiều file khớp, vui lòng chọn file cụ thể:${NC}"
    select f in $FOUND_FILES; do
        if [ -n "$f" ]; then
            make run FILE="$f"
            break
        else
            echo "Lựa chọn không hợp lệ."
        fi
    done
fi
