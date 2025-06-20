# File Operations in C (Linux System Programming)

This repository contains a comprehensive set of C programs that demonstrate how to perform low-level file operations using Linux system calls. These operations are fundamental in understanding how Linux handles files at the kernel level, bypassing standard I/O libraries like stdio.h.

---

## Table of Contents

- [1. Introduction to File Operations](#1-introduction-to-file-operations)
- [2. File Descriptors and File Abstraction in Linux](#2-file-descriptors-and-file-abstraction-in-linux)
- [3. Why Use System Calls Instead of Standard I/O?](#3-why-use-system-calls-instead-of-standard-io)
- [4. Common System Calls for File Operations](#4-common-system-calls-for-file-operations)
- [5. Error Handling and Return Values](#5-error-handling-and-return-values)
  
---

## 1. Introduction to File Operations

In Linux, almost everything is treated as a file: text files, binary files, devices, sockets, and even pipes. Understanding how to work with files at the system call level is essential for writing efficient and portable system software.

File operations include:

- Creating files
- Opening files
- Reading from files
- Writing to files
- Appending to files
- Fetching metadata (size, permissions, timestamps)
- Deleting or renaming files

These operations are done using low-level APIs provided by the *POSIX standard*, which interact directly with the Linux kernel.

---

## 2. File Descriptors and File Abstraction in Linux

When you open a file in Linux using the open() system call, the kernel returns an *integer file descriptor*. This FD represents an entry in the process's file descriptor table.

| File Descriptor | Meaning         |
|-----------------|-----------------|
| 0               | Standard Input  |
| 1               | Standard Output |
| 2               | Standard Error  |
| 3+              | User files      |

All file operations (read(), write(), etc.) use this FD to refer to the file.

---

## 3. Why Use System Calls Instead of Standard I/O?

Standard I/O functions like fopen() and fgets() are convenient but abstracted. System calls give you *fine-grained control*, which is critical for:

- Embedded systems
- OS-level programming
- Drivers and kernel modules
- High-performance or real-time applications

### Comparison:

| Standard I/O (stdio.h)  | System Call (fcntl.h, unistd.h) |
|---------------------------|--------------------------------------|
| fopen()                 | open()                             |
| fread(), fwrite()     | read(), write()                  |
| fclose()                | close()                            |
| Buffered                  | Unbuffered (immediate sys call)      |

---

## 4. Common System Calls for File Operations

| System Call | Header         | Purpose                                        |
|-------------|----------------|------------------------------------------------|
| open()    | <fcntl.h>    | Open/create a file and get file descriptor     |
| read()    | <unistd.h>   | Read bytes from a file                         |
| write()   | <unistd.h>   | Write bytes to a file                          |
| close()   | <unistd.h>   | Close the file descriptor                      |
| lseek()   | <unistd.h>   | Move file pointer (like cursor)                |
| stat()    | <sys/stat.h> | Get file metadata (permissions, size, etc.)    |
| unlink()  | <unistd.h>   | Delete a file                                  |

Each system call returns a value:
- ≥0 indicates success (often a descriptor or byte count)
- -1 indicates an error (use perror() or strerror(errno) to debug)

---

## 5. Error Handling and Return Values

System calls are *not guaranteed to succeed*. Always check the return value:

```c
int fd = open("file.txt", O_RDONLY);
if (fd == -1) {
    perror("open failed");
    exit(EXIT_FAILURE);
}
