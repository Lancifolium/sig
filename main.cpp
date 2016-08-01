#include "sgftree.h"
#include "sgf_properties.h"

int main(void) {
	SGFTree sgftree;
	sgftree.root = readsgffile("tmp.sgf");

}
