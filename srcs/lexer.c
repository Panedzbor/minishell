#include "../includes/minishell.h"

static int is_word(char c)
{
    if(c == '\0')
        return (0);
    if (is_symbol_oper(c))
        return (0);
    if (c == ' ' || c == '\t')
        return (0);
    return (1);
}

static char *tokenize_word(char **str)
{
    char *start;
    char *result;

    start = *str;
    while(is_word(**str))
        (*str)++;
    result = ft_substr(start, 0, *str - start);
    return (result);
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
        if (is_symbol_oper(*ptr) || *ptr == '(' || *ptr == ')')
            tokenize_operator(&ptr, &token_list);
        else
        {
            char *word = tokenize_word(&ptr);
            if (word)
            {
                add_token(&token_list, word, TOKEN_WORD);
                free(word);
            }
        }
    }
    return token_list;
}
