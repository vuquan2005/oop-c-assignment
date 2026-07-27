"""
Compiler module for C++ OOP Assignments
"""

import sys
import os
import subprocess
from pathlib import Path

# Terminal colors
GREEN = "\033[92m"
RED = "\033[91m"
YELLOW = "\033[93m"
CYAN = "\033[96m"
RESET = "\033[0m"
BOLD = "\033[1m"

PROJECT_ROOT = Path(__file__).resolve().parent.parent.parent
SRC_DIR = PROJECT_ROOT / "src"
BUILD_DIR = PROJECT_ROOT / "build"

CXX = os.environ.get("CXX", "g++")
CXXFLAGS = ["-Wall", "-Wextra", "-pedantic", "-g", "-O0", "-std=c++17"]


def get_target_binary_path(cpp_path: Path) -> Path:
    """Get output executable binary path for a given .cpp file."""
    rel_path = cpp_path.resolve().relative_to(PROJECT_ROOT)
    bin_dir = BUILD_DIR / rel_path.parent
    bin_name = rel_path.stem
    if sys.platform == "win32":
        bin_name += ".exe"
    return bin_dir / bin_name


def compile_file(cpp_path: Path, silent: bool = False) -> tuple[bool, Path, str]:
    """Compile a single C++ file into build directory."""
    cpp_path = cpp_path.resolve()
    if not cpp_path.exists():
        return False, Path(""), f"File not found: {cpp_path}"

    target_bin = get_target_binary_path(cpp_path)
    target_bin.parent.mkdir(parents=True, exist_ok=True)

    rel_src = cpp_path.relative_to(PROJECT_ROOT)
    rel_bin = target_bin.relative_to(PROJECT_ROOT)

    if not silent:
        print(f"{CYAN}Đang biên dịch {rel_src} -> {rel_bin} ...{RESET}")

    cmd = [CXX] + CXXFLAGS + [str(cpp_path), "-o", str(target_bin)]
    result = subprocess.run(cmd, capture_output=True, text=True)

    if result.returncode != 0:
        if not silent:
            print(f"{RED}Lỗi biên dịch!{RESET}\n{result.stderr}")
        return False, target_bin, result.stderr

    if not silent:
        print(f"{GREEN}Biên dịch thành công! {rel_bin}{RESET}")

    return True, target_bin, ""


def compile_all() -> tuple[bool, int, int]:
    """Compile all C++ files under src/ to verify zero build errors."""
    cpp_files = sorted(SRC_DIR.rglob("*.cpp"))
    print(
        f"{BOLD}=== Kiểm tra biên dịch tất cả bài tập ({len(cpp_files)} files) ==={RESET}\n"
    )

    passed = 0
    failed = 0

    for cpp_file in cpp_files:
        rel_path = cpp_file.relative_to(PROJECT_ROOT)
        ok, bin_path, err = compile_file(cpp_file, silent=True)
        if ok:
            print(f"  [{GREEN}BUILD OK{RESET}] {rel_path}")
            passed += 1
        else:
            print(f"  [{RED}BUILD FAIL{RESET}] {rel_path}\n{err}")
            failed += 1

    print(f"\n{BOLD}=== KẾT QUẢ ==={RESET}")
    print(f"Tổng số file : {len(cpp_files)}")
    print(f"Thành công   : {GREEN}{passed}{RESET}")
    print(f"Thất bại     : {RED if failed > 0 else GREEN}{failed}{RESET}\n")

    return failed == 0, passed, failed
