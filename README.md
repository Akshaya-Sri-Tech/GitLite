# GitLite

GitLite is a lightweight, Git-inspired version control system built in C++ as a learning project.  
The goal is to understand how real version control systems work internally by implementing core features such as repository initialization, staging, commits, and history tracking.

---

## Current Status

🚧 Early Development Stage (Repository Core Working)

GitLite currently supports a command-line interface, modular command routing, and repository initialization with persistent on-disk storage.

---

## Implemented Features

- Command-line argument parsing (argc, argv)
- CLI format:
  gitlite <command>
- Command routing system using unordered_map
- Modular command-based architecture
- Multi-file C++ project structure
- Repository initialization with disk-based structure

---

## Working Commands

### version

Displays GitLite version and available commands.

gitlite version

Output:
gitlite version 1.0.0
Commands available: init, add, commit, log, checkout, version

---

### init

Initializes a new GitLite repository inside repository/.gitlite.

gitlite init

Behavior:

If repository does not exist:
Initialized empty GitLite repository in repository/.gitlite

If repository already exists:
Repository already exists.

What it creates:
repository/.gitlite/
├── staging/
├── commits/
└── metadata.txt

---

## Project Structure

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
│   └── .gitlite/
│       ├── staging/
│       ├── commits/
│       └── metadata.txt
│
├── utils/
│   └── (future helper functions)
│
└── README.md

---

## Build Instructions

g++ src/main.cpp commands/*.cpp -o gitlite

---

## Run Examples

./gitlite version

./gitlite init

---

## How It Works

User Input
↓
main.cpp
↓
unordered_map (command router)
↓
function execution

Example flow:

gitlite init

Steps:
- Check if repository/.gitlite exists
- If exists → reject initialization
- If not → create repository structure
- Write metadata file

---

## Planned Features

- add → stage files
- commit → save snapshots
- status → show working tree state
- log → view commit history
- checkout → restore previous commits

---

## Learning Goals

- Understand internal Git architecture
- Learn system-level C++ programming
- Work with filesystem operations
- Build CLI tools
- Learn persistent storage design

---

## Notes

- Educational project (not production VCS)
- Repository state stored in repository/.gitlite
- Next milestone: implementing staging system (add)