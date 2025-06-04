
# 📁 dex — Directory Explorer in C

`dex` is a lightweight and fast command-line tool written in C to recursively display a directory tree. It supports sorting, filtering, and dotfile visibility — ideal for terminal users who want a simple and scriptable file-tree viewer.

---

## 🔧 Installation

### 🔨 Build and Install

```bash
git clone https://github.com/yourusername/dex.git
cd dex
cmake -B build
cmake --build build
sudo cmake --install build
````

* Installs the `dex` binary to `/usr/local/bin/dex` by default.

### 🗑 Uninstallation

```bash
sudo make -C build uninstall
```

* Removes the binary from your system.

---

## ▶️ Usage

```bash
dex [options] <directory>
```

* If `<directory>` is omitted, dex defaults to the current directory (`.`).
* Flags can appear in any order.
* You may use `-p <dir>` or `--path <dir>` to explicitly specify the path.

---

## ⚙️ Options

| Option                     | Description                                                              |
| -------------------------- | ------------------------------------------------------------------------ |
| `-h`, `--help`             | Show help/manual.                                                        |
| `-d`, `--show-dotfiles`    | Include dotfiles (files starting with `.`) in the output.                |
| `--sort=alpha`             | Sort entries alphabetically (default).                                   |
| `--sort=size`              | Sort directories by total size recursively.                              |
| `--ignore <name> [...]`    | Ignore one or more files or directories by name. Supports multiple args. |
| `-p <dir>`, `--path <dir>` | Explicitly specify the directory path to explore.                        |

> Note: If both `--ignore` and a path are provided, the last non-option argument is treated as the path.

---

## 📂 Examples

```bash
dex
```

> Show directory tree of the current folder.

```bash
dex --sort=size -d
```

> Include dotfiles and sort by size.

```bash
dex --ignore build .git
```

> Ignore the `build` and `.git` directories.

```bash
dex --path ~/projects
```

> Explore a specific directory.

---


## 📝 Description

* `dex` uses POSIX-compliant file and directory functions.
* It is written in modular C with a strict 1:1 `.c` ↔ `.h` structure.
* The CLI help output is generated from `Documentation/manual.txt`, allowing easy edits without recompiling.

---

## ✅ Dependencies

* GCC or Clang
* CMake ≥ 3.12
* Linux (tested on Arch Linux)

---

## 📜 License

This project is licensed under the [MIT License](LICENSE).

---

## 🙋 About

Written by Aviral Dubey — designed to be simple, efficient, and extensible. Inspired by Unix tools like `tree`, `ls`, and `exa`.

Pull requests and suggestions are welcome!

---

### ✅ Key Qualities:

- Clean **installation/uninstallation instructions**
- Full **usage section** with **flag breakdown**
- Minimalist tone, suitable for open-source audiences
- Ready to drop into GitHub with no edits needed except username
