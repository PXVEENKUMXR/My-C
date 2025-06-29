# Linux Kernel Subsystems & File Operations in C

This repository provides a hands-on introduction to Linux **kernel subsystems** through practical C programs demonstrating **low-level file operations** using system calls like `open()`, `read()`, `write()`, and more.

These programs are intended for students, system programmers, and Linux enthusiasts who want to understand how system calls interact directly with various kernel components.

---

## Table of Contents

- [1. Overview of Linux Kernel Subsystems](#1-overview-of-linux-kernel-subsystems)
- [2. File Operations via System Calls](#2-file-operations-via-system-calls)
- [3. Key Kernel Subsystems](#3-key-kernel-subsystems)
  - [3.1 Virtual File System (VFS)](#31-virtual-file-system-vfs)
  - [3.2 Process Management](#32-process-management)
  - [3.3 Memory Management](#33-memory-management)
  - [3.4 Inter-Process Communication (IPC)](#34-inter-process-communication-ipc)
  - [3.5 Device Drivers](#35-device-drivers)
- [4. Common System Calls](#4-common-system-calls)
- [5. Error Handling](#5-error-handling)
- [6. How to Compile & Run](#6-how-to-compile--run)
- [7. License](#7-license)

---

## 1. Overview of Linux Kernel Subsystems

The Linux kernel is modular and consists of several key subsystems:

- **VFS (Virtual File System)** – unified interface for all filesystems.
- **Scheduler** – manages process execution and CPU time.
- **Memory Manager** – handles physical and virtual memory.
- **IPC (Inter-Process Communication)** – enables processes to exchange data.
- **Networking Stack** – manages sockets and protocols.
- **Device Drivers** – control access to hardware.

---

## 2. File Operations via System Calls

Linux provides low-level system calls for file manipulation, allowing direct interaction with the kernel. These operations bypass the standard C library (`stdio.h`) and use:

- `open()`, `read()`, `write()`, `close()`
- `lseek()`, `stat()`, `unlink()`, etc.

These are essential for:
- Embedded systems
- Real-time applications
- OS and kernel-level development

---
