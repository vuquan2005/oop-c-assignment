#!/usr/bin/env python3
"""
Test Runner for C++ OOP Assignments
Performs compile checks and stdin/stdout integration testing.
"""

import sys
import os
import subprocess
import argparse
import difflib
import time
from pathlib import Path

# Colors for terminal output
GREEN = "\033[92m"
RED = "\033[91m"
YELLOW = "\033[93m"
CYAN = "\033[96m"
RESET = "\033[0m"
BOLD = "\033[1m"

PROJECT_ROOT = Path(__file__).resolve().parent.parent
SRC_DIR = PROJECT_ROOT / "src"
TESTS_DIR = PROJECT_ROOT / "tests"
BUILD_DIR = PROJECT_ROOT / "build" / "test_binaries"

CXX = os.environ.get("CXX", "g++")
CXXFLAGS = ["-Wall", "-Wextra", "-pedantic", "-g", "-O0", "-std=c++17"]


def normalize_output(text: str) -> str:
    """Normalize output by stripping trailing spaces per line and standardizing newlines."""
    lines = text.replace("\r\n", "\n").split("\n")
    return "\n".join(line.rstrip() for line in lines).strip()


def compile_file(cpp_path: Path) -> tuple[bool, Path, str]:
    """Compile a C++ file to build/test_binaries."""
    rel_path = cpp_path.relative_to(PROJECT_ROOT)
    bin_name = rel_path.with_suffix("").as_posix().replace("/", "_")
    target_bin = BUILD_DIR / bin_name

    BUILD_DIR.mkdir(parents=True, exist_ok=True)

    cmd = [CXX] + CXXFLAGS + [str(cpp_path), "-o", str(target_bin)]
    result = subprocess.run(cmd, capture_output=True, text=True)

    if result.returncode != 0:
        return False, target_bin, result.stderr

    return True, target_bin, ""


def run_test_case(target_bin: Path, in_path: Path, out_path: Path, timeout: float) -> tuple[bool, str, float]:
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
            text=True
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

    norm_actual = normalize_output(stdout)
    norm_expected = normalize_output(expected_output)

    if out_path.exists():
        if norm_actual == norm_expected:
            return True, "", elapsed
        else:
            diff = difflib.unified_diff(
                norm_expected.splitlines(keepends=True),
                norm_actual.splitlines(keepends=True),
                fromfile="Expected (.out)",
                tofile="Actual (stdout)"
            )
            diff_msg = "".join(diff)
            return False, f"Output Mismatch:\n{diff_msg}", elapsed
    else:
        # If no .out file exists, just checking if run was clean
        return True, "(No .out file, run clean)", elapsed


def find_test_cases(cpp_path: Path) -> list[tuple[Path, Path]]:
    """Find input/output file pairs for a given cpp file under tests/."""
    rel_cpp = cpp_path.relative_to(SRC_DIR)
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


def test_single_cpp(cpp_path: Path, compile_only: bool, timeout: float, verbose: bool) -> tuple[int, int, int]:
    """Test a single C++ source file. Returns (passed, failed, total)."""
    rel_path = cpp_path.relative_to(PROJECT_ROOT)
    print(f"\n{BOLD}{CYAN}Testing:{RESET} {rel_path}")

    # Step 1: Compile
    ok, target_bin, compile_err = compile_file(cpp_path)
    if not ok:
        print(f"  [{RED}BUILD FAIL{RESET}] Compilation Error:\n{compile_err}")
        return 0, 1, 1

    if compile_only:
        print(f"  [{GREEN}BUILD OK{RESET}] Compiled successfully")
        return 1, 0, 1

    # Step 2: Find test cases
    test_cases = find_test_cases(cpp_path)

    if not test_cases:
        print(f"  [{YELLOW}NO TESTS{RESET}] Build passed (No test cases found in tests/{cpp_path.relative_to(SRC_DIR).with_suffix('')})")
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


def main():
    parser = argparse.ArgumentParser(description="Integration Test Runner for C++ Assignments")
    parser.add_argument("--file", "-f", type=str, help="Specific C++ file to test")
    parser.add_argument("--dir", "-d", type=str, help="Directory inside src/ to test")
    parser.add_argument("--compile-only", "-c", action="store_true", help="Only verify compilation for files")
    parser.add_argument("--timeout", "-t", type=float, default=2.0, help="Execution timeout per test in seconds")
    parser.add_argument("--verbose", "-v", action="store_true", help="Show verbose diff output")

    args = parser.parse_args()

    cpp_files = []

    if args.file:
        file_path = Path(args.file).resolve()
        if not file_path.exists():
            # try relative to src
            file_path = SRC_DIR / args.file
        if not file_path.exists():
            print(f"{RED}Error: File {args.file} not found.{RESET}")
            sys.exit(1)
        cpp_files.append(file_path)
    elif args.dir:
        dir_path = Path(args.dir).resolve()
        if not dir_path.exists():
            dir_path = SRC_DIR / args.dir
        if not dir_path.exists():
            print(f"{RED}Error: Directory {args.dir} not found.{RESET}")
            sys.exit(1)
        cpp_files = sorted(dir_path.rglob("*.cpp"))
    else:
        cpp_files = sorted(SRC_DIR.rglob("*.cpp"))

    if not cpp_files:
        print(f"{YELLOW}No C++ files found to test.{RESET}")
        sys.exit(0)

    print(f"{BOLD}=== OOP C++ Assignment Test Runner ==={RESET}")
    print(f"Found {len(cpp_files)} C++ source file(s).\n")

    total_passed = 0
    total_failed = 0
    total_cases = 0

    start_total = time.time()

    for cpp_file in cpp_files:
        p, f, c = test_single_cpp(cpp_file, args.compile_only, args.timeout, args.verbose)
        total_passed += p
        total_failed += f
        total_cases += c

    elapsed_total = time.time() - start_total

    print(f"\n{BOLD}=== SUMMARY ==={RESET}")
    print(f"Total Files Tested : {len(cpp_files)}")
    print(f"Total Test Cases   : {total_cases}")
    print(f"Passed             : {GREEN}{total_passed}{RESET}")
    print(f"Failed             : {RED if total_failed > 0 else GREEN}{total_failed}{RESET}")
    print(f"Total Time         : {elapsed_total:.2f}s\n")

    if total_failed > 0:
        sys.exit(1)
    sys.exit(0)


if __name__ == "__main__":
    main()
