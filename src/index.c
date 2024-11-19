/* 
Index:
	There is an index file located at .tig/index. For each file of the project, there is an entry
	in the index containing its name (and path), its last blob object hash, and some metadata
	The index is initially loaded into memory and we work with its memory copy. The file will 
	be just a persistence measurement

	The index file is a mirror of the hashes of the files on the tree pointed by HEAD 

	Steps:
	- Create the index file in the init commadn
	- Create the interface between file and memory. Structs and funcionscA
	- implement update-index function
	- implement a diff fuction to check which files were modified since last index
		- recalculate hash and compare
		- The diff function should return some kind of structure where you can build a tree or something

	In short, heres the workflow
		- compare current file hashes with index hashes to determine which files changed
		- after the changed files are staged, compare the current hashes with the hashes in the HEAD commit.
		The different hashes will be the staged, but not yet commited files
		- On commit, create new trees for the directories that received changed files, and point to the trees
		of the unchanged directories
		- Every commit generetas a tree structure that reflects the whole repository. The commit object will point
		to the tree representing the root of the project.
*/
