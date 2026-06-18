# GitLite

GitLite is a lightweight, Git-inspired version control system built in C++ as a learning project.  
The goal is to understand how real version control systems work internally by implementing core features such as repository initialization, staging, commits, and history tracking.

---

## Current Status

🚧 Early Development Stage (Repository Core Working)

GitLite supports:
- CLI command system
- Command routing
- Repository initialization with persistent storage

---

## Implemented Features

- Command-line argument parsing (argc, argv)
- CLI format: gitlite <command>
- Command routing using unordered_map
- Modular command-based architecture
- Multi-file C++ project structure
- Repository initialization with disk structure

---

## Working Commands

### version

gitlite version

Output:
gitlite version 1.0.0
Commands available: init, add, commit, log, checkout, version

---

### init

gitlite init

Behavior:

If repo does NOT exist:
Initialized empty GitLite repository in repository/.gitlite

If repo already exists:
Repository already exists.

Creates:
repository/.gitlite/
|-- staging/
|-- commits/
|-- metadata.txt

---

## Project Structure

GitLite/
|
|-- src/
|   |-- main.cpp
|
|-- commands/
|   |-- version.h
|   |-- version.cpp
|   |-- init.h
|   |-- init.cpp
|   |-- add.h
|   |-- add.cpp
|   |-- commit.h
|   |-- commit.cpp
|   |-- log.h
|   |-- log.cpp
|   |-- checkout.h
|   |-- checkout.cpp
|
|-- repository/
|   |-- .gitlite/
|       |-- staging/
|       |-- commits/
|       |-- metadata.txt
|
|-- utils/
|
|-- README.md

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
    |
    v
main.cpp
    |
    v
unordered_map (command router)
    |
    v
function dispatch

Example:
gitlite init

Flow:
- Check if repository/.gitlite exists
- If yes → reject initialization
- If no → create repository structure
- Write metadata file

---

## Planned Features

- add → stage files
- commit → save snapshots
- status → working tree changes
- log → commit history
- checkout → restore previous state

---

## Learning Goals

- Git internal architecture
- System-level C++ programming
- Filesystem operations
- CLI tool design
- Persistent storage systems

---

## Notes

- Educational project (not production VCS)
- State stored in repository/.gitlite
- Next milestone: staging system (add)