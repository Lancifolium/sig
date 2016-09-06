#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include <unistd.h>
#include <getopt.h>

#include <stdarg.h>

#ifdef HAVE_UNISTD_H
/* For isatty(). */
#include <unistd.h>
#else
#include <io.h>
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

void
print_help_info() {
  printf("Usages: ./run \n"
         "\t-h, --help    print this help info \n"
         "\t-m, --merge   merge two sgf files \n");
}

char
option_choice(const char *arg) {
  if (arg[0] == '-') {
    return arg[1];
  }
  else return 0;
}

int
main(int argc, char *argv[])
{
  SGFTree sgftree;
  char **val;
  val = (char **)malloc(sizeof(char *));
  char aaa[] = "kjflsjf";
  switch (option_choice(argv[1])) {
  case 'h':
    print_help_info();
    break;
  case 's':
    if (argc < 2) {
      printf("No sgf file! \n");
      exit(-1);
    }
    sgftree_clear(&sgftree);
    sgftree_readfile(&sgftree, argv[2]);
    //printSGF(&sgftree);
    if (argc >= 3) split_sgffile(&sgftree, argv[3]);
    else split_sgffile(&sgftree, "sgf");
    sgfFreeNode(sgftree.root);
    break;
  case 'm':
    if (argc < 3) {
      printf("No 2 sgf files! \n");
      exit(-1);
    }
    break;
  case 't':
    sgftree_clear(&sgftree);
    sgftree_readfile(&sgftree, argv[2]);


    *val = aaa;
    printf("-------------%s\n", *val);
    if (sgfGetCharProperty(sgftree.root, "AB", val))
      printf("%s\n", *val);
    show_sgf_properties(sgftree.root);
    sgfFreeNode(sgftree.root);
    break;
  default:
    break;
  }

  return 0;
}  /* end main */
