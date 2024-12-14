#include "LexicalAnalysis.h"

int FillTokens(tokens_t* tokens, const buffer_t* buffer)
{
    if (!tokens || !buffer)
    {
        fprintf(stderr, "Error in FillTokens(): tokens(%p), buffer(%p)!\n", tokens, buffer);
        return -1;
    }

    char* cur_ptr = buffer->data;

    while (cur_ptr < buffer->data + buffer->size)
    {
        if (tokens->cnt >= MAX_TOKENS_CNT)
        {
            fprintf(stderr, "Error: too many tokens(max %d)!\n", MAX_TOKENS_CNT);
            return ERROR;
        }

        while (isspace(*cur_ptr)) cur_ptr++;

        if (cur_ptr >= buffer->data + buffer->size) break;

        if (isdigit(*cur_ptr))
        {
            double num = strtod(cur_ptr, &cur_ptr);

            tokens->array[tokens->cnt].type = NUM;
            tokens->array[tokens->cnt].num  = num;

            (tokens->cnt)++;

            //printf("New num: %lg\n",  tokens->array[tokens->cnt].num);

            continue;
        }

        int word_code = IsKeyWord(&cur_ptr);

        if (word_code < 0) return ERROR;

        if (word_code > 0)
        {
            tokens->array[tokens->cnt].type = OP;
            tokens->array[tokens->cnt].code = word_code;

            (tokens->cnt)++;

//             printf("Word_code: %d\ntoks_code: %d\ntoks_cnt:  %d\n", word_code,
//                     tokens->array[tokens->cnt - 1].code, tokens->cnt);
//
//             printf("New op: %d\n", tokens->array[tokens->cnt - 1].code);

            continue;
        }

        if (isalpha(*cur_ptr))
        {
            tokens->array[tokens->cnt].type = ID;

            int id_name_len = 0;

            sscanf(cur_ptr, "%s%n", tokens->array[tokens->cnt].id, &id_name_len);

            cur_ptr += id_name_len;

            (tokens->cnt)++;

            //printf("New id: %s\n", tokens->array[tokens->cnt].id);

            continue;
        }

        fprintf(stderr, "FillTokens() error: unknown token(%s)\n", cur_ptr);

        return ERROR;
    }

    return OK;
}

int IsKeyWord(char** word)
{
    if (!word)
    {
        fprintf(stderr, "Error in IsKeyWord(): word(%p)!\n", word);
        return ERROR;
    }

    int size = 0;

    if (!isalnum(**word))
    {
        (*word)++;
        size = 1;
    }

    else
    {
        while (isalnum(**word))
        {
            (*word)++;
            size++;
        }
    }

    for (int i = 0; i < OP_CNT; i++)
    {
        if (strncmp((*word) - size, operations[i].name, size) == 0)
        {
            //printf("Recognized operation: %d\nCurrent character: '%c'\n", operations[i].code, **word);
            return operations[i].code;
        }
    }

    (*word) -= size;

    return 0;
}
