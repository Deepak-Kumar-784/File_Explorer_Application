# 🗂️ File Explorer Application (LinuxOS)

### 📘 Overview

The **File Explorer Application** is a **console-based C++ project** that interacts directly with the **Linux operating system** to manage files and directories.
It provides a simple **menu-driven interface** where users can perform common file management tasks such as listing, navigating, creating, deleting, copying, renaming, searching, and managing file permissions.

This project is developed as part of **Assignment 1 (LinuxOS)** in the Operating Systems Laboratory.

---

## 🎯 Objective

To develop a **console-based File Explorer application in C++** that uses **Linux system calls** to perform file and directory operations efficiently within a terminal environment.

---

## ⚙️ Features

- **List Files & Directories** – Displays all files and folders in the current directory.
- **Change Directory** – Navigate to another directory path.
- **Create File** – Create new text files directly from the console.
- **Delete File** – Delete any file from the current directory.
- **Rename / Move File** – Rename or move files to a new location.
- **Copy File** – Create a duplicate of any existing file.
- **Search File** – Recursively search for a file in all subdirectories.
- **View / Change Permissions** – Display and modify file permissions using Linux permission codes.

---

## 🧠 Concepts and Linux System Calls Used

| Function / Command | Description                                                        |
| ------------------ | ------------------------------------------------------------------ |
| `opendir()`        | Opens a directory stream.                                          |
| `readdir()`        | Reads entries (files/folders) from the directory.                  |
| `closedir()`       | Closes the directory stream.                                       |
| `stat()`           | Retrieves file or directory information (type, permissions, etc.). |
| `chdir()`          | Changes the current working directory.                             |
| `remove()`         | Deletes a file from the file system.                               |
| `rename()`         | Renames or moves files.                                            |
| `system("chmod")`  | Changes file permissions using Linux `chmod` command.              |

---
