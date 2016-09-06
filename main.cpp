#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#ifdef HAVE_UNISTD_H
/* For isatty(). */
#include <unistd.h>
#else
//#include <io.h>
#endif

#if TIME_WITH_SYS_TIME
# include <sys/time.h>
# include <time.h>
#else
# if HAVE_SYS_TIME_H
#  include <sys/time.h>
# else
#  include <time.h>
# endif
#endif

#include "sgftree.h"

int
main(int argc, char *argv[])
{
  SGFTree sgftree;

  //char *infilename = "form.SGF";
  fprintf(stderr, "%d %s\n", argc, argv[1]); ////////////
  char *infilename = argv[1];
  //char *infilename = "tmp.sgf";

  sgftree_clear(&sgftree);

  sgftree_readfile(&sgftree, infilename);
  printSGF(&sgftree);
  //show_sgf_tree(sgftree.root);
  //writesgf(sgftree.root, "last.sgf");
  //sgftree.root->child;

  split_sgffile(&sgftree, "szp");


  sgfFreeNode(sgftree.root);

  return 0;
}  /* end main */
