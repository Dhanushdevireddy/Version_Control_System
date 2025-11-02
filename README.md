# MyGit — Lightweight Version Control System

**MyGit** is a lightweight version control system inspired by Git. It is designed to efficiently track changes in files and manage source code. This project provides a simplified implementation of core Git functionalities such as commit tracking, branching, and object management.

---

## Features

* Initialize a new repository
* Track and store file changes using SHA1 hashes
* Manage staging and commits
* Browse repository history
* Checkout specific commits
* Work with tree and blob objects

---

## Building the Project

To build the executable:

```bash
make
```

After successful compilation, the `mygit` executable will be created in the `test_folder` directory.

---

## Usage

MyGit supports commands similar to Git. Each command can be executed from the terminal in the following format:

### Initialize a Repository

```bash
./mygit init
```

Initializes a new repository by creating the necessary structure for tracking changes.

---

### Hash Object

```bash
./mygit hash-object [-w] <file_path>
```

Computes and stores a hash for a file’s content, creating a unique identifier.
The `-w` flag writes the object to the repository.

---

### Cat File

```bash
./mygit cat-file <flag> <object_sha>
```

Displays the content of the specified object (file, commit, or tree).

---

### Write Tree

```bash
./mygit write-tree
```

Records the current index state as a tree object, capturing the working directory snapshot.

---

### List Tree

```bash
./mygit ls-tree [--name-only] <tree_sha>
```

Lists the contents of a tree object, showing files and their hashes.
The `--name-only` flag displays only file names.

---

### Add Files

```bash
./mygit add .
./mygit add <file1> <file2> ...
```

Stages changes in the working directory for the next commit.

---

### Commit Changes

```bash
./mygit commit -m "Commit message"
```

Creates a new commit object recording the staged changes.

---

### View Log

```bash
./mygit log
```

Displays the commit history, showing:

* Commit ID (hash)
* Parent commit ID (if any)
* Tree object hash
* Author
* Date
* Commit message

---

### Checkout Commit

```bash
./mygit checkout <commit_sha>
```

Switches to the specified commit and updates the working directory accordingly.

---

## File Overview

| File                            | Description                                                 |
| ------------------------------- | ----------------------------------------------------------- |
| **add_to_index.hpp**            | Adds a file entry (path and hash) to the index file.        |
| **add.hpp**                     | Implements the functionality of the `add` command.          |
| **cat_file.hpp**                | Implements the functionality of the `cat-file` command.     |
| **checkout.hpp**                | Implements the functionality of the `checkout` command.     |
| **commit.hpp**                  | Implements the functionality of the `commit` command.       |
| **compress.hpp**                | Compresses a source file and stores it in the destination.  |
| **create_directory.hpp**        | Creates a directory at a specified path.                    |
| **create_file.hpp**             | Creates a file at a specified path.                         |
| **decompress.hpp**              | Decompresses a file and prints its output.                  |
| **delete_all_files.hpp**        | Deletes all files in the current working directory.         |
| **directory_contents.hpp**      | Returns all files and directories inside a given directory. |
| **file_size.hpp**               | Returns the size of a given file.                           |
| **hash_object.hpp**             | Implements the functionality of the `hash-object` command.  |
| **init.hpp**                    | Implements the functionality of the `init` command.         |
| **log.hpp**                     | Implements the functionality of the `log` command.          |
| **ls_tree.hpp**                 | Implements the functionality of the `ls-tree` command.      |
| **random_number_generator.hpp** | Generates a random number within given bounds.              |
| **repo_existence.hpp**          | Checks if a repository already exists.                      |
| **save_object.hpp**             | Creates a file in `.mygit/objects` for the given hash.      |
| **sha1.hpp**                    | Generates a SHA1 hash for a file.                           |
| **write_tree.hpp**              | Implements the functionality of the `write-tree` command.   |

---

## Repository Structure

When initialized, the repository creates a structure similar to:

```
.mygit/
├── objects/
├── refs/
└── HEAD
```

* **objects/** — stores all versioned objects (blobs, trees, commits)
* **refs/** — stores references to commits (like branches)
* **HEAD** — points to the current commit
