#include "sgftree.h"
#include "sgf_properties.h"

int main(void) {
	SGFTree sgftree;
	// sgftree.root = readsgffile("form.SGF");
	fprintf(stdout, "before all$$$$$$$$$$\n");
	sgftree_clear(&sgftree);
	sgftree_readfile(&sgftree, "tmp.sgf");
	fprintf(stdout, "before output----------\n");
	printSGF(&sgftree);
}
