# ⚡ GitLite
### A Mini Version Control System Built from Scratch in C++17

> 🔍 **Ever wondered what Git does behind `add`, `commit`, and `checkout`?**  
> I built the core mechanics myself — one hash, object, and commit at a time.

`⚙️ 8 Commands` · `🧠 Custom Hashing` · `📦 Object Storage` · `🌿 Branching`

## 🚀 Implemented Commands

`version` · `init` · `add` · `commit` · `branch` · `log` · `status` · `checkout`

## 🛠️ Get Started

**1. Clone the repository**

```bash
git clone https://github.com/Akshaya-Sri-Tech/GitLite.git
cd GitLite
```

**2. Compile**

Requires `g++` with C++17 support.

```bash
g++ src/main.cpp commands/*.cpp utils/*.cpp -o gitlite
```

**3. Run**

```bash
./gitlite init
```

GitLite creates a `repository/` directory and initializes its internal `.gitlite/` metadata. Run subsequent commands using the executable from the project directory.

## 🗂️ Inside the Repository

After `./gitlite init`:

```text
repository/
└── .gitlite/
    ├── HEAD
    ├── index
    ├── objects/
    └── refs/
        └── heads/
            └── main
```

- 📍 **`HEAD`** — identifies the current branch.
- 📝 **`index`** — maps staged filenames to object hashes.
- 📦 **`objects/`** — stores file snapshots and commit objects, organized by hash prefix.
- 🌿 **`refs/heads/main`** — holds the commit hash referenced by `main`.

## ⚙️ The Mechanics Behind GitLite

```text
 Working File
      │
      ▼
 Custom Content Hash ──► Object Store
                              ▲
                              │
                        Staging Index
                              │
                              ▼
                         Commit Object
                      (files + parent +
                       message + timestamp)
                              │
                              ▼
                       Branch Reference
                              ▲
                              │
                             HEAD
```

- 🔐 **Content addressing:** file contents are hashed to identify stored snapshots.
- 📥 **Staging:** the index records which file versions are prepared for a commit.
- 🧬 **Commit ancestry:** each commit points to its parent, forming a history that `log` can traverse.
- 🌿 **Branch references:** branches point to commits instead of maintaining separate copies of files.
- 🔄 **Checkout:** switches the active branch and restores files from its referenced commit.

## 📁 Project Structure

```text
GitLite/
├── commands/      # Individual command implementations
├── src/
│   └── main.cpp   # Entry point
├── utils/         # Repository and shared utilities
└── README.md
```

## 🔭 Next Up

- [ ] 🛡️ Replace the custom rolling hash with a stronger content hash.
- [ ] 🔎 Improve tracked-file and working-tree change detection.
- [ ] 🗑️ Add file removal and restoration commands.
- [ ] 🔀 Implement merging and conflict resolution.
- [ ] 🌳 Introduce dedicated tree objects.

## 🧰 Tech Stack

**C++17 · STL · `std::filesystem` · File I/O · g++**

C++ gave me direct control over filesystem operations, object storage, and repository metadata — the perfect way to explore version control below the command-line interface.

---

🧪 **A learning project built by implementing the internals, not wrapping Git.** GitLite uses a custom rolling hash and simplified object formats, so it is Git-inspired rather than compatible with Git repositories.
