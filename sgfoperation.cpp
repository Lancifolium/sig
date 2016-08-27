#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include <stack>

#include "sgftree.h"

int write_sgfbranch(char *filename, SGFNode *branch);


int merge_two_sgffiles(SGFTree *destree, SGFTree *srctree) {
  //destree->root->

}

int write_sgfbranch(char *filename, SGFNode *branch) {
  std::stack<SGFNode *> brsave;
  SGFNode *current = branch;
  while (current != NULL) { // trace branch
    brsave.push(current);
    current = current->parent;
  }

  FILE *wrl = fopen(filename, "w");

  //fprintf(wrl, "(;GM[1]AP[StoneBase:SGFParser.3.0.1]SZ[19]CA[gb2312]HA[0]");

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
  char __filename[256];
  int __filenum = 0;
  //sprintf(__filename, "%s%d.sgf", 10);
  SGFNode *current;
  current = tree->root;
  std::stack<SGFNode *> iterstk;
  iterstk.push(tree->root);

  while (!iterstk.empty()) {
    current = iterstk.top();
    iterstk.pop();

    /*
    while (current->child != NULL) {
      if (current->next != NULL) iterstk.push(current->next);
      current = current->child;
    }
    if (current->next != NULL) iterstk.push(current->next);
    //*/

    while (current != NULL) {
      if (current->next != NULL) iterstk.push(current->next);
      if (current->child == NULL) {
        sprintf(__filename, "%s_%d.sgf", filename, __filenum++);
        if (__filenum < 800)
        write_sgfbranch(__filename, current);
      }
      current = current->child;
    }
  }

}
