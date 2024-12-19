#include "LexicalAnalysis.h"

int FillTokens(tokens_t* tokens, const buffer_t* buffer)
{
    if (!tokens || !buffer)
    {
        fprintf(stderr, "Error in FillTokens(): tokens(%p), buffer(%p)!\n", tokens, buffer);
        return -1;
    }

    char* curr_ptr = buffer->data;

    while (curr_ptr < buffer->data + buffer->size)
    {
        SkipRubbish(&curr_ptr, buffer->data + buffer->size);

        if (curr_ptr >= buffer->data + buffer->size) break;

        if (isdigit(*curr_ptr))
        {
            double num = strtod(curr_ptr, &curr_ptr);

            tokens->array[tokens->cnt].type = NUM;
            tokens->array[tokens->cnt].num_val  = num;

            (tokens->cnt)++;

            //printf("New num: %lg\n",  tokens->array[tokens->cnt].num_val);

            continue;
        }

        int word_code = IsKeyWord(&curr_ptr);

        if (word_code < 0) return ERROR;

        if (word_code > 0)
        {
            tokens->array[tokens->cnt].type = OP;
            tokens->array[tokens->cnt].op_val = word_code;

            (tokens->cnt)++;

//             printf("Word_code: %d\ntoks_code: %d\ntoks_cnt:  %d\n", word_code,
//                     tokens->array[tokens->cnt - 1].code, tokens->cnt);
//
//             printf("New op: %d\n", tokens->array[tokens->cnt - 1].code);

            continue;
        }

        if (isalpha(*curr_ptr))
        {
            tokens->array[tokens->cnt].type = ID;

            int id_name_len = 0;

            sscanf(curr_ptr, "%s%n", tokens->array[tokens->cnt].id_val, &id_name_len);

            curr_ptr += id_name_len;

            (tokens->cnt)++;

            //printf("New id: %s\n", tokens->array[tokens->cnt].id_val);

            continue;
        }

        fprintf(stderr, "FillTokens() error: unknown token(%s), curr_ptr = %p\nprev: %s", curr_ptr, curr_ptr, curr_ptr - 2);

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

int SkipRubbish(char** curr_ptr, const char* end_ptr)
{
    if (!curr_ptr || !end_ptr)
    {
        fprintf(stderr, "SkipRubbish() error: curr_ptr(%p), end_ptr(%p)!\n", curr_ptr, end_ptr);
        return ERROR;
    }

    while (*curr_ptr < end_ptr && isspace(**curr_ptr)) (*curr_ptr)++;

    if (*curr_ptr < end_ptr && **curr_ptr == '~')
    {
        (*curr_ptr)++;

        while (*curr_ptr < end_ptr && **curr_ptr != '~') (*curr_ptr)++;

        (*curr_ptr)++;

        SkipRubbish(curr_ptr, end_ptr);
    }

    return OK;
}

int TokensCtor(tokens_t* tokens, int size)
{
    if (!tokens)
    {
        fprintf(stderr, "TokensCtor() error: null-pointer!\n");
        return ERROR;
    }

    tokens->cnt      = 0;
    tokens->curr_ptr = 0;
    tokens->size     = size;

    tokens->array = (Node_t*) calloc(size, sizeof(Node_t));

    if (!tokens->array)
    {
        fprintf(stderr, "TokensCtor() memory error!\n");
        return ERROR;
    }

    return OK;
}

int TokensDtor(tokens_t* tokens)
{
    if (!tokens)
    {
        fprintf(stderr, "TokensDtor() error: null-pointer!\n");
        return ERROR;
    }

    tokens->cnt      = 0;
    tokens->curr_ptr = 0;

    free(tokens->array);
    tokens->array = NULL;

    return OK;
}
