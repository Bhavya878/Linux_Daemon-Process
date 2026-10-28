
# Linux Daemon Process

A Linux system programming project in C that demonstrates daemon creation, background execution, process management, and activity logging in Ubuntu Linux.

## 📖 Table of Contents

- [📌 Project Overview](#-project-overview)
- [🎯 Objectives](#-objectives)
- [🔄 Daemon Process Flow](#-daemon-process-flow)
- [🏗️ System Architecture](#️-system-architecture)
- [⚙️ Technical Requirements](#️-technical-requirements)
- [💻 Software Requirements](#-software-requirements)
- [📂 Repository Structure](#-repository-structure)
- [✨ Features](#-features)
- [▶️ Build Instructions](#️-build-instructions)
- [🧪 Testing and Demonstration](#-testing-and-demonstration)
- [📈 Future Enhancements](#-future-enhancements)
- [👤 Author](#-author)

---

## 📌 Project Overview

This project demonstrates the creation and execution of a Linux daemon process using the C programming language and Linux system calls.

A daemon is a background process that runs independently of direct terminal interaction. It can perform tasks continuously without requiring the user to keep the terminal open.

The project demonstrates the traditional double-fork technique to detach a process from its controlling terminal. It uses system calls such as `fork()`, `setsid()`, `umask()`, and `chdir()` to establish the daemon environment.

The daemon maintains a PID file to identify its process and writes periodic activity messages to a log file. The project helps develop a practical understanding of Linux process management and system programming.

## 🎯 Objectives

- Understand daemon processes and background execution in Linux.
- Create a daemon using the `fork()` system call.
- Create a new session using `setsid()`.
- Understand the double-fork daemonization technique.
- Configure file creation permissions using `umask()`.
- Change the working directory using `chdir()`.
- Understand process identification and PID management.
- Maintain a PID file for identifying the daemon process.
- Record daemon activity in a log file.
- Gain practical experience with Linux system calls and C programming.

## 🔄 Daemon Process Flow

The following diagram illustrates the general daemonization sequence used by this project.

```text
             Program Starts
                   |
                   v
                fork()
                   |
          +--------+--------+
          |                 |
        Parent             Child
          |                 |
         Exit                v
                          setsid()
                             |
                             v
                           fork()
                             |
                   +---------+---------+
                   |                   |
             Intermediate          Final Child
                Parent                 |
                   |                   v
                  Exit          Daemon Initialization
                                       |
                                       v
                                  chdir("/")
                                       |
                                       v
                                   umask(0)
                                       |
                                       v
                              Background Execution
                                       |
                                       v
                               Create PID File
                                       |
                                       v
                              Write Activity Logs
                                       |
                                       v
                               Continue Running
```

*Note: This is a conceptual flow diagram. The exact sequence should be checked against the implementation in `student_daemon.c`.*

## 🏗️ System Architecture

| Component | Purpose |
|---|---|
| Process Creation | Uses `fork()` to create child processes during daemonization. |
| Session Management | Uses `setsid()` to create a new session and detach from the controlling terminal. |
| Directory Management | Uses `chdir("/")` to change the working directory to the root directory. |
| Permission Management | Uses `umask()` to configure the file creation mask. |
| Process Identification | Uses a PID file to identify the running daemon. |
| Activity Logging | Writes periodic daemon activity messages to a log file. |
| Background Execution | Allows the daemon to run independently of direct terminal interaction. |

## ⚙️ Technical Requirements

| Requirement | Purpose |
|---|---|
| Process management | Understanding parent and child processes. |
| Daemonization | Creating a background process independent of the terminal. |
| Session management | Detaching the daemon from the controlling terminal. |
| File handling | Creating and maintaining PID and log files. |
| System calls | Working with Linux process and file management interfaces. |
| Process monitoring | Verifying daemon execution using Linux commands. |

## 💻 Software Requirements

| Software | Purpose |
|---|---|
| Ubuntu Linux | Development and execution environment. |
| GCC | Compiling the C source code. |
| GNU/Linux system libraries | Providing access to Linux system calls. |
| Nano or Vim | Editing source code in the terminal. |
| Git | Tracking source code changes. |
| GitHub | Hosting and sharing the project repository. |

## 📂 Repository Structure

```text
Linux_Daemon-Process/
├── student_daemon.c
├── .gitignore
└── README.md
```

### Runtime Files

The program uses the following runtime files:

- `/tmp/student_daemon.pid` — stores the daemon's process ID.
- `/tmp/student_daemon.log` — stores periodic daemon activity messages.

These files are generated at runtime and are separate from the source files in the GitHub repository.

## ✨ Features

- **Daemon Creation:** Demonstrates Linux daemon process creation in C.
- **Double-Fork Technique:** Demonstrates process separation during daemonization.
- **Session Management:** Uses `setsid()` to establish a new session.
- **Background Execution:** Runs independently of direct terminal interaction.
- **Working Directory Configuration:** Uses `chdir("/")` during initialization.
- **File Creation Mask:** Configures file creation permissions using `umask()`.
- **PID File Management:** Records the daemon process ID in `/tmp/student_daemon.pid`.
- **Activity Logging:** Writes periodic activity messages to `/tmp/student_daemon.log`.
- **Linux System Programming:** Provides practical experience with Linux system calls.

## ▶️ Build Instructions

### 1. Open Ubuntu Terminal

Open your Ubuntu terminal.

### 2. Navigate to the Project Directory

If your source code is located in `~/daemon_project`, run:

```bash
cd ~/daemon_project
```

### 3. Compile the Source Code

Compile the program using GCC:

```bash
gcc -Wall -Wextra student_daemon.c -o student_daemon
```

### 4. Execute the Program

Run the executable:

```bash
./student_daemon
```

Follow the program's output to observe the daemon initialization process.

### 5. Verify the Daemon Process

Check whether the process is running:

```bash
pgrep -af student_daemon
```

### 6. Check the PID File

Display the stored process ID:

```bash
cat /tmp/student_daemon.pid
```

### 7. Monitor the Log File

View the most recent log entries:

```bash
tail -n 10 /tmp/student_daemon.log
```

*Note: Run the program according to its actual startup behavior. If the daemon is already running, avoid starting duplicate instances.*

## 🧪 Testing and Demonstration

The project can be tested using the following checks:

### Process Verification

Use `pgrep` or `ps` to check whether the daemon is running.

```bash
pgrep -af student_daemon
```

### PID Verification

Check whether the PID file contains the process ID.

```bash
cat /tmp/student_daemon.pid
```

### Log Verification

Inspect the log file to confirm that periodic activity messages are being written.

```bash
tail -n 10 /tmp/student_daemon.log
```

### Background Execution Verification

Inspect the process details to examine its process ID, parent process ID, and terminal association.

```bash
ps -p "$(cat /tmp/student_daemon.pid)" -o pid,ppid,tty,comm
```

These checks help demonstrate the daemon's process state and runtime activity.

## 📈 Future Enhancements

- Implement robust signal handling for graceful termination.
- Improve PID file cleanup when the daemon exits.
- Add duplicate-instance protection using file locking.
- Introduce configurable logging levels and timestamps.
- Improve error handling during daemon initialization.
- Add a systemd service configuration for service management.
- Develop automated tests for process creation and daemon lifecycle management.

## 👤 Author

**Bhavya Palloli**

**Project:** Linux Daemon Process

Linux System Programming | C Programming |  Process Management | Signals | File Handling | Error Handling | Systemd
