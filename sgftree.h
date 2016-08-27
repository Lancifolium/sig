#ifndef _SGFTREE_H_
#define _SGFTREE_H_

#include <stdio.h>
#include <stdarg.h> // for va_list

#include "sgf_properties.h"

#define EMPTY 0
#define WHITE 1
#define BLACK 2


void *xalloc(unsigned int);

/*
 * A property of an SGF node.  An SGF node is described by a linked
 * list of these.
 */

typedef struct SGFProperty_t {
  struct SGFProperty_t *next;
  short name;
  char *value;
} SGFProperty;


typedef struct SGFNode_t {
  SGFProperty *props;
  struct SGFNode_t *parent;
  struct SGFNode_t *child;
  struct SGFNode_t *next;
} SGFNode;


/* low level functions */
SGFNode *sgfPrev(SGFNode *node);
SGFNode *sgfRoot(SGFNode *node);
SGFNode *sgfNewNode(void);
void sgfFreeNode(SGFNode *node);

int sgfGetIntProperty(SGFNode *node, const char *name, int *value);
int sgfGetFloatProperty(SGFNode *node, const char *name, float *value);
int sgfGetCharProperty(SGFNode *node, const char *name, char **value);
void sgfAddProperty(SGFNode *node, const char *name, const char *value);
void sgfAddPropertyInt(SGFNode *node, const char *name, long val);
void sgfAddPropertyFloat(SGFNode *node, const char *name, float val);
void sgfOverwriteProperty(SGFNode *node, const char *name, const char *text);
void sgfOverwritePropertyFloat(SGFNode *node, const char *name, float val);
void sgfOverwritePropertyInt(SGFNode *node, const char *name, int val);
void *xrealloc(void *pt, unsigned int size);
SGFProperty *sgfMkProperty(const char *name, const  char *value,
			   SGFNode *node, SGFProperty *last);
void sgfFreeProperty(SGFProperty *prop);

SGFNode *sgfAddStone(SGFNode *node, int color, int movex, int movey);
SGFNode *sgfAddPlay(SGFNode *node, int who, int movex, int movey);
SGFNode *sgfAddPlayLast(SGFNode *node, int who, int movex, int movey);

void sgfWriteResult(SGFNode *node, float score, int overwrite);
void sgf_write_header(SGFNode *root, int overwrite, int seed, float komi,
		      int handicap, int level, int rules);

SGFNode *sgfLabel(SGFNode *node, const char *label, int i, int j);
SGFNode *sgfLabelInt(SGFNode *node, int num, int i, int j);
SGFNode *sgfCircle(SGFNode *node, int i, int j);
SGFNode *sgfSquare(SGFNode *node, int i, int j);
SGFNode *sgfTriangle(SGFNode *node, int i, int j);
SGFNode *sgfMark(SGFNode *node, int i, int j);
SGFNode *sgfAddComment(SGFNode *node, const char *comment);
SGFNode *sgfBoardText(SGFNode *node, int i, int j, const char *text);
SGFNode *sgfBoardChar(SGFNode *node, int i, int j, char c);
SGFNode *sgfBoardNumber(SGFNode *node, int i, int j, int number);
SGFNode *sgfStartVariant(SGFNode *node);
SGFNode *sgfStartVariantFirst(SGFNode *node);
SGFNode *sgfAddChild(SGFNode *node);

SGFNode *sgfCreateHeaderNode(int boardsize, float komi, int handicap);

/* Read SGF tree from file. */
SGFNode *readsgffile(const char *filename);
/* Specific solution for fuseki */
SGFNode *readsgffilefuseki(const char *filename, int moves_per_game);

/* Write SGF tree to a file. */
void unparse_node(FILE *file, SGFNode *node);
void unparse_root(FILE *file, SGFNode *node);
void restore_property(SGFProperty *prop); // these three funs are copied from sgfnode.cpp
int writesgf(SGFNode *root, const char *filename);


/* ---------------------------------------------------------------- */
/* ---                          SGFTree                         --- */
/* ---------------------------------------------------------------- */


typedef struct SGFTree_t {
  SGFNode *root;
  SGFNode *lastnode;
} SGFTree;


void sgftree_clear(SGFTree *tree);
int sgftree_readfile(SGFTree *tree, const char *infilename);

int sgftreeBack(SGFTree *tree);
int sgftreeForward(SGFTree *tree);

void sgftreeAddPlay(SGFTree *tree, int color, int movex, int movey);
void sgftreeAddPlayLast(SGFTree *tree, int color, int movex, int movey);
void sgftreeAddStone(SGFTree *tree, int color, int movex, int movey);
void sgftreeWriteResult(SGFTree *tree, float score, int overwrite);
SGFNode *sgftreeNodeCheck(SGFTree *tree);

void sgftreeCircle(SGFTree *tree, int i, int j);
void sgftreeSquare(SGFTree *tree, int i, int j);
void sgftreeTriangle(SGFTree *tree, int i, int j);
void sgftreeMark(SGFTree *tree, int i, int j);
void sgftreeAddComment(SGFTree *tree, const char *comment);
void sgftreeBoardText(SGFTree *tree, int i, int j, const char *text);
void sgftreeBoardChar(SGFTree *tree, int i, int j, char c);
void sgftreeBoardNumber(SGFTree *tree, int i, int j, int number);
void sgftreeStartVariant(SGFTree *tree);
void sgftreeStartVariantFirst(SGFTree *tree);
void sgftreeCreateHeaderNode(SGFTree *tree, int boardsize, float komi,
			     int handicap);
void sgftreeSetLastNode(SGFTree *tree, SGFNode *lastnode);


/* ---------------------------------------------------------------- */
/* ---                         Utilities                        --- */
/* ---------------------------------------------------------------- */


int get_moveX(SGFProperty *property, int boardsize);
int get_moveY(SGFProperty *property, int boardsize);
int get_moveXY(SGFProperty *property, int *i, int *j, int boardsize);

int show_sgf_properties(SGFNode *node);
int show_sgf_tree(SGFNode *node);
int is_markup_node(SGFNode *node);
int is_move_node(SGFNode *node);
int is_pass_node(SGFNode *node, int boardsize);
int find_move(SGFNode *node);

void printSGFPRO(SGFProperty *pro);
void printNode(SGFNode *node);
void printSGF(SGFTree *tree);

/* ---------------------------------------------------------------- */
/* ---                         SGFMerge                         --- */
/* ---------------------------------------------------------------- */

int merge_two_sgffiles(SGFTree *destree, SGFTree *srctree);
int split_sgffile(SGFTree *tree, const char *filename);

#endif
