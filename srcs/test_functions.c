#include "../includes/minishell.h"

void test_list_data(t_node *test_node)
{
	int i;

	i = 1;
	while (test_node)
	{
		ft_printf("INFO:  Node #%d: %s\n", i, test_node->command[0]);
		test_node = test_node->next;
		i++;
	}
}
void print_tokens(t_token *head)
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


void    test_anal_parent(t_token *token)
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