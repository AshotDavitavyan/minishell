#include "minishell.h"

int	redirects_checker(t_token *token)
{
	int	flag;

	if (ft_strchr(token -> token, '<') || ft_strchr(token -> token, '>'))
	{
		if (ft_strchr(token -> token, '<'))
			flag = 0;
		else if(ft_strchr(token -> token, '>'))
			flag = 1;
		else
			flag = -1;
	}
	else
		flag = -1;
	return (flag);
}

void	def_of_exec_a_file(char *token, char **argvv,char **file, int flag)
{
	char **argv;

	if(flag == -1)
	{
		*argvv = ft_split_V(token, ' ')[0];
		return ;
	}
	argv = ft_split_V(token, ' ');
	if (ft_strchr(argv[0], '>') || ft_strchr(argv[0], '<'))
	{
		*argvv = argv[1];
		*file = argv[0];
		(*file)++;
	}
	else
	{
		*argvv = argv[0];
		*file = argv[1];
		(*file)++;
	}
}

void	executing_one(int flag, char *argvv, char *file, char **env)
{
	int fd_file;
	char **args;
	int f;
	if (flag == 0)
		fd_file = open(file, O_RDWR, 0777);
	else if (flag == 1)
		fd_file = open(file, O_RDWR | O_TRUNC, 0777);
	f = fork();
	if (f == 0)
	{
		args = ft_split(argvv, ' ');
		if (flag == 0)
			dup2(fd_file, STDIN_FILENO);
		if (flag == 1)
			dup2(fd_file, STDOUT_FILENO);
		execve(true_path(argvv, env), args, env);
	}
}

void	exec_1(t_token *token, char **env)
{
	int flag;
	char *file;
	char *argvv;

	flag = redirects_checker(token);
	def_of_exec_a_file(token -> token, &argvv, &file, flag);
	executing_one(flag, argvv, file, env);
}
void	exec_n(t_token *token, char **env)
{
	t_variables variables;
	if (token -> token || env)
		;
	int i = 0;
	do_pipes(&variables, ft_lstsize(token));
	while (i < ft_lstsize(token) - 1)
		piping(&variables, i++);
}