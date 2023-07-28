#include "../../includes/minishell.h"

int	heredoc(t_token_small **tokens, t_token **token_final)
{
	(*token_final)->here_doc_flag = 1;
	*tokens = (*tokens)->next;
	(*token_final)->sep_arr = add_fd((*token_final)->sep_arr, *tokens, 0, NULL);
	if ((*token_final)->sep_arr == NULL)
		return (-1);
	return (0);
}

void	pick_the_right_flag(t_token **tokfin, t_token_small **tokens)
{
	while (*tokens != NULL)
	{
		if (check_for_special_signs(*tokens) == 3)
		{
			(*tokfin)->redir_flag_outout = 0;
			(*tokfin)->redir_flag_out = 1;
		}
		else if (check_for_special_signs(*tokens) == 4)
		{
			(*tokfin)->redir_flag_outout = 1;
			(*tokfin)->redir_flag_out = 0;
		}
		else if (check_for_special_signs(*tokens) == 5)
		{
			(*tokens) = (*tokens)->next;
			return ;
		}
		(*tokens) = (*tokens)->next;
	}
}

char	*str_tolower(char *to_lower)
{
	char	*save;
	char	*start;

	if (!to_lower)
		return (NULL);
	save = ft_strdup(to_lower);
	start = save;
	while (*save)
	{
		*save = ft_tolower(*save);
		save++;
	}
	return (start);
}

int	check_echo(char *to_check)
{
	char	*comp;

	comp = NULL;
	if (to_check != NULL)
		comp = str_tolower(to_check);
	if (ft_strncmp(comp, "echo", 4) == 0)
	{
		free(comp);
		return (0);
	}
	free(comp);
	return (-1);
}

int	str_find(char **tokens)
{
	char	**ptr;

	ptr = tokens;
	if (!tokens || !(*tokens))
		return (0);
	while (ptr != NULL)
	{
		if (check_echo(*ptr) == 0)
			return (1);
		ptr++;
	}
	return (0);
}
