# GitLite

GitLite is a lightweight Git-inspired version control system built in C++. It is designed to help understand the core concepts of version control, including file tracking, commits, and repository management.

## Features (V1)

* Initialize a repository
* Add files for tracking
* Create commits
* View repository status
* View commit history
* Restore previous commits

## Commands

```bash
gitlite version
gitlite init
gitlite add <file>
gitlite commit "<message>"
gitlite status
gitlite log
gitlite checkout <commit-id>
```
## Code Architecture

GitLite/
│
├── src/
│   └── main.cpp
│
├── commands/
│   ├── init.h
│   ├── init.cpp
│   │
│   ├── add.h
│   ├── add.cpp
│   │
│   ├── commit.h
│   ├── commit.cpp
│   │
│   ├── log.h
│   ├── log.cpp
│   │
│   ├── status.h
│   ├── status.cpp
│   │
│   └── checkout.h
│   └── checkout.cpp
│
├── repository/
│   ├── Repository.h
│   └── Repository.cpp
│
├── utils/
│   ├── FileManager.h
│   └── FileManager.cpp
│
├── README.md
└── .gitignore

## Tech Stack

* C++
* STL
* File System Library

## Status

Version 1 (In Development)
