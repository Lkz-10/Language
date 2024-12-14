#include <stdio.h>
#include <stdlib.h>

#include "LanguageGlobals.h"
#include "ReadData.h"
#include "LexicalAnalysis.h"

int PrintTokens(tokens_t tokens);

int main(const int argc, const char** argv)
{
    if (argc < 2)
    {
        fprintf(stderr, "Enter the file name!\n argv[0] = %s\n", argv[0]);
        return ERROR;
    }

    buffer_t buffer = {};

    ReadData(argv[1], &buffer);

    tokens_t tokens = {};

    //printf("buffer size: %d\nbuffer: %s\n", buffer.size, buffer.data);

    FillTokens(&tokens, &buffer);

    PrintTokens(tokens);

    free(buffer.data);
    buffer.data = NULL;

    return 0;
}

int PrintTokens(tokens_t tokens)
{
    for (int i = 0; i < MAX_TOKENS_CNT; ++i)
    {
        printf("%2d ", tokens.array[i].type);
    }
    printf("\n");

    for (int i = 0; i < MAX_TOKENS_CNT; ++i)
    {
        if (tokens.array[i].type == ID)
        {
            printf("%s ", tokens.array[i].id);
        }

        else if (tokens.array[i].type == NUM)
        {
            printf("%2lg ", tokens.array[i].num);
        }

        else printf("%2d ", tokens.array[i].code);
    }
    printf("\n");

    return 0;
}
