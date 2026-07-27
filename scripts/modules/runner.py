"""
Runner module to compile and execute a C++ file interactively
"""

import sys
import subprocess
from pathlib import Path
from .compiler import compile_file, PROJECT_ROOT, SRC_DIR

# Terminal colors
GREEN = "\033[92m"
RED = "\033[91m"
YELLOW = "\033[93m"
RESET = "\033[0m"
BOLD = "\033[1m"


def find_matching_cpp_file(target: str) -> Path | None:
    """Find matching C++ file in src/ based on name or path string."""
    if not target:
        return None

    # Check direct file
    p = Path(target).resolve()
    if p.is_file() and p.suffix == ".cpp":
        return p

    # Check relative to src
    p_src = SRC_DIR / target
    if p_src.is_file() and p_src.suffix == ".cpp":
        return p_src

    p_src_cpp = SRC_DIR / f"{target}.cpp"
    if p_src_cpp.is_file():
        return p_src_cpp

    # Search in src/
    print(f"Đang tìm kiếm file '{target}' trong thư mục src/...")
    found = list(SRC_DIR.rglob(f"*{target}*.cpp"))

    if not found:
        print(
            f"{RED}Lỗi: Không tìm thấy file nào khớp với '{target}' trong thư mục src/.{RESET}"
        )
        return None
    elif len(found) == 1:
        print(f"{GREEN}Đã tìm thấy file:{RESET} {found[0].relative_to(PROJECT_ROOT)}")
        return found[0]
    else:
        print(f"{YELLOW}Tìm thấy nhiều file khớp, vui lòng chọn file cụ thể:{RESET}")
        for idx, f in enumerate(found, start=1):
            print(f"  {idx}) {f.relative_to(PROJECT_ROOT)}")
        try:
            choice = input("Nhập số lựa chọn (1..N): ").strip()
            if choice.isdigit():
                sel = int(choice) - 1
                if 0 <= sel < len(found):
                    return found[sel]
        except (EOFError, KeyboardInterrupt):
            pass
        print(f"{RED}Lựa chọn không hợp lệ.{RESET}")
        return None


def run_file(target: str) -> bool:
    """Compile and run a C++ file interactively."""
    cpp_path = find_matching_cpp_file(target)
    if not cpp_path:
        return False

    ok, target_bin, _ = compile_file(cpp_path)
    if not ok:
        return False

    print(f"\n=== {YELLOW}START{RESET} ===")
    try:
        res = subprocess.run([str(target_bin)])
        print(f"=== {YELLOW}END (Mã thoát: {res.returncode}){RESET} ===\n")
        return res.returncode == 0
    except KeyboardInterrupt:
        print(f"\n{YELLOW}Đã dừng chương trình.{RESET}")
        return False
