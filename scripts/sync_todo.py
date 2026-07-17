#!/usr/bin/env python3
import os
import re
import sys
import html

def natural_sort_key(s):
    return [int(text) if text.isdigit() else text.lower() for text in re.split(r'(\d+)', s)]

def parse_header_comment(file_path, file_name):
    try:
        with open(file_path, 'r', encoding='utf-8') as f:
            content = f.read()
    except Exception as e:
        print(f"Lỗi đọc file {file_path}: {e}")
        return None

    # Tìm phần comment block /* ... */ hoặc /** ... */ ở đầu file
    match = re.search(r'/\*\*(.*?)\*/', content, re.DOTALL)
    if not match:
        match = re.search(r'/\*(.*?)\*/', content, re.DOTALL)
        if not match:
            return None

    comment_body = match.group(1)
    lines = []
    for line in comment_body.splitlines():
        line = line.strip()
        if line.startswith('*'):
            line = line[1:].strip()
        lines.append(line)

    info = {
        'file': '',
        'brief': '',
        'note': [],
        'author': '',
        'date': '',
        'status': ''
    }

    current_tag = None
    for line in lines:
        tag_match = re.match(r'^@(\w+)(.*)', line)
        if tag_match:
            current_tag = tag_match.group(1)
            val = tag_match.group(2).strip()
            if current_tag == 'note':
                if val:
                    info['note'].append(val)
            elif current_tag in info:
                info[current_tag] = val
        else:
            if current_tag == 'note':
                info['note'].append(line)
            elif current_tag in ['brief', 'author', 'date', 'status'] and line:
                info[current_tag] = (info[current_tag] + " " + line).strip()

    # Dọn dẹp note
    note_lines = info['note']
    while note_lines and not note_lines[0]:
        note_lines.pop(0)
    while note_lines and not note_lines[-1]:
        note_lines.pop(-1)
    info['note'] = note_lines

    return info

def format_folder_name(folder_name):
    # buoi1 -> Buổi 1, lab2 -> Lab 2, hỗ trợ thư mục lồng nhau
    parts = re.split(r'[/\\]', folder_name)
    formatted_parts = []
    for part in parts:
        if not part:
            continue
        match_buoi = re.match(r'^(buoi|Buoi)(\d+)$', part)
        if match_buoi:
            formatted_parts.append(f"Buổi {match_buoi.group(2)}")
            continue
        match_lab = re.match(r'^(lab|Lab)(\d+)$', part)
        if match_lab:
            formatted_parts.append(f"Lab {match_lab.group(2)}")
            continue
        if part.isupper():
            formatted_parts.append(part)
        else:
            formatted_parts.append(part.capitalize())
    return " - ".join(formatted_parts)

def format_item(info, relative_path):
    status_val = info['status'].strip().lower()
    status_box = "x" if status_val == 'done' else " "
    
    placeholders = ('<note>', '[note]', '[ghi chú]', 'ghi chú', 'note')
    filtered_notes = []
    for note in info['note']:
        note_strip = note.strip()
        if note_strip and note_strip.lower() not in placeholders:
            filtered_notes.append(html.escape(note_strip))
            
    note_content = " <br> ".join(filtered_notes)
    
    brief_escaped = html.escape(info['brief'])
    author_escaped = html.escape(info['author'])
    date_escaped = html.escape(info['date'])
    
    item = f"- [{status_box}] [{info['file']}]({relative_path}) {brief_escaped} <details>\n"
    item += f"    <summary>📅 {date_escaped}</summary>\n"
    item += f"    <blockquote>\n"
    if note_content:
        item += f"    {note_content} <br>\n"
    item += f"    👤 {author_escaped}\n"
    item += f"    </blockquote>\n"
    item += f"</details>"
    return item

def markdown_relative_path(from_dir, target_path):
    relative_path = os.path.relpath(target_path, from_dir)
    if not relative_path.startswith('.'):
        relative_path = f"./{relative_path}"
    return relative_path.replace(os.sep, '/')

def replace_auto_generated_block(file_content, new_content):
    marker = "<!-- Auto generated -->"
    parts = file_content.split(marker)
    if len(parts) >= 3:
        # Giữ phần đầu và phần cuối, thay thế phần giữa
        end_part = marker.join(parts[2:])
        return parts[0] + marker + "\n\n" + new_content.strip() + "\n\n" + marker + end_part
    else:
        print("Cảnh báo: Không tìm thấy cặp block <!-- Auto generated --> phù hợp.")
        return file_content

def main():
    script_dir = os.path.dirname(os.path.abspath(__file__))
    project_root = os.path.dirname(script_dir)
    src_dir = os.path.join(project_root, 'src')

    if not os.path.exists(src_dir):
        print(f"Lỗi: Không tìm thấy thư mục src tại {src_dir}")
        sys.exit(1)

    # 1. Quét các thư mục con trong src (hỗ trợ cấu trúc lồng nhau)
    subdirs = []
    for root, dirs, files in os.walk(src_dir):
        # Bỏ qua các thư mục ẩn (bắt đầu bằng '.')
        dirs[:] = [d for d in dirs if not d.startswith('.')]
        cpp_files = [f for f in files if f.endswith('.cpp')]
        if cpp_files:
            rel_path = os.path.relpath(root, src_dir)
            subdirs.append(rel_path)

    # Sắp xếp các thư mục theo thứ tự tự nhiên
    subdirs.sort(key=natural_sort_key)

    todo_sections = []

    for folder_name in subdirs:
        folder_path = os.path.join(src_dir, folder_name)
        cpp_files = [f for f in os.listdir(folder_path) if f.endswith('.cpp')]
        cpp_files.sort(key=natural_sort_key)

        folder_items = []
        for cpp_file in cpp_files:
            file_path = os.path.join(folder_path, cpp_file)
            parsed = parse_header_comment(file_path, cpp_file)
            if not parsed:
                parsed = {}
            
            info = {
                'file': parsed.get('file') or cpp_file,
                'brief': parsed.get('brief') or '[Mô tả ngắn gọn]',
                'note': parsed.get('note') or [],
                'author': parsed.get('author') or '[Author]',
                'date': parsed.get('date') or '[Date]',
                'status': parsed.get('status') or 'todo'
            }

            readme_relative_path = markdown_relative_path(folder_path, file_path)
            todo_relative_path = markdown_relative_path(project_root, file_path)
            folder_items.append((info, readme_relative_path, todo_relative_path))

        readme_items = [format_item(info, relative_path) for info, relative_path, _ in folder_items]
        todo_items = [format_item(info, relative_path) for info, _, relative_path in folder_items]

        # 2. Cập nhật hoặc tạo README.md của thư mục con
        readme_path = os.path.join(folder_path, 'README.md')
        display_name = format_folder_name(folder_name)
        folder_new_content = "\n\n".join(readme_items)

        if os.path.exists(readme_path):
            with open(readme_path, 'r', encoding='utf-8') as r:
                readme_content = r.read()
            updated_readme = replace_auto_generated_block(readme_content, folder_new_content)
            with open(readme_path, 'w', encoding='utf-8') as r:
                r.write(updated_readme)
            print(f"Đã cập nhật: {readme_path}")
        else:
            new_readme_template = f"# 📅 Bài tập {display_name}\n\n<!-- Auto generated -->\n\n<!-- Auto generated -->\n"
            updated_readme = replace_auto_generated_block(new_readme_template, folder_new_content)
            with open(readme_path, 'w', encoding='utf-8') as r:
                r.write(updated_readme)
            print(f"Đã tạo mới và ghi dữ liệu: {readme_path}")

        # 3. Chuẩn bị phần nội dung cho TODO.md
        folder_link = markdown_relative_path(project_root, folder_path)
        section_md = f"### 📅 Bài tập [{display_name}]({folder_link})\n\n" + "\n\n".join(todo_items)
        todo_sections.append(section_md)

    # 4. Cập nhật TODO.md
    todo_path = os.path.join(project_root, 'TODO.md')
    todo_new_content = "\n\n".join(todo_sections)

    if os.path.exists(todo_path):
        with open(todo_path, 'r', encoding='utf-8') as t:
            todo_content = t.read()
        updated_todo = replace_auto_generated_block(todo_content, todo_new_content)
        with open(todo_path, 'w', encoding='utf-8') as t:
            t.write(updated_todo)
        print(f"Đã cập nhật: {todo_path}")
    else:
        new_todo_template = "## 📝 Nhật ký tiến độ làm bài (Homework Progress Checklist)\n\nHãy đánh dấu `[x]` thay vì `[ ]` khi bạn đã hoàn thành bài tập đó.\n\n<!-- Auto generated -->\n\n<!-- Auto generated -->\n"
        updated_todo = replace_auto_generated_block(new_todo_template, todo_new_content)
        with open(todo_path, 'w', encoding='utf-8') as t:
            t.write(updated_todo)
        print(f"Đã tạo mới và ghi dữ liệu: {todo_path}")

if __name__ == '__main__':
    main()
