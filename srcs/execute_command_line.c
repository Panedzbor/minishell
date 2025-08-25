#include "../includes/minishell.h"

void execute_command_line(t_tree_node *node)
{
    if (node->type == NODE_COMMAND)
        validate_command(node);
    else if (node->type == NODE_PIPE)
        printf("PIPE\n");
    //else if...
}