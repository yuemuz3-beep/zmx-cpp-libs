import subprocess
from pathlib import Path


README = Path("README.md")


# 获取 Git 管理的文件
files = subprocess.check_output(
    ["git", "ls-files"],
    text=True,
    encoding="utf-8"
).splitlines()


# 构建目录树
tree = {}

for file in files:
    parts = Path(file).parts
    current = tree

    for part in parts:
        current = current.setdefault(part, {})


def build_tree(tree, prefix="", output=None):
    items = sorted(tree.items())

    for i, (name, children) in enumerate(items):
        last = i == len(items) - 1

        branch = "└── " if last else "├── "
        output.append(prefix + branch + name)

        if children:
            next_prefix = prefix + ("    " if last else "│   ")
            build_tree(children, next_prefix, output)


output = ["zmx-cpp-libs/"]
build_tree(tree, output=output)

tree_text = "\n".join(output)


# 读取 README
readme_text = README.read_text(encoding="utf-8")

start_marker = "<!-- TREE START -->"
end_marker = "<!-- TREE END -->"

start = readme_text.find(start_marker)
end = readme_text.find(end_marker)

if start == -1 or end == -1:
    raise RuntimeError(
        "README.md 中没有找到 TREE START / TREE END 标记"
    )

if start > end:
    raise RuntimeError(
        "TREE START 必须出现在 TREE END 之前"
    )


# 保留标记，只替换中间内容
new_text = (
        readme_text[:start + len(start_marker)]
        + "\n\n```text\n"
        + tree_text
        + "\n```\n\n"
        + readme_text[end:]
)


# 写回 README
README.write_text(new_text, encoding="utf-8")

print("README project tree updated.")