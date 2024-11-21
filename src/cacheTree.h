struct CacheTree;
struct CacheSubTree{
	struct CacheTree* tree;
};

struct CacheTree {
	int entries; //invalid = -1
	CacheSubTree** subtrees;
} ;
