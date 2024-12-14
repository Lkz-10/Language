#ifndef __LEXICAL_ANALYSIS_H__
#define __LEXICAL_ANALYSIS_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "LanguageGlobals.h"

int FillTokens (tokens_t* tokens, const buffer_t* buffer);
int IsKeyWord  (char** word);

#endif
