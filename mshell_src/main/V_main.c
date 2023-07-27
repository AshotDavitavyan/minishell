/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   V_main.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgribkov <vgribkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 15:07:01 by vgribkov          #+#    #+#             */
/*   Updated: 2023/07/27 18:38:18 by vgribkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/minishell.h"

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

// void	ft_lstdelone_token(t_token *token, void (*del)(char *))
// {
// 	if (!token)
// 		return ;
// 	(*del)(token->token);
// 	free(token);
// }

// void	ft_lstclear_token(t_token **token, void (*del)(char *))
// {
// 	t_token	*i;
// 	t_token	*j;

// 	i = *token;
// 	while (i)
// 	{
// 		j = i->next;
// 		ft_lstdelone_token(i, (*del));
// 		i = j;
// 	}
// 	*token = 0;
// }

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

// t_token	*ft_lstnew_token(char *token, t_shell *shell)
// {
// 	t_token	*node;

// 	node = malloc(sizeof(t_token));
// 	if (!node)
// 		return (0);
// 	node -> shell = shell; 
// 	node -> token = token;
// 	node ->next = NULL;
// 	return (node);
// }

// t_token	*ft_lstnew_upgr(char *token, char **r_fd_out, char **r_fd_in,  int flag_out, int flag_in, int h_flag, char **sep_arr, t_shell *shell)
// {
// 	t_token	*node;

// 	node = malloc(sizeof(t_token));
// 	if (!node)
// 		return (0);
// 	node -> shell = shell; 
// 	node -> token = token;
// 	node -> redir_fd_out = r_fd_out;
// 	node -> redir_fd_in = r_fd_in;
// 	node -> redir_flag_out = flag_out;
// 	node -> redir_flag_in = flag_in;
// 	node -> here_doc_flag = h_flag;
// 	node -> sep_arr = sep_arr;
// 	node ->next = NULL;
// 	return (node);
// }

// void	del_token(char *content)
// {
// 	char *a;

// 	a = content;
// 	a = NULL;
// }

// void	printf_node(t_token *lst)
// {
// 	if (!lst)
// 	{
// 		printf("list is empty");
// 		return;
// 	}
// 	while(lst)
// 	{
// 		printf("%s\n", lst -> token);
// 		lst = lst -> next;
// 	}
// }

// //----------------------------------------------------------------------------//
// int	count_words_V(char const *s, char c)
// {
// 	int	count;

// 	count = 0;
// 	while (*s != '\0')
// 	{
// 		while (*s == c && *s != '\0')
// 		s++;
// 		if (*s == '\0')
// 			return (count);
// 		while (*s != c && *s != '\0')
// 			s++;
// 		count++;
// 	}
// 	return (count);
// }

// char	**main_split_V(char *s, char c)
// {
// 	char	**words;
// 	int		i;
// 	int		j;
// 	int		k;

// 	i = 0;
// 	j = 0;
// 	words = (char **)malloc((count_words_V(s, c) + 1) * sizeof(char *));
// 	if (!words)
// 		return (NULL);
// 	while (s[i])
// 	{
// 		while (s[i] == c)
// 			i++;
// 		k = i;
// 		while (s[i] != c && s[i])
// 			i++;
// 		if (s[i + 1] == '-' && ft_isdigit(s[i + 2]) == 0)
// 		{
// 			i++;
// 			while (s[i] != c && s[i])
// 				i++;
// 		}
// 		if (i > k)
// 		{
// 			words[j] = ft_substr(s, k, i - k);
// 			j++;
// 		}
// 	}
// 	words[j] = NULL;
// 	return (words);
// }

// char	**ft_split_V(char *s, char c)
// {
// 	char	**words;
// 	int		count;

// 	if (!s)
// 		return (NULL);
// 	count = count_words_V(s, c);
// 	if (count == 0)
// 	{
// 		words = (char **)malloc(1 * sizeof(char *));
// 		if (!words)
// 			return (NULL);
// 		words[0] = NULL;
// 		return (words);
// 	}
// 	return (main_split_V(s, c));
// }

// //---------------------------------------------------------------------------//

void	printf_arr(char **input)
{
	int i = 0;

	while(input[i])
		printf("%s\n", input[i++]);
}

// void	init_env(t_shell **shell, char **envp)
// {
// 	int	i = 0;
// 	while (envp[i])
// 		i++;
// 	(*shell) -> envex = malloc(sizeof(char *) * (i + 1));
// 	i = -1;
// 	while (envp[++i])
// 	{
// 		if (ft_strncmp("OLDPWD", envp[i], 6) == 0)
// 			(*shell) -> envex[i] = ft_strdup("OLDPWD");
// 		else
// 			(*shell) -> envex[i] = ft_strdup(envp[i]);
// 	}
// 	(*shell) -> envex[i] = NULL;
// }

int bi_check_exec(t_token *token)
{
	char **arr;
	int	ret_value;
	
	ret_value = 0;
	arr = token -> token;
	if (ft_strcmp("env", str_to_lower(arr[0])) == 0)
		ret_value = bi_env(token -> shell);
	else if (ft_strcmp("pwd", str_to_lower(arr[0])) == 0)
		ret_value = bi_pwd();
	else if (ft_strcmp("echo", str_to_lower(arr[0])) == 0)
		ret_value = bi_echo(token);
	else if (ft_strcmp("cd", arr[0]) == 0)
		ret_value = bi_cd(token);
	else if (ft_strcmp("export", str_to_lower(arr[0])) == 0)
		ret_value = bi_export1(token -> shell);
	else if (ft_strcmp("unset", str_to_lower(arr[0])) == 0)
		ret_value = bi_unset(token -> shell);
	else if (ft_strcmp("exit", str_to_lower(arr[0])) == 0)
		ret_value = bi_exit(token);
	return (ret_value);
}

int	bi_execution(t_token *token)
{
		int ret_value;
		char **arr;
		int f;
		
		arr = token -> token;
		if (token -> redir_flag_out + token -> redir_flag_outout + token -> redir_flag_in == 1
			&& (ft_strcmp("exit", arr[0]) == 0))
		{
			ret_value = bi_check_exec(token);
			return (ret_value);
		}	
		if (token -> redir_flag_out + token -> redir_flag_outout + token -> redir_flag_in == 0)
		{
			ret_value = bi_check_exec(token);
			return (ret_value);
		}
		f = fork();
		if (f == -1)
		{
			ft_putstr_fd("minishell: fork: Resource temporarily unavailable\n", 2);
			exit(1);
		}
		if (f != 0)	
			return (0);
		ret_value = 0;
		redirector(token);
		ret_value = bi_check_exec(token);
		g_global_error = ret_value;
		exit(ret_value);
}
