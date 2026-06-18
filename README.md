GitLite

GitLite is a lightweight Git-inspired version control system written in C++ for learning how version control systems work internally.

It currently supports a command-line interface with a modular command system and repository initialization.

------------------------------------------------------------

CURRENT STATUS

- CLI command dispatcher implemented
- Modular command architecture (each command in separate files)
- Repository initialization working
- Persistent storage using filesystem (.gitlite directory)

------------------------------------------------------------

WORKING COMMANDS

gitlite version
→ Shows version and available commands

gitlite init
→ Creates repository inside repository/.gitlite
→ If already exists, prints error message

------------------------------------------------------------

REPOSITORY STRUCTURE

GitLite/
|
|-- src/
|   |-- main.cpp
|
|-- commands/
|   |-- version.cpp / .h
|   |-- init.cpp / .h
|   |-- add.cpp / .h
|   |-- commit.cpp / .h
|   |-- log.cpp / .h
|   |-- checkout.cpp / .h
|
|-- repository/
|   |-- .gitlite/
|       |-- staging/
|       |-- commits/
|       |-- metadata.txt
|
|-- utils/
|-- README.txt

------------------------------------------------------------

FLOW OF EXECUTION

User Input
    |
    v
main.cpp (CLI parser)
    |
    v
unordered_map command router
    |
    v
calls respective command function
    |
    v
executes command logic

Example:

gitlite init
→ check if repository/.gitlite exists
→ if yes: reject
→ if no: create folder structure + metadata

------------------------------------------------------------

DESIGN GOALS

- Learn how Git works internally
- Build CLI-based system in C++
- Understand file system persistence
- Practice modular software design
- Implement version control step by step

------------------------------------------------------------

NEXT FEATURES

- add (staging system)
- commit (snapshot storage)
- status (working tree state)
- log (history tracking)
- checkout (restore versions)

------------------------------------------------------------

NOTE

This is an educational project, not a production-ready version control system.