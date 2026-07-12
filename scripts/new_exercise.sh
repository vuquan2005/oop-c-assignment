#!/bin/bash

# Helper script to create a new folder and stub C++ exercises in src/
# Usage: ./scripts/new_exercise.sh [folder_name] [quantity]
# Examples:
#   ./scripts/new_exercise.sh buoi6 5
#   ./scripts/new_exercise.sh

set -e

RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# 1. Find the path to the src/ directory
CURR_DIR=$(pwd)
BASE_DIR=""

while [ "$CURR_DIR" != "/" ]; do
    if [ -d "$CURR_DIR/src" ]; then
        BASE_DIR="$CURR_DIR/src"
        break
    elif [ "$(basename "$CURR_DIR")" = "src" ]; then
        BASE_DIR="$CURR_DIR"
        break
    fi
    CURR_DIR=$(dirname "$CURR_DIR")
done

if [ -z "$BASE_DIR" ]; then
    echo -e "${RED}Lỗi: Không tìm thấy thư mục 'src' trong các thư mục cha.${NC}"
    echo -e "Hãy đảm bảo bạn đang chạy script này từ trong dự án bài tập OOP C++."
    exit 1
fi

# 2. Get input arguments
FOLDER_NAME="$1"
QUANTITY="$2"

# Interactive mode if arguments are missing
if [ -z "$FOLDER_NAME" ]; then
    echo -e "${BLUE}=== TẠO BÀI TẬP C++ MỚI ===${NC}"
    read -p "Nhập tên thư mục bài tập mới (Ví dụ: buoi6, lab6): " FOLDER_NAME
    FOLDER_NAME=$(echo "$FOLDER_NAME" | tr -d '[:space:]')
fi

if [ -z "$FOLDER_NAME" ]; then
    echo -e "${RED}Lỗi: Tên thư mục không được để trống!${NC}"
    exit 1
fi

if [ -z "$QUANTITY" ]; then
    read -p "Nhập số lượng bài tập cần tạo (Ví dụ: 3): " QUANTITY
fi

# Validate quantity
if ! [[ "$QUANTITY" =~ ^[0-9]+$ ]] || [ "$QUANTITY" -le 0 ]; then
    echo -e "${RED}Lỗi: Số lượng bài tập phải là số nguyên dương lớn hơn 0!${NC}"
    exit 1
fi

# Get Author Name (from environment, git config, or default)
if [ -z "$AUTHOR" ]; then
    AUTHOR=$(git config user.name 2>/dev/null || echo "<Name>")
fi

# 3. Create folder and files
TARGET_DIR="$BASE_DIR/$FOLDER_NAME"
mkdir -p "$TARGET_DIR"

echo -e "\nThư mục đích: ${YELLOW}$TARGET_DIR${NC}"
echo -e "Đang khởi tạo $QUANTITY bài tập..."

CREATED_COUNT=0
SKIPPED_COUNT=0

# Create README.md
README_PATH="$TARGET_DIR/README.md"
if [ ! -f "$README_PATH" ]; then
    DISPLAY_NAME="$FOLDER_NAME"
    if [[ "$FOLDER_NAME" =~ ^buoi([0-9]+)$ ]]; then
        DISPLAY_NAME="buổi ${BASH_REMATCH[1]}"
    elif [[ "$FOLDER_NAME" =~ ^Buoi([0-9]+)$ ]]; then
        DISPLAY_NAME="buổi ${BASH_REMATCH[1]}"
    elif [[ "$FOLDER_NAME" =~ ^lab([0-9]+)$ ]]; then
        DISPLAY_NAME="thực hành ${BASH_REMATCH[1]}"
    elif [[ "$FOLDER_NAME" =~ ^Lab([0-9]+)$ ]]; then
        DISPLAY_NAME="thực hành ${BASH_REMATCH[1]}"
    else
        DISPLAY_NAME="$(echo "${FOLDER_NAME:0:1}" | tr '[:lower:]' '[:upper:]')${FOLDER_NAME:1}"
    fi

    cat <<EOF > "$README_PATH"
# 📅 Bài tập ${DISPLAY_NAME}

<!-- Auto generated -->

<!-- Auto generated -->
EOF
    README_RELATIVE=$(echo "$README_PATH" | sed "s|$(dirname "$BASE_DIR")/||")
    echo -e "  - ${GREEN}[ĐÃ TẠO]${NC} $README_RELATIVE"
fi

for ((i=1; i<=QUANTITY; i++)); do
    FILE_NAME="${FOLDER_NAME}_${i}.cpp"
    FILE_PATH="$TARGET_DIR/$FILE_NAME"
    
    # Check if the file already exists to prevent overwriting
    if [ -f "$FILE_PATH" ]; then
        echo -e "  - ${YELLOW}[ĐÃ TỒN TẠI]${NC} $FILE_NAME (Bỏ qua)"
        SKIPPED_COUNT=$((SKIPPED_COUNT + 1))
    else
        # Create new file with standard C++ template
        cat <<EOF > "$FILE_PATH"
/**
 * @file ${FILE_NAME}
 * @brief [Mô tả ngắn gọn]
 * @note [Ghi chú]
 *
 * @author ${AUTHOR}
 * @date $(date +%d-%m-%Y)
 *
 * @status done
 */

#include <iostream>

using namespace std;

int main() {
    
    return 0;
}
EOF
        # Get relative path for better visualization
        RELATIVE_PATH=$(echo "$FILE_PATH" | sed "s|$(dirname "$BASE_DIR")/||")
        echo -e "  - ${GREEN}[ĐÃ TẠO]${NC} $RELATIVE_PATH"
        CREATED_COUNT=$((CREATED_COUNT + 1))
    fi
done

# 4. Show results
echo -e "\n${GREEN}=== HOÀN THÀNH ===${NC}"
echo -e "Thành công: Đã tạo ${GREEN}$CREATED_COUNT${NC} file mới, bỏ qua ${YELLOW}$SKIPPED_COUNT${NC} file đã có."
