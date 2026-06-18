GITLITE
--------------------------------------------------

### DESCRIPTION
GitLite is a lightweight Git-inspired version control system written in C++.
It is built for understanding how version control systems work internally.

--------------------------------------------------

## CURRENT STATUS
- CLI command system working
- Command routing using unordered_map
- Modular command structure
- Repository initialization implemented
- Persistent storage using .gitlite folder

--------------------------------------------------

## WORKING COMMANDS

### gitlite version
-> prints version and available commands

### gitlite init
-> creates repository in repository/.gitlite
-> prevents reinitialization if already exists

--------------------------------------------------

## FLOW OF EXECUTION

User Input
  |
  v
main.cpp (parse command)
  |
  v
command router (unordered_map)
  |
  v
calls command function
  |
  v
executes logic

## EXAMPLE:

gitlite init
  -> check repository/.gitlite exists
  -> if exists: reject
  -> else: create folder structure
  -> write metadata

--------------------------------------------------

## DESIGN GOALS
- Learn Git internals
- Build CLI tools in C++
- Understand filesystem persistence
- Practice modular system design
- Implement version control step by step

--------------------------------------------------

## NEXT FEATURES
- add (staging system)
- commit (snapshot system)
- status (working tree tracking)
- log (history tracking)
- checkout (restore versions)

--------------------------------------------------

## NOTE
This project is for learning purposes only.
Not a production version control system.
