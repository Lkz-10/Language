#ifndef __RECURSIVE_DESCENT_H__
#define __RECURSIVE_DESCENT_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "LanguageGlobals.h"

void    SyntaxError   (tokens_t* tokens, const char* expected_operator);
Node_t* GetNumber     (tokens_t* tokens);
Node_t* GetVariable   (tokens_t* tokens);
Node_t* GetFunction   (tokens_t* tokens);
Node_t* GetP          (tokens_t* tokens);
Node_t* GetT          (tokens_t* tokens);
Node_t* GetE          (tokens_t* tokens);
Node_t* GetAssignment (tokens_t* tokens);
Node_t* GetGrammar    (tokens_t* tokens);
int     OperatorCode  (const char* _operator);

#endif
