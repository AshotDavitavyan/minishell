#include "minishell.h"

int	ft_lstsize_token(t_token *lst)
{
	int	i;

	i = 0;
	while (lst != NULL)
	{
		lst = lst -> next;
		i++;
	}
	return (i);
}

t_token	*ft_lstlast_token(t_token *lst)
{
	while (lst)
	{
		if (!lst->next)
			return (lst);
		lst = lst -> next;
	}
	return (lst);
}

void	ft_lstdelone_token(t_token *token, void (*del)(char *))
{
	if (!token)
		return ;
	(*del)(token->token);
	free(token);
}

void	ft_lstclear_token(t_token **token, void (*del)(char *))
{
	t_token	*i;
	t_token	*j;

	i = *token;
	while (i)
	{
		j = i->next;
		ft_lstdelone_token(i, (*del));
		i = j;
	}
	*token = 0;
}

void	ft_lstadd_back_token(t_token **lst, t_token *new)
{
	t_token	*help;
	help = *lst;
	if (!help)
	{
		*lst = new;
		return ;
	}
	help = ft_lstlast_token(help);
	help -> next = new;
}

t_token	*ft_lstnew_token(char *token, t_shell *shell)
{
	t_token	*node;

	node = malloc(sizeof(t_token));
	if (!node)
		return (0);
	node -> shell = shell; 
	node -> token = token;
	node ->next = NULL;
	return (node);
}

void	del_token(char *content)
{
	char *a;

	a = content;
	a = NULL;
}

void	printf_node(t_token *lst)
{
	if (!lst)
	{
		printf("list is empty");
		return;
	}
	while(lst)
	{
		printf("%s\n", lst -> token);
		lst = lst -> next;
	}
}

//----------------------------------------------------------------------------//
int	count_words_V(char const *s, char c)
{
	int	count;

	count = 0;
	while (*s != '\0')
	{
		while (*s == c && *s != '\0')
		s++;
		if (*s == '\0')
			return (count);
		while (*s != c && *s != '\0')
			s++;
		count++;
	}
	return (count);
}

char	**main_split_V(char *s, char c)
{
	char	**words;
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	words = (char **)malloc((count_words_V(s, c) + 1) * sizeof(char *));
	if (!words)
		return (NULL);
	while (s[i])
	{
		while (s[i] == c)
			i++;
		k = i;
		while (s[i] != c && s[i])
			i++;
		if (s[i + 1] == '-' && ft_isdigit(s[i + 2]) == 0)
		{
			i++;
			while (s[i] != c && s[i])
				i++;
		}
		if (i > k)
		{
			words[j] = ft_substr(s, k, i - k);
			j++;
		}
	}
	words[j] = NULL;
	return (words);
}

char	**ft_split_V(char *s, char c)
{
	char	**words;
	int		count;

	if (!s)
		return (NULL);
	count = count_words_V(s, c);
	if (count == 0)
	{
		words = (char **)malloc(1 * sizeof(char *));
		if (!words)
			return (NULL);
		words[0] = NULL;
		return (words);
	}
	return (main_split_V(s, c));
}

//---------------------------------------------------------------------------//

void	printf_arr(char **input)
{
	int i = 0;

	while(input[i])
		printf("%s\n", input[i++]);
}

void	init_env(t_shell **shell, char **envp)
{
	int	i = 0;
	while (envp[i])
		i++;
	(*shell) -> envex = malloc(sizeof(char *) * (i + 1));
	i = -1;
	while (envp[++i])
	{
		if (ft_strncmp("OLDPWD", envp[i], 6) == 0)
			(*shell) -> envex[i] = ft_strdup("OLDPWD");
		else
			(*shell) -> envex[i] = ft_strdup(envp[i]);
	}
	(*shell) -> envex[i] = NULL;
}

char	**fd_parser(char *input)
{
	char	**out;
	int		i;
	int		count;

	count = 0;
	i = 0;
	while (input[i])
	{
		if (input[i] == '>' || input[i] == '<')
			count++;
		i++;
	}
	i = 0;
	count++;
	out = (char **)malloc(sizeof(char *) * (count + 1));
	while (*input)
	{
		if (*input != '<' && *input != '>')
		{
			out[i] = ft_strtrim(input, "<>");
			i++;
		}
		input++;
	}
	out[i] = NULL;
	return (out);
}

void	do_list(char **input, t_shell **shell, char *def_input) // первый у меня всегда НЕ редирект
{
	t_token *tmp;
	int i = 0;
	//----------------
	if (ft_strncmp("env", input[0], 4) == 0 ||
	ft_strncmp("pwd", input[0], 4) == 0 ||
	ft_strncmp("echo", input[0], 4) == 0 ||
	ft_strncmp("cd", input[0], 3) == 0 ||
	ft_strncmp("exit", input[0], 5) == 0 ||
	ft_strncmp("export", input[0], 7) == 0 ||
	ft_strncmp("unset", input[0], 5) == 0)
	{
		(*shell)->token = ft_lstnew_token(def_input, *shell);
		return ;
	}
	//----------------
	(*shell)->token = ft_lstnew_token(input[i], *shell);
	if (input[i + 1] && (ft_strchr(input[++i], '<') || ft_strchr(input[i], '>')))
	{
		if (ft_strchr(input[i], '<'))
			(*shell)->token->redirect_flag = 0;
		else
			(*shell)->token->redirect_flag = 1;
		(*shell)->token->redirect_fd = fd_parser(input[i]);
	}
	else
	{
		(*shell)->token->redirect_flag = -1;
		(*shell)->token->redirect_fd = malloc(sizeof(char *) * 1);
		(*shell)->token->redirect_fd[0] = malloc(sizeof(char) * 1);
		(*shell)->token->redirect_fd[0] = NULL;
	}
	tmp = (*shell)-> token;
	while(input[++i])
	{
		if (ft_strchr(input[i], '>') || ft_strchr(input[i], '<'))
		{
			if (ft_strchr(input[i], '>'))
				(*shell)->token->redirect_flag = 1;
			else
				(*shell)->token->redirect_flag = 0;
			(*shell)->token->redirect_fd = fd_parser(input[i]);
			i++;
		}
		else
			(*shell)->token->redirect_flag = -1;
		if (!input[i])
			break;
		tmp -> next = ft_lstnew_token(input[i], *shell);
		if (tmp ->next)
			tmp = tmp -> next;
	}
}

int	main(int argc, char **argv, char **env)
{
	t_shell *shell;
	char *user_input;
	char **input;
	
	shell = malloc(sizeof(t_shell));
	if (argc || argv || env)
		;
	init_env(&shell, env);
	while (1)
	{
		user_input = readline("shell$ ");
		input = ft_split_V(user_input, ' ');
		do_list(input, &shell, user_input);
		// printf_node(shell ->token);
		// exit(0);
		if (ft_strncmp("env", shell -> token -> token, 3) == 0)
			bi_env(shell);
		else if (ft_strncmp("pwd", shell -> token -> token, 3) == 0)//
			bi_pwd();
		else if (ft_strncmp("echo", shell -> token -> token, 4) == 0)//
			bi_echo(shell -> token);
		else if (ft_strncmp("cd", shell -> token -> token, 2) == 0)//
			bi_cd(shell -> token);
		else if (ft_strncmp("exit", shell -> token -> token, 4) == 0)//
			bi_exit(shell -> token);
		else if (ft_strncmp("export", shell -> token -> token, 6) == 0)
			bi_export1(shell);
		else if (ft_strncmp("unset", shell -> token -> token, 5) == 0)
			bi_unset(shell);
		else
			exec(shell);
		while (wait(NULL) != -1)
			;
		ft_lstclear_token(&shell -> token, (*del_token));
	}
	return (0);
}

