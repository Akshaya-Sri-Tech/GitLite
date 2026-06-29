# GitLite

> A lightweight Git-inspired version control system built from scratch in C++ for exploring the internal architecture of modern version control systems.

GitLite is a learning-focused implementation of a version control system that recreates Git's core concepts from scratch using modern C++. Instead of using existing Git libraries, every feature is implemented manually to explore how repositories, staging areas, object storage, commits, and version history work under the hood.

> **Project Status:** 🚧 Version 1 (In Development)

---

## Why GitLite?

Git is one of the most widely used developer tools, but most programmers interact with it only through commands.

The goal of GitLite is to understand what actually happens internally when commands like `git init`, `git add`, or `git commit` are executed by building those mechanisms from scratch.

---

# Features

### Implemented

* ✅ Command parsing using `argc`, `argv`, and `unordered_map`
* ✅ `version`
* ✅ `init`
* ✅ `add <filename>`
* ✅ Repository initialization
* ✅ Automatic `.gitlite` directory creation
* ✅ Staging area implementation
* ✅ Object storage using content-based hashing
* ✅ Metadata management

### Under Development

* 🚧 `commit`
* 🚧 `status`
* 🚧 `log`
* 🚧 `checkout`

---

# Tech Stack

* **Language:** C++17
* **Compiler:** g++ (GCC 16.1.0)

##Libraries Used

  * iostream
  * fstream
  * filesystem
  * string
  * unordered_map
  * functional

---

# Project Structure

```text
GitLite/
│
├── commands/
│   ├── add.cpp
│   ├── add.h
│   ├── init.cpp
│   ├── init.h
│   ├── version.cpp
│   ├── version.h
│   └── ...
│
├── src/
│   └── main.cpp
│
├── utils/
│
├── README.md
└── gitlite.exe
```

After running:

```bash
./gitlite init
```

GitLite creates the following repository structure:

```text
repository/
└── .gitlite/
    ├── staging/
    │   ├── objects/
    │   └── index.txt
    │
    ├── commits/
    │
    └── metadata.txt
```

---

# Commands

## Display Version

```bash
./gitlite version
```

---

## Initialize Repository

```bash
./gitlite init
```

Creates the internal `.gitlite` directory structure required to manage version control.

---

## Stage a File

```bash
./gitlite add <filename>
```

Stages a snapshot of the specified file by:

1. Reading the file contents.
2. Generating a content-based hash.
3. Creating an object inside the staging area.
4. Recording the file and hash in `index.txt`.

---

# How GitLite Works

```
Working Directory
        │
        │
        ▼
gitlite add
        │
        ▼
Read File
        │
        ▼
Generate Content Hash
        │
        ▼
Store Object
(repository/.gitlite/staging/objects/)
        │
        ▼
Update index.txt
        │
        ▼
Ready for Commit
```

---

# Current Object Storage

GitLite currently stores staged file snapshots inside:

```
repository/.gitlite/staging/objects/
```

Objects are organized using the first two characters of the generated hash, similar to Git's object storage layout.

Example:

```text
objects/
└── 52/
    └── 52130542502443599
```

---

# Current Hashing

GitLite currently uses a custom content-based rolling hash:

```cpp
hash_val=hash_val*31+static_cast<unsigned char>(ch);
```

This implementation is temporary and is intended for learning purposes.

Future versions will replace it with Git's SHA-1 style object hashing.

---

# Learning Objectives

This project is being built to understand:

* Version Control Systems
* Repository Architecture
* Content Addressable Storage
* Object Databases
* Blob Objects
* Staging Areas
* Commit History
* File System Operations
* Command Line Interfaces in C++
* Git Internals

---

# Roadmap

## Version 1

* [x] version
* [x] init
* [x] add
* [ ] commit
* [ ] status
* [ ] log
* [ ] checkout

## Version 2

Planned improvements include:

* SHA-1 object hashing
* Better staging/index management
* Branch support
* Merge
* Restore
* Remove (`rm`)
* Move (`mv`)
* Tree objects
* Merge conflict handling
* Performance improvements

---

# Note

GitLite is a learning project inspired by Git.

It is **not** intended to be a full replacement for Git, but rather an educational implementation focused on understanding the core ideas behind modern version control systems.

---

# Acknowledgements

GitLite is inspired by Git and is built purely for educational purposes to explore the internal design of version control systems.

---

