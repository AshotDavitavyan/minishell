#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <limits.h>

int main()
{
	char cwd[PATH_MAX];

    printf("%s\n", getcwd(cwd, sizeof(cwd)));
    if (chdir("../") == 0) {
       printf("%s\n", getcwd(cwd, sizeof(cwd)));
    } else {
        perror("chdir");
    }
    return 0;
}
