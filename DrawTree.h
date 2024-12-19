#ifndef __DRAW_TREE_H__
#define __DRAW_TREE_H__

#include <stdio.h>
#include <stdlib.h>

#include "LanguageGlobals.h"

int         DrawTree        (Node_t* root, const char* file_name);
int         DrawNode        (Node_t* node, FILE* file_ptr);
const char* CodeToOperator  (int code);

#endif
