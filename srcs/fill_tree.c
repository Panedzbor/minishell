#include "../includes/minishell.h"

t_tree_node *fill_tree(t_token *start, t_token *end)
{
    t_tree_node *tree;
    t_token *left_branch[2];
    t_token *right_branch[2];
    t_token *parent;

    if (!start)
        return (NULL);
    ft_bzero(left_branch, 2 * sizeof(t_token *));
    ft_bzero(right_branch, 2 * sizeof(t_token *));
    if (!end)
        end = find_list_end(start);
    parent = divide_tokens(start, end, left_branch, right_branch);
    tree = create_tree_node(parent);
    tree->left = fill_tree(left_branch[0], left_branch[1]);
    tree->right = fill_tree(right_branch[0], right_branch[1]);
    return (tree);
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

void assign_value_to_argv(t_tree_node *node, t_token *token)
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

t_node_type define_node_type(t_token_type tt)
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

t_token *find_list_end(t_token *start)
{
    t_token *current;

    current = start;
    while (current->next->token_type != TOKEN_END_OF_LIST)
        current = current->next;
    return (current);
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

t_token *subshell_trim(t_token *start, t_token *end, t_token **left)
{
    left[0] = start->next;
    left[1] = end->prev;
    return (start);
}

void check_if_word_sequence(t_token **priora, t_token **priora_end)
{
    t_token *temp;

    temp = NULL;
    if ((*priora)->token_type == TOKEN_WORD)
    {
        temp = *priora;
        while ((*priora)->prev && (*priora)->prev->priority == (*priora)->priority)
            *priora = (*priora)->prev;
    }
    if (temp && *priora != temp)
        *priora_end = temp;
}

t_token *find_lowest_priority(t_token *start, t_token *end)
{
    t_token *current;
    t_token *lowest;

    current = start;
    lowest = NULL;
    while (current != end)
    {
        if (!lowest)
            lowest = current;
        else if (current->priority <= lowest->priority)
            lowest = current;
        current = current->next;
    }
    if (start == end)
        lowest = start;
    if (current->priority <= lowest->priority)
        lowest = current;
    return (lowest);
}


void init_token_priority(t_priora *prior)
{
    prior->type[0] = TOKEN_AND;
    prior->value[0] = 1;
    prior->type[1] = TOKEN_OR;
    prior->value[1] = 1;
    prior->type[2] = TOKEN_PIPE;
    prior->value[2] = 2;
    prior->type[3] = TOKEN_REDIRECT_IN;
    prior->value[3] = 3;
    prior->type[4] = TOKEN_REDIRECT_IN_MANUAL;
    prior->value[4] = 3;
    prior->type[5] = TOKEN_REDIRECT_OUT;
    prior->value[5] = 3;
    prior->type[6] = TOKEN_REDIRECT_OUT_APPEND;
    prior->value[6] = 3;
    prior->type[7] = TOKEN_PAREN_LEFT;
    prior->value[7] = 4;
    prior->type[8] = TOKEN_PAREN_RIGH;
    prior->value[8] = 4;
    prior->type[9] = TOKEN_WORD;
    prior->value[9] = 5;
    prior->type[10] = TOKEN_END_OF_LIST;
    prior->value[10] = -1;
}

t_token *analyze_parenthesis(t_token *tokens, int parenth_open)
{
    t_token *current;
    static int parenth_level;

    current = tokens;
    while (current->token_type != TOKEN_END_OF_LIST)
    {
        if (parenth_open && current->token_type == TOKEN_PAREN_RIGH)
            return (current);
        if (!parenth_open && current->token_type == TOKEN_PAREN_RIGH)
            return (NULL);
        if (parenth_open)
            current->priority += parenth_level;
        if (current->token_type == TOKEN_PAREN_LEFT)
        {
            parenth_level += 10;
            current = analyze_parenthesis(current->next, 1);
            if (!current)
                return (NULL);
            parenth_level -= 10;
            current->priority += parenth_level;
        }
        current = current->next;
    }
    return (check_closed_parenths(current, parenth_open));
}

t_token *check_closed_parenths(t_token *last, int parenth_open)
{
    if (parenth_open)
        return (NULL);
    return (last);
}
