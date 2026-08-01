"""
Integration Tester module for C++ OOP Assignments
"""

import subprocess
import time
from pathlib import Path
from .compiler import compile_file, PROJECT_ROOT, SRC_DIR

# Terminal colors
GREEN = "\033[92m"
RED = "\033[91m"
YELLOW = "\033[93m"
CYAN = "\033[96m"
RESET = "\033[0m"
BOLD = "\033[1m"

TESTS_DIR = PROJECT_ROOT / "tests"


def find_test_cases(cpp_path: Path) -> list[Path]:
    """Find input test files (.in, .txt) for a given cpp file (under tests/ or co-located in src/)."""
    cpp_path = cpp_path.resolve()
    stem = cpp_path.stem

    candidate_dirs = []

    # 1. Global tests/ directory matching relative path structure (e.g., tests/buoi1/buoi1_1/)
    try:
        rel_cpp = cpp_path.relative_to(SRC_DIR)
        candidate_dirs.append(TESTS_DIR / rel_cpp.parent / stem)
    except ValueError:
        pass

    # 2. Co-located test directories in src/ (e.g., src/buoi1/tests/buoi1_1, src/buoi1/buoi1_1_tests, src/buoi1/tests)
    parent_dir = cpp_path.parent
    candidate_dirs.append(parent_dir / "tests" / stem)
    candidate_dirs.append(parent_dir / f"{stem}_tests")
    candidate_dirs.append(parent_dir / stem)
    candidate_dirs.append(parent_dir / "tests")

    test_files = []
    seen = set()

    for d in candidate_dirs:
        if d.exists() and d.is_dir():
            for ext in ("*.in", "*.txt"):
                for test_file in sorted(d.glob(ext)):
                    if test_file not in seen:
                        # If directory is parent/tests directly, filter files matching stem or numbers
                        if d.name == "tests" and not test_file.name.startswith(stem) and not test_file.stem.isdigit():
                            continue
                        test_files.append(test_file)
                        seen.add(test_file)

    return sorted(test_files, key=lambda p: p.name)


def run_test_case(
    target_bin: Path, in_path: Path, timeout: float
) -> tuple[bool, str, str, float]:
    """Run a single test case using stdin redirection."""
    with open(in_path, "r", encoding="utf-8") as f_in:
        input_data = f_in.read()

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
        return False, input_data, f"Timeout ({timeout}s exceeded)", time.time() - start_time
    except Exception as e:
        return False, input_data, f"Execution Error: {str(e)}", time.time() - start_time

    if proc.returncode != 0:
        return False, input_data, f"Runtime Error (Exit Code {proc.returncode}):\n{stderr}", elapsed

    return True, input_data, stdout, elapsed


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
            f"  [{YELLOW}NO TESTS{RESET}] Build passed (No test input files found in tests/{rel_test_folder} or co-located folder)"
        )
        return 1, 0, 1

    passed_count = 0
    failed_count = 0

    for idx, in_path in enumerate(test_cases, start=1):
        case_name = in_path.name
        passed, input_data, output_or_err, elapsed = run_test_case(
            target_bin, in_path, timeout
        )

        if passed:
            print(f"  [{GREEN}RUN OK{RESET}] Case #{idx} ({case_name}) - {elapsed:.3f}s")
            if input_data.strip():
                print(f"    {CYAN}📥 Input ({case_name}):{RESET}")
                for line in input_data.rstrip().splitlines():
                    print(f"      {line}")
            if output_or_err.strip():
                print(f"    {GREEN}📤 Output:{RESET}")
                for line in output_or_err.rstrip().splitlines():
                    print(f"      {line}")
            else:
                print(f"    {GREEN}📤 Output: (Empty stdout){RESET}")
            passed_count += 1
        else:
            print(f"  [{RED}ERROR{RESET}] Case #{idx} ({case_name}) - {elapsed:.3f}s")
            if input_data.strip():
                print(f"    {CYAN}📥 Input ({case_name}):{RESET}")
                for line in input_data.rstrip().splitlines():
                    print(f"      {line}")
            if output_or_err.strip():
                print(f"    {RED}💥 Error Output:{RESET}")
                for line in output_or_err.rstrip().splitlines():
                    print(f"      {line}")
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
    print(f"Successful Runs    : {GREEN}{total_passed}{RESET}")
    print(
        f"Failed Runs        : {RED if total_failed > 0 else GREEN}{total_failed}{RESET}"
    )
    print(f"Total Time         : {elapsed_total:.2f}s\n")

    return total_failed == 0
