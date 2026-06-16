# GitLite

GitLite is a lightweight, Git-inspired version control system built in C++ as a learning project.
The goal is to understand how real version control systems work internally by implementing core features like command parsing, repository initialization, staging, commits, and history tracking.

---

## Current Status

🚧 **Early Development Stage**

GitLite currently has a working command-line interface and a functional command dispatch system. Only the `version` command is fully implemented so far.

---

### ✅ Implemented

* Command-line argument parsing using `argc` and `argv`
* CLI command format:

  ```bash
  gitlite <command>
  ```
* Command routing system using `unordered_map`
* Function-based command architecture (modular design)
* Multi-file C++ project structure

### ✅ First Working Command

```bash
gitlite version
```

Output:

```text
GitLite Version 1.0
```

---

## Project Structure

```text
GitLite/
│
├── src/
│   └── main.cpp
│
├── commands/
│   ├── version.h
│   ├── version.cpp
│   ├── init.h
│   ├── init.cpp
│   ├── add.h
│   ├── add.cpp
│   ├── commit.h
│   ├── commit.cpp
│   ├── log.h
│   ├── log.cpp
│   ├── checkout.h
│   └── checkout.cpp
│
├── repository/
│   └── (future: stores gitlite metadata)
│
├── utils/
│   └── (future helper functions)
│
└── README.md
```

---

## Build Instructions

Compile the project from the **root directory**:

```bash
g++ src/main.cpp commands/*.cpp -o gitlite
```

---

## Run

### Version command

```bash
./gitlite version
```

---

## How It Works

GitLite uses a simple command dispatcher:

```text
User Input
   ↓
main.cpp
   ↓
unordered_map (command router)
   ↓
calls corresponding function
   ↓
command executes
```

Example:

```bash
gitlite version
```

Becomes:

* Parse `version`
* Find function in map
* Execute `version()`

---

## Planned Features (V1)

* `init` → Initialize repository
* `add` → Stage files
* `commit` → Save snapshots
* `status` → Show working tree state
* `log` → View commit history
* `checkout` → Restore previous state

---

## Learning Goals

This project is being built to understand:

* How Git works internally
* Command-line applications in C++
* File system operations
* Data structures used in real systems
* Modular software design

---

## Notes

* This is an educational project, not a production VCS
* Current focus is building the core engine step by step
