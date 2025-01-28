## Tree objects and index: relationships and flow

When you run _git update-index_, the all the modified files are hashed and the
index entries are updated to the new hashes. If you use _git restore --staged_
to bring back the previous index state (before the command update-index was run),
git uses the commit pointed by HEAD to reconstruct the index entries

After updating the index, running _git write tree_ will write a sequence of tree objects
representing the whole repository on the object database. Note that this will just store them,
but no commits will be created. To create a commit object, you can run a command called _git commit-tree_
which receives a tree object as argument, and defines a parent commit.

*Note:* Both the index restoration (using git restore) and the tree creation (using git write_tree)
can be heavy operations. Because of that, the index has whats called a cache tree, which is an in-memory recursive tree that mirrors the tree pointed by HEAD. 

*Note for further development:* Think of the best way to use the cache-tree :D

### References:
https://git-scm.com/book/en/v2/Git-Internals-Git-Objects
https://git-scm.com/docs/git-write-tree
https://git-scm.com/docs/git-commit-tree
https://git-scm.com/docs/git-restore
https://git-scm.com/docs/index-format
