#!/usr/bin/env python3
"""
Master CLI dispatcher for C++ OOP Assignment Workspace
"""

import sys
import shutil
import argparse
from pathlib import Path

# Add scripts directory to sys.path
SCRIPT_DIR = Path(__file__).resolve().parent
if str(SCRIPT_DIR) not in sys.path:
    sys.path.insert(0, str(SCRIPT_DIR))

from modules.compiler import compile_file, compile_all, PROJECT_ROOT, BUILD_DIR
from modules.tester import run_tests
from modules.runner import run_file
from modules.generator import create_new_exercise
from modules.todo_sync import sync_todo
from modules.setup_env import setup_environment

# Terminal colors
GREEN = "\033[92m"
RED = "\033[91m"
YELLOW = "\033[93m"
CYAN = "\033[96m"
RESET = "\033[0m"
BOLD = "\033[1m"


def print_help():
    print(f"{BOLD}{GREEN}=== C++ OOP Homework Workspace CLI ==={RESET}")
    print("Các lệnh hỗ trợ qua Makefile hoặc CLI:")
    print(
        "  make setup                          - Khởi tạo môi trường lập trình & thiết lập Git hooks"
    )
    print(
        "  make new                            - Khởi tạo thư mục và file bài tập C++ mới"
    )
    print(
        "  make run FILE=path/to/file.cpp      - Biên dịch và chạy tương tác file C++"
    )
    print(
        "  make build FILE=path/to/file.cpp    - Chỉ biên dịch file C++ vào thư mục build"
    )
    print(
        "  make build-all                      - Kiểm tra biên dịch tất cả file C++ trong src/"
    )
    print("  make test [FILE=...] [DIR=...]      - Chạy Integration Test Stdin/Stdout")
    print(
        "  make sync                           - Đồng bộ trạng thái bài tập sang TODO.md và README.md"
    )
    print("  make clean                          - Xóa thư mục build và các file tạm\n")
    print("Ví dụ:")
    print("  make run FILE=src/buoi1/buoi1_1.cpp")
    print("  make test FILE=src/buoi1/buoi1_1.cpp")
    print("  make build-all\n")


def clean_build():
    """Clean build directory and temporary files."""
    if BUILD_DIR.exists():
        shutil.rmtree(BUILD_DIR)
        print(
            f"  - [{GREEN}CLEAN{RESET}] Đã xóa thư mục {BUILD_DIR.relative_to(PROJECT_ROOT)}"
        )

    # Clean temporary files in project root
    for pattern in ["*.dat", "*.TXT", "*.txt", "*.tmp"]:
        for temp_file in PROJECT_ROOT.glob(pattern):
            if temp_file.is_file():
                temp_file.unlink()

    print(f"{GREEN}Đã dọn dẹp thư mục build và các file tạm.{RESET}")


def optional_int(value):
    if value is None or str(value).strip() == "":
        return None
    try:
        return int(value)
    except ValueError:
        raise argparse.ArgumentTypeError(f"Invalid integer value: '{value}'")


def main():
    parser = argparse.ArgumentParser(
        description="OOP C++ Assignment CLI Dispatcher", add_help=False
    )
    parser.add_argument("command", nargs="?", default="help", help="Action to perform")
    parser.add_argument("--file", "-f", type=str, help="Target C++ file")
    parser.add_argument("--dir", "-d", type=str, help="Target directory inside src/")
    parser.add_argument("--folder", type=str, help="Folder name for new exercise")
    parser.add_argument("--num", type=optional_int, help="Quantity for new exercise")
    parser.add_argument("--author", type=str, help="Author name")
    parser.add_argument(
        "--timeout", type=float, default=2.0, help="Test timeout in seconds"
    )

    args, unknown = parser.parse_known_args()
    cmd = args.command.lower()

    if cmd == "help":
        print_help()
    elif cmd == "setup":
        ok = setup_environment()
        sys.exit(0 if ok else 1)
    elif cmd == "new":
        folder = args.folder.strip() if args.folder and args.folder.strip() else None
        author = args.author.strip() if args.author and args.author.strip() else None
        ok = create_new_exercise(folder, args.num, author)
        sys.exit(0 if ok else 1)
    elif cmd == "build":
        if not args.file:
            print(
                f"{RED}Lỗi: Bạn cần chỉ định đường dẫn file bằng FILE=... (Ví dụ: make build FILE=src/buoi1/buoi1_1.cpp){RESET}"
            )
            sys.exit(1)
        ok, bin_path, err = compile_file(Path(args.file))
        sys.exit(0 if ok else 1)
    elif cmd in ["build-all", "test-compile"]:
        ok, p, f = compile_all()
        sys.exit(0 if ok else 1)
    elif cmd == "run":
        if not args.file:
            print(
                f"{RED}Lỗi: Bạn cần chỉ định đường dẫn file bằng FILE=... (Ví dụ: make run FILE=src/buoi1/buoi1_1.cpp){RESET}"
            )
            sys.exit(1)
        ok = run_file(args.file)
        sys.exit(0 if ok else 1)
    elif cmd == "test":
        ok = run_tests(args.file, args.dir, args.timeout)
        sys.exit(0 if ok else 1)
    elif cmd == "sync":
        ok = sync_todo()
        sys.exit(0 if ok else 1)
    elif cmd == "clean":
        clean_build()
        sys.exit(0)
    else:
        print(f"{RED}Lệnh không hợp lệ: {cmd}{RESET}\n")
        print_help()
        sys.exit(1)


if __name__ == "__main__":
    main()
