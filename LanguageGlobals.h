#ifndef __LANGUAGE_GLOBALS_H__
#define __LANGUAGE_GLOBALS_H__

struct buffer_t
{
    char* data;
    int   size;
};

struct op_t
{
    const char* name;
    int         code;
};

const int OP_CNT = 10;

const op_t operations[OP_CNT] = {{"+", 1},   {"-", 2},   {"*", 3}, {"/", 4}, {"=", 5}, {"(", 6},{")", 7},
                                 {"sin", 8}, {"cos", 9}, {"if", 10}};

enum types_t
{
    NUM = 0,
    ID  = 1,
    OP  = 2
};

const int ID_MAX_NAME_LEN = 10;

struct token_t
{
    types_t type;
    char    id[ID_MAX_NAME_LEN];
    int     code;
    double  num;
};

const int MAX_TOKENS_CNT = 20;

struct tokens_t
{
    int     cnt = 0;
    token_t array[MAX_TOKENS_CNT];
};

enum return_codes
{
    OK    = 0,
    ERROR = -1
};

#endif
