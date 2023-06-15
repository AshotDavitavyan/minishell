#include "minishell.h"

void	f_error(void)
{
	perror("Error");
	exit(0);
}

char	*path_finder(char **env)
{
	int		i;
	char	*path;

	i = 0;
	path = "PATH=";
	while (env[i])
	{
		if (*env[i] == 'P')
		{
			if (!(ft_strncmp(env[i], path, 5)))
				path = env[i];
		}
		i++;
	}
	return (path);
}

void	fn_path(char **res_split, char *argv)
{
	int	i;

	i = 0;
	while (res_split[i])
	{
		res_split[i] = ft_strjoin(res_split[i], "/");
		res_split[i] = ft_strjoin(res_split[i], argv);
		i++;
	}
}

char	*true_path(char *argv, char **env)
{
	int				i;
	char			**res_split;
	char			**args;
	char			*path;

	if (access(argv, F_OK) == 0)
		return (argv);
	if (ft_strchr (argv, '/') != NULL)
		f_error();
	path = "PATH=";
	i = 0;
	args = ft_split(argv, ' ');
	path = path_finder(env);
	i = 0;
	res_split = ft_split(path, ':');
	fn_path(res_split, args[0]);
	while (res_split[i])
	{
		if (access(res_split[i], F_OK) == 0)
			return (res_split[i]);
		i++;
	}
	f_error();
	return NULL;
}

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

void	def_of_exec_a_file(char *token, char **argvv,char **file)
{
	char **argv;

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
	def_of_exec_a_file(token -> token, &argvv, &file);
	executing_one(flag, argvv, file, env);
}
