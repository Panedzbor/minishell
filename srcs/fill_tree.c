#include "../includes/minishell.h"

/* t_tree_node *fill_tree(t_token *start, t_token *end) */
void fill_tree(t_token *start, t_token *end)
{
    t_tree_node *tree;
    //t_token *tree_branches[2][2];
    t_token *left_brach[2];
    t_token *right_branch[2];
    t_token *parent;

    /* parent =  */divide_input(start, end, left_brach, right_branch);
    //tree = create_tree_node();
}

/* t_token_type divide_input(t_token *start, t_token *end, t_token *left, t_token *right) */
void divide_input(t_token *start, t_token *end, t_token **left, t_token **right)
{
    t_token *priora;
    
    
    /* priora =  */find_lowest_priority(start, end);

}

/* t_token *find_lowest_priority(t_token *start, t_token *end) */
void find_lowest_priority(t_token *start, t_token *end)
{
    t_token *current;
    t_token *lowest;

    current = start;
    lowest = NULL;
    while (current != end && current->priority > 0)
    {
        if (!lowest)
            lowest = current;
        else if (current->priority <= lowest->priority)
            lowest = current;
        current = current->next;
    }
    if (current->token_type != TOKEN_END_OF_LIST)
    {
        if (current->priority <= lowest->priority)
            lowest = current;
    }
    /* printf("%s - %d - %ld\n", lowest->value, lowest->token_type, lowest->priority); */
}

void init_prior(t_priora *prior)
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
            parenth_level -= 10;
            current->priority += parenth_level;
        }
        current = current->next;
    }
    return (current);
}
