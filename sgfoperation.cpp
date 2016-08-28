#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include <stack>

#include "sgftree.h"

int write_sgfbranch(char *filename, SGFNode *branch);


int merge_two_sgffiles(SGFTree *destree, SGFTree *srctree) {

}

int write_sgfbranch(char *filename, SGFNode *branch) {
  std::stack<SGFNode *> brsave;
  SGFNode *current = branch;
  while (current != NULL) { // trace branch
    brsave.push(current);
    current = current->parent;
  }

  FILE *wrl = fopen(filename, "w");
  if (brsave.empty()) return 1; // empty tree

  fprintf(wrl, "(");
  unparse_root(wrl, brsave.top());
  restore_property(brsave.top()->props);
  brsave.pop();
  while (!brsave.empty()) {
    unparse_node(wrl, brsave.top());
    restore_property(brsave.top()->props);
    brsave.pop();
  }
  fprintf(wrl, "\n)");
  fclose(wrl); //
}

int split_sgffile(SGFTree *tree, const char *filename) {
  char namebuff[256];
  int namenum = 0;
  SGFNode *current;
  current = tree->root;
  std::stack<SGFNode *> iterstk;
  iterstk.push(tree->root);

  while (!iterstk.empty()) {
    current = iterstk.top();
    iterstk.pop();

    while (current != NULL) {
      if (current->next != NULL)
        iterstk.push(current->next);
      if (current->child == NULL) {
        sprintf(namebuff, "%s_%d.sgf", filename, namenum++);
        //if (namenum < 800)
        write_sgfbranch(namebuff, current);
      }
      current = current->child;
    } // end current != NULL
  } // end iteration stack

}
