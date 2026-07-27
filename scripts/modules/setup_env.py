"""
Setup Environment module for C++ OOP Assignments workspace
"""

import sys
import os
import shutil
import subprocess
from pathlib import Path
from .compiler import PROJECT_ROOT

# Terminal colors
GREEN = "\033[92m"
RED = "\033[91m"
YELLOW = "\033[93m"
RESET = "\033[0m"
BOLD = "\033[1m"


def check_command(cmd: str) -> bool:
    return shutil.which(cmd) is not None


def setup_git_hooks():
    """Configure git hooks path to .githooks and make hook executable."""
    githooks_dir = PROJECT_ROOT / ".githooks"
    pre_commit_hook = githooks_dir / "pre-commit"

    if pre_commit_hook.exists():
        try:
            os.chmod(pre_commit_hook, 0o755)
            subprocess.run(
                ["git", "config", "core.hooksPath", ".githooks"],
                cwd=PROJECT_ROOT,
                check=True,
            )
            print(
                f"  - [{GREEN}OK{RESET}] Đã kích hoạt Git pre-commit hook trong .githooks"
            )
        except Exception as e:
            print(f"  - [{YELLOW}WARN{RESET}] Không thể cấu hình git hooks: {e}")


def setup_environment() -> bool:
    """Setup workspace environment, check toolchains and git hooks."""
    print(f"{BOLD}=== C++ OOP Homework Workspace Setup ==={RESET}\n")

    # 1. Check Python
    print(f"  - [{GREEN}OK{RESET}] Python: {sys.version.split()[0]}")

    # 2. Check g++ compiler
    if check_command("g++"):
        try:
            res = subprocess.run(["g++", "--version"], capture_output=True, text=True)
            version_str = res.stdout.splitlines()[0] if res.stdout else "Available"
            print(f"  - [{GREEN}OK{RESET}] Trình biên dịch C++: {version_str}")
        except Exception:
            print(f"  - [{GREEN}OK{RESET}] Trình biên dịch C++: g++")
    else:
        print(f"  - [{RED}MISSING{RESET}] Cảnh báo: `g++` chưa được cài đặt!")
        print(
            f"    Vui lòng cài đặt build toolchain (Ubuntu: `sudo apt install build-essential`, Fedora: `sudo dnf install gcc-c++`)"
        )

    # 3. Check make
    if check_command("make"):
        print(f"  - [{GREEN}OK{RESET}] Công cụ make: Có sẵn")
    else:
        print(f"  - [{YELLOW}WARN{RESET}] Công cụ `make` chưa được cài đặt!")

    # 4. Setup Git Hooks
    setup_git_hooks()

    print(f"\n{GREEN}Cấu hình môi trường thành công! Kho bài tập đã sẵn sàng.{RESET}\n")
    return True
