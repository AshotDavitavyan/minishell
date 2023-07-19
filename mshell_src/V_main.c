/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   V_main.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgribkov <vgribkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 15:07:01 by vgribkov          #+#    #+#             */
/*   Updated: 2023/07/19 14:26:10 by vgribkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


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

// void	ft_lstdelone_token(t_token *token, void (*del)(char *))
// {
// 	if (!token)
// 		return ;
// 	(*del)(token->token);
// 	free(token);
// }

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

// void	printf_arr(char **input)
// {
// 	int i = 0;

// 	while(input[i])
// 		printf("%s\n", input[i++]);
// }

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


int	bi_execution(t_token *token)
{
		int ret_value;
		char **arr;

		arr = token -> token;
		ret_value = 0;
		if (token -> redir_flag_out + token -> redir_flag_outout + token -> redir_flag_in)
		{
			redirector_bi(token);
		}
		if (ft_strcmp("env", arr[0]) == 0)
			ret_value = bi_env(token -> shell);
		else if (ft_strcmp("pwd", arr[0]) == 0)
			ret_value = bi_pwd();
		else if (ft_strcmp("echo", arr[0]) == 0)
			ret_value = bi_echo(token);
		else if (ft_strcmp("cd", arr[0]) == 0)
			ret_value = bi_cd(token);
		else if (ft_strcmp("exit", arr[0]) == 0)
			ret_value = bi_exit(token);
		else if (ft_strcmp("export", arr[0]) == 0)
			ret_value = bi_export1(token -> shell);
		else if (ft_strcmp("unset", arr[0]) == 0)
			ret_value = bi_unset(token -> shell);
		global_error = ret_value;
		return (ret_value);
}

// int	main(int argc, char **argv, char **env)
// {
// 	t_shell *shell;
	
// 	shell = malloc(sizeof(t_shell));
// 	if (argc || argv || env)
// 		;
// 	init_env(&shell, env);

// 	//-----------------------------------Prompt---------------------------------------//

// 	char *args1 = NULL;
// 	char **Args1 = ft_split(args1, ' ');

// 	char *args2 = "a";
// 	char **Args2 = ft_split(args2, ' ');

// 	char *args3 = "b";
// 	char **Args3 = ft_split(args3, ' ');

// 	char *args4 = "a b";
// 	char **Args4 = ft_split(args4, ' ');

	// XXX ls > a XXX

	//shell -> token = ft_lstnew_upgr("ls -l-l", Args1, Args1, 0, 0, 0, Args1, shell);

	// XXX cat < a XXX

	//shell -> token = ft_lstnew_upgr("cat", Args2, 0, shell, -1, Args1);

	// XXX < a cat | wc -l  XXX

	//shell -> token = ft_lstnew_upgr("cat", Args2, 0, shell, -1, Args1);shell -> token -> next = ft_lstnew_upgr("wc -l", Args1, -1, shell, -1, Args1);

	// XXX < a yes | head XXX
	//char *lol = "\0";
	//shell -> token = ft_lstnew_upgr(lol, Args1, Args1, 0, 0, 0, Args1, shell);//shell -> token -> next = ft_lstnew_upgr("head", Args1, Args1, 0, 0, 0, Args1, shell);

	// XXX echo lol XXX

	//shell -> token =ft_lstnew_upgr("echo  lol", Args1, -1, shell, -1, Args1);

	// XXX  cat | wc -l XXX

	//shell -> token = ft_lstnew_upgr("cat", Args1, -1, shell, -1, Args1);shell -> token -> next = ft_lstnew_upgr("wc -l", Args1, -1, shell, -1, Args1);

	/// XXX < a cat | wc | wc | > b XXX

	//shell -> token = ft_lstnew_upgr("cat", Args2, 0, shell, -1, Args1);shell -> token -> next = ft_lstnew_upgr("wc", Args1, -1, shell, -1, Args1);;shell -> token -> next -> next = ft_lstnew_upgr("wc", Args3, 1, shell, -1, Args1);

	/// XXX cat << s

	//shell -> token = ft_lstnew_upgr("cat", Args1, -1, shell, 1, Args2);

	// pwd >> a

	//shell -> token = ft_lstnew_upgr("pwd", Args2, 2, shell, -1, Args1);

	// XXX cat | pwd | wc -l XXX ZA-PA

	//shell -> token = ft_lstnew_upgr("ls", Args1, -1, shell, -1, Args1);shell -> token -> next = ft_lstnew_upgr("pwd", Args1, -1, shell, -1, Args1);shell -> token -> next -> next = ft_lstnew_upgr("wc -l", Args1, -1, shell, -1, Args1);

	// XXX env | pwd XXX 

	//shell -> token = ft_lstnew_upgr("env", Args1, -1, shell, -1, Args1);shell -> token -> next = ft_lstnew_upgr("pwd", Args1, -1, shell, -1, Args1);

	// XXX ls | pwd | ls -al XXX

	//shell -> token = ft_lstnew_upgr("ls", Args1, -1, shell, -1, Args1);shell -> token -> next = ft_lstnew_upgr("pwd", Args1, -1, shell, -1, Args1);shell -> token -> next -> next= ft_lstnew_upgr("ls -al", Args1, -1, shell, -1, Args1);

	// XXX echo lol | wc XXX

	//shell -> token = ft_lstnew_upgr("cat", Args1, -1, shell, -1, Args1);shell -> token -> next = ft_lstnew_upgr("wc", Args1, -1, shell, -1, Args1);
	
	// XXX ls | cat | grep a XXX

	//shell -> token = ft_lstnew_upgr("ls", Args1, -1, shell, -1, Args1);shell -> token -> next = ft_lstnew_upgr("cat", Args1, -1, shell, -1, Args1);shell -> token -> next -> next = ft_lstnew_upgr("grep a", Args1, -1, shell, -1, Args1);

	// XXX cat << a | wc -l XXX

	//shell -> token = ft_lstnew_upgr("cat", Args1, -1, shell, 1, Args2);shell -> token -> next = ft_lstnew_upgr("wc -l", Args1, -1, shell, -1, Args1);

	//shell -> token = ft_lstnew_upgr("ls -a -l", Args1, -1, shell, -1, Args1);

	// XXX cat | ls XXX

	//shell -> token = ft_lstnew_upgr("cat", Args1, -1, shell, -1, Args1);shell -> token -> next = ft_lstnew_upgr("ls", Args1, -1, shell, -1, Args1);

	//-----------------------------------Prompt---------------------------------------//
// 	global_error = 0;
// 	exec(shell);
// 	ft_lstclear_token(&shell -> token, (*del_token));
// 	return (0);
// }
