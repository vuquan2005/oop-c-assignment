"""
Exercise Generator module for C++ OOP Assignments
"""

import sys
import os
import re
import datetime
import subprocess
from pathlib import Path
from .compiler import PROJECT_ROOT, SRC_DIR

# Terminal colors
GREEN = "\033[92m"
RED = "\033[91m"
YELLOW = "\033[93m"
BLUE = "\033[94m"
RESET = "\033[0m"
BOLD = "\033[1m"


def get_git_author() -> str:
    """Get author name from git config or environment."""
    author = os.environ.get("AUTHOR", "").strip()
    if author:
        return author
    try:
        res = subprocess.run(
            ["git", "config", "user.name"], capture_output=True, text=True
        )
        if res.returncode == 0 and res.stdout.strip():
            return res.stdout.strip()
    except Exception:
        pass
    return "<Name>"


def get_display_name(folder_name: str) -> str:
    """Convert folder name like 'buoi1' or 'lab2' to human readable display name."""
    m_buoi = re.match(r"^[Bb]uoi(\d+)$", folder_name)
    if m_buoi:
        return f"buổi {m_buoi.group(1)}"
    m_lab = re.match(r"^[Ll]ab(\d+)$", folder_name)
    if m_lab:
        return f"thực hành {m_lab.group(1)}"
    return folder_name.capitalize()


def create_new_exercise(
    folder: str = None, num: int = None, author: str = None
) -> bool:
    """Interactively or programmatically generate a new exercise directory and template files."""
    if not folder:
        print(f"{BLUE}=== TẠO BÀI TẬP C++ MỚI ==={RESET}")
        try:
            folder = input(
                "Nhập tên thư mục bài tập mới (Ví dụ: buoi6, lab6): "
            ).strip()
        except (EOFError, KeyboardInterrupt):
            print("\nĐã hủy.")
            return False

    if not folder:
        print(f"{RED}Lỗi: Tên thư mục không được để trống!{RESET}")
        return False

    if not num:
        try:
            val = input("Nhập số lượng bài tập cần tạo (Ví dụ: 3): ").strip()
            if val.isdigit():
                num = int(val)
        except (EOFError, KeyboardInterrupt):
            print("\nĐã hủy.")
            return False

    if not num or num <= 0:
        print(f"{RED}Lỗi: Số lượng bài tập phải là số nguyên dương lớn hơn 0!{RESET}")
        return False

    if not author:
        author = get_git_author()

    target_dir = SRC_DIR / folder
    target_dir.mkdir(parents=True, exist_ok=True)

    print(f"\nThư mục đích: {YELLOW}{target_dir.relative_to(PROJECT_ROOT)}{RESET}")
    print(f"Đang khởi tạo {num} bài tập...")

    created_count = 0
    skipped_count = 0

    # Create README.md in target exercise directory if missing
    readme_path = target_dir / "README.md"
    if not readme_path.exists():
        display_name = get_display_name(folder)
        readme_content = f"# 📅 Bài tập {display_name}\n\n<!-- Auto generated -->\n\n<!-- Auto generated -->\n"
        with open(readme_path, "w", encoding="utf-8") as f:
            f.write(readme_content)
        print(f"  - [{GREEN}ĐÃ TẠO{RESET}] {readme_path.relative_to(PROJECT_ROOT)}")

    today_str = datetime.datetime.now().strftime("%d-%m-%Y")

    for i in range(1, num + 1):
        file_name = f"{folder}_{i}.cpp"
        file_path = target_dir / file_name

        if file_path.exists():
            print(f"  - [{YELLOW}ĐÃ TỒN TẠI{RESET}] {file_name} (Bỏ qua)")
            skipped_count += 1
        else:
            code_template = f"""/**
 * @file {file_name}
 * @brief [Mô tả ngắn gọn]
 * @note [Ghi chú]
 *
 * @author {author}
 * @date {today_str}
 *
 * @status todo
 */

#include <iostream>

using namespace std;

int main() {{
    
    return 0;
}}
"""
            with open(file_path, "w", encoding="utf-8") as f:
                f.write(code_template)
            print(f"  - [{GREEN}ĐÃ TẠO{RESET}] {file_path.relative_to(PROJECT_ROOT)}")
            created_count += 1

    print(f"\n{GREEN}=== HOÀN THÀNH ==={RESET}")
    print(
        f"Thành công: Đã tạo {GREEN}{created_count}{RESET} file mới, bỏ qua {YELLOW}{skipped_count}{RESET} file đã có.\n"
    )
    return True
