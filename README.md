Version Control System (VCS):
    
    A lightweight version control system inspired by Git, designed to track changes in files and manage source code efficiently.


Instructions for generating the executable:

    execute "make" command in the terminal, upon which "mygit" executable is created in "test_folder"


Commands:
    
    init: Initializes a new repository, creating the necessary structure for tracking changes.

    hash-object: Computes and stores a hash for a file's content, creating a unique identifier.

    cat-file: Displays the content of a specified object (file or commit or tree object) in the repository.

    write-tree: Records the current index state as a tree object, capturing the working directory snapshot.

    ls-tree: Lists the contents of a specified tree object, showing files and their hashes.

    add: Stages changes in the working directory for the next commit.

    commit: Records staged changes with a unique identifier, creating a new commit object.

    checkout: Switches to a specified commit, updating the working directory accordingly.

    log: Displays the commit history, showing each commit's id/hash, parent commit id/hash, tree object of that working directory, author, date, and message for easy review of changes.


The above commands can be executed in the same structure of the actual git commands. For example:

    ./mygit init

    ./mygit hash-object [-w] test.txt

    ./mygit cat-file <flag> <file_sha>

    ./mygit write-tree

    ./mygit ls-tree [--name-only] <tree_sha>

    ./mygit add .
    ./mygit add main.cpp utils.cpp

    ./mygit commit -m "Commit message"
    ./mygit commit

    ./mygit log

    ./mygit checkout <commit_sha>


Use case of each file:

    add_to_index.hpp: given a file path and hash, this function adds that entry to the index file

    add.hpp: contains the main functionality of the "add" command

    cat_file.hpp: contains the main functionality of the "cat-file" command

    checkout.hpp: contains the main functionality of the "checkout" command

    commit.hpp: contains the main functionality of the "commit" command

    compress.hpp: given source file and destination file, this function compresses the source file and stores it in the destination file

    create_directory.hpp: creates a directory given its path

    create_file.hpp: creates a file given its path

    decompress.hpp: given the source file, this function decompresses the file and prints the output

    delete_all_files.hpp: deletes all files in the current working directory

    directory_contents.hpp: given a directory, this function returns all the files/directories inside this directory

    file_size.hpp: given a file path, this function returns its size

    hash_object.hpp: contains the main functionality of the "hash-object" command

    init.hpp: contains the main functionality of the "init" command

    log.hpp: contains the main functionality of the "log" command

    ls_tree.hpp: contains the main functionality of the "ls-tree" command

    random_number_generator.hpp: generates a random number between given bounds
    
    repo_existence.hpp: returns a boolean representing repository is already present or not

    save_object.hpp: given hash, it creates a file in the .mygit/objects folder

    sha1.hpp: given a file, it generates SHA1 hash for it

    write_tree.hpp: contains the main functionality of the "write-tree" command