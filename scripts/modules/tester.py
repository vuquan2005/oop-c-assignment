"""
Integration Testing & Quick Test Module for C++ OOP Assignments
"""

import sys
import time
import subprocess
from pathlib import Path
from .compiler import compile_file, PROJECT_ROOT, SRC_DIR
from .runner import find_matching_cpp_file

# Terminal colors
GREEN = "\033[92m"
RED = "\033[91m"
YELLOW = "\033[93m"
CYAN = "\033[96m"
BLUE = "\033[94m"
RESET = "\033[0m"
BOLD = "\033[1m"


def run_with_input(
    bin_path: Path, input_data: str, timeout: float = 2.0
) -> tuple[bool, str, str, float, int]:
    """Run binary with given stdin input string. Return (success, stdout, stderr, elapsed_time, exit_code)."""
    start_time = time.time()
    try:
        res = subprocess.run(
            [str(bin_path)],
            input=input_data,
            capture_output=True,
            text=True,
            timeout=timeout,
        )
        elapsed = time.time() - start_time
        return True, res.stdout, res.stderr, elapsed, res.returncode
    except subprocess.TimeoutExpired:
        elapsed = time.time() - start_time
        return False, "", "TIMEOUT: Chương trình chạy quá thời gian quy định.", elapsed, -1
    except Exception as e:
        elapsed = time.time() - start_time
        return False, "", str(e), elapsed, -1


def normalize_output(text: str) -> str:
    """Normalize text for comparison (strip trailing whitespace on each line)."""
    lines = [line.rstrip() for line in text.strip().splitlines()]
    return "\n".join(lines)


def format_test_box(
    title: str, input_str: str, output_str: str, err_str: str, elapsed: float, exit_code: int, expected_out: str | None = None
):
    """Print beautifully formatted test output box."""
    separator = "─" * 70
    print(f"\n{BOLD}{CYAN}┌{'─' * 68}┐{RESET}")
    print(f"{BOLD}{CYAN}│ 🧪 {title:<63} │{RESET}")
    print(f"{BOLD}{CYAN}├{'─' * 68}┤{RESET}")
    
    # Input section
    print(f"{BOLD}{BLUE} 📥 INPUT (Đầu vào):{RESET}")
    indented_in = "\n".join(f"    {line}" for line in input_str.strip().splitlines()) if input_str.strip() else "    (Không có input)"
    print(f"{indented_in}")
    
    # Output section
    print(f"\n{BOLD}{GREEN} 📤 OUTPUT (Kết quả thực thi):{RESET}")
    if output_str:
        indented_out = "\n".join(f"    {line}" for line in output_str.rstrip().splitlines())
        print(f"{indented_out}")
    else:
        print("    (Chương trình không in ra gì)")
        
    if err_str:
        print(f"\n{BOLD}{RED} ⚠️ STDERR (Lỗi runtime):{RESET}")
        indented_err = "\n".join(f"    {line}" for line in err_str.strip().splitlines())
        print(f"{indented_err}")

    # Check match if expected output exists
    if expected_out is not None:
        norm_actual = normalize_output(output_str)
        norm_exp = normalize_output(expected_out)
        if norm_actual == norm_exp:
            result_str = f"{GREEN}✅ PASS (Khớp 100% với file .out mong đợi){RESET}"
        else:
            result_str = f"{RED}❌ FAIL (Khác với file .out mong đợi){RESET}"
            print(f"\n{BOLD}{YELLOW} 🎯 EXPECTED OUTPUT (Mong đợi):{RESET}")
            indented_exp = "\n".join(f"    {line}" for line in expected_out.rstrip().splitlines())
            print(f"{indented_exp}")
    else:
        result_str = f"{YELLOW}ℹ️ (Đã hiển thị Output để bạn đối soát){RESET}"

    status_code = f"{GREEN}0{RESET}" if exit_code == 0 else f"{RED}{exit_code}{RESET}"
    print(f"\n{BOLD} ⏱️ Thời gian: {elapsed:.3f}s | Exit Code: {status_code} | {result_str}")
    print(f"{BOLD}{CYAN}└{'─' * 68}┘{RESET}\n")


def test_file_quick(cpp_path: Path, raw_input: str, timeout: float = 2.0) -> bool:
    """Run a C++ file with quick inline input string."""
    ok, target_bin, err = compile_file(cpp_path)
    if not ok:
        print(f"{RED}Không thể chạy test do lỗi biên dịch.{RESET}")
        return False

    # Format raw input: if spaces used instead of newlines, allow both
    input_str = raw_input.replace("\\n", "\n")
    if not input_str.endswith("\n"):
        input_str += "\n"

    rel_path = cpp_path.relative_to(PROJECT_ROOT)
    success, stdout, stderr, elapsed, exit_code = run_with_input(target_bin, input_str, timeout)
    
    format_test_box(
        title=f"QUICK TEST: {rel_path}",
        input_str=input_str,
        output_str=stdout,
        err_str=stderr,
        elapsed=elapsed,
        exit_code=exit_code,
    )
    return exit_code == 0


def get_test_dir_for_cpp(cpp_path: Path) -> Path:
    """Find tests directory for a given C++ file."""
    # E.g. src/buoi1/buoi1_1.cpp -> src/buoi1/tests/buoi1_1/
    return cpp_path.parent / "tests" / cpp_path.stem


def test_file_suite(cpp_path: Path, timeout: float = 2.0) -> bool:
    """Run all .in test cases in tests/<stem>/ for a C++ file."""
    ok, target_bin, err = compile_file(cpp_path)
    if not ok:
        print(f"{RED}Không thể chạy test do lỗi biên dịch.{RESET}")
        return False

    rel_path = cpp_path.relative_to(PROJECT_ROOT)
    test_dir = get_test_dir_for_cpp(cpp_path)
    
    if not test_dir.exists() or not list(test_dir.glob("*.in")):
        print(f"{YELLOW}Chưa có file test .in nào trong thư mục {test_dir.relative_to(PROJECT_ROOT) if test_dir.exists() else test_dir}{RESET}")
        print(f"{CYAN}Gợi ý: Dùng `make test FILE={rel_path} IN=\"...\"` để test nhanh với input truyền trực tiếp.{RESET}")
        return False

    in_files = sorted(test_dir.glob("*.in"))
    print(f"{BOLD}=== 🧪 Đang chạy {len(in_files)} test case cho {rel_path} ==={RESET}")

    all_passed = True
    for in_file in in_files:
        input_str = in_file.read_text(encoding="utf-8")
        out_file = in_file.with_suffix(".out")
        expected_out = out_file.read_text(encoding="utf-8") if out_file.exists() else None

        success, stdout, stderr, elapsed, exit_code = run_with_input(target_bin, input_str, timeout)

        if expected_out is not None:
            norm_actual = normalize_output(stdout)
            norm_exp = normalize_output(expected_out)
            if norm_actual != norm_exp or exit_code != 0:
                all_passed = False

        format_test_box(
            title=f"FILE TEST: {in_file.name} ({rel_path})",
            input_str=input_str,
            output_str=stdout,
            err_str=stderr,
            elapsed=elapsed,
            exit_code=exit_code,
            expected_out=expected_out,
        )

    return all_passed


def add_test_case(cpp_path: Path, raw_input: str, raw_output: str | None = None) -> bool:
    """Add a new .in (and optionally .out) test case file under tests/<stem>/."""
    test_dir = get_test_dir_for_cpp(cpp_path)
    test_dir.mkdir(parents=True, exist_ok=True)

    existing_ins = list(test_dir.glob("*.in"))
    next_idx = len(existing_ins) + 1
    
    in_file = test_dir / f"{next_idx}.in"
    input_str = raw_input.replace("\\n", "\n")
    if not input_str.endswith("\n"):
        input_str += "\n"
        
    in_file.write_text(input_str, encoding="utf-8")
    print(f"{GREEN}Đã tạo file test input:{RESET} {in_file.relative_to(PROJECT_ROOT)}")

    if raw_output is not None:
        out_file = test_dir / f"{next_idx}.out"
        out_str = raw_output.replace("\\n", "\n")
        if not out_str.endswith("\n"):
            out_str += "\n"
        out_file.write_text(out_str, encoding="utf-8")
        print(f"{GREEN}Đã tạo file test output:{RESET} {out_file.relative_to(PROJECT_ROOT)}")

    return True


def run_all_tests(target_dir: str | None = None, timeout: float = 2.0) -> bool:
    """Run tests for all C++ files or specific dir."""
    if target_dir:
        dir_path = SRC_DIR / target_dir if not Path(target_dir).is_absolute() else Path(target_dir)
        cpp_files = sorted(dir_path.rglob("*.cpp"))
    else:
        cpp_files = sorted(SRC_DIR.rglob("*.cpp"))

    files_with_tests = [f for f in cpp_files if (f.parent / "tests" / f.stem).exists() and list((f.parent / "tests" / f.stem).glob("*.in"))]

    if not files_with_tests:
        print(f"{YELLOW}Không tìm thấy test case .in nào trong các bài tập.{RESET}")
        print(f"{CYAN}Bạn có thể chạy `make test FILE=<tên_file> IN=\"<input>\"` để test bài tập bất kỳ.{RESET}")
        return True

    print(f"{BOLD}=== 🚀 TỰ ĐỘNG TEST TOÀN BỘ ({len(files_with_tests)} bài tập có test case) ==={RESET}\n")

    overall_passed = True
    for cpp_file in files_with_tests:
        ok = test_file_suite(cpp_file, timeout)
        if not ok:
            overall_passed = False

    return overall_passed
