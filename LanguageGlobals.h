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

const int OP_CNT = 17;

const op_t operations[OP_CNT] = {{"win", 1},   {"lose", 2},   {"star", 3}, {"goalkeeper", 4}, {"draw", 5},
                                 {"start", 6}, {"whistle", 7}, {"sin", 8},  {"cos", 9}, {"VAR", 10},
                                 {"PSG", 11},  {"Break", 12}, {"broadcast", 13}, {"July", 14},
                                 {"May", 15},  {"uefa", 16},  {"double", 17}};

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
