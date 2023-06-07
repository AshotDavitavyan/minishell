#include "minishell.h"

void	bi_env(int argc ,char **argv, char **env)
{
	if (argv || argc)
		;
	while (*env)
	{
		printf("%s\n", *env);
		env++;
	}
}

void	bi_pwd()
{
	char cwd[256];
	printf("%s\n", getcwd(cwd, sizeof(cwd)));
}



