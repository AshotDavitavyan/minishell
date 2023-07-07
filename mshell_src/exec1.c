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
	//f_error();
	printf("%s: command not found\n", args[0]);
	exit(0);
	return NULL;
}

void	here_d(t_shell *shell, int j)
{
	char *str;

	shell -> token -> here_fd = open("here_doc", O_RDWR | O_CREAT | O_TRUNC, 0664);
	if (shell -> token -> here_fd == -1)
		exit(1);
	while (1)
	{
		str = readline("> ");
		if (!str || !*str)
		{
			free(str);
			write(1, "\n", 1);
			break ;
		}
		if (ft_strncmp(str, shell -> token -> sep_arr[j], ft_strlen(shell -> token -> token)) == 0)
		{
			free(str);
			break;
		}
		write(shell -> token  -> here_fd, str, ft_strlen(str));
		write(shell -> token  -> here_fd, "\n", 1);
		free(str);
	}
}

void	here_doc_looper(t_shell *shell)
{
	int	j;

	j = 0;

	while (shell -> token -> here_doc_flag == 1 && shell -> token -> sep_arr[j])
	{
		here_d(shell, j);
		j++;
	}
}

void	executing_one(char *argvv, char **file, char **env, t_shell *shell)
{
	char **args;
	int f;
	int i;

	i = -1;
	f = fork();
	if (f == 0)
	{
		args = ft_split(argvv, ' ');
		here_doc_looper(shell);
		if (shell -> token -> redirect_flag == 0)
			dup2(open(file[ft_strlen_2d_arr(file) - 1], O_RDWR, 0644), STDIN_FILENO);
		if (shell -> token -> here_doc_flag == 1)
		{
			shell -> token -> here_fd = open("here_doc", O_RDWR, 0644);
			dup2(shell -> token -> here_fd , STDIN_FILENO);
		}
		if (shell -> token -> redirect_flag == 1)
		{
			while (file[++i + 1])
				open(file[i], O_RDWR | O_TRUNC | O_CREAT, 0644);
			dup2(open(file[ft_strlen_2d_arr(file) - 1], O_RDWR | O_TRUNC | O_CREAT, 0644), STDOUT_FILENO);
		}
		execve(true_path(argvv, env), args, env);
	}
}

