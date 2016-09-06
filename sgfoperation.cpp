#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include <stack>

#include "sgftree.h"

int write_sgfbranch(char *filename, SGFNode *branch);
int check_two_sgfnodes(SGFNode *desnode, SGFNode *srcnode);
int merge_two_sgfnodes(SGFNode *desnode, SGFNode *srcnode);

void swap(int *x,int *y) {
   int temp;
   temp = *x;
   *x = *y;
   *y = temp;
}

void quicksort(int list[],int m,int n) {
   int key,i,j,k;
   if( m < n) {
      k = (m + n) / 2;
      swap(&list[m],&list[k]);
      key = list[m];
      i = m+1; j = n;
      while(i <= j) {
         while((i <= n) && (list[i] <= key)) i++;
         while((j >= m) && (list[j] > key)) j--;
         if( i < j) swap(&list[i],&list[j]);
      }
      swap(&list[m],&list[j]);
      quicksort(list,m,j-1);
      quicksort(list,j+1,n);
   }
}

int // whether they have same move or add-stone list
check_two_sgfnodes(SGFNode *desnode, SGFNode *srcnode) { // 0 not equal; 1 equal
  SGFProperty *prop;
  int desval[300], srcval[300];
  int descount = 0, srccount = 0;
  int tmpval;
  prop = desnode->props;
  while (prop) {
    if (prop->name == SGFAB || prop->name == SGFAW ||
        prop->name == SGFB || prop->name == SGFW) {
      desval[descount] = prop->name << 16;
      desval[descount] += prop->value[0] + prop->value[1] << 8;
      descount++;
    }
    prop = prop->next;
  }
  prop = srcnode->props;
  while (prop) {
    if (prop->name == SGFAB || prop->name == SGFAW ||
        prop->name == SGFB || prop->name == SGFW) {
      srcval[srccount] = prop->name << 16;
      srcval[srccount] += prop->value[0] + prop->value[1] << 8;
      srccount++;
    }
    prop = prop->next;
  }

  if (descount == srccount) {
    quicksort(desval, 0, descount - 1);
    quicksort(srcval, 0, srccount - 1);
    for (tmpval = 0; tmpval < descount; tmpval++) {
      if (desval[tmpval] != srcval[tmpval])
        return 0;
    }
    return 1;
  }
  else return 0;
}

int
merge_two_sgfnodes(SGFNode *desnode, SGFNode *srcnode) {
  // no need check
  SGFNode *deslist, *srclist, *parent;
  parent = desnode->parent;
  deslist = desnode;
  srclist = srcnode;

}

int
merge_two_sgffiles(SGFTree *destree, SGFTree *srctree) {
  SGFNode *desnode, *srcnode;
  desnode = destree->root;
  srcnode = srctree->root;

  if (check_two_sgfnodes(desnode, srcnode)) {
    if (desnode->child == NULL) {
      desnode->child = srcnode->child;
    }
    else if (srcnode->child != NULL) {
      merge_two_sgfnodes(desnode->child, srcnode->child);
    }
  }
  else { // add additional root
    SGFNode *newroot = (SGFNode *)malloc(sizeof(SGFNode));
    newroot->child = desnode;
    desnode->next = srcnode;
    // ...
    destree->root = newroot;
  }
  return 1;
}

int
write_sgfbranch(char *filename, SGFNode *branch) {
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

int
split_sgffile(SGFTree *tree, const char *filename) {
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
