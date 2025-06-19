# 🔗 pipex

> Recreating shell pipelines in C, one pipe at a time.

## 📌 Project Overview

**pipex** is a 42 school UNIX project designed to deepen your understanding of process creation, file redirection, and inter-process communication through pipes. The goal is to reproduce the behavior of shell pipelines using **`fork()`**, **`execve()`**, and **`pipe()`** system calls.

You’ll implement the ability to connect two or more shell commands via pipes, manage input/output files, and simulate how the shell handles command chaining.

---

## 🧪 Example Usage

```bash
./pipex infile "grep hello" "wc -l" outfile
```
Equivalent shell command:

```bash
< infile grep hello | wc -l > outfile
```

This reads from **infile**, pipes the result of **grep hello** into **wc -l**, and writes the final output into **outfile**.

## 🛠️ Features

- Accepts four arguments: **file1 cmd1 cmd2 file2**

- Uses low-level system calls: **fork**, **pipe**, **execve**, **dup2**, etc.

- Correctly reproduces shell redirection: **< file1 cmd1 | cmd2 > file2**

- Manages memory and error handling cleanly

- Norm-compliant and leak-free

- Supports command arguments with and without options

## 🔥 Bonus Features (Implemented ✅)
- ✅ Multiple commands with multiple pipes
```bash
./pipex file1 cmd1 cmd2 cmd3 ... cmdN file2
```
Behaves like:
```bash
< file1 cmd1 | cmd2 | cmd3 | ... | cmdN > file2
```
- ✅ here_doc support
```bash
./pipex here_doc LIMITER cmd1 cmd2 file
```
Equivalent to:
```bash
cmd1 << LIMITER | cmd2 >> file
```

## 📌 How to Compile and Run
```bash
make          # Compiles mandatory part
make bonus    # Compiles bonus with multiple pipes and here_doc support
```
**Example Commands**
```bash
./pipex infile "ls -l" "wc -l" outfile
./pipex here_doc END cat "grep hello" outfile
```

