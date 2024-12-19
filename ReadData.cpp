#include "ReadData.h"

int ReadData(const char* file_name, buffer_t* buffer)
{
    FILE* file_ptr = fopen(file_name, "rb");

    if (!file_ptr)
    {
        fprintf(stderr, "File error!\n");
        return ERROR;
    }

    if (fseek(file_ptr, 0, SEEK_END) != 0)
    {
        fprintf(stderr, "fseek() error!\n");

        fclose(file_ptr);
        return ERROR;
    }

    buffer->size = ftell(file_ptr);
    //fprintf(stderr, "buf_size: %ld\n", buf_size);

    rewind(file_ptr);

    buffer->data = (char*) calloc(1, buffer->size + 1);

    if (!buffer->data)
    {
        fprintf(stderr, "Memory error!\n");

        fclose(file_ptr);

        return ERROR;
    }

    fprintf(stderr, "\nBefore fread():\ndata: %s\nsize: %d\n\n", buffer->data, buffer->size);

    if ((long int) fread(buffer->data, sizeof(char), buffer->size, file_ptr) < buffer->size)
    {
        fprintf(stderr, "Reading error!\n");

        fclose(file_ptr);
        free  (buffer->data);

        return ERROR;
    }

    buffer->size -= 2;

    fclose(file_ptr);

    return OK;
}

int BufferDtor(buffer_t* buffer)
{
    if (!buffer)
    {
        fprintf(stderr, "BufferDtor() error: null-pointer!\n");
        return ERROR;
    }

    buffer->size = 0;

    free(buffer->data);
    buffer->data = NULL;

    return OK;
}
