#include "../includes/minishell.h"

void test_print_tokens(t_token *head)
{
	int i;

	i = 1;
    while (head)
    {
        printf("Token: %d Value: %s Type: %d Priority: %ld\n", i , head->value, head->token_type, head->priority);fflush(stdout);
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
void test_print_shell_vars(t_shell *shell)
{
    int i;

    printf("\n--------------------LOCAL VARIABLES--------------------\n");
    if (shell->local_vars)
    {
        i = 0;
        while (shell->local_vars[i])
        {
            printf("%s\n", shell->local_vars[i]);
            i++;
        }
	}
    printf("\n--------------------LOCAL VARIABLES--------------------\n");
	printf("\n-----------------ENVIRONMENT VARIABLES-----------------\n");
    if (shell->envp)
    {
        i = 0;
        while (shell->envp[i])
        {
            printf("%s\n", shell->envp[i]);
            i++;
        }
    }
    printf("\n-----------------ENVIRONMENT VARIABLES-----------------\n");
}
