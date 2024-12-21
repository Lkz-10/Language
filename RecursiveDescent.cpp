#include "RecursiveDescent.h"

void SyntaxError(tokens_t* tokens, const char* expected_operator)
{
    if (!tokens)
    {
        fprintf(stderr, "SyntaxError() error: null-pointer!\n");
        exit(0);
    }

    fprintf(stderr, "Syntax error, token %d (Expected \"%s\")!\n\n", tokens->curr_ptr + 1, expected_operator);
    exit(0);
}

Node_t* GetNumber(tokens_t* tokens)
{
    if (!tokens)
    {
        fprintf(stderr, "GetNumber() error: null-pointer!\n");
        return NULL;
    }

    return &tokens->array[(tokens->curr_ptr)++];
}

Node_t* GetVariable(tokens_t* tokens)
{
    if (!tokens)
    {
        fprintf(stderr, "GetVariable() error: null-pointer!\n");
        return NULL;
    }

    // fprintf(stderr, "Variable \"%s\" got!\n", tokens->array[tokens->curr_ptr].id_val);

    return &tokens->array[(tokens->curr_ptr)++];
}

Node_t* GetFunction(tokens_t* tokens)
{
    if (!tokens)
    {
        fprintf(stderr, "Getfunction() error: null-pointer!\n");
        return NULL;
    }

    Node_t* function = &tokens->array[tokens->curr_ptr];

    // fprintf(stderr, "Function \"%s\" got!\n", tokens->array[tokens->curr_ptr].id_val);

    tokens->curr_ptr += 2;

    function->left = GetE(tokens);

    if (tokens->array[(tokens->curr_ptr)++].op_val != OperatorCode("whistle")) SyntaxError(tokens, ")");

    return function;
}

Node_t* GetP(tokens_t* tokens)
{
    if (!tokens)
    {
        fprintf(stderr, "GetP() error: null-pointer!\n");
        return NULL;
    }

    if (tokens->array[tokens->curr_ptr].op_val == OperatorCode("start"))
    {
        (tokens->curr_ptr)++;

        Node_t* value = GetE(tokens);

        if (tokens->array[tokens->curr_ptr].op_val != OperatorCode("whistle")) SyntaxError(tokens, ")");

        (tokens->curr_ptr)++;

        return value;
    }

    if (tokens->curr_ptr < tokens->cnt - 1 &&
        tokens->array[tokens->curr_ptr + 1].op_val == OperatorCode("start"))
    {
        // fprintf(stderr, "Going to GetFunction()!\n");
        return GetFunction(tokens);
    }

    if (tokens->array[tokens->curr_ptr].type == ID)
    {
        // fprintf(stderr, "Going to GetVariable()!\n");
        return GetVariable(tokens);
    }

    return GetNumber(tokens);
}

Node_t* GetT(tokens_t* tokens)
{
    if (!tokens)
    {
        fprintf(stderr, "GetT() error: null-pointer!\n");
        return NULL;
    }

    Node_t* value = GetP(tokens);

    while (tokens->array[tokens->curr_ptr].op_val == OperatorCode("star") ||
           tokens->array[tokens->curr_ptr].op_val == OperatorCode("goalkeeper"))
    {
        Node_t* _operator = &tokens->array[tokens->curr_ptr];

        (tokens->curr_ptr)++;

        Node_t* value2 = GetP(tokens);

        _operator->left  = value;
        _operator->right = value2;

        value = _operator;
    }

    return value;
}

Node_t* GetE(tokens_t* tokens)
{
    if (!tokens)
    {
        fprintf(stderr, "GetE() error: null-pointer!\n");
        return NULL;
    }

    Node_t* value = GetT(tokens);

    while (tokens->array[tokens->curr_ptr].op_val == OperatorCode("win") ||
           tokens->array[tokens->curr_ptr].op_val == OperatorCode("lose"))
    {
        Node_t* _operator = &tokens->array[tokens->curr_ptr];

        (tokens->curr_ptr)++;

        Node_t* value2 = GetT(tokens);

        _operator->left  = value;
        _operator->right = value2;

        value = _operator;
    }

    return value;
}

Node_t* GetAssignment(tokens_t* tokens)
{
     if (!tokens)
    {
        fprintf(stderr, "GetA() error: null-pointer!\n");
        return NULL;
    }

    Node_t* left_value = GetVariable(tokens);

    Node_t* _operator = &tokens->array[(tokens->curr_ptr)++];

    Node_t* right_value = GetE(tokens);

    _operator->left  = left_value;
    _operator->right = right_value;

    return _operator;
}

Node_t* GetOperation(tokens_t* tokens)
{
    if (!tokens)
    {
        fprintf(stderr, "GetOp() error: null-pointer!\n");
        return NULL;
    }

    Node_t* _operator = NULL;

    if (tokens->array[tokens->curr_ptr].op_val == OperatorCode("VAR"))
    {
        _operator = &tokens->array[(tokens->curr_ptr)++];

        if (tokens->array[(tokens->curr_ptr)++].op_val != OperatorCode("start")) SyntaxError(tokens, "(");

        _operator->left = GetE(tokens);

        if (tokens->array[(tokens->curr_ptr)++].op_val != OperatorCode("whistle")) SyntaxError(tokens, ")");

        _operator->right = GetOperation(tokens);
    }

    else if (tokens->array[tokens->curr_ptr].op_val == OperatorCode("broadcast"))
    {
        _operator = &tokens->array[(tokens->curr_ptr)++];

        if (tokens->array[(tokens->curr_ptr)++].op_val != OperatorCode("start")) SyntaxError(tokens, "(");

        _operator->left = GetE(tokens);

        if (tokens->array[(tokens->curr_ptr)++].op_val != OperatorCode("whistle")) SyntaxError(tokens, ")");
    }

    else if (tokens->array[tokens->curr_ptr].op_val == OperatorCode("July"))
    {
        (tokens->curr_ptr)++;

        _operator = GetOperation(tokens);

        Node_t* root_operator = _operator;

        while (tokens->curr_ptr < tokens->cnt - 1 && tokens->array[tokens->curr_ptr].op_val != OperatorCode("May"))
        {
            _operator->right = GetOperation(tokens);

            _operator = _operator->right;
        }

        (tokens->curr_ptr)++;
        //if (tokens->array[tokens->curr_ptr].op_val != OperatorCode("May")) SyntaxError(tokens, "}");

        return root_operator;
    }

    else if (tokens->curr_ptr < tokens->cnt - 1 &&
                tokens->array[tokens->curr_ptr + 1].op_val == OperatorCode("draw"))
    {
        _operator = GetAssignment(tokens);
    }

    else SyntaxError(tokens, "Operator");

    if (tokens->array[tokens->curr_ptr].op_val != OperatorCode("Break")) SyntaxError(tokens, ";");

    tokens->array[tokens->curr_ptr].left = _operator;

    return &tokens->array[(tokens->curr_ptr)++];
}

Node_t* GetGrammar(tokens_t* tokens)
{
     if (!tokens)
    {
        fprintf(stderr, "GetG() error: null-pointer!\n");
        return NULL;
    }

    Node_t* root = GetOperation(tokens);

    Node_t* _operator = root;

    //fprintf(stderr, "GetG() curr_ptr = %d\n", tokens->curr_ptr + 1);

    while (tokens->curr_ptr < tokens->cnt && tokens->array[tokens->curr_ptr].op_val != OperatorCode("PSG"))
    {
        //fprintf(stderr, "GetG() curr_ptr = %d\n", tokens->curr_ptr + 1);

        _operator->right = GetOperation(tokens);

        //fprintf(stderr, "GetG() curr_ptr (after GetA()) = %d\n", tokens->curr_ptr + 1);

        _operator = _operator->right;
    }

    if (tokens->array[tokens->curr_ptr].op_val != OperatorCode("PSG")) SyntaxError(tokens, "$");

    (tokens->curr_ptr)++;

    return root;
}

int OperatorCode(const char* _operator)
{
    if (!_operator)
    {
        fprintf(stderr, "OperatorCode() error: null-pointer!\n");
        return ERROR;
    }

    for (int i = 0; i < OP_CNT; ++i)
    {
        if (strcmp(_operator, operations[i].name) == 0)
        {
            return operations[i].code;
        }
    }

    return OK;
}
