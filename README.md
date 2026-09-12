# GitLite

> A lightweight Git-inspired version control system built from scratch in C++ for exploring the internal architecture of modern version control systems.

GitLite is a learning-focused implementation of a version control system that recreates Git's core concepts from scratch using modern C++. Instead of using existing Git libraries, every feature is implemented manually to explore how repositories, staging areas, object storage, commits, and version history work under the hood.

> **Project Status:** 🚧 Version 1 (In Development)

---

# Why GitLite?

Git is one of the most widely used developer tools, but most programmers interact with it only through commands.

The goal of GitLite is to understand what actually happens internally when commands like `git init`, `git add`, or `git commit` are executed by building those mechanisms from scratch.

---

# Features

### Implemented

* ✅ Command parsing using `argc`, `argv`, and `unordered_map`
* ✅ `version`
* ✅ `init`
* ✅ `add <filename>`
* ✅ `commit`
* ✅ `log`
* ✅ Repository initialization
* ✅ Automatic `.gitlite` directory creation
* ✅ Staging area implementation
* ✅ Object storage using content-based hashing
* ✅ Metadata management

### Under Development

* 🚧 `status`
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
 └──.gitlite/
        ├── HEAD
        ├── index
        ├── objects/
        └── refs/
                └── heads/
                        └── main
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

## Commit Changes

```bash
./gitlite commit "commit message"
```

Creates a commit from the currently staged files.

The commit process works by:

1. Reading the staging `index`.
2. Collecting the staged file information.
3. Reading the current `HEAD` to find the parent commit.
4. Creating commit metadata including the staged files, parent commit, timestamp, and commit message.
5. Generating a content-based hash for the commit.
6. Storing the commit object inside `.gitlite/objects/`.
7. Updating the current branch to point to the new commit.
8. Clearing the staging `index` after a successful commit. 📦

Example:

```bash
./gitlite add sample1.txt
./gitlite commit "Added sample1"
```

A commit object contains information similar to:

```text
tree:
<staged file information>

parent: <previous commit hash>

timestamp: <commit timestamp>

message: <commit message>
```

The first commit has no parent:

```text
parent: none
```

Subsequent commits store the previous commit hash as their parent, creating the foundation for commit history. 🔗

---

## View Commit History

```bash
./gitlite log
```

Displays the commit history of the current branch.

The `log` command works by:

1. Reading `HEAD` to determine the current branch.
2. Reading the current commit hash from the branch reference.
3. Opening the corresponding commit object from `.gitlite/objects/`.
4. Reading the commit message and timestamp.
5. Reading the parent commit hash.
6. Following the parent commit until reaching the first commit.
7. Displaying the commits from newest to oldest.

Example:

```text
./gitlite log
```

Output:

```text
commit 182736451
Date:   Sat Sep 12 14:30:25 2026

    Added sample2

commit 928374651
Date:   Sat Sep 12 14:12:03 2026

    Added sample1

commit 472819305
Date:   Sat Sep 12 13:45:17 2026

    Initial commit
```

Each commit stores its parent commit hash, creating a linked chain of commit history:

```text
HEAD
 │
 ▼
Commit 3
 │
 ▼
Commit 2
 │
 ▼
Commit 1
 │
 ▼
none
```

The `log` command traverses this chain backwards to reconstruct the commit history.

---

# How GitLite Works

```text
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
        │
        ▼
gitlite commit
        │
        ▼
Create Commit Object
        │
        ▼
Update Branch Reference
        │
        ▼
Clear Staging Index
```

---

# Current Object Storage

GitLite currently stores staged file snapshots inside:

```text
repository/.gitlite/staging/objects/
```

Objects are organized using the first two characters of the generated hash, similar to Git's object storage layout.

Example:

```text
objects/
└── 52/
    └── 52130542502443599
```

Commit objects are stored inside:

```text
repository/.gitlite/objects/
```

using the same hash-based directory structure. 📁

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
* [x] commit
* [ ] status
* [x] log
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

GitLite is inspired by Git and is built purely for educational purposes to explore the internal design of Git.
