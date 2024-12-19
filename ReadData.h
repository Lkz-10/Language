#ifndef __READ_DATA_H__
#define __READ_DATA_H__

#include <stdio.h>
#include <stdlib.h>

#include "LanguageGlobals.h"

int ReadData    (const char* file_name, buffer_t* buffer);
int BufferDtor  (buffer_t* buffer);

#endif
