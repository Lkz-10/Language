#include "LanguageHeaders.h"

int PrintTokens(tokens_t* tokens);
int CheckArgc  (const int argc, const char** argv);

int main(const int argc, const char** argv)
{
    CheckArgc(argc, argv);

    buffer_t buffer = {};
    ReadData(argv[1], &buffer);

    tokens_t tokens = {};
    TokensCtor(&tokens, buffer.size);

    // printf("\nbuffer size: %d\nbuffer: %s\n", buffer.size, buffer.data);

    FillTokens(&tokens, &buffer);

    PrintTokens(&tokens);

    Node_t* root = GetGrammar(&tokens);

    // printf("Root: %p\n", root);

    DrawTree(root, argv[2]);

    TokensDtor(&tokens);
    BufferDtor(&buffer);

    return 0;
}

int PrintTokens(tokens_t* tokens)
{
    FILE* file_ptr = fopen("Tokens_array.txt", "w");

    for (int i = 0; i < tokens->size; ++i)
    {
        fprintf(file_ptr, "%6d ", i + 1);
    }
    fprintf(file_ptr, "\n");

    for (int i = 0; i < tokens->size; ++i)
    {
        fprintf(file_ptr, "%6d ", tokens->array[i].type);
    }
    fprintf(file_ptr, "\n");

    for (int i = 0; i < tokens->cnt; ++i)
    {
        if (tokens->array[i].type == ID)
        {
            fprintf(file_ptr, "%6s ", tokens->array[i].id_val);
        }

        else if (tokens->array[i].type == NUM)
        {
            fprintf(file_ptr, "%6lg ", tokens->array[i].num_val);
        }

        else if (tokens->array[i].type == OP)
        {
            fprintf(file_ptr, "%6d ", tokens->array[i].op_val);
        }
        else fprintf(file_ptr, "   ");
    }
    fprintf(file_ptr, "\n");

    fclose(file_ptr);

    return 0;
}

int CheckArgc(const int argc, const char** argv)
{
    if (argc < 3)
    {
        fprintf(stderr, "Enter the file name!\n argv[0] = %s\n", argv[0]);
        return ERROR;
    }

    return OK;
}
