#include "../../includes/minishell.h"

void	print_tokens(t_token_small *tokens)
{
	int i = 0;
	while (tokens != NULL)
	{
		printf("token:[%s]\n", tokens->name);
		tokens = tokens->next;
		i++;
	}
	printf("size:[%d]\n", i);
}
void	print_env(char **envp)
{
	while(*envp)
	{
		printf("%s\n", *envp);
		envp++;
	}
}

void	print_arr(char **to_print, char *name)
{
    if (name != NULL)
    	printf("%s:", name);
	if (to_print == NULL)
	{
		printf("\n");
		return ;
	}
	printf("%s", *to_print);
	to_print++;
	while (*to_print && to_print)
	{
		printf(", %s", *to_print);
		to_print++;
	}
	printf("\n");
}

void	print_big_token(t_token *tokfin)
{
	while (tokfin != NULL)
	{
		printf("Here_fd:[%d]\n", tokfin->here_fd);
		printf("Here_doc_flag:[%d]\n", tokfin->here_doc_flag);
		print_arr(tokfin->sep_arr, "Sep_arr");
		printf("Redir_flag_out:[%d]\n", tokfin->redir_flag_out);
		printf("Redir_flag_in:[%d]\n", tokfin->redir_flag_in);
		printf("Redir_flag_outout:[%d]\n", tokfin->redir_flag_outout);
		print_arr(tokfin->redir_fd_out, "Redir_fd_out");
		print_arr(tokfin->redir_fd_in, "Redir_fd_in");
		print_arr(tokfin->token, "Token");
		tokfin = tokfin->next;
		printf("------------------------------------------------------------\n");
	}
}