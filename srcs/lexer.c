#include "../includes/minishell.h"
int is_parenth(char c)
{
    if ((c == '(') || (c == ')'))
        return (1);
    return (0);
}
static int is_word(char c, char *quote)
{
    if ((c == '"' || c == '\'') && !(*quote))
    {
        *quote = c;
        return (1);
    }
    if (!(*quote))
    {
        if (c == ' ' || c == '\t')
            return (0);
        if (is_parenth(c) || is_symbol_oper(c))
            return (0);
    }
    else if (c == *quote)
    {
        *quote = 0;
        return (1);
    }
    if (c == '\0')
        return (0);
    return (1);
}
void tokenize_parenth(char **str, t_token **token_list)
{
    char *ptr;

    ptr = *str;
    if (ptr[0] == '(')
        add_token(token_list, "(", TOKEN_PAREN_LEFT);
    else
        add_token(token_list, ")", TOKEN_PAREN_RIGH);
    *str = ptr + 1;
}

static void tokenize_word(char **str, t_token **token_list)
{
    char *start;
    char *result;
    char quote;

    result = NULL;
    quote = 0;
    start = *str;
    while (is_word(**str, &quote))
        (*str)++;
    if (!quote)
        result = ft_substr(start, 0, *str - start);
    else
        printf("quote error\n"); // TODO: function for errors
    if (result)
    {
        add_token(token_list, result, TOKEN_WORD);
        free(result);
    }
}

t_token *lexer(char *input)
{
    t_token *token_list;
    char *ptr;

    token_list = NULL;
    ptr = input;
    while (*ptr)
    {
        if (*ptr == ' ' || *ptr == '\t')
        {
            ptr++;
            continue;
        }
        else if (is_symbol_oper(*ptr))
            tokenize_operator(&ptr, &token_list);
        else if (is_parenth(*ptr))
            tokenize_parenth(&ptr, &token_list);
        else
            tokenize_word(&ptr, &token_list);
    }
    return token_list;
}
