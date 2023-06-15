#include "minishell.h"

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

void	ft_lstdelone_token(t_token *lst, void (*del)(char *))
{
	if (!lst)
		return ;
	(*del)(lst->token);
	free(lst);
}

void	ft_lstclear_token(t_token **lst, void (*del)(char *))
{
	t_token	*i;
	t_token	*j;

	i = *lst;
	while (i)
	{
		j = i->next;
		ft_lstdelone_token(i, (*del));
		i = j;
	}
	*lst = 0;
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

t_token	*ft_lstnew_token(char *token)
{
	t_token	*node;

	node = malloc(sizeof(t_token));
	if (!node)
		return (0);
	node ->token = token;
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

int	main(int argc, char **argv, char **env)
{
	t_token *token;

	if (argc || argv || env)
		;
	int i = 1;
	while(argc - 1)
	{
		ft_lstadd_back_token(&token, ft_lstnew_token(argv[i]));
		i++;
		argc--;
	}
	if (ft_strncmp("env", token -> token, 4) == 0)
		bi_env(env);
	else if (ft_strncmp("pwd", token -> token, 4) == 0)
		bi_pwd();
	else if (ft_strncmp("echo", token -> token, 4) == 0)
		bi_echo(token);
	else if (ft_lstsize_token(token) == 1)
		exec_1(token, env);
	ft_lstclear_token(&token, (*del_token));
	while (wait(NULL) != -1)
		;
	return (0);
}
