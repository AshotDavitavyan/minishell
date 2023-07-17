#include "minishell.h"

//single pipe error
//$"USER" prints adavitav, should print USER
//$$USER.1 malloc error 
//$USER1 malloc error prints davitav instead of adavitav or avitav if $USER12
//remove token if variable does not exist
//Signals
//Numbers with dollar signs
//Errors, parse errors etc
//create env variable which is special sign
//add history


void	error(void)
{
	write(2, "Error\n", 6);
	exit (1);
}
char	*space_skip(char *user_input)
{
	while (*user_input == ' ' && *user_input)
		user_input++;
	return (user_input);
}

void	lexing(char *u_i, t_token_small **tokens, t_shell **shell, t_token **tbig)
{
	u_i = put_spaces(u_i);
	get_tokens(u_i, tokens, 0);
	init_shell(tokens, shell);
	handle_dollar_signs(tokens);
	parse_tokens(*tokens, tbig, *tokens);
	print_big_token(*tbig);
}

void	sighandler(int signum)
{
	printf("\n");
	rl_on_new_line();
//	rl_replace_line("", 0);
	rl_redisplay();
	(void)signum;
}

// -----------------------------------------------My_shit---------------------------------------------------------------------


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

t_token	*ft_lstnew_upgr(char *token, char **r_fd_out, char **r_fd_in,  int flag_out, int flag_in, int h_flag, char **sep_arr, t_shell *shell)
{
	t_token	*node;

	node = malloc(sizeof(t_token));
	if (!node)
		return (0);
	node -> shell = shell; 
	node -> token = token;
	node -> redir_fd_out = r_fd_out;
	node -> redir_fd_in = r_fd_in;
	node -> redir_flag_out = flag_out;
	node -> redir_flag_in = flag_in;
	node -> here_doc_flag = h_flag;
	node -> sep_arr = sep_arr;
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

		if (token -> redir_flag_out + token -> redir_flag_outout + token -> redir_flag_in)
		{
			redirector_bi(token);
		}
		if (ft_strncmp("env", token -> token, 3) == 0)
			ret_value = bi_env(token -> shell);
		else if (ft_strncmp("pwd", token -> token, 3) == 0)
			ret_value = bi_pwd();
		else if (ft_strncmp("echo", token -> token, 4) == 0)
			ret_value = bi_echo(token);
		else if (ft_strncmp("cd", token -> token, 2) == 0)
			ret_value = bi_cd(token);
		else if (ft_strncmp("exit", token -> token, 4) == 0)
			ret_value = bi_exit(token);
		else if (ft_strncmp("export", token -> token, 6) == 0)
			ret_value = bi_export1(token -> shell);
		else if (ft_strncmp("unset", token -> token, 5) == 0)
			ret_value = bi_unset(token -> shell);
		else
			ret_value = 666;
		ret_value = global_error;
		return (ret_value);
}

// -----------------------------------------------My_shit-----------------------------------------------------------------------------

int	main(int argc, char **argv, char **env)
{
	t_token_small *tokens;
	t_token *token_final;
	t_shell *shell;
	tokens = NULL;
	token_final = NULL;
	global_error = 0;

	(void)argv;
	(void)argc;
	char *user_input;
	shell = malloc(sizeof(t_shell));
	init_env(&shell, env);
	while (1)
	{
		signal(SIGINT, sighandler);
		signal(SIGQUIT, SIG_IGN);
		user_input = readline("shell$ ");
		add_history(user_input);
		lexing(user_input, &tokens, &shell, &token_final);
		//free_tokens(&tokens);
		//free_big_tokens(&token_final);
		printf("%s\n", shell -> token -> token);
		exit(0);
		exec(shell);
		ft_lstclear_token(&shell -> token, (*del_token));
	}
	return (0);
}
