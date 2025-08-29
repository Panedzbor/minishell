#include "../includes/minishell.h"

void test_print_tokens(t_token *head)
{
	int i;

	i = 1;
    while (head)
    {
        printf("Token: %d Value: %s Type: %d Priority: %ld\n", i , head->value, head->token_type, head->priority);
        head = head->next;
		i++;
    }
}


void    test_analyze_parent(t_token *token)
{
	t_token *current;
	
	current = token;
	for (; current->token_type != TOKEN_END_OF_LIST; current = current->next)
		printf("%5s ", current->value);
	printf("\n");
	current = token;
	for (; current->token_type != TOKEN_END_OF_LIST; current = current->next)
		printf("%5ld ", current->priority);
	printf("\n");
}