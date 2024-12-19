#include "DrawTree.h"

int DrawTree(Node_t* root, const char* file_name)
{
    FILE* file_ptr = fopen(file_name, "w");

    fprintf(file_ptr, "digraph G\n{  rankdir = UD;\n");

    DrawNode(root, file_ptr);

    fprintf(file_ptr, "}\n");

    fclose(file_ptr);

    system("dot Tree.dot -Tpng -o Tree.png");

    return OK;
}

int DrawNode(Node_t* node, FILE* file_ptr)
{
    if (!node) return 0;

    if (!file_ptr)
    {
        fprintf(stderr, "DrawNode() file error!\n");
        return ERROR;
    }

    fprintf(file_ptr, "  \"%p\" [shape = Mrecord, color = ", node);

    switch(node->type)
    {
        case NUM:
        {
            fprintf(file_ptr, "\"darkblue\", style = \"filled\", fillcolor = \"lightcyan\", "
                              "fontcolor = \"darkblue\", label = \"{NUM | %lg}\"];\n", node->num_val);
            break;
        }

        case ID:
        {
            fprintf(file_ptr, "\"darkorange4\", style = \"filled\", fillcolor = \"lemonchiffon\", "
                              "fontcolor = \"darkorange4\", label = \"{ID | %s}\"];\n", node->id_val);
            break;
        }

        case OP:
        {
            fprintf(file_ptr, "\"darkgreen\", style = \"filled\", fillcolor = \"darkolivegreen1\", "
                              "fontcolor = \"darkgreen\", label = \"{OP | %s (%d)}\"];\n", CodeToOperator(node->op_val), node->op_val);
            break;
        }

        default:
        {
            fprintf(stderr, "Unknown type(DrawNode() switch): %d!\n", node->type);
            return ERROR;
        }
    }

    DrawNode(node->left,  file_ptr);
    DrawNode(node->right, file_ptr);

    if (node->left)  fprintf(file_ptr, "  \"%p\" -> \"%p\";\n", node, node->left);

    if (node->right) fprintf(file_ptr, "  \"%p\" -> \"%p\";\n", node, node->right);

    return OK;
}

const char* CodeToOperator(int code)
{
    for (int i = 0; i < OP_CNT; ++i)
    {
        if (operations[i].code == code)
        {
            return operations[i].name;
        }
    }

    return NULL;
}
