#include "../includes/minishell.h"

static void assign_value_to_argv(t_tree_node *node, t_token *token)
{
    t_token *temp;
    size_t count;

    temp = token;
    count = 0;
    while (temp->token_type == TOKEN_WORD)
    {
        count++;
        temp = temp->next;
    }
    node->argv = (char **)ft_calloc(count + 1, sizeof(char *));
    if (!node->argv)
        printf ("Error!\n");
    count = 0;
    while (token->token_type == TOKEN_WORD)
    {
        node->argv[count++] = token->value;
        token = token->next;
    }
    node->argv[count] = NULL;
}
static t_node_type define_node_type(t_token_type tt)
{
    if (tt == TOKEN_AND)
        return (NODE_AND);
    else if (tt == TOKEN_OR)
        return (NODE_OR);
    else if (tt == TOKEN_PIPE)
        return (NODE_PIPE);
    else if (tt == TOKEN_REDIRECT_IN)
        return (NODE_REDIRECT_IN);
    else if (tt == TOKEN_REDIRECT_IN_MANUAL)
        return (NODE_REDIRECT_IN_MANUAL);
    else if (tt == TOKEN_REDIRECT_OUT)
        return (NODE_REDIRECT_OUT);
    else if (tt == TOKEN_REDIRECT_OUT_APPEND)
        return (NODE_REDIRECT_OUT_APPEND);
    else if (tt == TOKEN_PAREN_LEFT)
        return (NODE_SUBSHELL);
    else if (tt == TOKEN_WORD)
        return (NODE_COMMAND);
    return (0);
}

static t_token *subshell_trim(t_token *start, t_token *end, t_token **left)
{
    left[0] = start->next;
    left[1] = end->prev;
    return (start);
}

t_tree_node *create_tree_node(t_token *token)
{
    t_tree_node *node;

    node = (t_tree_node*)ft_calloc(1, sizeof(t_tree_node));
    if (!node)
        printf("Error!\n");
    node->type = define_node_type(token->token_type);
    if (node->type == NODE_COMMAND)
        assign_value_to_argv(node, token);
    else
        node->argv = NULL;
    return (node);
}

t_token *divide_tokens(t_token *start, t_token *end, t_token **left, t_token **right)
{
    t_token *priora;
    t_token *priora_end;

    priora_end = NULL;
    priora = find_lowest_priority(start, end);
    check_if_word_sequence(&priora, &priora_end);
    if (priora->token_type == TOKEN_PAREN_RIGH)
        return (subshell_trim(start, end, left));
    if (priora != start)
    {
        left[0] = start;
        left[1] = priora->prev;
    }
    if (priora != end && priora_end != end)
    {
        if (!priora_end)
            right[0] = priora->next;
        else
            right[0] = priora_end->next;
        right[1] = end;
    }
    return (priora);
}