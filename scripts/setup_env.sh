#!/bin/bash

# Environment setup script for OOP C++ repository
# Detects OS and helps install compiler/tools (g++, make)

set -e

RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

echo -e "${GREEN}=== C++ OOP Homework Workspace Setup ===${NC}"

# Detect OS
if [ -f /etc/os-release ]; then
    . /etc/os-release
    OS=$ID
else
    OS=$(uname -s)
fi

echo -e "Hệ điều hành phát hiện: ${YELLOW}$OS${NC}"

case "$OS" in
    ubuntu|debian|raspbian)
        echo -e "Đang cài đặt các công cụ phát triển (build-essential, g++, make) cho Debian/Ubuntu..."
        sudo apt update
        sudo apt install -y build-essential make
        ;;
    fedora)
        echo -e "Đang cài đặt các công cụ phát triển (gcc-c++, make) cho Fedora..."
        sudo dnf install -y gcc-c++ make
        ;;
    centos|rhel|almalinux|rocky)
        echo -e "Đang cài đặt các công cụ phát triển cho RHEL-based OS..."
        sudo dnf groupinstall -y "Development Tools"
        sudo dnf install -y make
        ;;
    arch|manjaro)
        echo -e "Đang cài đặt các công cụ phát triển cho Arch Linux..."
        sudo pacman -Syu --needed base-devel
        ;;
    Darwin)
        echo -e "Hệ điều hành macOS. Đang kiểm tra Xcode Command Line Tools..."
        if ! xcode-select -p &>/dev/null; then
            echo -e "Xcode Command Line Tools chưa cài đặt. Đang kích hoạt cài đặt..."
            xcode-select --install
        else
            echo -e "${GREEN}Xcode Command Line Tools đã sẵn sàng!${NC}"
        fi
        ;;
    *)
        echo -e "${RED}Hệ điều hành không được hỗ trợ tự động cài đặt. Hãy tự cài đặt g++ và make thủ công.${NC}"
        echo -e "Với Windows: Cài đặt MSYS2 hoặc MinGW-w64 và thêm vào biến môi trường PATH."
        exit 1
        ;;
esac

# Verify installation
if command -v g++ &> /dev/null && command -v make &> /dev/null; then
    echo -e "${GREEN}Cài đặt thành công! g++ và make đã sẵn sàng.${NC}"
    g++ --version | head -n 1
    make --version | head -n 1
else
    echo -e "${RED}Có lỗi xảy ra trong quá trình kiểm tra g++/make. Hãy cài đặt thủ công.${NC}"
fi
