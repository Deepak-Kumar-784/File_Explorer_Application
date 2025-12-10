# File Explorer Application

**A robust, menu-driven console application for file and directory management on Linux systems using native C++ and system calls.**

---

## Overview

The **File Explorer Application** is a lightweight, command-line utility developed in C++ that provides direct access to Linux file system operations through an intuitive menu-driven interface. Built entirely using standard C++ libraries and POSIX system calls, this application enables users to efficiently manage files and directories without leaving the terminal environment.

Designed as a practical exploration of operating systems concepts, this project demonstrates core file system operations including navigation, creation, deletion, and permission management using native Linux APIs.

---

## Key Features

| Feature                         | Description                                                                            |
| ------------------------------- | -------------------------------------------------------------------------------------- |
| **📁 List Files & Directories** | View all files and subdirectories in the current location with clear visual indicators |
| **📂 Change Directory**         | Seamlessly navigate to different directories using absolute or relative paths          |
| **📄 Create File**              | Generate new files directly from the console interface                                 |
| **🗑️ Delete File**              | Permanently remove files from the file system                                          |
| **✏️ Rename/Move File**         | Rename files or move them to different locations with a single operation               |
| **📋 Copy File**                | Create binary-safe duplicates of existing files                                        |
| **🔍 Search File**              | Recursively search for files throughout the directory hierarchy                        |
| **🔐 Manage Permissions**       | View and modify file permissions using standard Unix octal notation                    |

---

## System Architecture

### Core Technologies

- **Language:** C++11
- **Platform:** Linux/Unix-based systems
- **Build:** Standard C++ compiler (g++, clang)
- **Standard Libraries:** STL, POSIX APIs

### System Calls Used

The application leverages the following Linux/POSIX system calls for efficient file operations:

| System Call  | Purpose                                                              |
| ------------ | -------------------------------------------------------------------- |
| `opendir()`  | Opens and initializes a directory stream for reading                 |
| `readdir()`  | Retrieves entries (files and subdirectories) from open directory     |
| `closedir()` | Properly closes directory streams and releases resources             |
| `stat()`     | Obtains detailed file metadata (type, size, permissions, timestamps) |
| `chmod()`    | Modifies file and directory access permissions                       |
| `chdir()`    | Changes the current working directory                                |
| `remove()`   | Deletes files from the file system                                   |
| `rename()`   | Renames or relocates files within the file system                    |

---

## User Interface

The application features a clean, interactive menu system:

```
=============================
      FILE EXPLORER MENU
=============================
1. List Files
2. Change Directory
3. Create File
4. Delete File
5. Rename/Move File
6. Copy File
7. Search File
8. Manage Permissions
9. Exit
Enter choice:
```

### Input Handling

- Robust error handling for invalid user inputs
- Input buffer management to prevent cascading errors
- Type validation for numeric menu selections
- Clear, user-friendly error messages

---

## Getting Started

### Prerequisites

- GCC or Clang compiler
- Linux/Unix-based operating system
- Standard C++ development libraries
- Terminal/Console access

### Compilation

```bash
g++ -o file_explorer Code/file_explorer.cpp
```

For enhanced compatibility and warnings:

```bash
g++ -Wall -Wextra -std=c++11 -o file_explorer Code/file_explorer.cpp
```

### Running the Application

```bash
./file_explorer
```

---

## Usage Examples

### Listing Files

```
Enter choice: 1
```

Displays all files and directories in the current location with [DIR] and [FILE] indicators.

### Creating a File

```
Enter choice: 3
Enter file name: document.txt
```

Creates a new empty file in the current directory.

### Searching for a File

```
Enter choice: 7
Enter file name to search: document.txt
```

Recursively searches all subdirectories and displays the complete path if found.

### Managing Permissions

```
Enter choice: 8
Enter file name: document.txt
```

Displays current permissions and allows modification using octal notation (e.g., 755).

---

## Technical Highlights

### Efficient Directory Traversal

- Uses POSIX `opendir()`, `readdir()`, and `closedir()` for optimal performance
- Filters special entries (`.` and `..`) to prevent loops
- Proper resource cleanup after each operation

### Safe File Operations

- Binary-safe file copying using stream buffers
- Error checking at each system call invocation
- Descriptive error messages using `perror()`

### Robust Permission Handling

- Bitwise operations for precise permission extraction
- Support for user, group, and other permission levels
- Octal notation input validation

### Input Validation

- Numeric input validation with error recovery
- Buffer clearing to prevent input overflow
- Exception handling for permission conversions

---

## Project Structure

```
File_Explorer_Application/
├── README.md                 # Project documentation
├── LICENSE                   # Project license
└── Code/
    └── file_explorer.cpp     # Main application source code
```

---

## Educational Value

This project effectively demonstrates:

- **POSIX System Calls:** Practical implementation of Linux file system APIs
- **File System Operations:** Directory navigation, file manipulation, and permissions
- **Memory Management:** Proper resource allocation and deallocation
- **Error Handling:** Comprehensive error detection and user feedback
- **User Interface Design:** Intuitive menu-driven interaction patterns
- **C++ Best Practices:** Efficient use of STL containers and standard libraries

---

## License

This project is distributed under the terms specified in the LICENSE file.

---

## Author

**Deepak Kumar Behera**

---

## Acknowledgments

Built as an exploration of operating systems concepts, demonstrating practical file system management through native Linux APIs and system calls.
