# Kernel Responsibilities Overview

## File Management (File System Management)
This refers to how the kernel handles files and directories. As mentioned in the `README.md`, the kernel uses a **Virtual File System (VFS)** layer to provide a consistent interface for various file systems (like `ext4`, `Btrfs`, `XFS`). It manages operations like:
- Creating, reading, writing, and deleting files
- Handling file permissions and metadata
  > Related examples can be found in the `File-Management.md` file.

## Memory Management
The kernel is responsible for allocating and managing both **physical RAM** and **virtual memory** for all running processes. According to the `README.md`, it handles:
- **Paging** (moving data between RAM and swap space)
- **Memory protection**, ensuring that processes cannot access each other’s memory
- Management of the **unique virtual memory address space** for each process
- > Related examples can be found in the `Memory Management.md` file.

## Process Management
This describes how the kernel handles the execution of programs. As per the `README.md`, the kernel is a **multitasking** operating system that manages both **processes** and **threads**. It includes:
- A **scheduler** to allocate CPU time efficiently
- Process creation (`fork()`, `exec()`)
- Managing process states (e.g., running, sleeping, zombie)
- **Inter-Process Communication (IPC)**
  > Related examples can be found in the `Process Management.md` file.

## Threads
Threads are lightweight units of execution within a process and are part of **Process Management**. They share the same memory space as their parent process, which allows:
- Faster communication between threads compared to processes
- More efficient task execution
> Examples using `pthreads` can be found in the `Threads.md` file.

## Signals
While not listed as a separate management area, **signals** are an important part of Process Management and IPC. They are:
- **Software interrupts** used to notify a process of an event
- Used for events like termination, Ctrl+C interrupts, or errors (e.g., division by zero)
- Processes can also send signals to one another

## IPC Mechanism (Inter-Process Communication)
Falls under **Process Management**. IPC refers to how processes communicate and synchronize with one another. The `README.md` mentions:
- **Pipes**: One-way communication between related processes
- **Message Queues**: Exchange messages through a queue system
- **Shared Memory**: Multiple processes access the same memory region — the fastest form of IPC
> Related examples can be found in the `Process Management.md` file.
