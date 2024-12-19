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

const int OP_CNT = 12;

const op_t operations[OP_CNT] = {{"+", 1},   {"-", 2},   {"*", 3},   {"/", 4}, {"=", 5}, {"(", 6},{")", 7},
                                 {"sin", 8}, {"cos", 9}, {"if", 10}, {"$", 11}, {";", 12}};

enum types_t
{
    NUM = 1,
    ID  = 2,
    OP  = 3
};

const int ID_MAX_NAME_LEN = 10;

struct Node_t
{
    types_t type;
    char    id_val[ID_MAX_NAME_LEN];
    int     op_val;
    double  num_val;
    Node_t* left;
    Node_t* right;
};

struct tokens_t
{
    int     cnt;
    int     curr_ptr;
    int     size;
    Node_t* array;
};

enum return_codes
{
    OK    = 0,
    ERROR = -1
};

#endif
