"""
Integration Tester module for C++ OOP Assignments
"""

import re
import math
import sys
import subprocess
import difflib
import time
from pathlib import Path
from .compiler import compile_file, PROJECT_ROOT, SRC_DIR

import unicodedata

# Terminal colors
GREEN = "\033[92m"
RED = "\033[91m"
YELLOW = "\033[93m"
CYAN = "\033[96m"
RESET = "\033[0m"
BOLD = "\033[1m"

TESTS_DIR = PROJECT_ROOT / "tests"


def normalize_line(line: str) -> str:
    """
    Normalize a single line:
    - Insert spaces around operators & prompt symbols (= : > ,).
    - Collapse multiple horizontal spaces/tabs ([ \t]+) into a single space.
    - Strip leading/trailing whitespace.
    """
    line = re.sub(r"([=:>,])", r" \1 ", line)
    line = re.sub(r"[ \t]+", " ", line.strip())
    return line


def normalize_output(text: str) -> str:
    """
    Normalize output line-by-line:
    - Standardize Unicode (NFC form).
    - Standardize newlines (\r\n -> \n).
    - Strip leading and trailing whitespace per line.
    - Collapse horizontal spaces & pad operators (= : > ,).
    - Preserve line breaks (\n).
    """
    text = unicodedata.normalize("NFC", text)
    text = text.replace("\r\n", "\n").replace("–", "-").replace("—", "-")
    lines = text.split("\n")
    norm_lines = [normalize_line(line) for line in lines]
    return "\n".join(norm_lines).strip()


def is_float(val_str: str) -> bool:
    """Check if string token represents a valid float/int number."""
    try:
        float(val_str)
        return True
    except ValueError:
        return False


def compare_tokens(act_token: str, exp_token: str, float_tol: float = 1e-4) -> bool:
    """Compare two single tokens (words/numbers)."""
    if act_token == exp_token:
        return True
    if is_float(act_token) and is_float(exp_token):
        return math.isclose(float(act_token), float(exp_token), abs_tol=float_tol)
    return False


def compare_lines(act_line: str, exp_line: str, float_tol: float = 1e-4) -> bool:
    """Compare two lines token-by-token after line normalization."""
    act_norm = normalize_line(act_line)
    exp_norm = normalize_line(exp_line)
    if act_norm == exp_norm:
        return True
    act_tokens = act_norm.split()
    exp_tokens = exp_norm.split()
    if len(act_tokens) != len(exp_tokens):
        return False
    return all(compare_tokens(a, e, float_tol) for a, e in zip(act_tokens, exp_tokens))


def compare_outputs(
    actual_raw: str, expected_raw: str, float_tol: float = 1e-4
) -> tuple[bool, str]:
    """
    Compare actual output with expected output using:
    1. Line-by-line horizontal whitespace collapse.
    2. Token-by-token comparison (text must match exactly, numbers match within float_tol).
    """
    norm_actual = normalize_output(actual_raw)
    norm_expected = normalize_output(expected_raw)

    if norm_actual == norm_expected:
        return True, ""

    act_lines = norm_actual.splitlines()
    exp_lines = norm_expected.splitlines()

    if len(act_lines) == len(exp_lines):
        if all(compare_lines(a, e, float_tol) for a, e in zip(act_lines, exp_lines)):
            return True, ""

    # Build detailed diff if comparison failed
    diff = difflib.unified_diff(
        norm_expected.splitlines(keepends=True),
        norm_actual.splitlines(keepends=True),
        fromfile="Expected (.out)",
        tofile="Actual (stdout)",
    )
    diff_msg = "".join(diff)
    return False, diff_msg


def find_test_cases(cpp_path: Path) -> list[tuple[Path, Path]]:
    """Find input/output file pairs for a given cpp file under tests/."""
    try:
        rel_cpp = cpp_path.resolve().relative_to(SRC_DIR)
    except ValueError:
        return []

    folder_name = rel_cpp.parent
    stem = rel_cpp.stem

    test_case_dir = TESTS_DIR / folder_name / stem
    if not test_case_dir.exists():
        return []

    test_cases = []
    in_files = sorted(test_case_dir.glob("*.in"))
    for in_file in in_files:
        out_file = in_file.with_suffix(".out")
        test_cases.append((in_file, out_file))

    return test_cases


def run_test_case(
    target_bin: Path, in_path: Path, out_path: Path, timeout: float
) -> tuple[bool, str, float]:
    """Run a single test case using stdin redirection."""
    with open(in_path, "r", encoding="utf-8") as f_in:
        input_data = f_in.read()

    expected_output = ""
    if out_path.exists():
        with open(out_path, "r", encoding="utf-8") as f_out:
            expected_output = f_out.read()

    start_time = time.time()
    try:
        proc = subprocess.Popen(
            [str(target_bin)],
            stdin=subprocess.PIPE,
            stdout=subprocess.PIPE,
            stderr=subprocess.PIPE,
            text=True,
        )
        stdout, stderr = proc.communicate(input=input_data, timeout=timeout)
        elapsed = time.time() - start_time
    except subprocess.TimeoutExpired:
        proc.kill()
        proc.communicate()
        return False, f"Timeout ({timeout}s exceeded)", time.time() - start_time
    except Exception as e:
        return False, f"Execution Error: {str(e)}", time.time() - start_time

    if proc.returncode != 0:
        return False, f"Runtime Error (Exit Code {proc.returncode}):\n{stderr}", elapsed

    if out_path.exists():
        matched, diff_msg = compare_outputs(stdout, expected_output)
        if matched:
            return True, "", elapsed
        else:
            return False, f"Output Mismatch:\n{diff_msg}", elapsed
    else:
        return True, "(No .out file, run clean)", elapsed


def test_single_cpp(cpp_path: Path, timeout: float = 2.0) -> tuple[int, int, int]:
    """Test a single C++ source file. Returns (passed, failed, total)."""
    rel_path = cpp_path.relative_to(PROJECT_ROOT)
    print(f"\n{BOLD}{CYAN}Testing:{RESET} {rel_path}")

    # Compile
    ok, target_bin, compile_err = compile_file(cpp_path, silent=True)
    if not ok:
        print(f"  [{RED}BUILD FAIL{RESET}] Compilation Error:\n{compile_err}")
        return 0, 1, 1

    # Find test cases
    test_cases = find_test_cases(cpp_path)
    if not test_cases:
        rel_test_folder = cpp_path.relative_to(SRC_DIR).with_suffix("")
        print(
            f"  [{YELLOW}NO TESTS{RESET}] Build passed (No test cases found in tests/{rel_test_folder})"
        )
        return 1, 0, 1

    passed_count = 0
    failed_count = 0

    for idx, (in_path, out_path) in enumerate(test_cases, start=1):
        case_name = in_path.name
        passed, msg, elapsed = run_test_case(target_bin, in_path, out_path, timeout)
        if passed:
            print(f"  [{GREEN}PASS{RESET}] Case #{idx} ({case_name}) - {elapsed:.3f}s")
            passed_count += 1
        else:
            print(f"  [{RED}FAIL{RESET}] Case #{idx} ({case_name}) - {elapsed:.3f}s")
            if msg:
                print(f"    {YELLOW}{msg}{RESET}")
            failed_count += 1

    return passed_count, failed_count, len(test_cases)


def run_tests(
    file_path: str = None, dir_path: str = None, timeout: float = 2.0
) -> bool:
    """Run tests for a file, a directory, or all files under src/."""
    cpp_files = []

    if file_path:
        p = Path(file_path).resolve()
        if not p.exists():
            p = SRC_DIR / file_path
        if not p.exists():
            print(f"{RED}Lỗi: Không tìm thấy file {file_path}{RESET}")
            return False
        cpp_files.append(p)
    elif dir_path:
        d = Path(dir_path).resolve()
        if not d.exists():
            d = SRC_DIR / dir_path
        if not d.exists():
            print(f"{RED}Lỗi: Không tìm thấy thư mục {dir_path}{RESET}")
            return False
        cpp_files = sorted(d.rglob("*.cpp"))
    else:
        cpp_files = sorted(SRC_DIR.rglob("*.cpp"))

    if not cpp_files:
        print(f"{YELLOW}Không tìm thấy file C++ nào để kiểm thử.{RESET}")
        return True

    print(f"{BOLD}=== OOP C++ Assignment Integration Test Runner ==={RESET}")
    print(f"Tìm thấy {len(cpp_files)} file C++.\n")

    total_passed = 0
    total_failed = 0
    total_cases = 0

    start_total = time.time()

    for cpp_file in cpp_files:
        p, f, c = test_single_cpp(cpp_file, timeout)
        total_passed += p
        total_failed += f
        total_cases += c

    elapsed_total = time.time() - start_total

    print(f"\n{BOLD}=== SUMMARY ==={RESET}")
    print(f"Total Files Tested : {len(cpp_files)}")
    print(f"Total Test Cases   : {total_cases}")
    print(f"Passed             : {GREEN}{total_passed}{RESET}")
    print(
        f"Failed             : {RED if total_failed > 0 else GREEN}{total_failed}{RESET}"
    )
    print(f"Total Time         : {elapsed_total:.2f}s\n")

    return total_failed == 0
