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

void	executing_one(int flag, char *argvv, char *file, char **env)
{
	int fd_file;
	char **args;
	int f;
	if (flag == 0)
		fd_file = open(file, O_RDWR, 0777);
	else if (flag == 1)
		fd_file = open(file, O_RDWR | O_TRUNC | O_CREAT, 0777);
	// printf("cmd - %s\n", argvv);
	// printf("fd - %s\n", file);
	// printf("flag - %d\n", flag);
	// exit(0);
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

void	exec_1(t_shell *shell)
{
	if (shell -> token -> token || shell -> envex)
		;
	executing_one(shell -> token -> redirect_flag, shell -> token -> token, shell -> token -> redirect_fd[0], shell -> envex);
}

void	exec(t_shell *shell)
{
	if (!shell -> token -> next)
		exec_1(shell);
	else
		return;
}
