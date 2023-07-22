#include "../../includes/minishell.h"

void	f_error(char *str)
{
	ft_putstr_fd("minishell: /adfa", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
	global_error = 127;
	exit(global_error);
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

void	true_path_error(char *argv)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(argv, 2);
	ft_putstr_fd(": command not found\n", 2);
	global_error = 127;
	exit(127);
}

char	*true_path(char *argv, char **env)
{
	int				i;
	char			**res_split;
	//char			**args;
	char			*path;

	if (access(argv, F_OK) == 0)
		return (argv);
	if (ft_strchr (argv, '/'))
		f_error(argv);
	path = "PATH=";
	i = 0;
	path = path_finder(env);
	i 	= 0;
	res_split = ft_split(path, ':');
	fn_path(res_split, argv);
	while (res_split[i])
	{
		if (access(res_split[i], F_OK) == 0)
			return (res_split[i]);
		i++;
	}
	true_path_error(argv);
	return NULL;
}

void	here_d(t_token *token, int j)
{
	char *str;

	token -> here_fd = open("here_doc", O_RDWR | O_CREAT | O_TRUNC, 0664);
	if (token -> here_fd == -1)
		exit(1);
	while (1)
	{
		str = readline("> ");
		if (!str)
		{
			free(str);
			write(1, "\n", 1);
			break ;
		}
		if (ft_strcmp(str, token -> sep_arr[j]) == 0)
		{
			free(str);
			break;
		}
		write(token  -> here_fd, str, ft_strlen(str));
		write(token  -> here_fd, "\n", 1);
		free(str);
	}
	close(token -> here_fd);
}

void	here_doc_looper(t_token *token)
{
	int	j;

	j = 0;

	while (token -> here_doc_flag == 1 && token -> sep_arr[j])
	{
		here_d(token, j);
		j++;
	}
}

int	open_0(char *argv)
{
	int fd;
	fd = open(argv, O_RDWR, 0644);
	if (fd == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(argv, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		global_error = 1;
		exit(1);
	}
	return (fd);
}
// int	open_1(char *argv)
// {
// 	int fd  = -1;
// 	fd = open(argv, O_RDWR | O_TRUNC | O_CREAT, 0644);
// 	if (fd == -1)
// 	{
// 		global_error = 1;
// 		ft_putstr_fd("aga", 2);
// 		exit(1);
// 	}
// 	return (fd);
// }

void	openh_dup2(int fd)
{
	fd = open("here_doc", O_RDWR, 0644);
	dup2(fd, STDIN_FILENO);
}


void	executing_one(t_shell *shell)
{
	int f;
	int i;

	here_doc_looper(shell -> token);
	i = -1;
	f = fork();
	if (f == -1)
	{
		ft_putstr_fd("minishell: fork: Resource temporarily unavailable\n", 2);
		exit(1);
	}
	if (f == 0)
	{
		global_error = 0;
		if (shell -> token -> redir_flag_in == 1)
			dup2(open_0(shell -> token -> redir_fd_in[ft_strlen_2d_arr(shell -> token -> redir_fd_in) - 1]), STDIN_FILENO);
		if (shell -> token -> redir_flag_out == 1)
		{
			while (shell -> token -> redir_fd_out[++i + 1])
				open(shell -> token -> redir_fd_out[i], O_RDWR | O_TRUNC | O_CREAT, 0644);
			dup2(open(shell -> token -> redir_fd_out[ft_strlen_2d_arr(shell -> token -> redir_fd_out) - 1], O_RDWR | O_TRUNC | O_CREAT, 0644), STDOUT_FILENO);
		}
		if (shell -> token -> redir_flag_outout == 1)
		{
			while (shell -> token -> redir_fd_out[++i + 1])
				open(shell -> token -> redir_fd_out[i], O_RDWR | O_CREAT, 0644);
			dup2(open(shell -> token -> redir_fd_out[ft_strlen_2d_arr(shell -> token -> redir_fd_out) - 1], O_RDWR | O_CREAT | O_APPEND, 0644), STDOUT_FILENO);
		}
		if (shell -> token -> here_doc_flag == 1)
		{
			openh_dup2(shell -> token -> here_fd);
		}

		execve(true_path(shell -> token -> token[0], shell -> envex),shell -> token -> token, shell -> envex);
	}
}
